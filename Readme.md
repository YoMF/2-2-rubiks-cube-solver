
# 2*2 Rubik's Cube Solver
<img src="https://github.com/YoMF/shared-assets/blob/142e5537330c71f20f6b26fc9ca3d7a139e0cee7/cube-YOB.png" width=100 height=100/>
  
  
## Description
This Project solves the [pocket cube](https://en.wikipedia.org/wiki/Pocket_Cube) without the optimization using group theory. The basic idea is to do a breath first search of all the possible permutation of the cube. When a cube is already encountered then the iteration breaks. We use a binary search tree to store all the permutations which enable us with a ```O(lgn)``` search time.<br><br>
Storing all the values are possible since we know that the no.of.possible states/permutations of pocket cube is ```< 4*10^6``` refer [here](https://en.wikipedia.org/wiki/Pocket_Cube).

Space complexity : ```O(n)```  
Time complexity : ```O(n*lg(n))``` *since we do one check per cube.*  
where n is the no.of.possible states of the cube.

## How to Use
```bash
#Enter the following command (in the main directory of project):
make
#Execute ./program (needs 1~2 mins to produce the result.)
```


- Implementation is provided for the above said algorithm.[Here](https://github.com/YoMF/2-2-rubiks-cube-solver/blob/b28eb3c36a667b9b180d833b5c99146be831fc3d/main.cpp#L49-L87)   
Along with the code to save the solution as a binary file.[Here](https://github.com/YoMF/2-2-rubiks-cube-solver/blob/b28eb3c36a667b9b180d833b5c99146be831fc3d/main.cpp#L107)<br>It can easily be modified to read.

- The Cube class provides functions to rotate and print (2d flattened). Not the most straight forward implementation but we tried to use binary representation as much as possible to improve the speed.  

## Explanation:  
- A rotation of 90 deg is regarded as a single move. So each state of the cube is rotated in six different ways ```[U, F, L, D, B, R]``` each time.
- We only use 3 faces since ``` clockwise roatation of U = Anti-clockwise rotation of D```
- This also makes a **corner fixed** *(aka cubicle)* Which serves as a fixed frame of reference. So we don't end up with same state in a different orientation.
- The solution is represented as a string of 
```UFLDBR``` characters.
- The string stored in the map(Binary search tree) is the steps required to reach the state from a solved cube. So the solution for the current state is Reversed and Complimented version of that.

```bash
# Eg: solved -> U -> D -> X;
#     X -> D' -> U' -> solved;
```  

## Result
```cpp
int main()
{
    Cube c;

    Bfs bfs(c);
    bfs.run(); // executes the algorithm.
    bfs.results();  // prints the result.

    // bfs.write_to_disk(); // saves the solution in current working directory.
}
```

The result contains the total no.of.states and the no.of.solutions sorted with their size in ascending order.  

![image](https://github.com/YoMF/shared-assets/blob/8680f6fd79cfdbd15f7bd7547964494c7890087d/Screenshot%20from%202021-07-16%2018-15-00.png)

## Built with
C++ and [makefile](https://github.com/YoMF/2-2-rubiks-cube-solver/blob/b28eb3c36a667b9b180d833b5c99146be831fc3d/makefile)

## Test Configurations:
- system :   Ubuntu 20.10 (64bit)  
- compiler:  g++  
- flags:     -std=c++20 -o3  

## Credits
[On pocket cube](https://en.wikipedia.org/wiki/Pocket_Cube)
## Contributions
Contributions are appreciated.

## License
[MIT](https://github.com/YoMF/shared-assets/blob/d87d8748a96b587e84eaa4824520721698065e46/LICENSE)

Feel Free to Use and distribute the code.
