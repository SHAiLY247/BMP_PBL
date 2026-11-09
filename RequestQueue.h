#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <string>
#include <vector>

// Types of operations supported
enum class OperationType
{
    Brightness,
    Contrast,
    Threshold,
    Inversion,
    Grayscale,
    Sepia,
    RGB,
    Crop,
    Rotate
};

// Stores one operation and its required values
struct ProcessingOperation
{
    OperationType type;

    int intValue;
    double doubleValue;

    int channel;

    int startRow;
    int startCol;
    int cropWidth;
    int cropHeight;

    int rotationChoice;

    ProcessingOperation()
    {
        intValue = 0;
        doubleValue = 0.0;
        channel = 1;

        startRow = 0;
        startCol = 0;
        cropWidth = 0;
        cropHeight = 0;

        rotationChoice = 1;
    }
};

// Stores one complete image-processing request
struct ProcessingJob
{
    std::string inputPath;
    std::string outputPath;

    std::vector<ProcessingOperation> operations;
};

class RequestQueue
{
private:

    struct Node
    {
        ProcessingJob request;
        Node* next;
    };

    Node* front;
    Node* rear;

public:

    RequestQueue();

    void enqueue(const ProcessingJob& request);

    bool dequeue(ProcessingJob& request);

    bool isEmpty();

    void clear();

    ~RequestQueue();
};

#endif