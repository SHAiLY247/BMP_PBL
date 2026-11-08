#include <iostream>
#include "BMPhandler.h"
#include "brightnessfilter.h"
#include "contrastfilter.h"
#include "InversionFilter.h"
#include "grayscalefilter.h"
#include "SepiaFilter.h"
#include "RGBFilter.h"
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

/*BrightnessFilter brightness(60);
brightness.apply(pixels);
std::cout << "Brightness filter applied!\n";

ContrastFilter contrast(2.5);
contrast.apply(pixels);
std::cout << "Contrast filter applied!\n";

GrayscaleFilter grayscale;
grayscale.apply(pixels);

InversionFilter inversion;
inversion.apply(pixels);

SepiaFilter sepia;
sepia.apply(pixels);
*/
RGBFilter redFilter(Channel::Red);
redFilter.apply(pixels);
saveBMP("red_channel.bmp", pixels, fileheader, infoheader);
std::cout << "rgb red channel applied!\n";

  if (saveBMP("red_channel.bmp", pixels, fileheader, infoheader))
{
    std::cout << "BMP saved successfully!\n";
}
else
{
    std::cout << "Failed to save BMP.\n";
}
loadBMP("input.bmp",pixels,fileheader,infoheader);
RGBFilter blueFilter(Channel::Blue);
blueFilter.apply(pixels);
saveBMP("blue_channel.bmp", pixels, fileheader, infoheader);
std::cout << "rgb blue channel applied!\n";

  if (saveBMP("blue_channel.bmp", pixels, fileheader, infoheader))
{
    std::cout << "BMP saved successfully!\n";
}
else
{
    std::cout << "Failed to save BMP.\n";
}
loadBMP("input.bmp",pixels,fileheader,infoheader);
RGBFilter greenFilter(Channel::Green);
greenFilter.apply(pixels);
saveBMP("green_channel.bmp", pixels, fileheader, infoheader);
std::cout << "rgb green channel applied!\n";

  if (saveBMP("green_channel.bmp", pixels, fileheader, infoheader))
{
    std::cout << "BMP saved successfully!\n";
}
else
{
    std::cout << "Failed to save BMP.\n";
}
    return 0;
}