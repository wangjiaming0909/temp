#pragma once

#include "036IsValidSudoku.h"
#include <stack>
#include <algorithm>
#include "../timer.h"

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
    using Board_t = vector<vector<char>>;
    void solveSudoku2(Board_t& board)
    {
        timer t("solveSudoku");
        NSquare<9> horizontalSq[9];
        NSquare<9> verticalSq[9];
        NSquare<9> SquareSq[9];

        for(size_t i = 0; i < board.size(); i++)
        {
            for(size_t j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] == '.') continue;

                unsigned int ch = board[i][j]-48-1;
                horizontalSq[i].set(ch);
                verticalSq[j].set(ch);
                SquareSq[(i/3) * 3+j/3].set(ch);
            }
        }
        re(board, 0, 0, horizontalSq, verticalSq, SquareSq);
    }

    bool re(Board_t& board, int i, int j, NSquare<9>* hsq, NSquare<9>* vsq, NSquare<9>* ssq)
    {
        if(i > 8 || j > 8) return true;
        static Board_t tmp = board;// 在leetcode上使用static会挂
//        for(auto& vv : board)
//        {
//            printVector(vv);
//            cout << endl;
//        }
//        cout << endl;
        if(tmp[i][j] != '.')
        {
            nextIJ(i,j);
            return re(board, i, j, hsq, vsq, ssq);
        }
        bool valid = false;
        for(int k = 0; k < 9; k++)
        {
            auto val = k+1;
            if(hsq[i].isSet(k) || vsq[j].isSet(k) || ssq[(i/3)*3 + j/3].isSet(k)) continue;

            hsq[i].set(k); vsq[j].set(k); ssq[(i/3)*3 + j/3].set(k);
            board[i][j] = 48+val;
            int lastI = i; int lastJ = j;
            nextIJ(i, j);
//            if(i > 8 || j > 8) return true;
            if(!re(board, i, j, hsq, vsq, ssq))
            {
                i = lastI; j = lastJ;
                hsq[i].unset(k);
                vsq[j].unset(k);
                ssq[(i/3)*3 + j/3].unset(k);
//                board[i][j] = '.';
                continue;
            }else
            {
                valid = true;
                break;
            }
        }
        if(!valid) return false;
        return true;
    }

    void solveSudoku(Board_t& board)
    {
        timer t("solveSudoku");
        NSquare<9> horizontalSq[9];
        NSquare<9> verticalSq[9];
        NSquare<9> SquareSq[9];

        for(size_t i = 0; i < board.size(); i++)
        {
            for(size_t j = 0; j < board[i].size(); j++)
            {
                if(board[i][j] == '.') continue;

                unsigned int ch = board[i][j]-48-1;
                horizontalSq[i].set(ch);
                verticalSq[j].set(ch);
                SquareSq[(i/3) * 3+j/3].set(ch);
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

        solveSudokuRecursive(board, nodes, 0, 0);
    }

    void nextIJ(int& i, int& j)
    {
        if(j == 8 && i < 8)
        {
            i++; j = 0;
        }
        else
            j++;
    }

    bool solveSudokuRecursive(Board_t& board, vector<vector<SudokuNode>> nodes, int i, int j)
    {
//        printSudokuNodes(nodes, board, s);
        if(i > 8 || j > 8) return true;
        vector<vector<SudokuNode>> oldNodes = nodes;
        auto& node = nodes[i][j];
        auto& oldNode = oldNodes[i][j];
        if(!node.needCal)
        {
            nextIJ(i, j);
            return solveSudokuRecursive(board, nodes, i, j);
        }

        while(oldNode.possibleValues.nextSet() != -1)
        {
            auto val = node.possibleValues.nextSet();
            node.possibleValues.unset(val);
            oldNode.possibleValues.unset(val);
            board[i][j] = (48 + val + 1);

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
            nextIJ(i, j);
            if(!solveSudokuRecursive(board, nodes, i, j))
            {
                i = lastI;
                j = lastJ;
                nodes = oldNodes;
                continue;
            }
            return true;
        }
        return false;
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

//        solveSudoku(v);
        solveSudoku2(v);

        for(auto& vv : v)
        {
            printVector(vv);
            cout << endl;
        }
    }
};
}


