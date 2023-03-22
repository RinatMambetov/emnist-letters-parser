#ifndef PARSER_HPP
#define PARSER_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "read_bmp.hpp"

namespace s21 {

class Parser {
 private:
  enum { LetterSideLength = 28, LetterLength = 784 };

  std::vector<std::vector<size_t>> m_matrix;
  std::string m_dataset_name;
  std::vector<std::string> m_filenames;

 public:
  Parser();
  ~Parser();
  explicit Parser(Parser const& rhs);
  Parser& operator=(Parser const& rhs);

  std::vector<std::vector<size_t>> getMatrix() const;

  void createDatasetMatrix(std::string const& filename, size_t letter);
  void createDatasetPics();
  void readBmp(std::string const& filename);
  void createBmpPics();
};

}  // namespace s21

#endif
