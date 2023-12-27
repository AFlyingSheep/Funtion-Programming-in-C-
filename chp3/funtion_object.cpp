#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "timer.h"

// Funtion and funtional object
// 自动推导返回值类型
auto fib(int n) {
  if (n < 2)
    return n;
  else
    return fib(n - 1) + fib(n - 2);
}

auto fib2(int n) {
  if (n >= 2)
    return fib(n - 1) + fib(n - 2);
  else
    return n;
}

// 返回值为返回表达式的 decltype 类型
// auto 与 decltype(auto)
// 也是有区别的，decltype(auto)作返回,
// 它实质是将返回值表达式代入到auto然后再用decltype规则进行推断，所以是不同于第一种的，比如直接推出引用
decltype(auto) ask(double t) { return 42 + t; }

// 完美传递实参
template <typename Object, typename Function>
decltype(auto) call_on_objdect(Object &&object, Function function) {
  return function(std::forward<Object>(object));
}

// 创建模板成员函数而非模板类
class older_than {
public:
  older_than(int limit) : limit_(limit) {}
  template <typename T> bool operator()(T &&object) const {
    return std::forward<T>(object).age() > limit_;
  }

private:
  int limit_;
};

class Person;
// 调用时：
void call() {
  std::vector<Person> persons;
  std::count_if(persons.begin(), persons.end(), older_than(5));
}

// lambda 表达式
// 编译时 C++ 将 lambda 表达式转换为一个新类，并且重载调用操作符为 lambda
// 函数中的函数体 求解 lambda 表达式会创建一个 closure
// 类实例，包含状态以及执行上下文的类对象 注意，lambda 表达式调用操作符默认为
// const，如果需要修改捕获的变量需要声明为 mutable

// 创建通用的 lambda
void common_lambda() {
  auto predicate = [limit = 42](auto &&object) { return object.age() < 42; };
  std::vector<Person> persons;
  std::count_if(persons.begin(), persons.end(), predicate);
}

// STL 对普通操作符提供了包装器，可以传递给算法
void wrapper() {
  std::vector<int> nums = {3, 2, 1, 5, 2};
  // 从 C++ 14 开始，无需指明类型，编译器自动推导
  std::sort(nums.begin(), nums.end(), std::greater<>());
}

// Boost phoenix 库很有意思，可以简化比较的写法
int main() {}