#ifndef READ_BMP_HPP
#define READ_BMP_HPP

#include <fstream>

#include "parser_utils.hpp"

// CIEXYZTRIPLE stuff
typedef int FXPT2DOT30;

typedef struct {
  FXPT2DOT30 ciexyzX;
  FXPT2DOT30 ciexyzY;
  FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct {
  CIEXYZ ciexyzRed;
  CIEXYZ ciexyzGreen;
  CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

// bitmap file header
typedef struct {
  unsigned short bfType;
  unsigned int bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int bfOffBits;
} BITMAPFILEHEADER;

// bitmap info header
typedef struct {
  unsigned int biSize;
  unsigned int biWidth;
  unsigned int biHeight;
  unsigned short biPlanes;
  unsigned short biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  unsigned int biXPelsPerMeter;
  unsigned int biYPelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
  unsigned int biRedMask;
  unsigned int biGreenMask;
  unsigned int biBlueMask;
  unsigned int biAlphaMask;
  unsigned int biCSType;
  CIEXYZTRIPLE biEndpoints;
  unsigned int biGammaRed;
  unsigned int biGammaGreen;
  unsigned int biGammaBlue;
  unsigned int biIntent;
  unsigned int biProfileData;
  unsigned int biProfileSize;
  unsigned int biReserved;
} BITMAPINFOHEADER;

// rgb quad
typedef struct {
  unsigned char rgbBlue;
  unsigned char rgbGreen;
  unsigned char rgbRed;
  unsigned char rgbReserved;
} RGBQUAD;

// read bytes
template <typename Type>
void read(std::ifstream &fp, Type &result, size_t size) {
  fp.read(reinterpret_cast<char *>(&result), size);
}

std::vector<size_t> getLetterMatrix(std::string const &filename, size_t len);

namespace consts {
double const red_to_grey(0.2126);
double const green_to_grey(0.7152);
double const blue_to_grey(0.0722);
}  // namespace consts

#endif
