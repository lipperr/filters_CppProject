#include "Bitmap.h"

bool Bitmap::LoadFromFile(std::string_view input_file_name) {
    std::ifstream file;
    std::string name(input_file_name);
    file.open(name, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }
    bool success = Load(file);

    return success;
}

bool Bitmap::Load(std::istream &in) {
    if (!in.eof()) {
        in.read(reinterpret_cast<char *>(&bmp_header_), sizeof(BmpHeader));
    } else {
        return false;
    }

    if (!in.eof()) {
        in.read(reinterpret_cast<char *>(&dib_header_), sizeof(DibHeader));
    } else {
        return false;
    }

    if (!ProcessDibHeader() || !ProcessBmpHeader() || !FillPixels(in)) {
        return false;
    }

    return true;
}

bool Bitmap::ProcessDibHeader() {
    width_ = dib_header_.width;
    height_ = dib_header_.height;
    colors_.resize(height_, std::vector<Pixel>(width_));
    if (dib_header_.bpp != BitCount) {
        return false;
    }
    return true;
}

bool Bitmap::ProcessBmpHeader() const {
    if (bmp_header_.signature != SIGN) {
        return false;
    }
    return true;
}

bool Bitmap::FillPixels(std::istream &in) {
    std::streamsize bytes_to_read = width_ * BPP;
    std::streamsize modified_padding_size = 4 - bytes_to_read % 4;
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            Pixel color{0, 0, 0};
            if (!in.eof()) {
                in.read(reinterpret_cast<char *>(&color), BPP);
                colors_[y][x] = color;
            } else {
                return false;
            }

        }
        if (modified_padding_size != 4) {
            int32_t padding;
            if (!in.eof()) {
                in.read(reinterpret_cast<char *>(&padding), modified_padding_size);
            } else {
                return false;
            }

        }
    }
    return true;
}

bool Bitmap::Upload(std::string_view output_file_name) {
    std::ofstream file;
    std::string name(output_file_name);
    file.open(name, std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }

    file.write(reinterpret_cast<char *>(&bmp_header_), sizeof(BmpHeader));
    file.write(reinterpret_cast<char *>(&dib_header_), sizeof(DibHeader));

    FillPixelsOut(file);
    file.close();

    return true;
}

void Bitmap::FillPixelsOut(std::ostream &in) const {

    std::streamsize bytes_to_read = width_ * BPP;
    std::streamsize modified_padding_size = 4 - bytes_to_read % 4;

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            Pixel color = colors_[y][x];
            in.write(reinterpret_cast<char *>(&color), BPP);
        }
        if (modified_padding_size != 4) {
            int32_t padding;
            in.write(reinterpret_cast<char *>(&padding), modified_padding_size);
        }
    }
}

