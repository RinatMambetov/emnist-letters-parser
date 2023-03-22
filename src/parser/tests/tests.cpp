#include <gtest/gtest.h>

#include "Parser.hpp"

TEST(Parser, default_constructor) { s21::Parser p; }

// TEST(Parser, copy_constructor) {
TEST(Parser, copy_constructor_skip) {
  s21::Parser p;
  std::string path("../../datasets/emnist-letters/emnist-letters-test.csv");
  p.createDatasetMatrix(path, 1);
  s21::Parser copy(p);
}

// TEST(Parser, copy_operator) {
TEST(Parser, copy_operator_skip) {
  s21::Parser p;
  std::string path("../../datasets/emnist-letters/emnist-letters-test.csv");
  p.createDatasetMatrix(path, 1);
  s21::Parser copy;
  copy = p;
}

// TEST(Parser, getMatrix) {
TEST(Parser, getMatrix_skip) {
  s21::Parser p;
  std::string path("../../datasets/emnist-letters/emnist-letters-test.csv");
  p.createDatasetMatrix(path, 1);
  std::vector<std::vector<size_t>> m = p.getMatrix();

  std::vector<size_t> v{
      1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   4,   21,  32,  37,  37,
      20,  1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   4,   22,  110, 172, 203, 217, 214, 138, 15,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   20,  45,  114, 145, 232, 252, 254, 254, 232, 93,  6,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,
      67,  122, 203, 222, 249, 254, 254, 250, 207, 51,  4,   1,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   5,   47,  175, 231,
      254, 254, 253, 232, 209, 142, 111, 119, 93,  53,  18,  0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   33,  190, 247, 253, 254, 253,
      219, 98,  54,  77,  177, 243, 236, 165, 81,  2,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   3,   84,  233, 254, 254, 254, 228, 126, 91,
      118, 188, 250, 254, 254, 215, 125, 4,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   20,  169, 251, 254, 255, 253, 218, 213, 233, 245, 252,
      254, 255, 254, 222, 140, 9,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   27,  190, 253, 254, 255, 254, 242, 246, 252, 254, 254, 254, 255,
      254, 233, 173, 22,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      8,   126, 244, 254, 254, 254, 254, 254, 254, 254, 252, 250, 252, 254, 251,
      232, 100, 20,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   33,
      163, 244, 251, 254, 254, 252, 245, 232, 172, 130, 173, 232, 253, 253, 230,
      111, 7,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   33,  127,
      175, 243, 243, 177, 115, 82,  22,  5,   22,  100, 232, 250, 250, 190, 115,
      33,  8,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   10,  34,  113,
      113, 34,  4,   2,   0,   0,   0,   32,  152, 170, 188, 243, 242, 160, 92,
      33,  8,   0,   0,   0,   0,   0,   0,   0,   0,   1,   7,   32,  32,  7,
      0,   0,   0,   0,   0,   17,  75,  81,  108, 218, 243, 188, 145, 106, 42,
      5,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   2,   2,   9,   77,  112, 51,  50,  106, 112, 24,  0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   2,   3,   0,   0,   4,   15,  4,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0};
  for (size_t i = 0; i < m[0].size(); ++i) {
    EXPECT_EQ(m[0][i], v[i]);
  }
}

// TEST(Parser, createPicsTest) {
TEST(Parser, createPicsTest_skip) {
  s21::Parser p;
  std::string path("../../datasets/emnist-letters/emnist-letters-test.csv");
  p.createDatasetMatrix(path, 2);
  p.createDatasetPics();
}

// TEST(Parser, createPicsTrain) {
TEST(Parser, createPicsTrain_skip) {
  s21::Parser p;
  std::string path("../../datasets/emnist-letters/emnist-letters-train.csv");
  p.createDatasetMatrix(path, 3);
  p.createDatasetPics();
}

TEST(Parser, read_create_bmp) {
  s21::Parser p;
  p.readBmp("../../datasets/letters/a28.bmp");
  p.readBmp("../../datasets/letters/c28.bmp");
  p.readBmp("../../datasets/letters/o28.bmp");
  p.readBmp("../../datasets/letters/v28.bmp");
  p.readBmp("../../datasets/letters/z28.bmp");
  p.createBmpPics();
  p.readBmp("../../datasets/letters/A512.bmp");
  p.readBmp("../../datasets/letters/c256.bmp");
  p.readBmp("../../datasets/letters/o400.bmp");
  p.readBmp("../../datasets/letters/v128.bmp");
  p.readBmp("../../datasets/letters/z99.bmp");
  p.createBmpPics();
}

TEST(Parser, read_not_exist_file) {
  s21::Parser p;
  ASSERT_THROW(p.readBmp("../../datasets/letters/8.bmp"),
               std::invalid_argument);
}

TEST(Parser, read_not_bmp_file) {
  s21::Parser p;
  ASSERT_THROW(p.readBmp("../../datasets/letters/wrong_file.txt"),
               std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
