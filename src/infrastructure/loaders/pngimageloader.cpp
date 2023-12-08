#include "pngimageloader.h"
#include <cstdlib>
#include<cmath>
#include<stdexcept>
#include<string>
#include <QtZlib/zlib.h>
#include<QByteArray>
#include<QMap>
#include<limits>

PNGImageLoader::PNGImageLoader()
{

}


QByteArray qGzipUncompress(const QByteArray& data) {
    if (data.size() <= 4) {
        // The input data is too small to be valid compressed data
        return QByteArray();
    }

    z_stream strm;
    strm.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(data.data()));
    strm.avail_in = data.size();
    strm.total_out = 0;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    if (inflateInit2(&strm, 15 + 32) != Z_OK) {
        return QByteArray();
    }

    QByteArray outBuffer;
    const int bufferSize = 4096;
    std::unique_ptr<char[]> buffer(new char[bufferSize]);

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef *>(buffer.get());
        strm.avail_out = bufferSize;

        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            inflateEnd(&strm);
            return QByteArray();
        }

        outBuffer.append(buffer.get(), bufferSize - strm.avail_out);
    } while (ret != Z_STREAM_END && strm.avail_out == 0);

    inflateEnd(&strm);

    if (ret != Z_STREAM_END) {
        return QByteArray();
    }

    return outBuffer;
}

unsigned int bytes_to_int(const char *bytes) {
    return (static_cast<unsigned char>(bytes[0]) << 24) |
           (static_cast<unsigned char>(bytes[1]) << 16) |
           (static_cast<unsigned char>(bytes[2]) << 8) |
           (static_cast<unsigned char>(bytes[3]));
}

unsigned char Paeth_predictor(int left, int up, int upper_left){
    unsigned char p = left + up - upper_left;
    unsigned char p_left = abs(p - left);
    unsigned char p_up = abs(p - up);
    unsigned char p_upper_left = abs(p - upper_left);
    if (p_left < p_up && p_left < p_upper_left){
        return left;
    } else if (p_up < p_left && p_up < p_upper_left){
        return up;
    } else {
        return upper_left;
    }
}

QByteArray filter(const QByteArray &original, int width, int height, int bytes_for_pixel) {
    QByteArray result;
    result.reserve(original.size() - original.size() / (width * bytes_for_pixel)); // Optional, to optimize memory allocation
    std::vector<unsigned char> filter_bytes;

    int number_string = 0;
    for (int i = 0; i < original.size(); i += width * bytes_for_pixel + 1) {
        unsigned char filter = original[i];
        filter_bytes.push_back(filter);
        switch (filter) {
        case 0:
            for (int j = i + 1; j < i + width * bytes_for_pixel + 1; j++){
                result.append(original[j]);
            }
            break;
        case 1:
            for (int j = i + 1; j < i + width * bytes_for_pixel + 1; j++){
                if (result.size() - 3 < number_string * width * bytes_for_pixel){
                    result.append(original[j]);
                    continue;
                }
                result.append(original[j] + result[result.size() - bytes_for_pixel]);
            }
            break;
        case 2:
            for (int j = i + 1; j < i + width * bytes_for_pixel + 1; j++){
                if (result.size() - width * bytes_for_pixel < 0){
                    result.append(original[j]);
                    continue;
                }
                result.append(original[j] + result[result.size() - width * bytes_for_pixel]);
            }
            break;
        case 3:
            for (int j = i + 1; j < i + width * bytes_for_pixel + 1; j++){
                unsigned char first = 0;
                unsigned char second = 0;
                if (result.size() - bytes_for_pixel >= number_string * width * bytes_for_pixel){
                    first = result[result.size() - bytes_for_pixel];
                }
                if (result.size() - width * bytes_for_pixel >= 0){
                    second = result[result.size() - width * bytes_for_pixel];
                }
                result.append(original[j] + (first + second) / 2);
            }
            break;
        case 4:
            for (int j = i + 1; j < i + width * bytes_for_pixel + 1; j++){
                unsigned char left = 0;
                if (result.size() - bytes_for_pixel >= i + 1){
                    left = result[result.size() - bytes_for_pixel];
                }
                unsigned char up = 0;
                if (result.size() - width * bytes_for_pixel >= 0){
                    up = result[result.size() - width * bytes_for_pixel];
                }
                unsigned char upper_left = 0;
                if (result.size() - width * bytes_for_pixel - 1 >= std::max(i - width * bytes_for_pixel + 1, 0)){
                    upper_left = result[result.size() - width * bytes_for_pixel - 1];
                }
                result.append(original[j] + Paeth_predictor(left, up, upper_left));
            }
            break;
        }

        number_string++;
    }

    return result;
}

