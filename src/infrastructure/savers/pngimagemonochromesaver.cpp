#include "pngimagemonochromesaver.h"
#include<QByteArray>
#include <QtZlib/zlib.h>

pngimagemonochromesaver::pngimagemonochromesaver()
{

}

unsigned long crc_table2[256];
int crc_table_computed2 = 0;

void make_crc_table2()
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
        crc_table2[n] = c;
    }
    crc_table_computed2 = 1;
}

unsigned long update_crc2(unsigned long crc, unsigned char *buf, int len)
{
    unsigned long c = crc;
    int n;

    if (!crc_table_computed2)
        make_crc_table2();
    for (n = 0; n < len; n++) {
        c = crc_table2[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }
    return c;
}

unsigned long crc2(unsigned char *buf, int len)
{
    return update_crc2(0xffffffffL, buf, len) ^ 0xffffffffL;
}

QByteArray Compress2(QByteArray postBody)
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

void write_bytes2(QByteArray bytes, std::ofstream &out){
    for (int i = 0; i < bytes.size(); i++){
        out.write(&bytes[i], 1);
    }
}

void int_to_bytes2(int n, char* bytes, int bit = 8) {
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
}

void pngimagemonochromesaver::save(Image *image, std::ofstream &out, std::string dithering_type, int bytes_count){
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
        data_arr.append(image->pixels()[i].channels[0] * 255.0);
    }
    QByteArray compress_data = Compress2(data_arr);

    QByteArray chunk;
    chunk.append("IHDR");
    int_to_bytes2(image->width(), t);
    chunk.append(t, 4);
    int_to_bytes2(image->height(), t);
    chunk.append(t, 4);
    chunk.append((char)8);
    chunk.append((char)0);
    chunk.append((char)0);
    chunk.append((char)0);
    chunk.append((char)0);

    int_to_bytes2(13, t);
    out.write(t, 4);
    write_bytes2(chunk, out);
    int_to_bytes2(crc2((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes2(compress_data.size(), t);
    out.write(t, 4);
    chunk.append("IDAT");
    chunk.append(compress_data);
    write_bytes2(chunk, out);
    int_to_bytes2(crc2((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    chunk.clear();
    int_to_bytes2(0, t);
    out.write(t, 4);
    chunk.append("IEND");
    write_bytes2(chunk, out);
    int_to_bytes2(crc2((unsigned char*)chunk.data(), chunk.size()), t);
    out.write(t, 4);

    //    delete algorithm;
    //    delete [] data;
}
