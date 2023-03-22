#include "read_bmp.hpp"

#include "read_bmp_utils.hpp"

std::vector<size_t> getLetterMatrix(std::string const& filename, size_t len) {
  std::ifstream fileStream(filename, std::ifstream::binary);
  if (!fileStream)
    throw std::invalid_argument("Error opening file '" + filename + "'.");

  // заголовoк изображения
  BITMAPFILEHEADER fileHeader;
  makeFileHeader(fileStream, fileHeader);

  if (fileHeader.bfType != 0x4D42)
    throw std::invalid_argument("Error: '" + filename + "' is not BMP file.");

  // информация изображения
  BITMAPINFOHEADER fileInfoHeader;
  makeFileInfoHeader(fileStream, fileInfoHeader);

  // получаем информацию о битности
  int colorsCount = fileInfoHeader.biBitCount >> 3;
  if (colorsCount < 3) {
    colorsCount = 3;
  }

  int bitsOnColor = fileInfoHeader.biBitCount / colorsCount;
  int maskValue = (1 << bitsOnColor) - 1;

  if (fileInfoHeader.biSize >= 40) ifBmpV1(fileStream, fileInfoHeader);

  fileInfoHeader.biRedMask = 0;
  fileInfoHeader.biGreenMask = 0;
  fileInfoHeader.biBlueMask = 0;

  if (fileInfoHeader.biSize >= 52) ifBmpV2(fileStream, fileInfoHeader);

  // если маска не задана, то ставим маску по умолчанию
  if (fileInfoHeader.biRedMask == 0 || fileInfoHeader.biGreenMask == 0 ||
      fileInfoHeader.biBlueMask == 0) {
    fileInfoHeader.biRedMask = maskValue << (bitsOnColor * 2);
    fileInfoHeader.biGreenMask = maskValue << bitsOnColor;
    fileInfoHeader.biBlueMask = maskValue;
  }

  if (fileInfoHeader.biSize >= 56)
    ifBmpV3(fileStream, fileInfoHeader);
  else
    fileInfoHeader.biAlphaMask = maskValue << (bitsOnColor * 3);

  if (fileInfoHeader.biSize >= 108) ifBmpV4(fileStream, fileInfoHeader);

  if (fileInfoHeader.biSize >= 124) ifBmpV5(fileStream, fileInfoHeader);

  checkUnsupportedFormat(fileInfoHeader);

  // rgb info
  std::shared_ptr<std::shared_ptr<RGBQUAD[]>[]> rgbInfo(
      new std::shared_ptr<RGBQUAD[]>[fileInfoHeader.biHeight]);

  for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
    rgbInfo[i] =
        std::shared_ptr<RGBQUAD[]>(new RGBQUAD[fileInfoHeader.biWidth]);
  }

  // определение размера отступа в конце каждой строки
  int linePadding =
      ((fileInfoHeader.biWidth * (fileInfoHeader.biBitCount / 8)) % 4) & 3;

  // чтение
  unsigned int bufer;

  for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
    for (unsigned int j = 0; j < fileInfoHeader.biWidth; j++) {
      read(fileStream, bufer, fileInfoHeader.biBitCount / 8);

      rgbInfo[i][j].rgbRed = bitextract(bufer, fileInfoHeader.biRedMask);
      rgbInfo[i][j].rgbGreen = bitextract(bufer, fileInfoHeader.biGreenMask);
      rgbInfo[i][j].rgbBlue = bitextract(bufer, fileInfoHeader.biBlueMask);
      rgbInfo[i][j].rgbReserved = bitextract(bufer, fileInfoHeader.biAlphaMask);
    }
    fileStream.seekg(linePadding, std::ios_base::cur);
  }

  std::vector<size_t> m;

  for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
    for (unsigned int j = 0; j < fileInfoHeader.biWidth; j++) {
      double red = (+rgbInfo[i][j].rgbRed) * consts::red_to_grey;
      double green = (+rgbInfo[i][j].rgbGreen) * consts::green_to_grey;
      double blue = (+rgbInfo[i][j].rgbBlue) * consts::blue_to_grey;
      m.push_back(red + green + blue);
    }
  }

  std::reverse(m.begin(), m.end());

  if (fileInfoHeader.biHeight > len) {
    m = mirror_v(m, fileInfoHeader.biHeight);
    m = shrink_matrix(m, fileInfoHeader.biHeight, len);
  } else
    m = mirror_v(m, len);

  return m;
}
