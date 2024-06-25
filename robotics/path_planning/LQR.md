线性二次调节器（LQR）是一种在控制理论中用于设计最优控制器的方法。LQR算法的目的是通过优化某个性能指标，找到一个反馈增益矩阵 \( K \)，使得系统的性能最优。

在LQR问题中，考虑线性时不变系统的状态方程：

\[ \dot{x}(t) = Ax(t) + Bu(t) \]

LQR控制器的目标是找到一个控制输入 \( u(t) \)，使得以下成本函数最小化：

\[ J = \int_0^\infty (x(t)^TQx(t) + u(t)^TRu(t)) \, dt \]

其中，\( Q \) 和 \( R \) 是权重矩阵，通常是对称正定矩阵。

### 推导反馈增益矩阵 \( K \)

1. **代入控制律**：假设我们使用状态反馈控制律 \( u(t) = -Kx(t) \)，其中 \( K \) 是我们要确定的反馈增益矩阵。代入状态方程得到闭环系统的状态方程：

\[ \dot{x}(t) = (A - BK)x(t) \]

2. **李雅普诺夫方程**：为了保证系统的稳定性，我们引入李雅普诺夫方程。我们假设存在一个对称正定矩阵 \( P \)，使得李雅普诺夫方程成立：

\[ (A - BK)^TP + P(A - BK) = -Q \]

3. **最优控制问题的哈密顿-雅可比-贝尔曼（HJB）方程**：我们利用最优控制理论中的HJB方程来推导最优 \( K \)。最优值函数 \( V(x) = x^TPx \) 满足以下HJB方程：

\[ 0 = \min_u \left\{ x^TQx + u^TRu + \frac{\partial V}{\partial x} (Ax + Bu) \right\} \]

代入 \( V(x) = x^TPx \)，我们有：

\[ \frac{\partial V}{\partial x} = 2x^TP \]

所以HJB方程变为：

\[ 0 = x^TQx + u^TRu + (2x^TP)(Ax + Bu) \]

4. **确定最优控制输入**：为了最小化HJB方程，我们对 \( u \) 求导，并令其等于零：

\[ \frac{\partial}{\partial u} \left( x^TQx + u^TRu + 2x^TP(Ax + Bu) \right) = 0 \]

\[ 2u^TR + 2x^TPB = 0 \]

解得最优控制输入：

\[ u = -R^{-1}B^TPx \]

这表明最优控制输入 \( u(t) = -Kx(t) \) 中的反馈增益矩阵 \( K \) 为：

\[ K = R^{-1}B^TP \]

5. **Riccati方程**：为了求得矩阵 \( P \)，我们需要解一个代数Riccati方程：

\[ A^TP + PA - PBR^{-1}B^TP + Q = 0 \]

通过求解这个方程，我们可以得到矩阵 \( P \)，进而计算反馈增益矩阵 \( K \)。

### 总结

反馈增益矩阵 \( K = R^{-1}B^TP \) 是通过以下步骤得到的：

1. 假设状态反馈控制律 \( u = -Kx \) 并代入状态方程。
2. 使用李雅普诺夫方程确保系统稳定性。
3. 利用最优控制理论中的HJB方程推导最优值函数。
4. 通过最小化HJB方程，确定最优控制输入 \( u \)。
5. 解代数Riccati方程得到矩阵 \( P \)，从而计算反馈增益矩阵 \( K \)。

这就是LQR算法中如何推导出反馈增益矩阵 \( K \) 的过程。

https://zgh551.github.io/2020/02/20/%E5%9F%BA%E7%A1%80%E7%AE%97%E6%B3%95-LQR-%E7%A6%BB%E6%95%A3%E6%97%B6%E9%97%B4%E6%9C%89%E9%99%90%E8%BE%B9%E7%95%8C/

iLQR（Iterative Linear Quadratic Regulator）和 DDP（Differential Dynamic Programming）是两种用于非线性控制和轨迹优化的算法，它们都利用了动态规划的思想，但在具体实现和计算方法上有所不同。

### 主要区别

1. **二次近似方法**：
   - **iLQR**：iLQR 只对代价函数进行二次近似，对系统动态方程进行一阶线性近似。这意味着 iLQR 在每次迭代中线性化系统动态方程，然后在这个线性化的系统上求解 LQR 问题。
   - **DDP**：DDP 同时对代价函数和系统动态方程都进行二次近似。这意味着 DDP 在每次迭代中不仅线性化系统动态方程，还对其进行二次近似，从而在动态方程的二次近似上求解 LQR 问题。

2. **计算量和收敛速度**：
   - **iLQR**：由于只对系统动态方程进行一阶线性近似，iLQR 的计算量相对较小，适合处理较大规模的控制问题。收敛速度通常较快，但在处理高度非线性系统时，可能不如 DDP 精确。
   - **DDP**：由于同时对系统动态方程进行一阶和二阶近似，DDP 的计算量较大，但在处理高度非线性系统时具有更高的精度。收敛速度可能会比 iLQR 慢，但结果更加准确。

