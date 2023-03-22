#include "read_bmp_utils.hpp"

unsigned char bitextract(const unsigned int byte, const unsigned int mask) {
  if (mask == 0) return 0;

  // определение количества нулевых бит справа от маски
  int maskBufer = mask, maskPadding = 0;
  while (!(maskBufer & 1)) {
    maskBufer >>= 1;
    maskPadding++;
  }

  // применение маски и смещение
  return (byte & mask) >> maskPadding;
}

void makeFileHeader(std::ifstream& fileStream, BITMAPFILEHEADER& fileHeader) {
  read(fileStream, fileHeader.bfType, sizeof(fileHeader.bfType));
  read(fileStream, fileHeader.bfSize, sizeof(fileHeader.bfSize));
  read(fileStream, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
  read(fileStream, fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
  read(fileStream, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));
}

void makeFileInfoHeader(std::ifstream& fileStream,
                        BITMAPINFOHEADER& fileInfoHeader) {
  read(fileStream, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));

  if (fileInfoHeader.biSize >= 12) {
    read(fileStream, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));
    read(fileStream, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
    read(fileStream, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
    read(fileStream, fileInfoHeader.biBitCount,
         sizeof(fileInfoHeader.biBitCount));
  }
}

void ifBmpV1(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader) {
  read(fileStream, fileInfoHeader.biCompression,
       sizeof(fileInfoHeader.biCompression));
  read(fileStream, fileInfoHeader.biSizeImage,
       sizeof(fileInfoHeader.biSizeImage));
  read(fileStream, fileInfoHeader.biXPelsPerMeter,
       sizeof(fileInfoHeader.biXPelsPerMeter));
  read(fileStream, fileInfoHeader.biYPelsPerMeter,
       sizeof(fileInfoHeader.biYPelsPerMeter));
  read(fileStream, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
  read(fileStream, fileInfoHeader.biClrImportant,
       sizeof(fileInfoHeader.biClrImportant));
}

void ifBmpV2(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader) {
  read(fileStream, fileInfoHeader.biRedMask, sizeof(fileInfoHeader.biRedMask));
  read(fileStream, fileInfoHeader.biGreenMask,
       sizeof(fileInfoHeader.biGreenMask));
  read(fileStream, fileInfoHeader.biBlueMask,
       sizeof(fileInfoHeader.biBlueMask));
}

void ifBmpV3(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader) {
  read(fileStream, fileInfoHeader.biAlphaMask,
       sizeof(fileInfoHeader.biAlphaMask));
}

void ifBmpV4(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader) {
  read(fileStream, fileInfoHeader.biCSType, sizeof(fileInfoHeader.biCSType));
  read(fileStream, fileInfoHeader.biEndpoints,
       sizeof(fileInfoHeader.biEndpoints));
  read(fileStream, fileInfoHeader.biGammaRed,
       sizeof(fileInfoHeader.biGammaRed));
  read(fileStream, fileInfoHeader.biGammaGreen,
       sizeof(fileInfoHeader.biGammaGreen));
  read(fileStream, fileInfoHeader.biGammaBlue,
       sizeof(fileInfoHeader.biGammaBlue));
}

void ifBmpV5(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader) {
  read(fileStream, fileInfoHeader.biIntent, sizeof(fileInfoHeader.biIntent));
  read(fileStream, fileInfoHeader.biProfileData,
       sizeof(fileInfoHeader.biProfileData));
  read(fileStream, fileInfoHeader.biProfileSize,
       sizeof(fileInfoHeader.biProfileSize));
  read(fileStream, fileInfoHeader.biReserved,
       sizeof(fileInfoHeader.biReserved));
}

void checkUnsupportedFormat(BITMAPINFOHEADER& fileInfoHeader) {
  if (fileInfoHeader.biSize != 12 && fileInfoHeader.biSize != 40 &&
      fileInfoHeader.biSize != 52 && fileInfoHeader.biSize != 56 &&
      fileInfoHeader.biSize != 108 && fileInfoHeader.biSize != 124)
    throw std::invalid_argument("Error: Unsupported BMP format.");

  if (fileInfoHeader.biBitCount != 16 && fileInfoHeader.biBitCount != 24 &&
      fileInfoHeader.biBitCount != 32)
    throw std::invalid_argument("Error: Unsupported BMP bit count.");

  if (fileInfoHeader.biCompression != 0 && fileInfoHeader.biCompression != 3)
    throw std::invalid_argument("Error: Unsupported BMP compression.");
}
