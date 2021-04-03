#include <iostream>
#include <vector>
#include <fstream>
#include <string>
void read_from_space_sep_file(std::vector<std::vector<int>>& arr, std::string fileName)
{
    std::string line;
    std::ifstream file(fileName);
    std::vector<int> temp;
    int iterator = 0;
    if (file.is_open())
    {     
        while (getline(file, line))
        {

            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] != ' ')
                {             
                    temp.push_back(int(line[i])-48);
                }
                   
            }
            arr.push_back(temp);
            temp.clear();          
        }
    }
    file.close();
}
void read_from_csv(std::vector<std::vector<int>>& arr, std::string fileName)
{
    std::string line;
    std::ifstream file(fileName);
    std::vector<int> temp;
    int iterator = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] != ',')
                {
                    temp.push_back(int(line[i]) - 48);
                }
            }
            arr.push_back(temp);
            temp.clear();
        }
    }
    file.close();
}


void print_sudoku(std::vector<std::vector<int>>& arr)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if ( j%3 ==0 && j !=0)
                std::cout << "| "<< arr[i][j] << " ";
            else
            std::cout << arr[i][j] << " ";
        }
        if (i % 3 == 2 && i != 8)
            std::cout << "\n---------------------\n";
        else
            std::cout << std::endl;
    }
}


bool check(std::vector<std::vector<int>> & arr, int i, int j, int val)
{
    for (int k = 0; k < 9; k++)
    {
        if (arr[i][k] == val)
            return false;
    }
    for (int k = 0; k < 9; k++)
    {
        if (arr[k][j] == val)
            return false;
    }
    int box_row = i / 3;
    int box_col = j / 3;
    for (int k = box_row * 3; k < (box_row * 3 + 3); k++)
    {
        for (int l = box_col * 3; l < (box_col * 3 + 3); l++)
        {
            if (arr[k][l] == val)
                return false;
        }
    }
    return true;
}

bool solve_sudoku(std::vector<std::vector<int>> & arr, int row, int col)
{

    if (row == 8 && col == 9)
        return true;
    if (col == 9)
    {
        row++;
        col = 0;
    }
    if (arr[row][col] != 0)
        return solve_sudoku(arr, row, col + 1);
    for (int i = 1; i <= 9; i++)
    {
        if (check(arr, row, col, i))
        {
            arr[row][col] = i;
            if (solve_sudoku(arr, row, col + 1))
                return true;

        }
        arr[row][col] = 0;

    }

    return false;
}




int main()
{
    std::vector<std::vector<int>> board;/* = {
        {7, 8, 0, 4, 0, 0, 1, 2, 0},
        {6, 0, 0, 0, 7, 5, 0, 0, 9},
        {0, 0, 0, 6, 0, 1, 0, 7, 8},
        {0, 0, 7, 0, 4, 0, 2, 6, 0},
        {0, 0, 1, 0, 5, 0, 9, 3, 0},
        {9, 0, 4, 0, 6, 0, 0, 0, 5},
        {0, 7, 0, 3, 0, 0, 0, 1, 2},
        {1, 2, 0, 0, 0, 7, 4, 0, 0},
        {0, 4, 9, 2, 0, 6, 0, 0, 7}
    };*/
    read_from_space_sep_file(board, "board.txt");
    print_sudoku(board);
    solve_sudoku(board, 0, 0);
    std::cout << "\n\n";
    print_sudoku(board);
    return 0;
}