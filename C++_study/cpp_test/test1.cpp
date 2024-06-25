// #include <iostream>

// int cuttingRope(int n) {
//   if (n < 4) {
//       return n - 1;
//   }
//   const int mod = 1e9 + 7;
//   auto qpow = [&](long long a, long long n) {
//       long long ans = 1;
//       for (; n; n >>= 1) {
//           if (n & 1) {
//               ans = ans * a % mod;
//           }
//           a = a * a % mod;
//       }
//       return (int) ans;
//   };
//   if (n % 3 == 0) {
//       return qpow(3, n / 3);
//   }
//   if (n % 3 == 1) {
//       return qpow(3, n / 3 - 1) * 4L % mod;
//   }
//   return qpow(3, n / 3) * 2 % mod;
// }

// int main() {
//   int n = 50;
//   std::cout << cuttingRope(n) << std::endl;
//   return 0;
// }

// #include <iostream>
// #include <vector>
// #include <algorithm>


// template <typename InputIt, typename OutputIt, typename ElemType, typename Comp> 
// OutputIt filter(InputIt first, InputIt last, OutputIt at, const ElemType& val, Comp pred) {
//     while ((first = std::find_if(first, last, [&](const auto& elem){ return pred(elem, val); })) != last) {
//         std::cout << "found value: " << *first << std::endl;
//         *at++ = *first++;
//     }
//     return at;
// }

// int main() {
//     std::vector<int> numbers = {1, 2, 3, 4, 5};
//     std::vector<int> result;

//     // 调用 filter 函数
//     filter(numbers.begin(), numbers.end(), std::back_inserter(result), 3, std::less<int>());
//     // back_inserter可以使用inserter()替代
//     // insterter(vac, vec.end())

//     // 打印输出结果
//     for (int num : result) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }


// class Stack
// {
// private:
//     /* data */
//     std::vector<std::string> stack_;
// public:
//     Stack(/* args */);
//     virtual ~Stack();
//     bool push(const std::string& elem);
//     bool pop(const std::string& elem);
//     bool peek(const std::string& elem);
//     bool empty();
//     bool fill();

    
    

// };

// Stack::Stack(/* args */)
// {
// }

// Stack::~Stack()
// {
// }

// #include <iostream>
// #include <vector>
// #include <Eigen/Dense>

// typedef Eigen::Matrix<double, 5, 1> State_RK;
//    State_RK Diff(const State_RK& state, 
//                        const Eigen::Vector2d &input) {
//     State_RK ds;
//     ds(0) = state(3) * std::cos(state(2));
//     ds(1) = state(3) * std::sin(state(2));
//     ds(2) = state(4);
//     ds(3) = input(0);
//     ds(4) = input(1);
//     return ds;
//   }

//   void Step(const State_RK& state, 
//                    const Eigen::Vector2d& input, 
//                    const double dt,
//                    State_RK &new_sta){
//     // Runge–Kutta
//     State_RK k1 = Diff(state, input);
//     State_RK k2 = Diff(state + k1 * dt / 2, input);
//     State_RK k3 = Diff(state + k2 * dt / 2, input);
//     State_RK k4 = Diff(state + k3 * dt, input);
//     new_sta = state + (k1 + k2 * 2 + k3 * 2 + k4) * dt / 6;
//   }

// int main() {
//     State_RK x_init, new_sta;
//     x_init << 0.0, 0.0, 3.14, 0.5, 1.5;
//     double dt = 0.25;
//     Eigen::Vector2d input = {0.0, 0};
//     Step(x_init, input, dt, new_sta);
//     // 打印矩阵
//     std::cout << "Band Matrix:" << std::endl;
//     std::cout << new_sta << std::endl;

//     return 0;
// }

// int main()
// {
//     // 定义 A 和 b
//     Eigen::Matrix<double, 3, 4> A;
//     Eigen::Matrix<double, 3, 1> b;

//     // 填充 A 和 b，这里仅作示例，实际情况根据需求填充
//     A << 1, 2, 3, 4,
//          5, 6, 7, 8,
//          9, 10, 11, 12;
//     b << 1, 2, 3;

