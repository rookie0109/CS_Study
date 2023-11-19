# 深蓝学院-motion-planning

## graph based search
小知识：
```cpp
// 将ptr指向的内存块的前num字节都设置为value的值
void *memset(void *ptr, int value, size_t num);
int arr[5];
// 使用 memset 将数组的所有元素初始化为零
memset(arr, 0, sizeof(arr));

#define inf 1<<20 // 可以作为等号右边的值，但不能直接<< 打印
#define inf (1<<20)  // 可以直接打印

// multimap将{key,value}当做元素，允许重复元素。multimap根据key的排序准则⾃动将元素排序，因此使⽤时只需考虑插⼊和删除操作即可。

// * inv_resolution 相较于 / resolution的好处：
// 1. 减少除法运算，提高计算效率，避免出现除零错误

#define _use_jps 1
#if _use_jps
    {
      /*code */
    }
#endif
```
### A*算法
与Dijse算法最本质的区别是增加了启发式函数。
核心思想：计算节点f = g + h,扩展当前节点的邻居，更改对应f,加入优先级队列中，不断从中抽取最小的f，直到队列为空或者找到目标点
本项目主要使用了均匀的栅格地图，通过读取点云，根据点云位置，判断是否是占据的索引
工程经验：路径生成运行斜向运动，改变启发函数h,使其更加接近h*（当前节点与目标点的真实成本），当h = h*时，算法具有最优解，但对于存在障碍物的环境而言，难以确定；**最重要的改进：打破对称性**减少不必要的扩展，通过给h增加系数，使其更加**接近起始点之间的直线**.

没有障碍物的闭式结果：

![image-20231024094935825](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-astar-h.png)

```cpp
// 节点的数据结构如下
struct GridNode
{     
    int id;        // 1--> open set, -1 --> closed set
    Eigen::Vector3d coord;  // 坐标
    Eigen::Vector3i dir;    // 扩展方向
    Eigen::Vector3i index;  // 索引
    double gScore, fScore;  // g 和 f
    GridNodePtr cameFrom;
    std::multimap<double, GridNodePtr>::iterator nodeMapIt;   // 没啥用
};
```

算法伪代码

![image-20231024100503098](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-astar-algorithm.png)

改进：

Weighted A*:引入权重 f = g + wh; 较小的权重会导致更慢但更精确的搜索，而较大的权重会导致更快但可能不太准确的搜索。

Anytime A*: 在搜索的过程中逐步改进路径，

其余还有ARAstar和Dstar

### Jump Point Search

会找到对称性，并打破。会根据事先的规则，

首先会对邻居进行剪枝（如果经过节点x到x的父节点的距离大于直接从父节点经过，则这些邻居没有必要进行扩展）

![image-20231024101056749](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-nieghbor_pruning.png)

核心是找到forced neighbor(应该有一个非常固定的检测方法)

跳点的概念：

- 如果点 y 是起点或目标点，则 y 是跳点
- 如果 y 有邻居且是强迫邻居则 y 是跳点， 从上文强迫邻居的定义来看 neighbor 是强迫邻居，current 是跳点，二者的关系是伴生的
- 如果 父节点到 y 是对角线移动，并且 y 经过水平或垂直方向移动可以到达跳点，则 y 是跳点。

算法流程：

1、openlist取一个权值最低的节点，然后开始搜索。（这些和A*是一样的） 

2、搜索时，先进行 直线搜索（4个方向，跳跃搜索），然后再 斜向搜索（4个方向，只搜索一步）。如果期间某个方向搜索到跳点或者碰到障碍（或边界），则当前方向完成搜索，若有搜到跳点就添加进openlist。 # 跳跃搜索是指沿直线方向一直搜下去（可能会搜到很多格），直到搜到跳点或者障碍（边界）。一开始从起点搜索，会有4个直线方向（上下左右），要是4个斜方向都前进了一步，此时直线方向会有8个。 

3、若斜方向没完成搜索，则斜方向前进一步，重复上述过程。 # 因为直线方向是跳跃式搜索，所以总是能完成搜索。

4、若所有方向已完成搜索，则认为当前节点搜索完毕，将当前节点移除于openlist，加入closelist。 

5、重复取openlist权值最低节点搜索，直到openlist为空或者找到终点。

**A* 与 JPS对比**：

**优点**:

