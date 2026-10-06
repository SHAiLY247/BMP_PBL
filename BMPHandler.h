#ifndef BMPHANDLER_H
#define BMPHANDLER_H
#include <string>
#include <vector>
#pragma pack (push,1)

struct BMPFileHeader{
    unsigned short filetype;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixeloffsize;
};

struct BMPInfoHeader{
    unsigned int headersize;
     int width;
     int height;
     unsigned short planes;
     unsigned short bitsperpixel;
     unsigned int compression;
    unsigned int imagesize;
     int hori_resolution;
     int ver_resolution;
     unsigned int colorsused;
     unsigned int impcolors;

};

#pragma pack(pop)

struct pixel{
     unsigned char red;
     unsigned char blue;
     unsigned char green;
};

bool loadBMP(const std::string& filePath, std::vector<std::vector<pixel>>& pixels, BMPFileHeader& fileHeader,BMPInfoHeader& infoHeader);

#endif