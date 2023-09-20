# 深蓝学院

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
```