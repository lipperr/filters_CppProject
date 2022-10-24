#include "EdgeFilter.h"
#include "GsFilter.h"
Bitmap *EdgeFilter::Apply(Bitmap *image) {
    GsFilter filter;
    image = filter.Apply(image);
    Bitmap::BmpHeader bmp_header = image->GetBmpHeader();
    Bitmap::DibHeader dib_header = image->GetDibHeader();
    int32_t height = image->GetHeight();
    int32_t width = image->GetWidth();
    std::vector<std::vector<Bitmap::Pixel>> colors(height, std::vector<Bitmap::Pixel>(width));

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            int32_t b = std::min(255, std::max(0, 4 * image->GetPixels(i, j).blue +
                                                  (-1) * image->GetPixels(std::min(height - 1, i + 1), j).blue +
                                                  (-1) * image->GetPixels(std::max(0, i - 1), j).blue +
                                                  (-1) * image->GetPixels(i, std::min(width, j + 1)).blue +
                                                  (-1) * image->GetPixels(i, std::max(0, j - 1)).blue));
            if (b > threshold_) {
                colors[i][j] = {255, 255, 255};
            } else {
                colors[i][j] = {0, 0, 0};
            }
        }
    }
    return new Bitmap(bmp_header, dib_header, colors);
}