3. **反馈增益矩阵计算**：
   - **iLQR**：在反向传播过程中，只计算一阶导数和二阶代价函数的 Hessian 矩阵，并通过求解 LQR 问题得到反馈增益矩阵。
   - **DDP**：在反向传播过程中，计算一阶导数、二阶导数和二阶混合导数，并通过求解 LQR 问题得到反馈增益矩阵。由于考虑了动态方程的二阶导数，DDP 的反馈增益矩阵能够更好地反映系统的非线性特性。

4. **数值稳定性和正定性**：
   - **iLQR**：由于只进行一阶线性近似，iLQR 在数值计算上相对简单，但可能会遇到不稳定或非正定的情况，需要进行正则化处理。
   - **DDP**：由于考虑了系统动态的二阶近似，DDP 通常具有更好的数值稳定性，但计算过程复杂度较高，需要更高的计算资源。

### 举例说明

假设我们有一个非线性动态系统：
\[ \mathbf{x}_{t+1} = f(\mathbf{x}_t, \mathbf{u}_t) \]
并且我们要最小化以下成本函数：
\[ J = \sum_{t=0}^{T-1} l(\mathbf{x}_t, \mathbf{u}_t) + l_f(\mathbf{x}_T) \]

#### iLQR 方法

1. **线性化动态方程**：
   \[ \mathbf{x}_{t+1} \approx \mathbf{A}_t \mathbf{x}_t + \mathbf{B}_t \mathbf{u}_t + \mathbf{c}_t \]
   其中，\(\mathbf{A}_t\) 和 \(\mathbf{B}_t\) 是在当前轨迹上计算的 Jacobian 矩阵。

2. **二次近似成本函数**：
   \[ \delta J \approx \sum_{t=0}^{T-1} \left[ \begin{pmatrix} \delta \mathbf{x}_t \\ \delta \mathbf{u}_t \end{pmatrix}^T \begin{pmatrix} \mathbf{Q}_t & \mathbf{S}_t \\ \mathbf{S}_t^T & \mathbf{R}_t \end{pmatrix} \begin{pmatrix} \delta \mathbf{x}_t \\ \delta \mathbf{u}_t \end{pmatrix} + \begin{pmatrix} \mathbf{q}_t \\ \mathbf{r}_t \end{pmatrix}^T \begin{pmatrix} \delta \mathbf{x}_t \\ \delta \mathbf{u}_t \end{pmatrix} \right] + \text{constant} \]

3. **反向传播计算反馈增益矩阵**：
   \[ \mathbf{K}_t = -(\mathbf{R}_t + \mathbf{B}_t^T \mathbf{P}_{t+1} \mathbf{B}_t)^{-1} (\mathbf{S}_t + \mathbf{B}_t^T \mathbf{P}_{t+1} \mathbf{A}_t) \]

#### DDP 方法

1. **线性化和二次近似动态方程**：
   \[ \mathbf{x}_{t+1} \approx \mathbf{A}_t \mathbf{x}_t + \mathbf{B}_t \mathbf{u}_t + \mathbf{c}_t + \frac{1}{2} \begin{pmatrix} \mathbf{x}_t \\ \mathbf{u}_t \end{pmatrix}^T \begin{pmatrix} \mathbf{A}_{xx} & \mathbf{A}_{xu} \\ \mathbf{A}_{ux} & \mathbf{A}_{uu} \end{pmatrix} \begin{pmatrix} \mathbf{x}_t \\ \mathbf{u}_t \end{pmatrix} \]

2. **二次近似成本函数**：
   \[ \delta J \approx \sum_{t=0}^{T-1} \left[ \begin{pmatrix} \delta \mathbf{x}_t \\ \delta \mathbf{u}_t \end{pmatrix}^T \begin{pmatrix} \mathbf{Q}_t & \mathbf{S}_t \\ \mathbf{S}_t^T & \mathbf{R}_t \end{pmatrix} \begin{pmatrix} \delta \mathbf{x}_t \\ \delta \mathbf{u}_t \end{pmatrix} + \begin{pmatrix} \mathbf{q}_t \\ \mathbf{r}_t \end{pmatrix}^T \begin{pmatrix} \delta \mathbf{x}_t \\ \delta \mathbf{u}_t \end{pmatrix} \right] + \text{constant} \]

3. **反向传播计算反馈增益矩阵**：
   \[ \mathbf{K}_t = -(\mathbf{R}_t + \mathbf{B}_t^T \mathbf{P}_{t+1} \mathbf{B}_t + \mathbf{H}_{\mathbf{u}\mathbf{u}})^{-1} (\mathbf{S}_t + \mathbf{B}_t^T \mathbf{P}_{t+1} \mathbf{A}_t + \mathbf{H}_{\mathbf{u}\mathbf{x}}) \]

### 总结

- **iLQR** 是一种更简单、更快的算法，适用于大规模、较低非线性的控制问题。
- **DDP** 是一种计算量更大、但精度更高的算法，适用于高度非线性的控制问题。

选择哪种算法通常取决于具体应用的需求和计算资源的限制。