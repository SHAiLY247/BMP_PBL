#ifndef UNDOSTACK_H
#define UNDOSTACK_H
#include <vector>
#include <stack>
#include "BMPHandler.h"
class UndoStack
{
    private:
        std::stack<std::vector<std::vector<pixel>>>states;
        int maxSize;
    public:
        UndoStack(int limit=5);
        void pushState(const std::vector<std::vector<pixel>>& pixels);
        bool popState(std::vector<std::vector<pixel>>& pixels);
        bool isEmpty();
        void clear();    
};
#endif