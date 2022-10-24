#include "SharpFilter.h"

Bitmap *SharpFilter::Apply(Bitmap *image) {
    Bitmap::BmpHeader bmp_header = image->GetBmpHeader();
    Bitmap::DibHeader dib_header = image->GetDibHeader();
    int32_t height = image->GetHeight();
    int32_t width = image->GetWidth();
    std::vector<std::vector<Bitmap::Pixel>> colors(height, std::vector<Bitmap::Pixel>(width));

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            int32_t b = std::min(255, std::max(0, 5 * image->GetPixels(i, j).blue +
                                                  (-1) * image->GetPixels(std::min(height - 1, i + 1), j).blue +
                                                  (-1) * image->GetPixels(std::max(0, i - 1), j).blue +
                                                  (-1) * image->GetPixels(i, std::min(width, j + 1)).blue +
                                                  (-1) * image->GetPixels(i, std::max(0, j - 1)).blue));
            int32_t g = std::min(255, std::max(0, 5 * image->GetPixels(i, j).green +
                                                  (-1) * image->GetPixels(std::min(height - 1, i + 1), j).green +
                                                  (-1) * image->GetPixels(std::max(0, i - 1), j).green +
                                                  (-1) * image->GetPixels(i, std::min(width, j + 1)).green +
                                                  (-1) * image->GetPixels(i, std::max(0, j - 1)).green));
            int32_t r = std::min(255, std::max(0, 5 * image->GetPixels(i, j).red +
                                                  (-1) * image->GetPixels(std::min(height - 1, i + 1), j).red +
                                                  (-1) * image->GetPixels(std::max(0, i - 1), j).red +
                                                  (-1) * image->GetPixels(i, std::min(width, j + 1)).red +
                                                  (-1) * image->GetPixels(i, std::max(0, j - 1)).red));
            colors[i][j].blue = b;
            colors[i][j].green = g;
            colors[i][j].red = r;
        }
    }


    return new Bitmap(bmp_header, dib_header, colors);
}