//     // 计算 scale
//     Eigen::VectorXd scale = A.rowwise().norm();

//     // 定义 halves 和 work
//     Eigen::Matrix<double, 5, 3, Eigen::ColMajor> halves(5, 3);
//     // Eigen::VectorXd work((4 + 2) * (4 + 2) * (4 - 1) / 2 + 1 - 4);

//     // 填充 halves 的 topRows
//     halves.template topRows<4>() = (A.array().colwise() / scale.array()).transpose();

//     // 填充 halves 的 bottomRows
//     halves.template bottomRows<1>() = (-b.array() / scale.array()).transpose();

//     // 输出结果
//     std::cout << "scale:\n" << scale << std::endl;
    
//     std::cout << "Halves:\n" << halves << std::endl;
//     // std::cout << "Work:\n" << work << std::endl;

//     return 0;
// }

// int index_x = std::floor(next_pose.X / kMapResol + 0.5);
//       int index_y = std::floor(next_pose.Y / kMapResol + 0.5);

// void someFunction(int a) const {
//     std::cout << a << std::endl;
// }

// int main() {
//     // double a, b;
//     // while(std::cin >> a >> b) {
//     //   int index_x = std::floor(a / 1.0 + 0.5);
//     //   int index_y = std::floor(b / 1.0 + 0.5);

//     //   std::cout << index_x << "  " << index_y << std::endl;
//     // }
//     // return 0;
//     // int a = 10, b = 20;
//     // const int* p = &a;
//     // p = &b;
//     // std::cout << (*p) << std::endl;
//     someFunction(10);
//     return 0;

// }

// #include <iostream>
// #include <string>

// int main() {
//     std::string line;

//     std::getline(std::cin, line, '\n');

//     std::cout << "Read line: " << line << std::endl;

//     return 0;
// }

// 5
// 1627845600,client1,factorA,10
// 1627845605,client2,factorB,15
// 1627845610,client1,factorA,5
// 1627845610,client1,factorB,8
// 1627845620,client2,factorB,20
// 2
// factorA,5
// factorB,7
// #include <iostream>
// #include <string>
// #include <unordered_map>
// #include <unordered_set>

// #include <sstream>
// #include <vector>
// #include <map>

// struct Log
// {
//     int time_stamp;
//     std::string name;
//     std::string factor;
//     int dura;
// };

// int main() {
//     std::vector<Log> logs;
//     std::unordered_map<std::string, int> factor_hash;
//     int log_size, factor_size;
//     std::cin >> log_size;
//     std::cin.ignore();
//     std::string line, t;
//     // for (int i = 0; i < log_size; ++i) {
//     //     Log log;
//     //     std::getline(std::cin, line);
//     //     std::stringstream ss(line);
//     //     std::getline(ss, t, ',');
//     //     log.time_stamp = std::stoi(t);
//     //     std::getline(ss, log.name, ',');
//     //     std::getline(ss, log.factor, ',');
//     //     std::getline(ss, t, ',');
//     //     log.dura = std::stoi(t);
//     //     // ss << log.dura;
//     //     if (log.dura > 100 || log.dura < 0) {
//     //         log.dura = 0;
//     //     }
//     //     logs.push_back(log);
//     // }
//     // std::cin >> factor_size;
//     // std::cin.ignore();
//     // for (int i = 0; i < factor_size; ++i) {
//     //     std::getline(std::cin, line);
//     //     std::stringstream ss(line);
//     //     std::string factor_name;
//     //     std::getline(ss, factor_name, ',');
//     //     int factor;
//     //     ss >> factor;
//     //     // std::cin.ignore();  读取时长时不需要？
//     //     factor_hash[factor_name] = factor;
//     // }
//     for (int i = 0; i < log_size; ++i) {
//         Log log;
//         std::getline(std::cin, line);
//         std::stringstream ss(line);
//         std::getline(ss, t, ',');
//         log.time_stamp = std::stoi(t);
//         std::getline(ss, log.name, ',');
//         std::getline(ss, log.factor, ',');
//         // std::getline(ss, t, ',');
//         // log.dura = std::stoi(t);
//         // std::cout << ss << std::endl;
//         ss >> log.dura;
//         if (log.dura > 100 || log.dura < 0) {
//             log.dura = 0;
//         }
//         logs.push_back(log);
//     }
//     std::cin >> factor_size;
//     std::cin.ignore();
//     for (int i = 0; i < factor_size; ++i) {
//         std::getline(std::cin, line);
//         std::stringstream ss(line);
//         std::string factor_name;
//         std::getline(ss, factor_name, ',');
//         int factor;
//         ss >> factor; // 修正这里的错误
//         factor_hash[factor_name] = factor; // 修正这里的错误
//     }


