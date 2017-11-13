/*************************************************************************
	> File Name: graph.h
	> Author: 
	> Mail: 
	> Created Time: Mon 13 Nov 2017 11:14:26 AM CST
 ************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H

typedef enum{
    UNDISCOVERED,
    DISCOVERED,
    VISITED
}VStatus;

typedef enum{
    UNDETERMINTED,
    TREE,
    CROSS,
    FORWARD,
    BACKWARD
}EType;

template <typename Tv, typename Te>
class graph{
private:

public:
    
};
#endif
