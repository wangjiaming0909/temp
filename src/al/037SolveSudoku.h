#pragma once

#include "036IsValidSudoku.h"
#include <stack>
#include <algorithm>

namespace al {

struct SudokuNode
{
    SudokuNode()
        : i(0), j(0), possibleValues(), needCal(false)
    {
    }
    SudokuNode(unsigned int i, unsigned int j, const NSquare<9>& v) : i(i), j(j), possibleValues(v), needCal(false)
    {}
    SudokuNode(const SudokuNode& s) = default;
    unsigned int i;
    unsigned int j;
    NSquare<9> possibleValues;
    bool needCal;
};

void printSudokuNodes(const vector<vector<SudokuNode>>& nodes, const vector<vector<char>>& board, stack<int> s)
{
    stack<int> reverseStack{};
    while (!s.empty()) {
        reverseStack.push(s.top());
        s.pop();
    }
    for(size_t i = 0; i < nodes.size(); i++)
    {
        for(size_t j = 0; j < nodes[i].size(); j++)
        {
            if(board[i][j] != '.')
            {
                cout << board[i][j] << " ";
            }
            else
            {
                if(!reverseStack.empty())
                {
                    cout << reverseStack.top() << " ";
                    reverseStack.pop();
                }
                else
                {
                    cout << ". ";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

class SolveSudoku : public ILeetCode
{
public:
    bool solveSudoku(vector<vector<char>>& board)
    {
        NSquare<9> horizontalSq[9];
        NSquare<9> verticalSq[9];
        NSquare<9> SquareSq[9];

        for(size_t i = 0; i < board.size(); i++)
        {
            for(size_t j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] == '.') continue;

                unsigned int ch = board[i][j]-48-1;
                if(!horizontalSq[i].set(ch) && !verticalSq[j].set(ch) && !SquareSq[(i/3) * 3+j/3].set(ch))
                { }
            }
        }


        vector<vector<SudokuNode>> nodes;
        nodes.resize(9);
        for(auto& n : nodes)
        {
            n.resize(9);
        }

        int numsToCal = 0;
        for(size_t i = 0; i < board.size(); i++)
        {
            for(size_t j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] != '.')
                {
                    continue;
//                    NSquare<9> ns{};
//                    unsigned int ch = board[i][j]-48-1;
//                    ns.set(ch);
//                    nodes[i][j].possibleValues = ns;
                }
                NSquare<9> sq{};
                sq.merge(horizontalSq[i]);
                sq.merge(verticalSq[j]);
                sq.merge(SquareSq[i/3*3+j/3]);
                sq.NOT();
                nodes[i][j].possibleValues = sq;
                nodes[i][j].needCal = true;
                numsToCal++;
            }
        }

        stack<int> s{};
        auto ret = solveSudokuRecursive(board, nodes, 0, 0, s);
//        printStack(s);
        return ret;


//        stack<unsigned int> s{};
//        size_t i = 0;
//        size_t j = 0;
//        stack<pair<int, int>> lastIJ{};
//        while(s.size() < numsToCal)
//        {
//            cout << "i: " << i;
//            cout << " j: " << j << endl;
//            if(!nodes[i][j].needCal)
//            {
//                if(j == 8 && i < 8)
//                {
//                    i++; j = 0;
//                }
//                else
//                    j++;
//                continue;
//            }
//            auto& node = nodes[i][j];
//            if(node.possibleValues.nextSet() == -1)//没有选择了
//            {
//                if(lastIJ.size() > 0)
//                {
//                    auto lastV = s.top() - 1;
//                    auto lastI = lastIJ.top().first;
//                    auto lastJ = lastIJ.top().second;

//                    //set 同一行的
//                    for(auto& n : nodes[lastI])
//                    {
//                        n.possibleValues.set(lastV);
//                    }
//                    //set 同一列的
//                    for(auto& v : nodes)
//                    {
//                        v[lastJ].possibleValues.set(lastV);
//                    }
//                    //set 同一个square的
//                    for(int k = (lastI/3)*3; k < 3*(lastI/3+1); k++)
//                    {
//                        for(int l = (lastJ/3)*3; l < 3*(lastJ/3+1); l++)
//                        {
//                            nodes[k][l].possibleValues.set(lastV);
//                        }
//                    }
//                    nodes[lastI][lastJ].possibleValues.unset(lastV);
//                    lastIJ.pop();
//                    s.pop();
//                    i = lastI; j =lastJ; continue;
//                }
//            }else
//            {
//                auto val = node.possibleValues.nextSet();
//                s.push(val + 1);
//                node.possibleValues.unset(val);

//                //去掉同一行的
//                for(auto& n : nodes[i])
//                {
//                    n.possibleValues.unset(val);
//                }
//                //去掉同一列的
//                for(auto& v : nodes)
//                {
//                    v[j].possibleValues.unset(val);
//                }
//                //去掉同一个3X3的?????
//                for(int k = (i/3)*3; k < 3*(i/3+1); k++)
//                {
//                    for(int l = (j/3)*3; l < 3*(j/3+1); l++)
//                    {
//                        nodes[k][l].possibleValues.unset(val);
//                    }
//                }
//                lastIJ.push(make_pair<int, int>(i, j));
//            }
//            if(j == 8 && i < 8)
//            {
//                i++; j = 0;
//            }
//            else
//                j++;
//        }
    }

    bool solveSudokuRecursive(vector<vector<char>>& board, vector<vector<SudokuNode>> nodes, int i, int j, stack<int>& s)
    {
//        printSudokuNodes(nodes, board, s);
        if(i > 8 || j > 8) return true;
        vector<vector<SudokuNode>> oldNodes = nodes;
        auto& node = nodes[i][j];
        auto& oldNode = oldNodes[i][j];
        if(!node.needCal)
        {
            if(j == 8 && i < 8)
            {
                i++; j = 0;
            }
            else
                j++;
            return solveSudokuRecursive(board, nodes, i, j, s);
        }
        if(node.possibleValues.nextSet() == -1)
        {
            return false;
        }
        else
        {
            while(oldNode.possibleValues.nextSet() != -1)
            {
                auto val = node.possibleValues.nextSet();
                node.possibleValues.unset(val);
                oldNode.possibleValues.unset(val);
                s.push(val+1);

                //去掉同一行的
                for(auto& n : nodes[i])
                {
                    n.possibleValues.unset(val);
                }
                //去掉同一列的
                for(auto& v : nodes)
                {
                    v[j].possibleValues.unset(val);
                }
                //去掉同一个3X3的?????
                for(int k = (i/3)*3; k < 3*(i/3+1); k++)
                {
                    for(int l = (j/3)*3; l < 3*(j/3+1); l++)
                    {
                        nodes[k][l].possibleValues.unset(val);
                    }
                }
                int lastI = i;
                int lastJ = j;
                if(j == 8 && i < 8)
                {
                    i++; j = 0;
                }
                else if(j == 8 && i == 8)
                    return true;
                else
                    j++;
                if(!solveSudokuRecursive(board, nodes, i, j, s))
                {
                    i = lastI;
                    j = lastJ;
                    nodes = oldNodes;
//                    //去掉同一行的
//                    for(auto& n : nodes[i])
//                    {
//                        n.possibleValues.set(val);
//                    }
//                    //去掉同一列的
//                    for(auto& v : nodes)
//                    {
//                        v[j].possibleValues.set(val);
//                    }
//                    //去掉同一个3X3的?????
//                    for(int k = (i/3)*3; k < 3*(i/3+1); k++)
//                    {
//                        for(int l = (j/3)*3; l < 3*(j/3+1); l++)
//                        {
//                            nodes[k][l].possibleValues.set(val);
//                        }
//                    }
                    s.pop();
                    continue;
                }
                return true;
            }
            return false;
        }
    }

    void test() override
    {

        vector<vector<char>> v{
            {'5', '3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };

        auto nodes = solveSudoku(v);

//        for(auto& vv : nodes)
//        {
//            printVector(vv);
//            cout << endl;
//        }
    }
};
}


