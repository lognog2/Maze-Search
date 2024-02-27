# Maze Search
*Maze files*
-
- Input files (maze0-maze7) in the mazes folder
  - The first two digits are the number of rows and columns in the maze, respectively.
  - The next block of numbers is the maze data.
    - Each number, when converted to binary, shows on what sides there is a wall. The order goes WSEN.
    - For example, a maze unit with value 11 = 1011, meaning there is a wall on all sides except south.
  - The next four numbers are the start row and column and the goal row and column, respectively.
 
*How it works*
-
- Reads in a maze from the above data and prints the maze layout, along with the path taken.
  - The maze layout is stored in a 2D array, and the path is stored in stacks for rows and columns.
  - From the specified starting point, the program checks the north, east, south, and west wall for an opening, in that order.
  - Once an opening that hasn't been visited is found, the program moves to that space in the maze, by adding it to the stack.
  - The previous space is marked with an arrow in the direction the path goes.
  - If the program reaches a dead end, it marks the space with an X and backtracks through the stack until another opening is found.
  - This process repeats until the goal is reached or the maze is declared unsolvable.

*Future ideas*
-
- random maze generator
- custom maze maker built-in
