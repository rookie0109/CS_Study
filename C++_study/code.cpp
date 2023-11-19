#include <iostream>
#include <vector>

std::vector<int> dir = {-1, 0, 1, 0, -1};
int MaxIsland(std::vector<std::vector<int>>& islan) {
    if (island.empty()) return 0;
    int m = islan.size(), n = island[0].size();
    int result = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (island[i][j] == 1) {
                int count = 0;
                dfs(island, i, j, count);
                result = max(result, count);
            }
        }
    }
    return result;
    

}

void dfs (std::vector<std::vector<int>>& islan, int m, int n, int& count) {
    island[m][n] = 0;
    for (int i = 0; i < 4; ++i) {
        int x = m + dir[i];
        int y = n + dir[i + 1];
        if (x > 0 &&  x < island.size() &&
            y > 0 &&  y < island[0].size() && 
            islan[x][y] == 1) {
                ++count;
                dfs(island, x, y, count);
            }
    }
    return;


}