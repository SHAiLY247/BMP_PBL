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

using namespace std;

int main() {
    vector<vector<pixel>> pixels;
    BMPFileHeader fileHeader{};
    BMPInfoHeader infoHeader{};
    UndoStack undoStack(5);

    bool imageLoaded = false;
    string filename;

    int choice;

    while (true) {
        cout << "\n===============================================\n";
        cout << "   BMP IMAGE PROCESSING AND PIXEL ANALYSIS\n";
        cout << "===============================================\n";
        cout << "1. Load BMP Image\n";
        cout << "2. Apply Filter\n";
        cout << "3. Undo Last Operation\n";
        cout << "4. Threshold Image\n";
        cout << "5. Analyze Pixel Regions (Phase III)\n";
        cout << "6. Save Image\n";
        cout << "7. Exit\n";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 7) {
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
            cout << "3. Back\n";
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

                undoStack.pushState(pixels);
                BrightnessFilter filter(amount);
                FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels);
                cout << "Brightness applied.\n";
            }
            else if (filterChoice == 2) {
                double factor;
                cout << "Contrast factor (0 < Contrast Factor < 2): ";
                if (!(cin >> factor) || factor < 0 || factor > 10) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid contrast factor.\n";
                    continue;
                }

                undoStack.pushState(pixels);
                ContrastFilter filter(factor);
                FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels);
                cout << "Contrast applied.\n";
            }
        }
        else if (choice == 3) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
            }
            else if (undoStack.popState(pixels)) {
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

        undoStack.pushState(pixels);

        Threshold thresholdFilter(thresholdValue);
        thresholdFilter.apply(pixels);

         cout << "Thresholding applied successfully!\n";
     }
        else if (choice == 5) {
            cout << "Region analysis is planned for Phase III.\n";
        }
        else if (choice == 6) {
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