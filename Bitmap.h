
#ifndef PROJECT1_BITMAP_H
#define PROJECT1_BITMAP_H

#include <cstdlib>
#include <string_view>
#include <fstream>
#include <utility>
#include <vector>


class Bitmap {
public: // служебные структуры bmp файла
    Bitmap() = default;

    ~Bitmap() = default;;
    using Byte = unsigned char;
    static const auto BPP = 3; // bytes per pixel
    static const size_t BitCount = 24; // bits per pixel
    static const size_t SIGN = 19778; // 4d42 - expected signature


    struct BmpHeader {
        uint16_t signature;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t pixels_offset;
    } __attribute__((packed));

    struct DibHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t num_color_planes;
        uint16_t bpp;
        uint32_t compress;
        uint32_t img_size;
        int32_t hor_res;
        int32_t ver_res;
        uint32_t color_nums;
        uint32_t imp_color_used;

    }  __attribute__((packed));


    struct Pixel {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
    } __attribute__((packed));

    Bitmap(BmpHeader bmp_header, DibHeader dib_header, std::vector<std::vector<Pixel>> colors) : height_(
            dib_header.height), width_(dib_header.width), bmp_header_(bmp_header),dib_header_(dib_header),
            colors_(std::move(colors)) {}

    bool Load(std::istream &in);

    bool LoadFromFile(std::string_view input_file_name);

    bool Upload(std::string_view output_file_name);

    BmpHeader GetBmpHeader() {
        return bmp_header_;
    }

    DibHeader GetDibHeader() {
        return dib_header_;
    }

    int32_t GetHeight() const {
        return height_;
    }

    int32_t GetWidth() const {
        return width_;
    }


    std::vector<std::vector<Bitmap::Pixel>> GetColor() {
        return colors_;
    }

    Bitmap::Pixel GetPixels(size_t i, size_t j) {
        return colors_[i][j];
    }


protected:
    // section for protected methods

    // checks the given dib header for validity, extracts fields needed for our particular problem
    // returns false if the header is not appropriate and, hence, the bmp file is
    bool ProcessDibHeader();

    // checks signature of the given file and returns false in case of wrong file format
    bool ProcessBmpHeader() const;

    // downloads info about pixels
    bool FillPixels(std::istream &in);

    // uploads info about pixels
    void FillPixelsOut(std::ostream &in) const;

protected:
    int width_ = 0;
    int height_ = 0;
    Bitmap::BmpHeader bmp_header_{};
    Bitmap::DibHeader dib_header_{};
    std::vector<std::vector<Pixel>> colors_;
};

#endif //PROJECT1_BITMAP_H



