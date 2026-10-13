#include "BMPHandler.h"
#include <fstream>
#include <iostream>
 using namespace std;

bool loadBMP(
    const std:: string& filePath,
    std::vector<std::vector<pixel>>& pixels,
    BMPFileHeader& fileHeader,
    BMPInfoHeader& infoHeader
)
{
    ifstream file(filePath, std::ios::binary);

    if (!file)
    {
        cout << "Could not open the BMP file.\n";
        return false;
    }

    file.read((char*)&fileHeader, sizeof(fileHeader));//reading fileheader
          if (!file)
{
    std::cout << "Error reading BMP file header.\n";
    return false;
}
    file.read((char*)&infoHeader, sizeof(infoHeader));//reading info header
if (!file)
{
    std::cout << "Error reading BMP info header.\n";
    return false;
}

          if(fileHeader.filetype!=0X4D42){//check bmp type
        cout<<"input is not bmp file."<<endl;
        return false;
     }
    
     if (infoHeader.headersize!= 40)
{
    std::cout << "Unsupported BMP information header.\n";
    return false;
}
    if(infoHeader.bitsperpixel!=24)//check bit
    {
        cout<<" only 24 bit bmp file is supported"<<endl;
        return false;
    }
    if (infoHeader.compression!= 0)//check compression
    {
    cout << "Compressed BMP files are not supported.\n";
    return false; 
     } 

        if (infoHeader.width <= 0 || infoHeader.height == 0)
{
    std::cout << "Invalid BMP dimensions.\n";
    return false;
}
     int width=infoHeader.width;
     int height=infoHeader.height;


    bool topDown = (height < 0);

     if (height < 0)
    {
      height = -height;
     }  

    int rowSize=width*3;
     int padding=(4-(rowSize%4))%4;

      cout << "Row size: " << rowSize << " bytes" << std::endl;
     cout << "Padding per row: " << padding << " bytes" << std::endl;

     pixels.resize(height, std::vector<pixel>(width));
     file.seekg(fileHeader.pixeloffsize, std::ios::beg);
     if (!file)
{
    std::cout << "Error accessing pixel data.\n";
    return false;
}

     for (int row = 0; row < height; row++)
{
    int pixelRow;
    if (topDown)
      {
    pixelRow = row;
        }
     else
      {
    pixelRow = height - 1 - row;
          }
    for (int col = 0; col < width; col++)
    {
        file.read((char*)&pixels[pixelRow][col], sizeof(pixel));
            if (!file)
    {
        std::cout << "Error reading pixel data.\n";
        return false;
    }

    }
    file.ignore(padding);

}
    return true;
}
bool saveBMP(
    const std::string& filePath,
    const std::vector<std::vector<pixel>>& pixels,
    BMPFileHeader fileHeader,
    BMPInfoHeader infoHeader
)
{
    std::ofstream file(filePath, std::ios::binary);

    if (!file)
    {
        std::cout << "Could not create the BMP file.\n";
        return false;
    }
    int width = infoHeader.width;
int height = infoHeader.height;

if (height < 0)
{
    height = -height;
}

int rowSize = width * 3;
int padding = (4 - (rowSize % 4)) % 4;

unsigned int imageSize = (rowSize + padding) * height;

infoHeader.imagesize = imageSize;
fileHeader.filesize = fileHeader.pixeloffsize + imageSize;
    file.write((char*)&fileHeader, sizeof(fileHeader));

file.write((char*)&infoHeader, sizeof(infoHeader));

if (!file)
{
    std::cout << "Error writing BMP headers.\n";
    return false;
}

    for (int row = 0; row < height; row++)
{
    int pixelRow;

    if (infoHeader.height < 0)
    {
        pixelRow = row;
    }
    else
    {
        pixelRow = height - 1 - row;
    }

    for (int col = 0; col < width; col++)
    {
        file.write((char*)&pixels[pixelRow][col], sizeof(pixel));
    }

    for (int i = 0; i < padding; i++)
    {
        file.put(0);
    }
}

if (!file)
{
    std::cout << "Error writing BMP pixel data.\n";
    return false;
}

return true;
}