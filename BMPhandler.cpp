#include "BMPHandler.h"
#include <fstream>
#include <iostream>
 using namespace std;

bool loadBMP(
    const string& filePath,
    vector<vector<pixel>>& pixels,
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

    file.read((char*)&infoHeader, sizeof(infoHeader));//reading info header


          if(fileHeader.filetype!=0X4D42){//check bmp type
        cout<<"input is not bmp file."<<endl;
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
    return true;
}