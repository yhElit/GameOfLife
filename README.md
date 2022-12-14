# Game of Life
C++ implementation of Conway's Game of Life

## Rules
- Every cell has 8 neighbours
    - Horizontally
    - Vertically
    -  Diagonally
<br></br>  
- **Rule 1:** Any dead cell with exactly three living neighbours becomes a live
cell
- **Rule 2:** Any live cell with two or three living neighbours stay alive
- **Rule 3:** Any live cell with fewer than two living neighbours dies
- **Rule 4:** Any live cell with more than three living neighbours dies
<br></br>  

## Notes
**Calculates Game Of Life in sequential mode on CPU**
- Outputs correct state after n generations
- Considers wrap-around at borders
- Reads input board from file
    - First line are rows and columns, e.g. 100,100
    - ‘x’ – live cell
    - ‘.’ – dead cell
- Writes output board to file in same format
- Measures setup, computation and finalization time
- Every generation at time t influences the following generation t + 1
<br></br>  

**Command Line Parameters**
- --load <filename> (filename to read input board)
- --save <filename> (filename to save output board)
- --generations <n> (run n generations)
- --measure (print time measurements)
<br></br>  

**Program call example**

 gol --load random250_in.gol --save random250_out.gol --generations 250 --measure