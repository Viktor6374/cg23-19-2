#include "pngimageloader.h"
#include <cstdlib>
#include<cmath>
#include<stdexcept>
#include<string>
#include <QtZlib/zlib.h>
#include<QByteArray>
#include<QMap>

PNGImageLoader::PNGImageLoader()
{

}


QByteArray qGzipUncompress(const QByteArray& data)
{
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
    int bufferSize = 4096;
    std::unique_ptr<char[]> buffer(new char[bufferSize]);

    int ret;
    do {
        strm.next_out = reinterpret_cast<Bytef *>(buffer.get());
        strm.avail_out = bufferSize;

        ret = inflate(&strm, Z_NO_FLUSH);
        switch (ret) {
        case Z_NEED_DICT:
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
            inflateEnd(&strm);
            return QByteArray();
        }

        if (bufferSize - strm.avail_out > 0) {
            outBuffer.append(buffer.get(), bufferSize - strm.avail_out);
        }
    } while (strm.avail_out == 0);

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

int bytes_to_int(char *bytes, int bit) {
//    return pow(256,0) * bytes[0] + pow(256,1) * bytes[1] + pow(256,2) * bytes[2] + pow(256,3) * bytes[3];
    return ((bytes[0] & 0xff) << 24) | ((bytes[1] & 0xff) << 16) | ((bytes[2] & 0xff) << 8) | (bytes[3] & 0xff);
//    return (int)ch[0] << (3 * bit) | (int)ch[1] << (2 * bit) | (int)ch[2] << bit | (int)ch[3];
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


Image *PNGImageLoader::load(std::ifstream &in)
{
    int indent = 4;
    char str[indent];
    in.read((char *)str, indent);
    std::string t = "";
    int width;
    int height;
    int number_bits;
    int color_type;
    std::vector<char> compressed_bytes;
    QMap<int, Pixel> palette;
    do
    {
        char length_str[4];
        in.read((char *)length_str, 4);
        char type[4];
        in.read((char *)type, 4);
        t = type;
        int length = bytes_to_int(length_str, 8);
        unsigned char data[length];
        in.read((char *)data, length);
        if (std::string(type) == "IHDR")
        {
            width = bytes_to_int((char*) data, 8);
            height = bytes_to_int((char*)data + 4, 8);
            number_bits = (int) data[8];
            color_type = (int)data[9];
        }
        if (std::string(type) == "IDAT")
        {
//            QByteArray compressed_bytes_(data);
//            QByteArray uncompressed_bytes = qGzipUncompress(compressed_bytes_);

            compressed_bytes.insert(compressed_bytes.end(), data, data + length);
        }
        if (std::string(type) == "PLTE" && color_type == 3)
        {
            for (int i = 0; i < length; i += 3)
            {
                Pixel current_pixel(data[i] / 255.0, data[i + 1] / 255.0, data[i + 2] / 255.0);
                palette.insert(i / 3, current_pixel);
            }
        }
        char sum_str[4];
        in.read((char *)sum_str, 4);
        unsigned long sum = (unsigned long)bytes_to_int(sum_str, 8);
//        QByteArray chunk = QByteArray(data);
//        chunk.append(type);
//        chunk.append(data);
        char chunk[length + 8];
        strcpy(chunk, length_str);
        strcat(chunk, type);
        strcat(chunk, (char*)data);
        int e = compressed_bytes.size();
        unsigned long crc = Crc32(reinterpret_cast<unsigned char*>(chunk), (unsigned long)(length + 8));
        unsigned int crc2 = CRC32_function((unsigned char*)chunk, (unsigned long)(length + 8));
        if (sum != crc){
//            throw std::logic_error(std::to_string(sum) + " " + std::to_string(crc));
        }
    } while(t != "IEND");
    QByteArray img = QByteArray(reinterpret_cast<const char*>(compressed_bytes.data()), compressed_bytes.size());
    QByteArray uncompressed_bytes = qGzipUncompress(img);

    uncompressed_bytes = removeEvery1280thByte(uncompressed_bytes);

    QByteArray test("testq");
    for (int i =0; i < 1000; i++){
        test.append("test1");
    }
    QByteArray comp = Compress(test);
    QByteArray uncomp = qGzipUncompress(comp);

    std::vector<Pixel> pixels;
//    for (int i = 0; i < uncompressed_bytes.size() - 2; i += 1){
//        if (i % 4096 ==0){
//            uncompressed_bytes.remove(i, 1);
//        }
//    }
    for (int i = 0; i < uncompressed_bytes.size() - 2; i += 3)
    {
//        if (i % 1280 == 0 || (i + 1) % 1280 == 0 || (i + 2) % 1280 == 0){
//            continue;
//        }
        Pixel current_pixel(((float)uncompressed_bytes[i] / 255.0), ((float)uncompressed_bytes[i + 1] / 255.0), ((float)uncompressed_bytes[i + 2]) / 255.0);
        pixels.push_back(current_pixel);
    }
//    throw std::logic_error(std::to_string(width * height) + " " + std::to_string(uncompressed_bytes.size()));
    return new Image(width, height, pixels);
}

