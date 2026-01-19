# FEC 静态表协议（FecTableId=1）

目的：把 FEC 的“可变项”变为“固定约定”，让发送端与接收端在数据面仅携带少量字段（`FecTableId/FecProfileId`）即可完成解码；不引入任何控制面广播。

关键约束：
- 本文档即“最终真相”：两端代码内置同一份静态表与生成规则。
- 未来若要扩展/替换，新增 `FecTableId` 并同步升级两端；当前版本只讨论 `FecTableId=1`。

安全备注：本协议不提供加密/鉴权；“提前约定表”只会增加解析门槛，不等价于安全。

---

## 0) FecTableId -> 静态表内容（V1：你单人推进时的“最终真相”）

目标：把“能固定的都固定”，让接收端解码路径尽量确定、便于做小系统求解与性能优化。

通用约束：
- GF(256) primitive polynomial：`0x11D`
- 符号大小（`SymbolBytes`）：`1200`
- 数据面每包携带 `FecTableId/FecProfileId`；`K/R/Scheme` 均从静态表查出。

### 0.1 FecTableId

- `FecTableId = 1`
- 含义：本节定义的所有 `FecProfileId`、矩阵生成规则、尾包兜底规则。
- 落地建议：两端代码里写死 `FecTableId=1`；日志打印一次，便于排查“表不一致”。

### 0.2 Scheme 定义

- `Scheme = 1`：`GF256_Cauchy_RS`（systematic；Cauchy 族，接近 MDS，missing<=R 时恢复成功率高）
- `Scheme = 2`：`XOR_Parity`（规则见 0.5；用于小尾块与小 K，解码快）

### 0.3 FecProfileId 静态表（FecTableId=1）

| FecProfileId | 名称 | Scheme | K | R | 系数/矩阵 |
|---:|---|---:|---:|---:|---|
| `0x10` | `RS_K32_R8_CAUCHY_V1` | 1 | 32 | 8 | Cauchy（见 0.4） |
| `0x11` | `RS_K16_R2_CAUCHY_V1` | 1 | 16 | 2 | Cauchy（见 0.4） |
| `0x20` | `XOR_K8_R1_V1` | 2 | 8 | 1 | 系数全为 1（见 0.5） |
| `0x21` | `XOR_K4_R1_V1` | 2 | 4 | 1 | 系数全为 1（见 0.5） |
| `0x22` | `XOR_K3_R1_V1` | 2 | 3 | 1 | 系数全为 1（见 0.5） |
| `0x23` | `XOR_K2_R1_V1` | 2 | 2 | 1 | 系数全为 1（见 0.5） |

约定：`FecProfileId=0` 表示“不参与按组 FEC”（通常同时令 `FecGroupId=0`）。

### 0.4 Cauchy RS 系数生成规则（适用于 `Scheme=1`）

对任意 `K,R`（本版本只用到 `32/8` 与 `16/2`）：

- `X[i] = i`，`i=0..K-1`
- `Y[j] = 0x80 + j`，`j=0..R-1`
- 系数（row-major）：

$$a[j,i] = (X[i] \oplus Y[j])^{-1}$$

其中 $\oplus$ 为 XOR（GF(256) 加法），$^{-1}$ 为 GF(256) 乘法逆元（primitive poly `0x11D`）。

这套取值保证 `X[i] != Y[j]` 恒成立（不会出现除以 0），实现简单、两端一致性强。

### 0.5 XOR 统一规则（适用于 `Scheme=2`）

当某组使用 `Scheme=2`（例如 `XOR_K8_R1_V1`）时：

- 该组的 parity 定义为：

$$p = s_0 \oplus s_1 \oplus \cdots \oplus s_{k-1}$$

其中 `k = K(Profile)`，每个 `s_i` 是 1200 字节符号；源包不足 1200 的尾片按 0 补齐参与 XOR。

接收端恢复：若且仅若缺失源包数 `missing==1`，用同样的 XOR 关系恢复缺失符号。

