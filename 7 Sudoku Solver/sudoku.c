#include <stdio.h>
//?  when we pass 2d array to the fuction [9][9] no need of first square bracket size[][9] but whne we declare inside main function we need to give like this[9][9]
int puzzle[][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

void print_puzzle(int puzzle[9][9]);
int valid_move(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);
//? new feature
int is_valid_sudoku(int puzzle[9][9]);

int main()
{
  printf("\n\tWelcome to SUDOKU Solver !!!");
  printf("\n\nOriginal Puzzle:");
  print_puzzle(puzzle);
  //? to check whether the given sudoku is valid or not?
  if (!is_valid_sudoku(puzzle))
  {
    printf("\nThe given Sudoku puzzle is INVALID!\n");
    return 0;
  }
  if (solve_puzzle(puzzle, 0, 0))
  {
    printf("\n The puzzle is solved: ");
    print_puzzle(puzzle);
  }
  else
  {
    printf("\n This puzzle is not Solvable\n");
  }
  return 0;
}

int solve_puzzle(int puzzle[9][9], int row, int col)
{

  if (col == 9)
  {
    if (row == 8)
    {
      return 1; // Puzzle solved
    }
    //? reset col and move to next row
    row++;
    col = 0;
  }

  if (puzzle[row][col] > 0)
  {
    // traversing in row wise col+1
    // when we reach the index 8 if we increment  which is index 9 it is invalid to handle that
    // the above statement is done
    return solve_puzzle(puzzle, row, col + 1);
  }

  //? try to fill 1 to 9 in the puzzle[row][col]
  for (int i = 1; i <= 9; i++)
  {
    // if the value of i doesn't exist in the corresponding rows and col the fill the value of i.
    if (valid_move(puzzle, row, col, i))
    {
      puzzle[row][col] = i;
      if (solve_puzzle(puzzle, row, col + 1))
      {
        return 1;
      }
      puzzle[row][col] = 0; // backtracking
    }
  }
  return 0;
}

int valid_move(int puzzle[9][9], int row, int col, int val)
{

  // valid row
  for (int i = 0; i < 9; i++)
  {
    if (puzzle[row][i] == val)
    {
      return 0;
    }
  }

  // valid column
  for (int i = 0; i < 9; i++)
  {
    if (puzzle[i][col] == val)
    {
      return 0;
    }
  }

  // valid square
  //? this is to find the starting index of the square in 3X3 grid
  int r = row - row % 3;
  int c = col - col % 3;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      //? Traversing every values in the 3X3 grid
      if (puzzle[r + i][c + j] == val)
      {
        return 0;
      }
    }
  }

  return 1;
}

void print_puzzle(int puzzle[9][9])
{
  printf("\n+-------+-------+-------+");
  for (int row = 0; row < 9; row++)
  {
    if (row % 3 == 0 && row != 0)
    {
      printf("\n|-------+-------+-------|");
    }
    printf("\n");
    for (int col = 0; col < 9; col++)
    {
      if (col % 3 == 0)
      {
        printf("| ");
      }
      if (puzzle[row][col] != 0)
      {
        printf("%d ", puzzle[row][col]);
      }
      else
      {
        printf("  ");
      }
    }
    printf("|");
  }
  printf("\n+-------+-------+-------+\n");
}

int is_valid_sudoku(int puzzle[9][9])
{
  for (int row = 0; row < 9; row++)
  {
    for (int col = 0; col < 9; col++)
    {
      int val = puzzle[row][col];
      if (val != 0)
      {
        puzzle[row][col] = 0;
        if (!valid_move(puzzle, row, col, val))
        {
          return 0;
        }
        puzzle[row][col] = val;
      }
    }
  }
  return 1;
}