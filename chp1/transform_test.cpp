#include <algorithm>
#include <iostream>
#include <ostream>
#include <ranges>
#include <vector>

int single_handle(int x) { return x + 1; }

std::vector<int> multi_handle(std::vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    vec[i] += 1;
  }
  return std::move(vec);
}

int main() {
  int input = 1;
  std::vector<int> input_vector(5, 2);
  std::vector<int> result_vector(input_vector.size());

  std::transform(input_vector.begin(), input_vector.end(),
                 result_vector.begin(), single_handle);

  for (auto v : result_vector) {
    std::cout << v << std::endl;
  }
}