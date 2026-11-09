#include "UndoStack.h"

UndoStack::UndoStack(int limit)
{
    if (limit > 0)
        maxSize = limit;
    else
        maxSize = 5;
}

void UndoStack::pushState(
    const std::vector<std::vector<pixel>>& pixels,
    const BMPInfoHeader& infoHeader
)
{
    // Remove the oldest state if stack is full
    if (states.size() >= maxSize)
    {
        std::stack<ImageState> temp;

        while (states.size() > 1)
        {
            temp.push(states.top());
            states.pop();
        }

        states.pop();

        while (!temp.empty())
        {
            states.push(temp.top());
            temp.pop();
        }
    }

    // Store the current image and its dimensions
    ImageState state;

    state.pixels = pixels;
    state.infoHeader = infoHeader;

    states.push(state);
}

bool UndoStack::popState(
    std::vector<std::vector<pixel>>& pixels,
    BMPInfoHeader& infoHeader
)
{
    if (states.empty())
    {
        return false;
    }

    ImageState state = states.top();
    states.pop();

    pixels = state.pixels;
    infoHeader = state.infoHeader;

    return true;
}

bool UndoStack::isEmpty()
{
    return states.empty();
}

void UndoStack::clear()
{
    while (!states.empty())
    {
        states.pop();
    }
}