#include "GsFilter.h"
Bitmap *GsFilter::Apply(Bitmap *image) {
    Bitmap::BmpHeader bmp_header = image->GetBmpHeader();
    Bitmap::DibHeader dib_header = image->GetDibHeader();
    size_t height = image->GetHeight();
    size_t width = image->GetWidth();
    std::vector<std::vector<Bitmap::Pixel>> colors(height, std::vector<Bitmap::Pixel>(width));
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            Bitmap::Pixel color = image->GetPixels(i, j);
            int32_t gr = 0.114 * color.blue + 0.587 * color.green + 0.299 * color.red;
            colors[i][j].blue = gr;
            colors[i][j].green = gr;
            colors[i][j].red = gr;
        }
    }
    return new Bitmap(bmp_header, dib_header, colors);
}
