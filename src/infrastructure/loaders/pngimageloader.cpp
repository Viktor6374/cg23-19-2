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

    // 15 + 32 means a window size of 15, and the 32 specifies to detect gzip or zlib header
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
        return QByteArray(); // Decompression didn't finish successfully
    }

    return outBuffer;
}

//QByteArray UnCompress(QByteArray src)

//    QByteArray outBuffer;
//    z_stream strm;
//    strm.zalloc = NULL;
//    strm.zfree = NULL;
//    strm.opaque = NULL;

//    strm.avail_in = src.size();
//    strm.next_in = (Bytef *)src.data();

//    int err = -1, ret = -1;
//    err = inflateInit2(&strm, MAX_WBITS);
//    if (err == Z_OK) {
//        while (true)
//        {
//            char buffer[4096] = { 0 };
//            strm.avail_out = 4096;
//            strm.next_out = (Bytef *)buffer;
//            int code = inflate(&strm, Z_FINISH);
//            outBuffer.append(buffer, 4096 - strm.avail_out);
//            if (Z_STREAM_END == code || Z_OK != code)
//            {
//                break;
//            }
//        }
//    }
//    inflateEnd(&strm);
//    return outBuffer;
//}

int bytes_to_int(const char *bytes) {
    return (static_cast<unsigned char>(bytes[0]) << 24) |
           (static_cast<unsigned char>(bytes[1]) << 16) |
           (static_cast<unsigned char>(bytes[2]) << 8) |
           (static_cast<unsigned char>(bytes[3]));
}
void int_to_bytes(int x, char* ch, int bit) {
    ch[3] = (char)(x & ((int)pow(2, bit) - 1));
    ch[2] = (char)((x >> bit) & ((int)pow(2, bit) - 1));
    ch[1] = (char)((x >> 2 * bit) & ((int)pow(2, bit) - 1));
    ch[0] = (char)((x >> 3 * bit) & ((int)pow(2, bit) - 1));
}

unsigned int CRC32_function(unsigned char *buf, unsigned long len)
{
    unsigned long crc_table[256];
    unsigned long crc;
    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    };
    crc = 0xFFFFFFFFUL;
    while (len--)
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFUL;
}

unsigned long Crc32(unsigned char *buf, unsigned long len)
{
    //инициализируем таблицу расчёта Crc32
    unsigned long crc_table[256];//массив 32 бита = 4 байтам
    unsigned long crc;//переменная 32 бита = 4 байтам
    for (int i = 0; i < 256; i++)//инициализируем цикл массива
    {
        crc = i;
        for (int j = 0; j < 8; j++)//цикл перебора полинома
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        crc_table[i] = crc;
    };
    crc = 0xFFFFFFFFUL;
    while (len--)// проверка условия продолжения
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFUL; //конец функции расчёта Crc32
};


QByteArray Compress(QByteArray postBody)
{
    QByteArray outBuf;
    z_stream c_stream;
    int err = 0;
    int windowBits = 15;
    int GZIP_ENCODING = 16;
    if (!postBody.isEmpty())
    {
        c_stream.zalloc = (alloc_func)0;
        c_stream.zfree = (free_func)0;
        c_stream.opaque = (voidpf)0;
        c_stream.next_in = (Bytef *)postBody.data();
        c_stream.avail_in = postBody.size();
        if (deflateInit2(&c_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                         windowBits | GZIP_ENCODING, 8, Z_DEFAULT_STRATEGY) != Z_OK) return QByteArray();
        for (;;) {
            char destBuf[4096] = { 0 };
            c_stream.next_out = (Bytef *)destBuf;
            c_stream.avail_out = 4096;
            int err = deflate(&c_stream, Z_FINISH);
            outBuf.append(destBuf, 4096 - c_stream.avail_out);
            if (err == Z_STREAM_END || err != Z_OK)
            {
                break;
            }
        }
        auto total = c_stream.total_out;
        deflateEnd(&c_stream);
        total = c_stream.total_out;
    }
    return outBuf;
}


QByteArray removeEvery1280thByte(const QByteArray &original) {
    QByteArray result;
    result.reserve(original.size() - original.size() / (1280 * 3)); // Optional, to optimize memory allocation

    for (int i = 0; i < original.size(); ++i) {
        if ((i + 1) % (1280 * 3) != 0) {
            // Keep the byte if its position is not a multiple of 1280
            result.append(original[i]);
        }
    }

    return result;
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
        if (in.gcount() != 4) break;

        if (t == "IEND") break;
    }

    QByteArray img(reinterpret_cast<const char*>(compressed_bytes.data()), static_cast<int>(compressed_bytes.size()));
    QByteArray uncompressed_bytes = qGzipUncompress(img);
    uncompressed_bytes = removeEvery1280thByte(uncompressed_bytes);

    std::vector<Pixel> pixels;
    for (int i = 0; i < uncompressed_bytes.size() - 2; i += 3) {
        float channel1 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i])) / 255.0f;
        float channel2 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i + 1])) / 255.0f;
        float channel3 = static_cast<float>(static_cast<unsigned char>(uncompressed_bytes[i + 2])) / 255.0f;

        Pixel current_pixel(channel1, channel2, channel3);
        pixels.push_back(current_pixel);
    }

    return new Image(width, height, pixels); // Assuming Image constructor takes width, height, and pixel data
}

