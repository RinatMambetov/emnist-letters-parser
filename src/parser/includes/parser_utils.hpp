#ifndef PARSER_UTILS_HPP
#define PARSER_UTILS_HPP

#include "Parser.hpp"

std::vector<std::string> resplit(std::string const &s,
                                 std::regex const &sep_regex);

std::vector<size_t> str_to_num_v(std::vector<std::string> const &v);

std::vector<size_t> normalize_v(std::vector<size_t> &v, size_t len);

void fill_outfile(std::fstream &outfile, std::vector<size_t> const &v,
                  size_t len);

std::vector<size_t> mirror_v(std::vector<size_t> const &v, size_t len);

std::vector<size_t> shrink_matrix(std::vector<size_t> const &m,
                                  unsigned int begin_side_len, size_t len);

std::string create_dir(std::string const &filename);

#endif
