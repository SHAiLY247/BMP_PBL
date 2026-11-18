#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include <vector>
#include <stack>
#include "BMPHandler.h"

struct ImageState
{
    std::vector<std::vector<pixel>> pixels;
    BMPInfoHeader infoHeader;
};

class UndoStack
{
private:
    std::stack<ImageState> states;
    int maxSize;

public:
    UndoStack(int limit = 5);

    void pushState(
        const std::vector<std::vector<pixel>>& pixels,
        const BMPInfoHeader& infoHeader
    );

    bool popState(
        std::vector<std::vector<pixel>>& pixels,
        BMPInfoHeader& infoHeader
    );

    bool isEmpty();

    void clear();
};

#endif