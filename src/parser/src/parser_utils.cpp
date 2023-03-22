#include "parser_utils.hpp"

std::vector<std::string> resplit(std::string const &s,
                                 std::regex const &sep_regex) {
  std::sregex_token_iterator iter(s.begin(), s.end(), sep_regex, -1);
  std::sregex_token_iterator end;
  return {iter, end};
}

std::vector<size_t> str_to_num_v(std::vector<std::string> const &v) {
  std::vector<size_t> result;
  for (auto const &i : v) {
    result.push_back(std::stoul(i));
  }
  return result;
}

std::vector<std::vector<size_t>> create_zero_v2d(size_t len) {
  std::vector<std::vector<size_t>> result;
  for (size_t i = 0; i < len; ++i) {
    std::vector<size_t> line(len, 0);
    result.push_back(line);
  }
  return result;
}

std::vector<std::vector<size_t>> rotate_sqrt_v(
    std::vector<std::vector<size_t>> const &v2d, size_t len) {
  std::vector<std::vector<size_t>> result = create_zero_v2d(len);
  for (size_t i = 0; i < len; ++i) {
    for (size_t j = 0; j < len; ++j) {
      result[j][i] = v2d[i][j];
    }
  }
  return result;
}

std::vector<size_t> normalize_v(std::vector<size_t> &v, size_t len) {
  std::vector<std::vector<size_t>> v2d = create_zero_v2d(len);
  size_t item(0);
  for (size_t i = 0; i < len; ++i) {
    for (size_t j = 0; j < len; ++j) {
      v2d[i][j] = v[item];
      ++item;
    }
  }
  std::vector<std::vector<size_t>> rotated_v2d = rotate_sqrt_v(v2d, len);
  std::vector<size_t> result;
  for (size_t i = 0; i < len; ++i) {
    for (size_t j = 0; j < len; ++j) {
      result.push_back(rotated_v2d[i][j]);
    }
  }
  return result;
}

void fill_outfile(std::fstream &outfile, std::vector<size_t> const &v,
                  size_t len) {
  for (size_t i = 0; i < v.size(); ++i) {
    if (i % len == 0 && i != 0) outfile << "\n";
    if (v[i] == 0)
      outfile << ' ';
    else if (v[i] < 100)
      outfile << '\'';
    else if (v[i] < 200)
      outfile << '|';
    else
      outfile << '@';
    outfile << "  ";
  }
}

template <typename T>
std::vector<T> slicing_v(std::vector<T> const &v, size_t start, size_t end) {
  auto first = v.begin() + start;
  auto last = v.begin() + end + 1;
  return std::vector<T>(first, last);
}

std::vector<size_t> mirror_v(std::vector<size_t> const &v, size_t len) {
  std::vector<size_t> result;
  for (size_t i = 0; i < len; ++i) {
    std::vector<size_t> slice = slicing_v(v, i * len, i * len + len - 1);
    std::reverse(slice.begin(), slice.end());
    for (auto const &i : slice) {
      result.push_back(i);
    }
  }
  return result;
}

std::vector<size_t> add_zeroes(std::vector<size_t> const &m, size_t len) {
  size_t begin_len = m.size();
  size_t delta = begin_len % len;
  std::vector<size_t> result(m);
  if (delta % 2 != 0) {
    result.push_back(0);
    --delta;
  }
  result.insert(result.begin(), delta / 2, 0);
  result.insert(result.end(), delta / 2, 0);
  return result;
}

std::vector<std::vector<size_t>> split_matrix(std::vector<size_t> const &m,
                                              unsigned int side_len,
                                              size_t len) {
  std::vector<std::vector<size_t>> result;
  for (size_t i = 0; i < side_len; ++i) {
    std::vector<size_t> slice =
        slicing_v(m, i * side_len, i * side_len + side_len - 1);
    slice = add_zeroes(slice, len);
    result.push_back(slice);
  }
  return result;
}

std::vector<size_t> shrink_line(std::vector<size_t> const &m, size_t len) {
  size_t quotient = m.size() / len;
  std::vector<size_t> result;
  std::vector<size_t> elems;
  size_t counter(0);
  for (auto const &i : m) {
    if (counter == quotient) {
      result.push_back(*std::max_element(elems.begin(), elems.end()));
      elems.clear();
      counter = 0;
    }
    elems.push_back(i);
    ++counter;
  }
  return result;
}

std::vector<std::vector<size_t>> rotate_left_v2d(
    std::vector<std::vector<size_t>> const &v2d) {
  size_t hight = v2d.size();
  size_t width = v2d[0].size();
  std::vector<std::vector<size_t>> result;
  for (size_t w = 0; w < width; ++w) {
    std::vector<size_t> line;
    for (size_t h = 0; h < hight; ++h) {
      line.push_back(v2d[h][w]);
    }
    result.push_back(line);
  }
  return result;
}

std::vector<size_t> shrink_matrix(std::vector<size_t> const &m,
                                  unsigned int begin_side_len, size_t len) {
  std::vector<std::vector<size_t>> v2d = split_matrix(m, begin_side_len, len);
  for (auto &m : v2d) {
    m = shrink_line(m, len);
  }
  v2d = rotate_left_v2d(v2d);
  for (auto &m : v2d) {
    m = shrink_line(m, len);
  }
  v2d = rotate_sqrt_v(v2d, len);
  std::vector<size_t> result;
  for (std::vector<size_t> const &m : v2d) {
    result.insert(result.end(), m.begin(), m.end());
  }
  return result;
}

std::string create_dir(std::string const &filename) {
  std::string dirname = "output/" + filename.substr(filename.rfind("/") + 1);
  std::filesystem::create_directory(dirname);
  return dirname;
}
