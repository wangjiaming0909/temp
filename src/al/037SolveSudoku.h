#pragma once

#include "036IsValidSudoku.h"
#include <stack>

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

class SolveSudoku : public ILeetCode
{
public:
    void solveSudoku(vector<vector<char>>& board)
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
                if(board[i][j] != '.') continue;
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

        stack<unsigned int> s{};
        size_t i = 0;
        size_t j = 0;
        stack<pair<int, int>> lastIJ{};
        while(s.size() < numsToCal)
        {
            if(!nodes[i][j].needCal)
            {
                if(j == 8 && i < 8)
                {
                    i++; j = 0;
                }
                else
                    j++;
                continue;
            }
            auto& node = nodes[i][j];
            if(node.possibleValues.nextSet() == -1)//没有选择了
            {
                if(lastIJ.size() > 0)
                {
                    auto lastV = s.top() - 1;
                    auto lastI = lastIJ.top().first;
                    auto lastJ = lastIJ.top().second;
                    nodes[lastI][lastJ].possibleValues.set(lastV);

                    //set 同一行的
                    for(auto& n : nodes[lastI])
                    {
                        n.possibleValues.unset(lastV);
                    }
                    //set 同一列的
                    for(auto& v : nodes)
                    {
                        v[lastJ].possibleValues.unset(lastV);
                    }
                    //set 同一个square的
                    for(int k = 0; k > (lastI/3)*3 && k < 3*(lastI/3+1); k++)
                    {
                        for(int l = 0; l > (lastJ/3)*3 && l < 3*(lastJ/3+1); lastJ++)
                        {
                            nodes[k][l].possibleValues.unset(lastV);
                        }
                    }
                }
            }else
            {
                auto val = node.possibleValues.nextSet();
                s.push(val + 1);
                node.possibleValues.unset(val);

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
                for(int k = 0; k >= (i/3)*3 && k < 3*(i/3+1); k++)
                {
                    for(int l = 0; l >= (j/3)*3 && l < 3*(j/3+1); j++)
                    {
                        nodes[k][l].possibleValues.unset(val);
                    }
                }
                lastIJ.push(make_pair<int, int>(i, j));
            }
            if(j == 8 && i < 8)
            {
                i++; j = 0;
            }
            else
                j++;
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

        solveSudoku(v);

        for(auto& vv : v)
        {
            printVector(vv);
            cout << endl;
        }
    }
};
}


