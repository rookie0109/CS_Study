# Eigen
circleObs = Eigen::Map<const Eigen::Matrix<double, 3, -1, Eigen::ColMajor>>(
            circleObsVec.data(), 3, circleObsVec.size() / 3);
 这段代码创建了一个名为 `circleObs` 的 Eigen 矩阵，用于表示圆形障碍物。让我来解释一下：

- `Eigen::Map<const Eigen::Matrix<double, 3, -1, Eigen::ColMajor>>(circleObsVec.data(), 3, circleObsVec.size() / 3)`: 这是一个 Eigen 映射操作，用于将一个线性数组 `circleObsVec` 映射到一个大小为 3 行的矩阵中，矩阵的列数根据输入数组的大小自动确定。

  - `Eigen::Matrix<double, 3, -1, Eigen::ColMajor>`: 这部分指定了要创建的矩阵的类型。它是一个大小为 3 行、列数动态确定的双精度矩阵。`-1` 的意思是 Eigen 库会根据输入的数据自动确定列数。`Eigen::ColMajor` 表示矩阵的内存布局为列优先。
  - `circleObsVec.data()`: 这是指向 `circleObsVec` 线性数组的指针，它包含了圆形障碍物的数据。
  - `3, circleObsVec.size() / 3`: 这是矩阵的行数和列数。行数为 3，列数为 `circleObsVec` 数组的大小除以 3，因为每个障碍物由三个值表示其坐标。

所以，这行代码将一个线性数组解释为一个 3xN 的矩阵，其中 N 是障碍物的数量，每一列包含一个障碍物的 x、y、z 坐标。           