#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <vector>
#include <cstdlib>

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
#include "grayscalefilter.h"
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
        cout << "\n===============================================\n";
        cout << "   BMP IMAGE PROCESSING AND PIXEL ANALYSIS\n";
        cout << "===============================================\n";
        cout << "1. Load BMP Image\n";
        cout << "2. Apply Filter\n";
        cout << "3. Undo Last Operation\n";
        cout << "4. Threshold Image\n";
        cout << "5. Crop Image\n";
        cout << "6. Rotate Image\n";
        cout << "7. Pixel Region Analysis\n";
        cout << "8. Save Image\n";
        cout << "9. Exit\n";
        cout << "\nEnter your choice: ";

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
                     << ", Height: " << abs(infoHeader.height) << '\n';
            }
            else {
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
            cout << "6. Grayscale\n";
            cout << "7. Back\n";
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

                undoStack.pushState(pixels, infoHeader);
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
            else if (filterChoice == 5) {
                int channelChoice;

                cout << "\n1. Red Channel\n";
                cout << "2. Green Channel\n";
                cout << "3. Blue Channel\n";
                cout << "Choose channel: ";

                if (!(cin >> channelChoice) || channelChoice < 1 || channelChoice > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid channel choice.\n";
                    continue;
                }

                undoStack.pushState(pixels, infoHeader);

                Channel channel;
                if (channelChoice == 1) {
                    channel = Channel::Red;
                }
                else if (channelChoice == 2) {
                    channel = Channel::Green;
                }
                else {
                    channel = Channel::Blue;
                }

                RGBFilter filter(channel);
                FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels);
                cout << "RGB channel applied successfully.\n";
            }
            else if (filterChoice == 6) {
                undoStack.pushState(pixels, infoHeader);
                GrayscaleFilter filter;
                FilterPipeline pipeline;
                pipeline.addFilter(&filter);
                pipeline.executePipeline(pixels);
                cout << "Grayscale filter applied successfully.\n";
            }
            else if (filterChoice != 7) {
                cout << "Invalid filter choice.\n";
            }
        }
        else if (choice == 3) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
            }
            else if (undoStack.popState(pixels, infoHeader)) {
                cout << "Undo successful. Current size: "
                     << infoHeader.width << "x" << abs(infoHeader.height) << '\n';
            }
            else {
                cout << "Nothing to undo.\n";
            }
        }
        else if (choice == 4) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
                continue;
            }

            int thresholdValue;
            cout << "Enter threshold (0-255): ";

            if (!(cin >> thresholdValue) || thresholdValue < 0 || thresholdValue > 255) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

            int imgHeight = static_cast<int>(pixels.size());
            int imgWidth = static_cast<int>(pixels[0].size());

            cout << "\n--- CROP IMAGE ---\n";
            cout << "Current Dimensions: " << imgWidth << " px (width) x " << imgHeight << " px (height)\n";
            cout << "1. Center Crop (Specify target width & height)\n";
            cout << "2. Trim Margins (Remove pixels from Top, Bottom, Left, Right)\n";
            cout << "3. Percentage Crop (Crop using % of width & height)\n";
            cout << "4. Exact Coordinates (Top-Left X, Y, Width, Height)\n";
            cout << "Choose crop method (1-4): ";

            int cropMode;
            if (!(cin >> cropMode)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\n";
                continue;
            }

            int startRow = 0, startCol = 0, cropWidth = 0, cropHeight = 0;

            if (cropMode == 1) {
                cout << "Enter target width (max " << imgWidth << "): ";
                cin >> cropWidth;
                cout << "Enter target height (max " << imgHeight << "): ";
                cin >> cropHeight;

                startCol = (imgWidth - cropWidth) / 2;
                startRow = (imgHeight - cropHeight) / 2;
            }
            else if (cropMode == 2) {
                int top, bottom, left, right;
                cout << "Pixels to trim from TOP: ";
                cin >> top;
                cout << "Pixels to trim from BOTTOM: ";
                cin >> bottom;
                cout << "Pixels to trim from LEFT: ";
                cin >> left;
                cout << "Pixels to trim from RIGHT: ";
                cin >> right;

                if (cin.fail() || top < 0 || bottom < 0 || left < 0 || right < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid margin values. Margins must be 0 or positive.\n";
                    continue;
                }

                startRow = top;
                startCol = left;
                cropWidth = imgWidth - left - right;
                cropHeight = imgHeight - top - bottom;
            }
            else if (cropMode == 3) {
                double leftPct, topPct, widthPct, heightPct;
                cout << "Left offset % (0 to 99): ";
                cin >> leftPct;
                cout << "Top offset % (0 to 99): ";
                cin >> topPct;
                cout << "Target width % (1 to 100): ";
                cin >> widthPct;
                cout << "Target height % (1 to 100): ";
                cin >> heightPct;

                startCol = static_cast<int>((leftPct / 100.0) * imgWidth);
                startRow = static_cast<int>((topPct / 100.0) * imgHeight);
                cropWidth = static_cast<int>((widthPct / 100.0) * imgWidth);
                cropHeight = static_cast<int>((heightPct / 100.0) * imgHeight);
            }
            else if (cropMode == 4) {
                cout << "Enter starting X / column from left (0 to " << imgWidth - 1 << "): ";
                cin >> startCol;
                cout << "Enter starting Y / row from top (0 to " << imgHeight - 1 << "): ";
                cin >> startRow;
                cout << "Enter crop width: ";
                cin >> cropWidth;
                cout << "Enter crop height: ";
                cin >> cropHeight;
            }
            else {
                cout << "Invalid crop method.\n";
                continue;
            }

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid numeric input.\n";
                continue;
            }

            vector<vector<pixel>> oldPixels = pixels;
            BMPInfoHeader oldInfoHeader = infoHeader;

            if (cropImage(pixels, infoHeader, startRow, startCol, cropWidth, cropHeight)) {
                undoStack.pushState(oldPixels, oldInfoHeader);
                cout << "Image cropped successfully! New size: "
                     << infoHeader.width << "x" << abs(infoHeader.height) << '\n';
            }
            else {
                cout << "Crop failed: Selected region (" << cropWidth << "x" << cropHeight
                     << " at X=" << startCol << ", Y=" << startRow
                     << ") is out of bounds (" << imgWidth << "x" << imgHeight << ").\n";
            }
        }
        else if (choice == 6) {
            if (!imageLoaded) {
                cout << "Load an image first.\n";
                continue;
            }

            int rotationChoice;

            cout << "\n--- ROTATE IMAGE ---\n";
            cout << "Current Dimensions: " << infoHeader.width << "x" << abs(infoHeader.height) << '\n';
            cout << "1. Rotate 90 degrees clockwise\n";
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
                cout << "Image rotated successfully! New size: "
                     << infoHeader.width << "x" << abs(infoHeader.height) << '\n';
            }
            else {
                cout << "Rotation failed: Invalid rotation choice.\n";
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
            }
            else {
                cout << "Failed to save image.\n";
            }
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}