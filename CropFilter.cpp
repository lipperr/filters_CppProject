#include "CropFilter.h"

Bitmap *CropFilter::Apply(Bitmap *image) {

    Bitmap::BmpHeader bmp_header = image->GetBmpHeader();
    Bitmap::DibHeader dib_header = image->GetDibHeader();
    int height = image->GetHeight();
    std::vector<std::vector<Bitmap::Pixel>> colors(height_, std::vector<Bitmap::Pixel>(width_));

    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            colors[i][j] = image->GetPixels(height - height_ + i, j);
        }
    }
    bmp_header.file_size = height_ * width_ * 3 + 54;
    dib_header.height = height_;
    dib_header.width = width_;
    return new Bitmap(bmp_header, dib_header, colors);
}