std::vector<Pixel> create_pixels(QByteArray uncompressed_bytes, int color_type, QMap<int, Pixel> palette){
    std::vector<Pixel> pixels;
    if (color_type == 0){
        for (int i = 0; i < uncompressed_bytes.size(); i++) {
            float channel1 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i])) / 255.0f;

            Pixel current_pixel(channel1, channel1, channel1);
            pixels.push_back(current_pixel);
        }
    } else if (color_type == 2){
        for (int i = 0; i < uncompressed_bytes.size() - 2; i += 3) {
            float channel1 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i])) / 255.0f;
            float channel2 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i + 1])) / 255.0f;
            float channel3 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i + 2])) / 255.0f;

            Pixel current_pixel(channel1, channel2, channel3);
            pixels.push_back(current_pixel);
        }
    } else if (color_type == 3){
        for (int i = 0; i < uncompressed_bytes.size(); i++) {
            unsigned char number_color = static_cast<unsigned char>(uncompressed_bytes[i]);

            Pixel current_pixel(palette[number_color]);
            pixels.push_back(current_pixel);
        }
    }

    return pixels;
}

unsigned long crc_table[256];
int crc_table_computed = 0;

void make_crc_table()
{
    unsigned long c;
    int n, k;

    for (n = 0; n < 256; n++) {
        c = (unsigned long) n;
        for (k = 0; k < 8; k++) {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[n] = c;
    }
    crc_table_computed = 1;
}

unsigned long update_crc(unsigned long crc, unsigned char *buf, int len)
{
    unsigned long c = crc;
    int n;

    if (!crc_table_computed)
        make_crc_table();
    for (n = 0; n < len; n++) {
        c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}

unsigned long crc(unsigned char *buf, int len)
{
    return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}


Image *PNGImageLoader::load(std::ifstream &in) {
    const int indent = 4;
    char str[indent];
    in.read(str, indent);
    std::string t = "";
    int width, height, number_bits, color_type;
    std::vector<unsigned char> compressed_bytes;
    QMap<int, Pixel> palette;

    while (true) {
        char length_str[4];
        in.read(length_str, 4);
        if (in.gcount() != 4) break;

        char type[4];
        in.read(type, 4);
        if (in.gcount() != 4) break;

        t.assign(type, type + 4);

        int length = bytes_to_int(length_str);
        std::vector<unsigned char> data(length);
        in.read(reinterpret_cast<char*>(data.data()), length);
        if (in.gcount() != length) break;

        if (t == "IHDR") {
            width = bytes_to_int(reinterpret_cast<char*>(data.data()));
            height = bytes_to_int(reinterpret_cast<char*>(data.data()) + 4);
            number_bits = static_cast<int>(data[8]);
            color_type = static_cast<int>(data[9]);
        } else if (t == "IDAT") {
            compressed_bytes.insert(compressed_bytes.end(), data.begin(), data.end());
        } else if (t == "PLTE" && color_type == 3) {
            for (size_t i = 0; i < data.size(); i += 3) {
                Pixel current_pixel(data[i] / 255.0, data[i + 1] / 255.0, data[i + 2] / 255.0);
                palette.insert(static_cast<int>(i / 3), current_pixel);
            }
        }

        char sum_str[4];
        in.read(sum_str, 4);
        unsigned int sum = bytes_to_int(sum_str);
        if (in.gcount() != 4) break;

        std::vector<unsigned char> chunk;
        chunk.insert(chunk.end(), type, type + 4);
        chunk.insert(chunk.end(), data.begin(), data.end());

        unsigned long crc_ = crc(&chunk[0], chunk.size());

        if (crc_ != sum){
            throw std::logic_error("The checksum does not match!");
        }

        if (t == "IEND") break;
    }

    QByteArray img(reinterpret_cast<const char*>(compressed_bytes.data()), static_cast<int>(compressed_bytes.size()));
    QByteArray uncompressed_bytes = qGzipUncompress(img);
    uncompressed_bytes = filter(uncompressed_bytes, width, height, color_type == 2 ? 3 : 1);

    std::vector<Pixel> pixels = create_pixels(uncompressed_bytes, color_type, palette);

    return new Image(width, height, pixels); // Assuming Image constructor takes width, height, and pixel data
}

