#include "Parser.hpp"

#include "parser_utils.hpp"

s21::Parser::Parser() : m_matrix(), m_dataset_name(), m_filenames() {}

s21::Parser::~Parser() {}

s21::Parser::Parser(s21::Parser const& rhs)
    : m_matrix(rhs.m_matrix),
      m_dataset_name(rhs.m_dataset_name),
      m_filenames(rhs.m_filenames) {}

s21::Parser& s21::Parser::operator=(s21::Parser const& rhs) {
  if (this == &rhs) return *this;
  m_matrix = rhs.m_matrix;
  m_dataset_name = rhs.m_dataset_name;
  m_filenames = rhs.m_filenames;
  return *this;
}

std::vector<std::vector<size_t>> s21::Parser::getMatrix() const {
  return m_matrix;
}

void s21::Parser::createDatasetMatrix(std::string const& filename,
                                      size_t letter) {
  m_dataset_name = filename;
  m_matrix.clear();
  std::fstream infile(filename);

  while (infile) {
    std::string line;
    getline(infile, line);
    if (line.size() == 0) continue;
    if (std::stoul(line.substr(0, line.find(','))) != letter) continue;
    std::vector<std::string> v_str = resplit(line, std::regex{","});
    std::vector<size_t> v_num = str_to_num_v(v_str);
    v_num = normalize_v(v_num, LetterSideLength);
    m_matrix.push_back(v_num);
  }
  infile.close();
}

void s21::Parser::createDatasetPics() {
  std::string dirname = create_dir(m_dataset_name);
  for (size_t line = 0; line < m_matrix.size(); ++line) {
    std::string path = dirname + '/' + std::to_string(line + 1) + '_' +
                       std::to_string(m_matrix[line][0]) + ".txt";
    std::fstream outfile(path, std::ios::out);
    fill_outfile(outfile, m_matrix[line], LetterSideLength);
    outfile.close();
  }
  m_matrix.clear();
}

void s21::Parser::readBmp(std::string const& fileName) {
  m_filenames.push_back(fileName);
  std::vector<size_t> m = getLetterMatrix(m_filenames.back(), LetterSideLength);
  m_matrix.push_back(m);
}

void s21::Parser::createBmpPics() {
  std::string dirname = create_dir("/bmpPics");
  for (size_t i = 0; i < m_filenames.size(); ++i) {
    std::string path = dirname + '/' +
                       m_filenames[i].substr(m_filenames[i].rfind("/") + 1) +
                       ".txt";
    std::fstream outfile(path, std::ios::out);
    fill_outfile(outfile, m_matrix[i], LetterSideLength);
    outfile.close();
  }
  m_filenames.clear();
  m_matrix.clear();
}
