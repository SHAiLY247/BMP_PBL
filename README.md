# BMP Image Processing and Pixel Analysis System

A modular, dependency-free **24-bit BMP Image Processor** built from scratch in **C++** using Object-Oriented Programming (OOP) and Data Structures & Algorithms (DSA). Developed for the **Project-Based Learning (PBL) Phase-III Evaluation** (`Team ID: DSCPP-III-2026-T150`) at the Department of Computer Science & Engineering, **Graphic Era (Deemed to be University), Dehradun**.

---

## Key Features

### 1. Raw 24-bit BMP File I/O
* Parses and writes uncompressed 24-bit `.bmp` files directly from raw binary headers (`BITMAPFILEHEADER` & `BITMAPINFOHEADER`).
* Automatically calculates row byte size and 4-byte row padding on load and save.
* Validates file existence, format signature, and bit depth before processing.

### 2. Polymorphic Image Filters
* **Brightness Adjustment** – Shifts pixel intensity values (`-255` to `+255`) with clamping (`0–255`).
* **Contrast Adjustment** – Scales pixel intensity around the midpoint for sharper or softer contrast.
* **Color Inversion** – Generates photo-negative images (`255 - channel`).
* **Sepia Tone** – Applies warm vintage color-matrix transformations.
* **RGB Channel Isolation** – Isolates individual Red, Green, or Blue channels.
* **Grayscale** – Converts 24-bit RGB pixels into luminance-weighted monochrome values (`0.299R + 0.587G + 0.114B`).
* **Thresholding / Binarization** – Converts pixels into pure black (`0,0,0`) or white (`255,255,255`) based on a `0–255` threshold value.

### 3. Geometric Transformations
* **Crop Image** – Supports 4 cropping modes with automatic header dimension updates:
  1. Center Crop (specify target width & height)
  2. Trim Margins (remove pixels from top, bottom, left, right)
  3. Percentage Crop (crop using % of width & height)
  4. Exact Coordinates (top-left `X, Y`, width & height)
* **Rotate Image** – Supports `90°` clockwise, `90°` anticlockwise, and `180°` rotations.

### 4. DSA-Powered State & Batch Management
* **Filter Pipeline (`FilterPipeline`)** – Polymorphic execution pipeline built on an abstract `Filter` base class.
* **Undo Stack (`UndoStack`)** – LIFO stack storing previous pixel matrices and headers to revert operations cleanly.
* **Batch Request Queue (`RequestQueue`)** – Linked-list FIFO queue (`enqueue`, `dequeue`, `isEmpty`, `clear`) that lets users queue multi-step image processing jobs (`ProcessingJob`) and execute them sequentially.

### 5. Graph-Based Pixel Region Analysis
* Treats a thresholded/binarized image as a 2D pixel grid and counts distinct 4-connected foreground regions.
* Supports two selectable graph traversal algorithms:
  * **Breadth-First Search (BFS)** using `std::queue`
  * **Iterative Depth-First Search (DFS)** using `std::stack` (prevents call-stack overflow on high-resolution images)

---

## Project Structure

```text
BMP_PBL/
├── main.cpp                   # Interactive CLI menu, batch runner & module integration
├── BMPHandler.h / .cpp        # 24-bit BMP binary file reader/writer & pixel struct
├── filter.h                   # Abstract base Filter class
├── FilterPipeline.h / .cpp    # Polymorphic filter execution pipeline
├── brightnessfilter.h / .cpp  # Brightness filter
├── contrastfilter.h / .cpp    # Contrast filter
├── grayscalefilter.h / .cpp   # Luminance grayscale filter
├── InversionFilter.h / .cpp   # Color inversion filter
├── SepiaFilter.h / .cpp       # Sepia tone filter
├── RGBFilter.h / .cpp         # Red / Green / Blue channel filter
├── Threshold.h / .cpp         # Binary thresholding filter
├── CropRotate.h / .cpp        # 4-mode cropping & 90°/180° rotation
├── UndoStack.h / .cpp         # Stack-based undo state manager
├── RequestQueue.h / .cpp      # Linked-list FIFO batch job queue
├── RegionAnalysis.h / .cpp    # Connected-component analysis (BFS & Iterative DFS)
├── input.bmp                  # Sample 24-bit BMP test image
├── input2coffee.bmp           # Sample 24-bit BMP test image
├── command.txt                # Quick copy-paste build & run commands
└── pblreport.pdf              # Project documentation report
```

---

## How to Build & Run

### Prerequisites
* A C++ compiler supporting C++11 or later (e.g., **MinGW-w64 / GCC `g++`** on Windows, or `g++` on Linux/macOS).
* A valid uncompressed **24-bit `.bmp`** image in the project root (such as the included `input.bmp`).