// // 打印 logs
//     std::cout << "Logs:" << std::endl;
//     for (const auto& log : logs) {
//         std::cout << "Timestamp: " << log.time_stamp << ", Name: " << log.name << ", Factor: " << log.factor << ", Duration: " << log.dura << std::endl;
//     }

//     // 打印 factor_hash
//     std::cout << "Factor Hash:" << std::endl;
//     for (const auto& pair : factor_hash) {
//         std::cout << "Factor Name: " << pair.first << ", Factor Price: " << pair.second << std::endl;
//     }
//     std::map<std::string, int> client_cost;
//     std::unordered_map<std::string, std::unordered_set<int>> client_time;
//     for (auto &log : logs) {
//         if (client_cost.find(log.name) == client_cost.end()) {
//             client_cost[log.name] = factor_hash[log.factor] * log.dura;
//             client_time[log.name].insert(log.time_stamp);
//         } else {
//             if (client_time[log.name].find(log.time_stamp) == client_time[log.name].end()) {
//                 client_cost[log.name] += factor_hash[log.factor] * log.dura;
//                 client_time[log.name].insert(log.time_stamp);
//             }
//         }
//     }
//     // std::map<std::string, int> client_cost;
//     // std::unordered_map<std::string, std::unordered_set<int>> client_time;
//     // for (auto &log : logs) {
//     //     if (client_cost.find(log.name) == client_cost.end()) {
//     //         client_cost[log.name] = factor_hash[log.factor] * log.dura; // 修正这里的错误
//     //         client_time[log.name].insert(log.time_stamp);
//     //     } else {
//     //         if (client_time[log.name].find(log.time_stamp) == client_time[log.name].end()) {
//     //             client_cost[log.name] += factor_hash[log.factor] * log.dura; // 修正这里的错误
//     //             client_time[log.name].insert(log.time_stamp);
//     //         }
//     //     }
//     // }

//     for (auto & c : client_cost) {
//         std::cout << c.first << ',' << c.second << std::endl;
//     }



//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <vector>
// #include <queue>
// #include <set>
// #include <algorithm>

// int main() {
//     int size;
//     std::cin >> size;
//     std::cin.ignore();
//     std::vector<std::vector<int>> mat(size, std::vector<int>(size, 0));
//     for (int i = 0; i < size; ++i) {
//         for (int j = 0; j < size; ++j) {
//             int sim;
//             std::cin >> sim;
//             if (sim > 0) {
//                 mat[i][j] = sim;
//             }
//         }
//         std::cin.ignore();
//     }
//     // std::cout << 1 << std::endl;
//     std::vector<bool> visited(size, false);
//     std::set<int, std::greater<int>> ans;
//     for (int i = 0; i < size; ++i) {
//         if (visited[i]) continue;
//         std::queue<std::pair<int, int>> index_q;
//         for (int j = 0; j < size; ++j) {
//             if (mat[i][j] > 0 && !visited[j]) {
//                 index_q.push({i, j});
//             }
//         }
//         visited[i] = true;
//         int sum = 0;
//         while (!index_q.empty())
//         {
//             int n = index_q.size();
//             for (int k = 0; k < n; ++k) {
//                 auto target = index_q.front();
//                 visited[target.second] = true;
//                 sum += mat[target.first][target.second];
//                 for (int l = 0; l < size; ++l) {
//                     if (mat[target.second][l] > 0 && !visited[l]) {
//                         index_q.push({target.second, l});
//                     }
//                 }
//                 index_q.pop();
//             }
//         }
//         ans.insert(sum);
        
