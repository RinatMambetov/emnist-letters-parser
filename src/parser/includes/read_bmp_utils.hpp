#ifndef READ_BMP_UTILS_HPP
#define READ_BMP_UTILS_HPP

#include "read_bmp.hpp"

unsigned char bitextract(const unsigned int byte, const unsigned int mask);

void makeFileHeader(std::ifstream& fileStream, BITMAPFILEHEADER& fileHeader);

void makeFileInfoHeader(std::ifstream& fileStream,
                        BITMAPINFOHEADER& fileInfoHeader);

void ifBmpV1(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader);

void ifBmpV2(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader);

void ifBmpV3(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader);

void ifBmpV4(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader);

void ifBmpV5(std::ifstream& fileStream, BITMAPINFOHEADER& fileInfoHeader);

void checkUnsupportedFormat(BITMAPINFOHEADER& fileInfoHeader);

#endif