### Step 1: Clone the Repository
```bash
git clone [https://github.com/SHAiLY247/BMP_PBL.git](https://github.com/SHAiLY247/BMP_PBL.git)
cd BMP_PBL
```

### Step 2: Compile & Run

**Standard Command:**
```bash
g++ main.cpp BMPHandler.cpp brightnessfilter.cpp contrastfilter.cpp CropRotate.cpp FilterPipeline.cpp grayscalefilter.cpp InversionFilter.cpp RegionAnalysis.cpp RequestQueue.cpp RGBFilter.cpp SepiaFilter.cpp Threshold.cpp UndoStack.cpp -o app.exe && app.exe
```

**Windows Defender Fallback (if compiling inside `C:\...\Documents` triggers an antivirus/permission block):**
```bash
g++ main.cpp BMPHandler.cpp brightnessfilter.cpp contrastfilter.cpp CropRotate.cpp FilterPipeline.cpp grayscalefilter.cpp InversionFilter.cpp RegionAnalysis.cpp RequestQueue.cpp RGBFilter.cpp SepiaFilter.cpp Threshold.cpp UndoStack.cpp -o D:\app.exe && D:\app.exe
```

*(Note: On Linux/macOS, replace `app.exe` with `./app`.)*

---

## CLI Usage Guide

Launch the executable to access the main menu:

```text
===============================================
   BMP IMAGE PROCESSING AND PIXEL ANALYSIS
===============================================
1. Load BMP Image
2. Apply Filter
3. Undo Last Operation
4. Threshold Image
5. Crop Image
6. Rotate Image
7. Pixel Region Analysis
8. Save Image
9. Batch Processing (Request Queue)
10. Exit
```

### Walkthrough
1. **Load an Image (`1`):** Enter a 24-bit BMP filename (e.g., `input.bmp`). Dimensions, row size, and padding are displayed automatically.
2. **Apply Filters (`2`):** Choose from:
   * `1. Brightness`
   * `2. Contrast`
   * `3. Inversion`
   * `4. Sepia`
   * `5. RGB Channel` *(Red, Green, or Blue)*
   * `6. Grayscale`
   * `7. Back`
3. **Undo (`3`):** Reverts the image (and dimensions, if cropped/rotated) to its previous state.
4. **Crop (`5`) & Rotate (`6`):** Select your preferred crop mode (`1–4`) or rotation angle (`90° CW`, `90° CCW`, `180°`).
5. **Pixel Region Analysis (`7`):**
   * First apply **Option `4` (Threshold Image)** to binarize the loaded image in memory.
   * Immediately select **Option `7` (Pixel Region Analysis)** and choose either:
     * `1. Analyze using BFS (Queue-based)`
     * `2. Analyze using DFS (Iterative Stack-based)`
   * Outputs the total number of distinct connected foreground regions detected.
6. **Save Image (`8`):** Enter an output filename (e.g., `output.bmp`) to write the modified image to disk.
7. **Batch Processing (`9`):**
   * Select `1. Add Batch Job (Enqueue)` to specify an input `.bmp`, output `.bmp`, and a chain of operations (`1–9`, ending with `0`).
   * Repeat to queue multiple jobs, then select `2. Process All Queued Jobs (Dequeue FIFO)` to execute and save every job in exact FIFO order.

---

## Team Contributions & Branching

**Mentor:** Mr. Himanshu Mainwal

| Member | Enrollment No. | Branch | Role | Core Technical Contributions |
| :--- | :--- | :--- | :--- | :--- |
| **Ananya Sharma** | `2510010367` | `ananya-integration` | Integration & CLI | Interactive CLI menu, full module integration in `main.cpp`, 4-mode Crop & Rotate (`CropRotate`), and branch merges. |
| **Gurveen Kaur** | `2510011077` | `gurveen-bmp-handler` | BMP I/O & Filters | 24-bit BMP file parser/writer (`BMPHandler`), Brightness, Contrast, Grayscale, Inversion, Sepia, and RGB Channel filters. |
| **Ashvath Shaily** | `2510010076` | `ashvath-graph` | Thresholding & Graphs | Image binarization (`Threshold`) and connected-component Region Analysis (`RegionAnalysis`) using BFS and Iterative DFS. |
| **Rashika Jain** | `2510010842` | `rashika-dsa` | DSA & Pipeline | Polymorphic `FilterPipeline`, Stack-based `UndoStack`, and linked-list FIFO `RequestQueue` for batch processing. |

---

## License

This project is licensed under the terms specified in the [LICENSE](LICENSE) file.