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
    if (!data.data()) {
        qWarning("qGzipUncompress: Data is null");
        return QByteArray();
    }

    // Инициализировать структуру потока
    z_stream unGzipStream;
    unGzipStream.next_in = (z_Bytef*) data.data (); // введите начальный адрес байта
    unGzipStream.avail_in = data.size (); // введите размер байта
    unGzipStream.zalloc = Z_NULL;
    unGzipStream.zfree = Z_NULL;
    unGzipStream.opaque = Z_NULL;
        // Инициировать состояние внутреннего потока
    int ret = inflateInit2(&unGzipStream,16);
    if(ret != Z_OK)
    {
        qWarning("qGzipUncompress: The call to inflateInit2 returns the wrong value");
        return QByteArray();
    }

    unsigned char buffer[4096];
    QByteArray gzipUnomprData;
        // Используйте буферный цикл 4MB для получения данных и добавить полученные данные в Uncprdata, пока полученные данные не станут пустыми для пустых
    do
    {
        unGzipStream.avail_out = 4096; // Получить размер области буфера декомпрессии данных
        unGzipStream.next_out = buffer; // получение начального адреса зоны буфера данных декомпрессии
        memset(buffer,0,4096);
            // Delax Data
        ret = inflate(&unGzipStream,Z_NO_FLUSH);
        switch(ret)
        {
        case Z_MEM_ERROR:
            qWarning("qGzipUncompress: Z_DATA_ERROR: Not enough memory");
            return QByteArray();
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;
        case Z_DATA_ERROR:
            qWarning("qGzipUncompress: Z_DATA_ERROR: Input data is corrupted");
            return QByteArray();
        }
        if(ret != Z_FINISH)
        {
            gzipUnomprData.append((char*)buffer);
        }
    }while(unGzipStream.avail_out == 0);
    return gzipUnomprData;
}

QByteArray UnCompress(QByteArray src)
{
    QByteArray outBuffer;
    z_stream strm;
    strm.zalloc = NULL;
    strm.zfree = NULL;
    strm.opaque = NULL;

    strm.avail_in = src.size();
    strm.next_in = (Bytef *)src.data();

    int err = -1, ret = -1;
    err = inflateInit2(&strm, MAX_WBITS + 16);
    if (err == Z_OK) {
        while (true)
        {
            char buffer[4096] = { 0 };
            strm.avail_out = 4096;
            strm.next_out = (Bytef *)buffer;
            int code = inflate(&strm, Z_FINISH);
            outBuffer.append(buffer, 4096 - strm.avail_out);
            if (Z_STREAM_END == code || Z_OK != code)
            {
                break;
            }
        }
    }
    inflateEnd(&strm);
    return outBuffer;
}

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
        char data[length];
        in.read((char *)data, length);
        if (std::string(type) == "IHDR")
        {
            width = bytes_to_int(data, 8);
            height = bytes_to_int(data + 4, 8);
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
        strcat(chunk, data);
        int e = compressed_bytes.size();
        unsigned long crc = Crc32(reinterpret_cast<unsigned char*>(chunk), (unsigned long)(length + 8));
        unsigned int crc2 = CRC32_function((unsigned char*)chunk, (unsigned long)(length + 8));
        if (sum != crc){
//            throw std::logic_error(std::to_string(sum) + " " + std::to_string(crc));
        }
    } while(t != "IEND");
//    QByteArray img = QByteArray(reinterpret_cast<const char*>(compressed_bytes.data()), compressed_bytes.size());
//    QByteArray uncompressed_bytes = qGzipUncompress(img);

    std::vector<Pixel> pixels;
    for (int i = 0; i < compressed_bytes.size(); i += 3)
    {
        Pixel current_pixel(compressed_bytes[i] / 255.0, compressed_bytes[i + 1] / 255.0, compressed_bytes[i + 2] / 255.0);
        pixels.push_back(current_pixel);
    }
    throw std::logic_error(std::to_string(width * height) + " " + std::to_string(pixels.size()));
    return new Image(width, height, pixels);
}

