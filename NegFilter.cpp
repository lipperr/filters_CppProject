#include "NegFilter.h"
Bitmap *NegFilter::Apply(Bitmap *image) {
    Bitmap::BmpHeader bmp_header = image->GetBmpHeader();
    Bitmap::DibHeader dib_header = image->GetDibHeader();
    int32_t height = image->GetHeight();
    int32_t width = image->GetWidth();
    std::vector<std::vector<Bitmap::Pixel>> colors(height, std::vector<Bitmap::Pixel>(width));

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {

            colors[i][j].blue = 255 - image->GetPixels(i, j).blue;
            colors[i][j].green = 255 - image->GetPixels(i, j).green;
            colors[i][j].red = 255 - image->GetPixels(i, j).red;
        }
    }
    return new Bitmap(bmp_header, dib_header, colors);
}