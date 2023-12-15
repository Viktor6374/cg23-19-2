#include "pngimagesaver.h"
#include<QByteArray>
#include <QtZlib/zlib.h>

pngimagesaver::pngimagesaver()
{

}

unsigned long crc_table1[256];
int crc_table_computed1 = 0;

void make_crc_table1()
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
        crc_table1[n] = c;
    }
    crc_table_computed1 = 1;
}

unsigned long update_crc1(unsigned long crc, unsigned char *buf, int len)
{
    unsigned long c = crc;
    int n;

    if (!crc_table_computed1)
        make_crc_table1();
    for (n = 0; n < len; n++) {
        c = crc_table1[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}

unsigned long crc1(unsigned char *buf, int len)
{
    return update_crc1(0xffffffffL, buf, len) ^ 0xffffffffL;
}

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

void write_bytes(QByteArray bytes, std::ofstream &out){
    for (int i = 0; i < bytes.size(); i++){
        out.write(&bytes[i], 1);
    }
}

void int_to_bytes(int n, char* bytes, int bit = 8) {
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
}

void pngimagesaver::save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count){
    unsigned char signature[8] {137, 80, 78, 71, 13, 10, 26, 10};
    out.write((char *) signature, 8);

//    auto algorithm = _dithering_algorithm_factory->create(dithering_type);
//    char *data = (char*)algorithm->execute(image, bytes_count);

    char t[4];

    QByteArray data_arr;
    for (int i = 0; i < image->pixels().size(); i++){
        if (i % image->width() == 0){
            data_arr.append((char)0);
        }
        for (int j = 0; j < 3; j++){
            data_arr.append(image->pixels()[i].channels[j] * 255.0);
        }
    }
    QByteArray compress_data = Compress(data_arr);

    QByteArray chunk;
    chunk.append("IHDR");
    int_to_bytes(image->width(), t);
    chunk.append(t, 4);
    int_to_bytes(image->height(), t);
    chunk.append(t, 4);
    chunk.append((char)8);
    chunk.append((char)2);
    chunk.append((char)0);
    chunk.append((char)0);
    chunk.append((char)0);

    int_to_bytes(13, t);
    out.write(t, 4);
    write_bytes(chunk, out);
    int_to_bytes(crc1((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes(1, t);
    out.write(t, 4);
    chunk.append("sRGB");
    chunk.append((char)0);
    write_bytes(chunk, out);
    int_to_bytes(crc1((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes(4, t);
    out.write(t, 4);
    chunk.append("gAMA");
    unsigned char d[4] {0, 0, 177, 143};
    chunk.append((char*) d, 4);
    write_bytes(chunk, out);
    int_to_bytes(crc1((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes(9, t);
    out.write(t, 4);
    chunk.append("pHYs");
    unsigned char e[9] {0, 0, 14, 195, 0, 0, 14, 195, 1};
    chunk.append((char*) e, 9);
    write_bytes(chunk, out);
    int_to_bytes(crc1((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes(compress_data.size(), t);
    out.write(t, 4);
    chunk.append("IDAT");
    chunk.append(compress_data);
    write_bytes(chunk, out);
    int_to_bytes(crc1((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes(0, t);
    out.write(t, 4);
    chunk.append("IEND");
    write_bytes(chunk, out);
    int_to_bytes(crc1((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

//    delete algorithm;
//    delete [] data;
}

