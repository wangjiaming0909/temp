#ifndef _GRAPH_SEACH_H_
#define _GRAPH_SEACH_H_

namespace gra
{

class search
{
  public:
    virtual bool marked(int v) = 0;
    virtual int count() = 0;
};
}

#endif // _GRAPH_SEACH_H_