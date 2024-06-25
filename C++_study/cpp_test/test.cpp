// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <sstream>

// int main() {
//     std::string line;
//     while (std::getline(std::cin, line)) {
//         std::stringstream ss(line);
//         std::vector<std::string> words;
//         std::string word;
//         // while (std::getline(ss, word, ',')) {
//         //     words.push_back(word);
//         // }
//         while (ss >> word) {
//             words.push_back(word);
//             std::cout << word << std::endl;
//         }
//         std::cout << "words size:" << words.size() << std::endl;
//         std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
//             return a < b;
//         });
//         for (size_t i = 0; i < words.size(); ++i) {
//             std::cout << words[i];
//             if (i != words.size() - 1) {
//                 std::cout << ",";
//             }
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }
// #include <iostream>
// #include <vector>
// #include <string>
// #include <sstream>

// template <typename T>
// void process(T& val) {
//     std::cout << T << std::endl;
// }

// template <typename T>
// void process(T&& val) {
//     std::cout << T << std::endl;
// }


// using namespace std;

// int countBalancedSubsequences(const string& s) {
//     int n = s.size();
//     vector<vector<int>> dp(n + 1, vector<int>(2, 0)); // dp[i][j]表示以s[i-1]结尾的平衡串的数量，j表示当前结尾字符是第几个字符
//     int count[26][2] = {0}; // count[i][j]表示以字符i结尾的平衡串数量，j表示当前结尾字符是第几个字符

//     for (int i = 1; i <= n; ++i) {
//         int c = s[i - 1] - 'a';
//         dp[i][0] = dp[i - 1][0]; // 不选择当前字符，平衡串数量不变
//         dp[i][1] = dp[i - 1][1]; // 不选择当前字符，平衡串数量不变
//         // 选择当前字符，统计平衡串数量
//         dp[i][1 - c % 2] = (dp[i][1 - c % 2] + dp[i - 1][c % 2] + 1) % 1000000007;
//         // 更新以当前字符结尾的平衡串数量
//         count[c][i % 2] = (count[c][i % 2] + dp[i][c % 2]) % 1000000007;
//     }

//     int result = 0;
//     for (int i = 0; i < 26; ++i) {
//         result = (result + count[i][n % 2]) % 1000000007;
//     }
//     return result;
// }

// int main() {

//     int a = 10;
//     process(a);
//     process(std::forward<string>("123"));


//     // int i;
//     // std::cin >>i; 
//     // std::cin.ignore();

//     // string line;
//     // std::getline(std::cin, line);
//     // std::stringstream ss(line);
//     // for (int j = 0; j < i; ++j) {
//     //     std::string num;
//     //     std::getline(ss, num, ' ');
//     //     cout << num << endl;
//     // }
//     // int result = countBalancedSubsequences(s);
//     // cout << result << endl;
//     return 0;
// }


// #include <iostream>
// #include <utility>

// // 函数 print 接受一个左值引用参数和一个右值引用参数，并打印它们的值
// void print(int& lvalue, int&& rvalue) {
//     std::cout << "Left value: " << lvalue << std::endl;
//     std::cout << "Right value: " << rvalue << std::endl;
// }

// // 函数 process 接受一个左值引用参数和一个右值引用参数，并将它们转发给 print 函数
// // 左值引用不需要完美转发，右值引用才需要
// template<typename LRef, typename RRef>
// void process(LRef&& lref, RRef&& rref) {
//     print(std::forward<LRef>(lref), std::forward<RRef>(rref));
// }

// int main() {
//     int x = 42;
//     process(x, 100);  // 调用 process，传递左值引用和右值引用
//     return 0;
// }

// #include <iostream>

// class BaseTest
// {
// private:
//     /* data */
// public:
//     // BaseTest(/* args */);
//     ~BaseTest() {};
//     virtual void process(int a) noexcept = 0;
// };

// class Test : public BaseTest
// {
// private:
//     /* data */
// public:
//     // Test(/* args */);
//     ~Test() {};
//     void process(int a) noexcept override {
//         std::cout << a << std::endl;
//     }
// };

// int main() {

//     BaseTest* ss = new Test();
//     ss->process(10);
//     delete ss;
//     return 0;
// }

#include <iostream>
// osqp-eigen
#include "OsqpEigen/OsqpEigen.h"
// eigen
#include <Eigen/Dense>
 
using namespace std;
Eigen::SparseMatrix<double> hessian;
Eigen::VectorXd gradient;
Eigen::SparseMatrix<double> linearMatrix;
Eigen::VectorXd lowerBound;
Eigen::VectorXd upperBound;
 
int initMat(OsqpEigen::Solver& solver)
{
    unsigned int numOfVar = 3;
    unsigned int numOfCons = 4;
    solver.data()->setNumberOfVariables(numOfVar);
    solver.data()->setNumberOfConstraints(numOfCons);
 
    hessian.resize(numOfVar, numOfVar);
    gradient.resize(numOfVar);
    linearMatrix.resize(numOfCons, numOfVar);
    lowerBound.resize(numOfCons);
    upperBound.resize(numOfCons);
 
 
    hessian.insert(0, 0) = 1;
    hessian.insert(0, 1) = -1;
    hessian.insert(0, 2) = 1;
    // hessian.insert(1, 0) = -1;
    hessian.insert(1, 1) = 2;
    hessian.insert(1, 2) = -2;
    // hessian.insert(2, 0) = 1;
    // hessian.insert(2, 1) = -2;
    hessian.insert(2, 2) = 4;
   //cout << "hessian" << hessian << endl;
   /* hessian << 1, -1, 1,
              -1, 2, -2,
               1, -2, 4;*/
 
    gradient << 2, -3, 1;
    
    linearMatrix.insert(0, 0) = 1;
    linearMatrix.insert(1, 1) = 1;
    linearMatrix.insert(2, 2) = 1;
    linearMatrix.insert(3, 0) = 1;
    linearMatrix.insert(3, 1) = 1;
    linearMatrix.insert(3, 2) = 1;
    /*linearMatrix << 1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,
                    1, 1, 1;*/
 
    lowerBound << 0, 0, 0, 0.5;
    upperBound << 1, 1, 1, 0.5;
 
    if (!solver.data()->setHessianMatrix(hessian)) return false;
    if (!solver.data()->setGradient(gradient)) return false;
    if (!solver.data()->setLinearConstraintsMatrix(linearMatrix)) return false;
    if (!solver.data()->setLowerBound(lowerBound)) return false;
    if (!solver.data()->setUpperBound(upperBound)) return false;
 
    return true;
}
 
int main() {
    OsqpEigen::Solver solver;
 
    // set the solver
    solver.settings()->setWarmStart(true);
 
    // instantiate the solver
    if (initMat(solver)) {
        if (!solver.initSolver()) return 1;
    }
    else {
        cout << "initilize QP solver failed" << endl;
        return 1;
    }
 
    // solve
    solver.solve();
 
    Eigen::VectorXd QPSolution;
    QPSolution = solver.getSolution();
    
    cout << "x1 = " << QPSolution[0] << endl
        << "x2 = " << QPSolution[1] << endl
        << "x3 = " << QPSolution[2] << endl;
}