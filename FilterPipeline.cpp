#include "FilterPipeline.h"
#include "Filter.h"
FilterPipeline::FilterPipeline()
{
    head=nullptr;
}
void FilterPipeline::addFilter(Filter* filter)
{
    Node* newNode=new Node;
    newNode->filter= filter;
    newNode->next= nullptr;
    if(head== nullptr)
    {
        head=newNode;
        return;
    }
    Node* current= head;
    while(current->next!=nullptr)
    {
        current=current->next;
    }
    current->next= newNode;
}
void FilterPipeline::removeFilter(int index)
{
    if(head==nullptr||index<0)
        return;
    
    if(index==0)
    {
        Node* temp=head;
        head=head->next;
        delete temp;
        return;
    }
    Node* current=head;
    for(int i=0;i<index-1;i++)
    {
        if(current->next==nullptr)
        {
            return;
        }
        current=current->next;
    }
    if(current->next==nullptr)
    {
        return;
    }
    Node* temp=current-> next;
    current->next=temp->next;
    delete temp;
}
void FilterPipeline::reorderFilters(int fromIndex,int toIndex)
{
    if(head==nullptr)
    {
        return;
    }
    if(fromIndex==toIndex)
    {
        return;
    }
    if(fromIndex<0|| toIndex<0)
    {
        return;
    }
    //Find the node to move
    Node* movingNode;
    if(fromIndex==0)
    {
        movingNode=head;
        head=head->next;
    }
    else{
        Node* beforeMoving=head;
        for(int i=0;i<fromIndex-1;i++)
        {
            if(beforeMoving->next==nullptr)
            {
                return;
            }
            beforeMoving=beforeMoving->next;
        }
        if(beforeMoving->next==nullptr)
        {
            return;
        }
        movingNode=beforeMoving->next;
        beforeMoving->next=movingNode->next;
    }
    //put node at beginning
    if(toIndex==0)
    {
        movingNode->next=head;
        head=movingNode;
        return;
    }
    Node* current=head;
    for(int i=0;i<toIndex-1;i++)
    {
        if(current==nullptr|| current->next==nullptr)
        {
            return;
        }
        current=current->next;
    }
    movingNode->next=current->next;
    current->next=movingNode;
}
void FilterPipeline::executePipeline(std::vector<std::vector<pixel>>& pixels)
{
    Node* current=head;
    while(current!=nullptr)
    {
        current->filter->apply(pixels);
        current=current->next;
    }
}
void FilterPipeline::clear()
{
    Node* current=head;
    while(current!=nullptr)
    {
        Node* temp=current;
        current=current->next;
        delete temp;
    }
    head=nullptr;
}
FilterPipeline::~FilterPipeline()
{
    clear();
}