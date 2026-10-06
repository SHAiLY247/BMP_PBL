#include <iostream>
#include "BMPhandler.h"
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

  }
  else{
    cout<<"could not open bmp"<<endl;
  }
    return 0;
}