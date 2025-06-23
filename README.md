# Collection-of-various-Hanoi-Tower-variations
Here is a repository that contains visualizations of various Tower of Hanoi variants, which can be used for Tower of Hanoi course teaching. If it helps you, please give it a star. If you have any questions about the code, you can contact zhongmingliu2004@qq.com.The other code is being organized. Please stay calm and patient. &#9745; represents successful upload.

Read this in other languages: (English)(README.md), (中文)(README_zh.md).

We have completed the translation of the following Tower of Hanoi variants' visualizations:
1. Classic Tower of Hanoi &#9745;
2. Adjacent-Move Tower of Hanoi
3. Red-Blue Bicolor Tower of Hanoi
4. Double-Decker Tower of Hanoi
5. Bicolor Tower of Hanoi Decomposition
6. Tricolor Tower of Hanoi Decomposition



Here is the English version of the Tower of Hanoi problem description formatted for GitHub Markdown:

### Problem Description
- **Initial State**: There are three pegs, A, B, and C. Peg A has n disks stacked in ascending order of size from top to bottom.
- **Goal**: Move all n disks from peg A to peg C using peg B as an auxiliary.
- **Rules**:
  1. Only one disk can be moved at a time.
  2. Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack or on an empty peg.
  3. No disk may be placed on top of a smaller disk.

### Recursive Solution Approach
The problem is typically solved using recursion. The key insight is breaking down the complex problem of moving n disks into simpler sub-problems:

1. **Recursive Decomposition**: To move n disks from A to C:
   - First, move the top n-1 disks from A to B (using C as auxiliary).
2. **Move the Largest Disk**: Move the nth disk (the largest) from A to C.
3. **Recursive Reassembly**: Move the n-1 disks from B to C (using A as auxiliary).

### Derivation of Minimum Moves
- **Recurrence Relation**: Let \( T(n) \) be the minimum number of moves required for n disks.
  - Base case: \( T(1) = 1 \) (direct move).
  - For \( n > 1 \):
    1. Move n-1 disks from A to B: \( T(n-1) \) moves.
    2. Move the nth disk from A to C: 1 move.
    3. Move n-1 disks from B to C: \( T(n-1) \) moves.
    - Therefore, the recurrence relation is \( T(n) = 2T(n-1) + 1 \).
- **Closed-Form Solution**:
  - By solving the recurrence: \( T(n) + 1 = 2(T(n-1) + 1) \).
  - This forms a geometric sequence with \( T(n) + 1 = 2^n \), hence \( T(n) = 2^n - 1 \).

### Example (n=3 Disks)
The sequence of moves requires \( 2^3 - 1 = 7 \) steps:

1. Move disk 1 from A → C
2. Move disk 2 from A → B
3. Move disk 1 from C → B
4. Move disk 3 from A → C
5. Move disk 1 from B → A
6. Move disk 2 from B → C
7. Move disk 1 from A → C

This approach efficiently solves the problem using recursion, with the number of moves growing exponentially with the number of disks.

