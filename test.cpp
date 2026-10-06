#include <iostream>
#include "BMPhandler.h"
using namespace std;
 
int main()
{
    pixel p;
    p.red=255;
    p.blue=0;
    p.green=0;

    cout<<"pixel created succesfully "<<endl;
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    cout<<"Bmp structures created successfully";
    return 0;
}