#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "timer.h"

double average_score(std::vector<int> &scores) {
  //   return std::accumulate(scores.begin(), scores.end(), 0) /
  //   (double)scores.size();

  // version of higher order funtion, return multiple
  return std::accumulate(scores.begin(), scores.end(), 0,
                         std::multiplies<int>()) /
         (double)scores.size();
}

// ==================== Count line by std::accumulate =========================

int accumulate_line(int last_count, char ch) {
  if (ch == '\n')
    return last_count + 1;
  return last_count;
}

// STL implement it by override operator ()
template <typename T> struct Accumulate_line {
  int operator()(int last_count, T ch) {
    if (ch == '\n')
      return last_count + 1;
    return last_count;
  }
};

int count_line(const std::string &input_string) {
  //   return std::accumulate(input_string.begin(), input_string.end(), 0,
  //                          accumulate_line);
  return std::accumulate(input_string.begin(), input_string.end(), 0,
                         Accumulate_line<char>());
}

// =============== Erase blank in the head and tail ===========================
bool is_blank(char c) { return c == ' '; }

std::string trim_left(std::string s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), is_blank));
  return s;
}

std::string trim_right(std::string s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), is_blank).base(), s.end());
  return s;
}

std::string trim(std::string str) {
  return trim_right(trim_left(std::move(str)));
}

// =============== test move and copy in recursion =========================

bool is_letter(char r) {
  return ((r >= 'a' && r <= 'z') || (r >= 'A' && r <= 'Z'));
}

std::vector<char> append_letter(std::vector<char> previous, char ch) {
  if (is_letter(ch))
    previous.push_back(ch);
  return previous;
}

std::vector<char> collect_letter(std::string vec_char) {
  return std::accumulate(vec_char.begin(), vec_char.end(), std::vector<char>{},
                         append_letter);
}

std::vector<char> append_letter_move(std::vector<char> previous, char ch) {
  if (is_letter(ch))
    previous.push_back(ch);
  return std::move(previous);
}

std::vector<char> collect_letter_move(std::string vec_char) {
  return std::accumulate(vec_char.begin(), vec_char.end(), std::vector<char>{},
                         append_letter_move);
}

std::string repeat(std::string str, int n) {
  if (n == 0) return str;
  return str + repeat(str, n - 1);
}

int main() {
  std::string str =
      "fjaeiwofjioawh8304130hr098a3j09ruja03wujhre082h85jr0CM$*%^&U$)%&"
      "0a70CURJEOWmutoamumucouto4u2089umt0w4a3utm90w3uc5t903a";
  str = repeat(str, 5000);
  double time_st = dtime();
  collect_letter(str);
  time_st = dtime() - time_st;

  printf("Copy spend %.4lf seconds\n", time_st);

  time_st = dtime();
  collect_letter_move(str);
  time_st = dtime() - time_st;

  printf("Move spend %.4lf seconds\n", time_st);
}