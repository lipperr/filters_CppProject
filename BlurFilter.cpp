#include "BlurFilter.h"

Bitmap *BlurFilter::Apply(Bitmap *image) {
    Bitmap::BmpHeader bmp_header = image->GetBmpHeader();
    Bitmap::DibHeader dib_header = image->GetDibHeader();
    int32_t height = image->GetHeight();
    int32_t width = image->GetWidth();
    std::vector<std::vector<Bitmap::Pixel>> colors(height, std::vector<Bitmap::Pixel>(width));
    std::vector<double> coeffs;
    double t;
    double k = 0;
    double sum = -(2 * C);
    while (sum <= 0.95) {
        t = C * std::pow(M_E, -((k * k) / (2 * sigma_ * sigma_)));
        t /= 0.95;
        coeffs.push_back(t);
        sum += 2 * t;
        ++k;
    }
    int radius = coeffs.size();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            double b = 0;
            double g = 0;
            double r = 0;
            for (int y = -radius; y < radius; ++y) {
                int m = std::max(std::min(i + y, height - 1), 0);
                Bitmap::Pixel color = image->GetPixels(m, j);
                b += color.blue * coeffs[std::abs(y)] / 255.0;
                g += color.green * coeffs[std::abs(y)] / 255.0;
                r += color.red * coeffs[std::abs(y)] / 255.0;
            }
            colors[i][j].blue = b > 1 ? 255 : static_cast<uint8_t>(b * 255);
            colors[i][j].green = g > 1 ? 255 : static_cast<uint8_t>(g * 255);
            colors[i][j].red = r > 1 ? 255 : static_cast<uint8_t>(r * 255);
        }
    }
    std::vector<std::vector<Bitmap::Pixel>> colors2 = colors;
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            double b = 0;
            double g = 0;
            double r = 0;
            for (int x = -radius; x < radius; ++x) {
                int m = std::max(std::min(j + x, height - 1), 0);
                Bitmap::Pixel color = colors2[i][m];
                b += color.blue * coeffs[std::abs(x)] / 255.0;
                g += color.green * coeffs[std::abs(x)] / 255.0;
                r += color.red * coeffs[std::abs(x)] / 255.0;
            }
            colors[i][j].blue = b > 1 ? 255 : static_cast<uint8_t>(b * 255);
            colors[i][j].green = g > 1 ? 255 : static_cast<uint8_t>(g * 255);
            colors[i][j].red = r > 1 ? 255 : static_cast<uint8_t>(r * 255);

        }
    }

    return new Bitmap(bmp_header, dib_header, colors);
}