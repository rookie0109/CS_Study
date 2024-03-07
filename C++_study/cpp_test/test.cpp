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

#include <iostream>
#include <Eigen/Dense>

int main() {
    // 定义矩阵维度
    int dim = 6;
    
    // 创建带状矩阵
    Eigen::MatrixXd band_matrix = Eigen::MatrixXd::Zero(dim, dim);

    // 设置对角线元素为4
    band_matrix.diagonal().setConstant(4);

    // 设置上下方各有一条1
    for (int i = 0; i < dim - 1; ++i) {
        band_matrix(i, i + 1) = 1;
        band_matrix(i + 1, i) = 1;
    }

    // 打印矩阵
    std::cout << "Band Matrix:" << std::endl;
    std::cout << band_matrix << std::endl;
    std::cout << "Band Matrix inv:" << std::endl;
    std::cout << band_matrix.inverse() << std::endl;

    return 0;
}
