#ifndef _DS_PRIORITY_QUEUE_H_
#define _DS_PRIORITY_QUEUE_H_

namespace ds{

template <class T>
class maxpriorityqueue
{
  public:
    virtual ~maxpriorityqueue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T &top() = 0;
    virtual void pop() = 0;
    virtual void push(const T &element) = 0;
};
}
#endif // _DS_PRIORITY_QUEUE_H_