#include "RegionAnalysis.h"
#include <iostream>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

// Helper to check if a pixel is foreground (assuming thresholded to pure white)
bool isForeground(pixel p) {
    return (p.red == 255 && p.green == 255 && p.blue == 255);
}

// 4-Way Connectivity Breadth-First Search
void runBFS(vector<vector<pixel>>& pixels, vector<vector<bool>>& visited, int startRow, int startCol) {
    int rows = pixels.size();
    int cols = pixels[0].size();
    queue<pair<int, int>> q;
    
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;

    // Movement arrays for Top, Bottom, Left, Right
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int r = current.first;
        int c = current.second;

        for (int i = 0; i < 4; i++) {
            int nR = r + dRow[i];
            int nC = c + dCol[i];
            
            // Boundary check and unvisited foreground check
            if (nR >= 0 && nR < rows && nC >= 0 && nC < cols) {
                if (!visited[nR][nC] && isForeground(pixels[nR][nC])) {
                    visited[nR][nC] = true;
                    q.push({nR, nC});
                }
            }
        }
    }
}

// 4-Way Connectivity Iterative Depth-First Search (Prevents Stack Overflow)
void runIterativeDFS(vector<vector<pixel>>& pixels, vector<vector<bool>>& visited, int startRow, int startCol) {
    int rows = pixels.size();
    int cols = pixels[0].size();
    stack<pair<int, int>> s;
    
    s.push({startRow, startCol});
    visited[startRow][startCol] = true;

    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!s.empty()) {
        pair<int, int> current = s.top();
        s.pop();
        int r = current.first;
        int c = current.second;

        for (int i = 0; i < 4; i++) {
            int nR = r + dRow[i];
            int nC = c + dCol[i];

            if (nR >= 0 && nR < rows && nC >= 0 && nC < cols) {
                if (!visited[nR][nC] && isForeground(pixels[nR][nC])) {
                    visited[nR][nC] = true;
                    s.push({nR, nC});
                }
            }
        }
    }
}

void analyzeRegions(vector<vector<pixel>>& pixels) {
    if (pixels.empty() || pixels[0].empty()) {
        cout << "Image is empty. Please load an image first.\n";
        return;
    }

    int choice;
    cout << "\n===============================================\n";
    cout << "           REGION ANALYSIS (PHASE III)\n";
    cout << "===============================================\n";
    cout << "1. Analyze using BFS (Queue-based)\n";
    cout << "2. Analyze using DFS (Iterative Stack-based)\n";
    cout << "Enter your choice: ";
    
    if (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    int rows = pixels.size();
    int cols = pixels[0].size();
    
    // Create a boolean matrix to track visited pixels (Memory optimized)
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int regionCount = 0;

    // Scan every pixel to find unvisited foreground regions
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (!visited[r][c] && isForeground(pixels[r][c])) {
                // Found a new region, traverse it fully
                if (choice == 1) {
                    runBFS(pixels, visited, r, c);
                } else {
                    runIterativeDFS(pixels, visited, r, c);
                }
                regionCount++;
            }
        }
    }

    cout << "\n--- Analysis Complete ---\n";
    cout << "Total distinct regions found: " << regionCount << '\n';
    if (choice == 1) cout << "Method: Breadth-First Search\n";
    else cout << "Method: Depth-First Search\n";
}