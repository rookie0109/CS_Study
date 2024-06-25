# Eigen
circleObs = Eigen::Map<const Eigen::Matrix<double, 3, -1, Eigen::ColMajor>>(
            circleObsVec.data(), 3, circleObsVec.size() / 3);
 这段代码创建了一个名为 `circleObs` 的 Eigen 矩阵，用于表示圆形障碍物。让我来解释一下：

- `Eigen::Map<const Eigen::Matrix<double, 3, -1, Eigen::ColMajor>>(circleObsVec.data(), 3, circleObsVec.size() / 3)`: 这是一个 Eigen 映射操作，用于将一个线性数组 `circleObsVec` 映射到一个大小为 3 行的矩阵中，矩阵的列数根据输入数组的大小自动确定。

  - `Eigen::Matrix<double, 3, -1, Eigen::ColMajor>`: 这部分指定了要创建的矩阵的类型。它是一个大小为 3 行、列数动态确定的双精度矩阵。`-1` 的意思是 Eigen 库会根据输入的数据自动确定列数。`Eigen::ColMajor` 表示矩阵的内存布局为列优先。
  - `circleObsVec.data()`: 这是指向 `circleObsVec` 线性数组的指针，它包含了圆形障碍物的数据。
  - `3, circleObsVec.size() / 3`: 这是矩阵的行数和列数。行数为 3，列数为 `circleObsVec` 数组的大小除以 3，因为每个障碍物由三个值表示其坐标。

所以，这行代码将一个线性数组解释为一个 3xN 的矩阵，其中 N 是障碍物的数量，每一列包含一个障碍物的 x、y、z 坐标。 

在 Eigen 中，稀疏矩阵的内部索引和外部索引分别指的是以下内容：

1. **内部索引（Inner Index）**：稀疏矩阵中非零元素的列索引，以及它们在数据数组中的位置索引。内部索引用于存储每个非零元素在矩阵数据数组中的位置，以便在稀疏矩阵的压缩存储中进行有效地访问和操作。

2. **外部索引（Outer Index）**：稀疏矩阵的行索引，以及每一行的第一个非零元素在内部索引数组中的起始位置。外部索引用于存储每一行的第一个非零元素在内部索引数组中的位置，以及该行的行号，这样可以快速定位每行的非零元素在稀疏矩阵数据数组中的位置。

通过使用内部索引和外部索引，Eigen 可以有效地表示稀疏矩阵，并提供高效的稀疏矩阵操作和计算。在稀疏矩阵的压缩存储格式中，内部索引和外部索引通常以紧凑的方式存储，以节省存储空间并提高访问效率。

```cpp
Eigen::SparseMatrix<double> &P;
// 将矩阵储存成上三角的形式，一般用于对称矩阵
P = P.triangularView<Eigen::Upper>();
P.makeCompressed();

// 这一行代码创建了一个 Eigen::Map 对象，用于将矩阵 P 的内部索引指针映射为一个 Eigen::VectorXi 类型的向量。
// P. innerIndexPtr() 返回内部索引的指针，P.nonZeros() 返回矩阵中非零元素的数量。
Eigen::Map<const Eigen::VectorXi> iIdxP(P.innerIndexPtr(), P.nonZeros());
// P.outerIndexPtr() 返回外部索引的指针，P.cols() + 1 表示外部索引的长度
Eigen::Map<const Eigen::VectorXi> oIdxP(P.outerIndexPtr(), P.cols() + 1);
// 这一行代码将内部索引向量转换为类型为 c_int 的 Eigen 矩阵。
Eigen::Matrix<c_int, -1, 1> innerIdxP = iIdxP.cast<c_int>();
Eigen::Matrix<c_int, -1, 1> outerIdxP = oIdxP.cast<c_int>();
// 将稀疏矩阵转换成稠密矩阵
Eigen::SparseMatrix<double> BB_sparse = BB.sparseView();
// 第0列开始选择Cx.row()行
A_T.middleCols(0, Cx.rows()) = Cx.transpose();
```


`Eigen::Spline`是Eigen库中的一个类，用于表示和计算样条曲线。样条曲线是一种平滑的曲线，通过一组给定的控制点和一些额外的条件（例如边界条件或导数）来定义。`Eigen::Spline`支持三种不同类型的样条曲线：

1. **Linear Spline（线性样条）：** 每两个控制点之间的曲线段都是线性的，曲线在各段之间可能有不连续的点。
   
2. **Cubic Spline（三次样条）：** 每两个控制点之间的曲线段都是三次多项式，曲线是连续可微的，通常用于实现平滑的插值曲线。

3. **Quintic Spline（五次样条）：** 每两个控制点之间的曲线段都是五次多项式，曲线是连续可微的，提供更高阶的平滑度。

`Eigen::Spline`类提供了一组方法来计算样条曲线上的点、导数或者积分值，以及计算曲线的一些性质，如弧长或曲率。此外，它还支持在给定参数处对样条曲线进行插值，从而得到新的点或导数值。

总的来说，`Eigen::Spline`是一个灵活且功能强大的工具，用于在数学和工程应用中处理和计算平滑曲线。