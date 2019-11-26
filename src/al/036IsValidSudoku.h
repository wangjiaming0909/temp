#pragma once

#include <cstring>
#include "leetcode.h"


namespace al {

template <unsigned int N>
struct NSquare
{
    NSquare()
    {
        memset(arr, 0, N);
    }
    NSquare(const NSquare& nsq) = default;
    bool set(unsigned int i)
    {
        bool isS = isSet(i);
        arr[i] = 1;
        return isS;
    }
    void unset(unsigned int i)
    {
        arr[i] = 0;
    }
    bool isSet(unsigned int i)
    {
        if(i > N - 1) return false;
        return arr[i] == 1;
    }
    void merge(const NSquare& nsq)
    {
        for(size_t i = 0; i < N ; i++)
        {
            if(nsq.arr[i] == 1)
                set(i);
        }
    }
    void NOT()
    {
        for(size_t i = 0; i < N; i++)
        {
            if(arr[i] == 1) arr[i] = 0;
            else if(arr[i] == 0) arr[i] = 1;
        }
    }
    vector<unsigned int> setSet()const
    {
        vector<unsigned int> v;
        for(size_t i = 0; i < N; i++)
        {
            if(arr[i] == 1) v.push_back(i);
        }
        return v;
    }
    vector<unsigned int> notSetSet() const
    {
        vector<unsigned int> v;
        for(size_t i = 0; i < N; i++)
        {
            if(arr[i] == 0) v.push_back(i);
        }
        return v;
    }
    int nextSet() const
    {
        for(size_t i = 0; i < N; i++)
        {
            if(arr[i] == 1) return i;
        }
        return -1;
    }

    char arr[N];
};

class ValidSudoku : public ILeetCode
{
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
//        vector<NSquare<9>> horizontalSq{};
//        horizontalSq.resize(9);
//        vector<NSquare<9>> verticalSq{};
//        verticalSq.resize(9);
//        vector<NSquare<9>> SquareSq{};
//        SquareSq.resize(9);

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
                else return false;
            }
        }
        return true;
    }

    void test() override
    {
        /*
        ["5","3",".",".","7",".",".",".","."],
        ["6",".",".","1","9","5",".",".","."],
        [".","9","8",".",".",".",".","6","."],
        ["8",".",".",".","6",".",".",".","3"],
        ["4",".",".","8",".","3",".",".","1"],
        ["7",".",".",".","2",".",".",".","6"],
        [".","6",".",".",".",".","2","8","."],
        [".",".",".","4","1","9",".",".","5"],
        [".",".",".",".","8",".",".","7","9"]
        */
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

        cout << isValidSudoku(v) << endl;
    }
};
}
