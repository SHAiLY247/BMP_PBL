#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>

#include "BMPHandler.h"
#include "brightnessfilter.h"
#include "contrastfilter.h"
#include "FilterPipeline.h"
#include "UndoStack.h"
#include "Threshold.h"
#include "CropRotate.h"
#include "RequestQueue.h"
#include "InversionFilter.h"
#include "SepiaFilter.h"
#include "RGBFilter.h"
#include "RegionAnalysis.h"

using namespace std;

int main() {
    vector<vector<pixel>> pixels;
    BMPFileHeader fileHeader{};
    BMPInfoHeader infoHeader{};
    UndoStack undoStack(5);
    RequestQueue requestQueue;
    bool imageLoaded = false;
    string filename;

    int choice;

    while (true) {
        cout<< "\n===============================================\n";
        cout<< "   BMP IMAGE PROCESSING AND PIXEL ANALYSIS\n";
        cout<< "===============================================\n";
        cout<< "1. Load BMP Image\n";
        cout<< "2. Apply Filter\n";
        cout<< "3. Undo Last Operation\n";
        cout<< "4. Threshold Image\n";
        cout<< "5. Crop Image\n ";
        cout<< "6. Rotate Image\n";
        cout<< "7. Pixel Region Analysis\n";
        cout<< "8. Save Image\n";
        cout<< "9. Exit\n";
        cout<< "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 9) {
            cout << "Exiting program.\n";
            break;
        }

        if (choice == 1) {
            cout << "Enter BMP filename (e.g. input.bmp): ";
            cin >> filename;

            if (loadBMP(filename, pixels, fileHeader, infoHeader)) {
                imageLoaded = true;
                undoStack.clear();
                cout << "BMP loaded successfully!\n";
                cout << "Width: " << infoHeader.width
                     << ", Height: " << infoHeader.height << '\n';
            } else {
                cout << "Could not load BMP. Check filename and format.\n";
            }
        }
        else if (choice == 2) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
                continue;
            }

            cout << "\n1. Brightness\n";
            cout << "2. Contrast\n";
            cout << "3. Inversion\n";
            cout << "4. Sepia\n";
            cout << "5. RGB Channel\n";
            cout << "6. Back\n";
            cout << "Choose filter: ";

            int filterChoice;
            if (!(cin >> filterChoice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (filterChoice == 1) {
                int amount;
                cout << "Brightness amount (-255 to 255): ";
                if (!(cin >> amount) || amount < -255 || amount > 255) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid brightness amount.\n";
                    continue;
                }

                undoStack.pushState(pixels,infoHeader);
                BrightnessFilter filter(amount);
                FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels);
                cout << "Brightness applied.\n";
            }
            else if (filterChoice == 2) {
                double factor;
                cout << "Contrast factor (e.g. 1.2): ";
                if (!(cin >> factor) || factor < 0 || factor > 10) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid contrast factor.\n";
                    continue;
                }

               undoStack.pushState(pixels, infoHeader);
                ContrastFilter filter(factor);
                FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels);
                cout << "Contrast applied.\n";
            }
            else if (filterChoice == 3) {
            undoStack.pushState(pixels, infoHeader);
            InversionFilter filter;
            FilterPipeline pipeline;
            pipeline.addFilter(&filter);
            pipeline.executePipeline(pixels);

            cout << "Inversion applied successfully.\n";
              }
            else if (filterChoice == 4) {
              undoStack.pushState(pixels, infoHeader);
               SepiaFilter filter;
               FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels); 
               cout << "Sepia filter applied successfully.\n";
              }
              else if (filterChoice == 5)
{
    int channelChoice;

    cout << "\n1. Red Channel\n";
    cout << "2. Green Channel\n";
    cout << "3. Blue Channel\n";
    cout << "Choose channel: ";

    if (!(cin >> channelChoice) ||
        channelChoice < 1 || channelChoice > 3)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid channel choice.\n";
        continue;
    }

    undoStack.pushState(pixels,infoHeader);

    Channel channel;

    if (channelChoice == 1)
        channel = Channel::Red;
    else if (channelChoice == 2)
        channel = Channel::Green;
    else
        channel = Channel::Blue;

    RGBFilter filter(channel);
    FilterPipeline pipeline;
    pipeline.addFilter(&filter);
    pipeline.executePipeline(pixels);

    cout << "RGB channel applied successfully.\n";
}
    }
        else if (choice == 3) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
            }
            else if (undoStack.popState(pixels,infoHeader)) {
                cout << "Undo successful.\n";
            }
            else {
                cout << "Nothing to undo.\n";
            }
        }
        else if (choice == 4) 
        {
          if (!imageLoaded) {
          cout << "Load an image first.\n";
          continue;
         }

        int thresholdValue;

         cout << "Enter threshold (0-255): ";

         if (!(cin >> thresholdValue) ||
        thresholdValue < 0 ||
        thresholdValue > 255) {

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );

        cout << "Invalid threshold. Enter a value from 0 to 255.\n";
        continue;
    }

        undoStack.pushState(pixels, infoHeader);

        Threshold thresholdFilter(thresholdValue);
        thresholdFilter.apply(pixels);

         cout << "Thresholding applied successfully!\n";
     }
        else if (choice == 5) {
    if (!imageLoaded) {
        cout << "Load an image first.\n";
        continue;
    }

    int startRow, startCol, cropWidth, cropHeight;

    cout << "Enter starting row: ";
    cin >> startRow;

    cout << "Enter starting column: ";
    cin >> startCol;

    cout << "Enter crop width: ";
    cin >> cropWidth;

    cout << "Enter crop height: ";
    cin >> cropHeight;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        continue;
    }

    vector<vector<pixel>> oldPixels = pixels;
BMPInfoHeader oldInfoHeader = infoHeader;

if (cropImage(pixels, infoHeader,
              startRow, startCol,
              cropWidth, cropHeight)) {

    undoStack.pushState(oldPixels, oldInfoHeader);

    cout << "Crop operation completed.\n";
}
}
else if (choice == 6) {
    if (!imageLoaded) {
        cout << "Load an image first.\n";
        continue;
    }

    int rotationChoice;

    cout << "\n1. Rotate 90 degrees clockwise\n";
    cout << "2. Rotate 90 degrees anticlockwise\n";
    cout << "3. Rotate 180 degrees\n";
    cout << "Choose rotation: ";

    if (!(cin >> rotationChoice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        continue;
    }

   vector<vector<pixel>> oldPixels = pixels;
BMPInfoHeader oldInfoHeader = infoHeader;

if (rotateImage(pixels, infoHeader, rotationChoice)) {

    undoStack.pushState(oldPixels, oldInfoHeader);
}
}
 
        else if (choice == 7) {
            if (!imageLoaded) {
        cout << "Load an image first.\n";
        continue;
    }

    analyzeRegions(pixels);
        }
        else if (choice == 8) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
                continue;
            }

            string output;
            cout << "Enter output filename (e.g. output.bmp): ";
            cin >> output;

            if (saveBMP(output, pixels, fileHeader, infoHeader)) {
                cout << "Image saved to " << output << '\n';
            } else {
                cout << "Failed to save image.\n";
            }
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}