1. **更高的搜索效率**：JPS算法能够剪枝不必要的搜索，跳过那些无法影响最终路径的节点。这可以大大减少搜索空间，加速搜索过程。
2. **减少节点扩展**：JPS算法减少了需要扩展的节点数，因此在大多数情况下，它需要更少的计算资源。
3. **全局最优解**：与A*算法一样，JPS算法能够找到全局最优路径。
4. **适用于大规模地图**：JPS算法在大规模地图上表现出色，因为它有效减少了搜索的复杂性。

**缺点**:

1. **难以实现**：JPS算法的实现比标准A*算法复杂，需要更多的编程工作。
2. **不适用于动态环境**：JPS算法通常用于静态地图，难以应对动态环境中的实时路径规划需求。
3. **不适用于所有场景**：JPS算法适用于特定类型的地图，特别是二维网格地图，但不适用于所有类型的地图。
4. **复杂的边界情况处理**：在处理地图的边界情况时，JPS算法可能需要额外的处理和特殊情况考虑。
5. JSP减少了在open_list的节点，但是增加了状态查询，如下图所示情况，不适合JSP

![image-20231031164645027](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-jsp-worse.png)

## sample-based path planning

### probabilistic road map

基本流程：首先在空间中随机撒点，之后将点进行连接，最后找到路径

![image-20231024105137543](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-PRM.png)

### RRT

![image-20231024105546309](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-RRT-algorithm.png)

优点：能够找到起始点之间的一条路径；比PRM更加具有目标导向

缺点：不是最优的解决方案；不够高效；在整个空间中进行采样

优化：使用KD-Tree储存节点，找最近的点；分别从起点和终点生长一个树

### RRT*

x_new生成之后，找到x_new一定范围内的节点（x1, .. ,xn）判断是否有节点以x_new为父节点的成本更低，如果是，更改其父节点

![image-20231031163712281](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-rrtstar.png)

### 其余改进：

kinodynamic-RRT* :使用满足动力学约束的曲线连接x_new与x_near

Anytime-RRT*：机器人运动的过程中不断地更新路径，在机器人执行当前路径时保持最优的树节点路径，更好的适应机器人运动过程中环境变化比较大的情况。

Informed RRT *：把采样的范围限制在一个椭圆里面

## kinodynamic path finding

为什么需要基于动力学的规划：

由粗到细的过程，轨迹只能在局部进行优化，不可行的路径对于非完整性系统而言没有用

![image-20231031170045362](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-kinodynamic-planning.png)

### State Lattice Planning

基本思想：所构建的图之间的边通过可行的运动轨迹连接。正向过程是控制空间离散；反向过程是状态空间离散

前向过程：固定输入u和时间间隔T，易于实现，但是没有任务导向，规划效率较低

反向过程：难以计算，较好的任务导向，更高的规划效率

状态空间模型：ds = As + Bu,其中A是幂零矩阵(nilpotent),在连续空间下，状态视为：

![image-20231031182657643](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-nilpotent.png)

在状态空间采样：使用Reed-shepp曲线

基于控制空间的采样曲线在初始速度方向较为密集，与初始方向比较相似

### Boundary Value problem

BVP是状态栅格采样规划的基础，没有通用的解决方案，同样演化出复杂的数值优化

对于最小化jerk而言一般选择五次多项式，min snap而言，选择七次多项式（泛函分析，内容可以证明的）

