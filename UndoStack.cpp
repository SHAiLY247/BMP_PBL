#include "UndoStack.h"
UndoStack::UndoStack(int limit)
{
    if(limit>0)
    maxSize= limit;
    else
    maxSize=5;
}
void UndoStack::pushState(const std::vector<std::vector<pixel>>& pixels )
{
   // If stack is full, remove the oldest state
    if(states.size()>=maxSize)
    {
        std::stack<std::vector<std::vector<pixel>>>temp;
        while(states.size()>1)
        {

        temp.push(states.top());
        states.pop();
    }
    //remove the oldest state
    states.pop();
    while(!temp.empty())
    {
        states.push(temp.top());
        temp.pop();
    }
}
   //Add new state
    states.push(pixels);
}
bool UndoStack::popState(std::vector<std::vector<pixel>>& pixels)
{
    if(states.empty())
    {
        return false;
    }
    pixels=states.top();
    states.pop();
    return true;
}
bool UndoStack::isEmpty()
{
    return states.empty();
}
void UndoStack::clear()
{
    while(!states.empty())
    {
        states.pop();
    }
}