//     }

//     for (auto &val : ans) {
//         std::cout << val << " ";
//     }
//     std::cout << std::endl;



//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <vector>
// #include <queue>
// #include <stack>
// #include <set>
// #include <algorithm>
// #include <sstream>

// int main() {
//     int size;
//     std::cin >> size;
//     std::cin.ignore();
//     std::vector<std::vector<int>> region(size, std::vector<int>(size, 0));
//     for (int i = 0; i < size; ++i) {
//         for (int j = 0; j < size; ++j) {
//             int sim;
//             std::cin >> sim;
//             if (sim > 0) {
//                 region[i][j] = sim;
//             }
//         }
//         std::cin.ignore();
//     }

//     int id;
//     std::string temp;
//     std::getline(std::cin, temp);
//     std::vector<int> error_ids;
//     std::stringstream ss(temp);
//     while (ss >> id)
//     {
//         error_ids.push_back(id - 1);
//     }
//     for (int i = 0; i < error_ids.size(); ++i) {
//         std::cout  << error_ids[i] << std::endl;
//     }
    
//     id = -1;
//     int ans;
//     for (int i = 0; i < error_ids.size(); ++i) {
//         std::vector<bool> visited(size, false);
//         std::stack<int> dfs_stk;
//         dfs_stk.push(error_ids[i]);
//         int count = 0;

//         while (!dfs_stk.empty()) {
//             int t = dfs_stk.top();
//             visited[t] = true;
//             dfs_stk.pop();

//             count++;
//             for (int j = 0; j < size; ++j) {
//                 if (region[t][j] > 0 && t != j && !visited[j]) {
//                     dfs_stk.push(j);

//                 }
//             }
//         }

//         if (count > id) {
//             ans = error_ids[i] + 1;
//         }
        
//     }
//     std::cout << ans << std::endl;