**[OBVP](https://blog.csdn.net/Amos98/article/details/123261802)**:

使用庞特里亚金最小值原理[minimum principle](https://zhuanlan.zhihu.com/p/483647239)

相关改进：

使用轨迹库：直接查询轨迹成本，而不是初始生成

启发式搜索：忽略障碍物或者忽略动力学

### hybrid A*

如果控制空间是连续的，那么通常不使用Lattice Graph。相反，如果控制空间是离散的，那么Lattice Graph是一种常见的方法，用于描述路径规划问题。

所谓hybrid就是将A*与lattice graph相关联

![img](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\v2-hybrid-Astar.jpg)

不同的启发函数的影响：

![image-20231031190931202](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-hybridAstar-heuristic.png)

在搜索的过程中，不断查找叶子节点直接到达终点的解，可以每N个节点找一次，随着树的增长，N越来越小

### kinodynamic RRT*

与RRT的主要区别：

- 采样过程：不再是在（x, y, z）三个状态中采样，而是在状态空间采样
- 邻近节点：使用OBVP将节点进行连接，邻近的概念不再是欧式距离，而是两个状态之间的成本（时间-能量最优）
- 选择父节点：选择最小代价的
- x_near由x_rand的后向可达集得到， rewire的过程中计算前向可达集和求解OBVP问题

给定一个当前的点，在cost范围内能到的所有状态，称为当前状态的前向可达集。以当前的点为终末状态，空间中的在cost范围内的所有能到达当前的点的所有状态，称为当前状态的反向可达集。**将前向可达集用kd-tree储存起来。**

前向可达集是所有可能到达时间的高维椭球体的并集

### minimum snap trajectory generation

为什么进行轨迹平滑：更有利于自主移动，速度或者更高阶的变量不能突变，机器人不应该停下来转向，节省能量

平滑轨迹的生成：

边界条件：起始点位置（姿态）

中间条件：中间点，曲线多阶连续可导

平滑标准：可以转化为最小输入

无人机姿态与加速度相关，min jerk 最小化角速度，对于视觉追踪较好，视角变化的更平滑；mini snap最小化推力变化，可以节省能量。 

mini snap trajectory generation 求解一个分段多项式，每一段的时间需要确定（每一段的时间需要从0开始，更加数值稳定）

[转换成QP问题](https://blog.csdn.net/u011341856/article/details/121861930)TODO:使用QP求解器进行求解

在优化变量的过程中对于高阶项可能造成系数较小，造成数值不稳定，可以将系数转化为速度，加速度等具有真实物理意义的变量。

![image-20231031210314231](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-coeff-to-derivatives.png)

将等式约束加到方程中会编程一个无约束问题，之后进行闭式求解。

对于含有不等式约束的QP问题，通常需要使用数值优化的方法进行求解（如内点法，逐步二次规划法）

对于规划出的轨迹可能与障碍物发生碰撞,逐步向其中添加中间点，使其不断接近A*规划的轨迹，或者增加软硬约束

![image-20231031211313863](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-iterative.png)

增加数值稳定性的方法：使用相对坐标轴，并对时间进行归一化

多段多项式之间的时间分配可以使用梯形速度获知使用迭代数值化分配的方法
贝塞尔曲线在路径规划中相对于多项式曲线有一些优点，尤其是在控制曲线的平滑性和计算效率方面：

多项式曲线可以处得到单个信号的最小化的最佳解决方案，但面对snap^2 + jerl^2不能满足

1. **平滑性**：贝塞尔曲线通常更加平滑，因为它是通过控制点之间的插值来生成的，这有助于减少路径中的急剧变化和抖动。平滑的路径更容易执行，尤其是对于自动驾驶车辆和机器人。
2. **控制点数量**：贝塞尔曲线通常需要更少的控制点来定义曲线。这可以减少路径规划问题的复杂性，减少计算量，同时也减小了路径描述的存储需求。
3. **自由度**：使用贝塞尔曲线时，可以更自由地控制控制点的位置，从而更容易实现特定的曲线形状。这使得贝塞尔曲线适用于需要特定形状路径的应用，如艺术绘图和动画。
4. **参数化控制**：贝塞尔曲线的参数化方法使得曲线的修改更为直观。通过移动或调整控制点，可以轻松地对路径进行修改，而不需要重新计算整个曲线。
5. **适用于多段路径**：贝塞尔曲线可以用于连接多段路径，使得路径规划系统可以更灵活地处理复杂环境中的路径连接问题。
6. **计算效率**：对于低阶的贝塞尔曲线，计算效率通常较高，因为它们可以使用递归算法来生成。

## planning tips

1. 几何关系

![image-20231024103743426](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-point-line-dis.png)

![image-20231024104115752](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-crossproduct.png)

![image-20231024104453612](F:\VscodeProjects\CS_Study\robotics\path_planning\图片\image-line-intersect.png)

直线与多边形是否相交

射线法：

选择一个起始点，可以是直线上的任意一点，通常是在多边形外部。从起始点沿着直线方向绘制一条射线，向多边形内部延伸。计算射线与多边形的交点数。如果射线与多边形的边界相交奇数次，那么直线与多边形相交；如果交点数为偶数，直线与多边形不相交。

