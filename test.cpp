#include <iostream>
#include "BMPhandler.h"
#include "brightnessfilter.h"
using namespace std;
 
int main()
{
  vector<vector<pixel>> pixels;
  BMPFileHeader fileheader;
  BMPInfoHeader infoheader;
  bool result=loadBMP("input.bmp",pixels,fileheader,infoheader);

  if(result)
  {
    cout<<"bmp opened successfully"<<endl;
     std::cout << "First pixel's Blue value: "
          << (int)pixels[0][0].blue << std::endl;

std::cout << "First pixel's Green value: "
          << (int)pixels[0][0].green << std::endl;

std::cout << "First pixel's Red value: "
          << (int)pixels[0][0].red << std::endl;
  }
  else{
    cout<<"could not open bmp"<<endl;
  }

  BrightnessFilter brightness(60);

brightness.apply(pixels);

std::cout << "Brightness filter applied!\n";

  if (saveBMP("bright_output.bmp", pixels, fileheader, infoheader))
{
    std::cout << "BMP saved successfully!\n";
}
else
{
    std::cout << "Failed to save BMP.\n";
}
    return 0;
}