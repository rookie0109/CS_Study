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
工程经验：路径生成运行斜向运动，改变启发函数h,使其更加接近h*（当前节点与目标点的真实成本），当h = h*时，算法具有最优解，但对于存在障碍物的环境而言，难以确定；**最重要的改进：打破对称性**减少不必要的扩展，通过给h增加系数，使其更加接近起始点之间的直线
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