---

## 1) 系数到底是什么？
以 GF(256) 的 systematic FEC 为例：
- 一组有 `k` 个源包（source symbols），`r` 个冗余包（parity symbols）。
- 每个 parity 包对应一行系数：

对第 `j` 条 parity（`j=0..r-1`）：

- 系数向量：`a[j,0..k-1]`（每个系数 1 字节，属于 GF(256)）
- parity payload（逐字节）：

$$p_j = \sum_{i=0}^{k-1} a_{j,i} \cdot s_i$$

其中加法是 XOR，乘法是 GF(256) 乘（与你们目前 `0x11D` primitive poly 的实现一致即可）。

所以：除 `k/r` 外，还必须有一份“parity 系数矩阵” `A`，尺寸为 `r x k`。

---

## 2) 接收端求解步骤（尽量“小系统”，适用于 `Scheme=1` 的 RS profiles）

目的：避免做 32×32 的通用消元；只对缺失源包数 `m` 做 `m×m` 求解。

对同一 `(FrameId, FecGroupId, FecTableId=1, FecProfileId in {0x10,0x11})`：

1) 从 `(FecTableId,FecProfileId)` 查 `K,R`，统计缺失源包集合 `M = {i | i in [0..K-1] 且源包缺失}`，令 `m = |M|`。
2) 若 `m==0`：无需解码；若 `m>R`：本组在当前冗余下无法恢复。
3) 选择用于求解的 parity 行集合 `J`：
  - 优先使用已收到的 parity 中 `j` 最小的 `m` 行（即 `FecGroupIndex = K + j`，从小到大取）
  - 若 parity 不足 `m` 行，则继续等待（短 TTL）
4) 构造 RHS：对每个选中的 parity 行 `j`，先计算

$$b_j = p_j \oplus \bigoplus_{i \notin M} (a[j,i] \cdot s_i)$$

其中 `p_j` 是该 parity payload（1200B），`s_i` 是已收到的源 payload（不足 1200B 的尾片按 0 补齐参与计算）。

5) 构造系数子矩阵 `A'`：大小 `m×m`，`A'[row, col] = a[j_row, i_col]`，其中 `j_row ∈ J`、`i_col ∈ M`。
6) 求解 `A' * x = b` 得到缺失源 payload `x`（每个未知是 1200B 向量）。

说明：这 6 步是确定性的；唯一的“变化”来自缺失集合 `M`。由于 `m<=8`，GF(256) 上的 `m×m` 消元非常快，性能瓶颈主要在 1200B payload 的乘加与内存访问。

---

## 3) 数据包头字段使用约定（FecTableId=1）

当前最终约定：
- `FecTableId`：固定为 `1`。
- `FecProfileId`：在 `FecTableId=1` 内选择策略（见 0.3 表）。

因此：`K/R/Scheme` 不再从包头携带，而是由 `(FecTableId,FecProfileId)` 唯一确定。

---

## 5) 与现有视频 UDP 头的配合（你们当前文档）
你们现有头里：
- `PacketSeqNum`：SCReAM 专用
- `FrameId/FragmentIndex/TotalFragments`：组帧与传统 XOR 冗余

若引入按组 GF256 FEC：
- 仍可保留原字段不动。
- 再增加你们已经讨论过的：
  - `FecGroupId`（8，帧内序号；0 表示不参与）
  - `FecGroupIndex`（8）
  - `FecTableId`（8，当前固定为 1）
  - `FecProfileId`（8，查表得到 K/R/Scheme/系数规则）

---

## 6) 最小落地版本（建议）
如果你想“最快跑通且可调参”：
- 数据包头：每包携带 `FecGroupId/FecGroupIndex/FecTableId/FecProfileId`。
- 静态表：固定为 `FecTableId=1`（见 0.3）。

等跑通后再决定：是否要新增 `FecTableId=2` 来支持在线切换/自适应。
