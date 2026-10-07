#ifndef FILTERPIPELINE_H
#define FILTERPIPELINE_H
#include <vector>
#include "BMPHandler.h"
class Filter;
class FilterPipeline
{
     private:
             struct Node
             {
                Filter* filter;
                Node* next;
             };
             Node* head;
      public:
            FilterPipeline();
            void addFilter(Filter* filter);
            void removeFilter(int index);
            void reorderFilters(int fromIndex,int toIndex);
            void executePipeline(std::vector<std::vector<pixel>>& pixels);
            void clear();
            ~FilterPipeline();
};
#endif