//     return 0;
// }


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <Eigen/Sparse>
#include <Eigen/Dense>
int main() {

  // constexpr int nums_of_variables = 12;
  // std::string filename = "test.txt";
  // std::ofstream fout(filename);
  // if (!fout) {
  //   std::cout << "Error opening file: " << filename << std::endl;
  //   return 1;
  // }

  // std::string symbol1 = "w1 + w2 + w3";
  // std::string symbol2 = "-2w1 - w2";
  // std::string symbol3 = "5w1 + 2w2 + w3";
  // std::string symbol4 = "w1";
  // std::string symbol5 = "-4w1 - w2";
  // std::string symbol6 = "6w1 + 2w2 + w3";
  
  // std::vector<std::vector<std::string>> columns(
  //                       nums_of_variables, 
  //                       std::vector<std::string>(nums_of_variables, "0"));
  // int col_num = 0;
  // for (int col = 0; col < 2; ++col) {
  //   columns[col][col] = symbol1;
  //   ++col_num;
  // }

  // for (int col = 2; col < 4; ++col) {
  //   columns[col - 2][col] = symbol2;
  //   columns[col][col] = symbol3;
  //   ++col_num;
  // }

  // int second_point_from_last_index = nums_of_variables / 2 - 2;

  // for (int point_index = 2; point_index < second_point_from_last_index; 
  //     ++point_index) {
      
  //   int col_index = point_index * 2;
  //   for (int col = 0; col < 2; ++col) {
  //     col_index += col;
  //     columns[col_index - 4][col_index] = symbol4;
  //     columns[col_index - 2][col_index] = symbol5;
  //     columns[col_index][col_index] = symbol6;
  //     ++col_num;
  //   }
  // }

  // int second_point_col_from_last_col = nums_of_variables - 4;
  // int last_point_col_from_last_col = nums_of_variables - 2;
  // for (int col = second_point_col_from_last_col; 
  //     col < last_point_col_from_last_col; ++col) {
  //   columns[col -4][col] = symbol4;
  //   columns[col -2][col] = symbol5;
  //   columns[col][col] = symbol3;
  //   ++col_num;

  // }
  // for (int col = last_point_col_from_last_col; col < nums_of_variables; ++col) {
  //   columns[col - 4][col] = symbol4;
  //   columns[col - 2][col] = symbol2;
  //   columns[col][col] = symbol1;
  //   ++col_num;
  // }
  // // 将columns存入文件
  // const int width = 20;
  // for (int i = 0; i < nums_of_variables; ++i) {
  //   for (int j = 0; j < nums_of_variables; ++j) {
  //      fout << std::setw(width) << columns[i][j] << " ";
  //   }
  //   fout << std::endl;
  // }
  // fout.close();

    double weight_pos_deviation = 1.0;    // w1 平滑代价
  double weight_path_length = 1.0;      // w2 路径长度代价
  double weight_ref_deviation = 1.0;    // w3 参考线偏差代价

  double cost_weight1 = weight_pos_deviation + 
                        weight_path_length + weight_ref_deviation;
  double cost_weight2 = -2.0 * weight_pos_deviation - 
                        weight_path_length;
  double cost_weight3 = 5.0 * weight_pos_deviation + 
                        2.0 * weight_path_length + weight_ref_deviation;
  double cost_weight4 = weight_pos_deviation;
  double cost_weight5 = -4.0 * weight_pos_deviation - 
                        weight_path_length;
  double cost_weight6 = 6.0 * weight_pos_deviation + 
                        2.0 * weight_path_length + weight_ref_deviation;
  const int num_of_variable = 22;
  Eigen::SparseMatrix<double> qp_Q;
  qp_Q.resize(num_of_variable, num_of_variable);
  // Eigen::VectorXd qp_f;
  // qp_f.resize(num_of_variable);
  // Eigen::SparseMatrix<double> qp_A;
  // qp_A.resize(num_of_variable, num_of_variable);
  // Eigen::VectorXd qp_l;
  // qp_l.resize(num_of_variable);
  // Eigen::VectorXd qp_u;
  // qp_u.resize(num_of_variable);
  // Eigen::VectorXd qp_primal_solution;
  // qp_primal_solution.resize(num_of_variable);


  for (int col = 0; col < 2; ++col) {
    qp_Q.coeffRef(col, col) = cost_weight1;
    std::cout << "(" << col << ", " << col << ") " << std::endl;
  }

  for (int col = 2; col < 4; ++col) {
    qp_Q.coeffRef(col - 2, col) = cost_weight2;
    qp_Q.coeffRef(col, col) = cost_weight3;
    std::cout << "(" << col - 2 << ", " << col << ") " << std::endl;
    std::cout << "(" << col << ", " << col << ") " << std::endl;

  }

  int second_point_from_last_index = num_of_variable / 2 - 2;
  for (int point_index = 2; point_index < second_point_from_last_index; 
      ++point_index) {
    
    int col_index = 2 * point_index;
    for (int col = 0; col < 2; ++col) {
      col_index += col;
      qp_Q.coeffRef(col_index - 4, col_index) = cost_weight4;
      qp_Q.coeffRef(col_index - 2, col_index) = cost_weight5;
      qp_Q.coeffRef(col, col) = cost_weight6;
      std::cout << "(" << col - 4 << ", " << col << ") " << std::endl;

    }
  }

  int second_point_col_from_last_col = num_of_variable - 4;
  int last_point_col_from_last_col = num_of_variable - 2;
  for (int col = second_point_col_from_last_col; 
      col < last_point_col_from_last_col; ++col) {
   
    qp_Q.coeffRef(col - 4, col) = cost_weight4;
    qp_Q.coeffRef(col - 2, col) = cost_weight5;
    qp_Q.coeffRef(col, col) = cost_weight3;
  }

  for (int col = last_point_col_from_last_col; col < num_of_variable; ++col) {
    qp_Q.coeffRef(col - 4, col) = cost_weight4;
    qp_Q.coeffRef(col - 2, col) = cost_weight2;
    qp_Q.coeffRef(col, col) = cost_weight1;
  }
  return 0;
}