# TD_Algorithms_DataStructure
Practical exercises from UHA taught by Mr. Fawaz
<img width="1400" height="938" alt="image" src="https://github.com/user-attachments/assets/a1c6f577-a796-40e3-af96-7a42280c4046" />

## 📚 TD Contents

### TD-1 : Complexity Analysis and Recursion

#### Exercise 1 : Fibonacci Sequence
**Objective** : Compare different approaches to calculate Fibonacci numbers
- **Naive recursive algorithm** : Simple implementation with O(2^n) complexity - very computationally expensive
- **Dynamic programming (Memoization)** : Optimization using memoization table to avoid redundant recalculations
- **Performance measurement** : Comparison of execution times to demonstrate the optimization impact

#### Exercise 2 : Prime Numbers
**Objective** : Implement and compare different prime testing strategies
- **Naive algorithm** : Division verification up to √n - O(n√n)
- **Sieve of Eratosthenes** : Efficient method to count all prime numbers < N - O(n log log n)
- **Complexity analysis** : Demonstration of drastic improvement with the sieve

---

### TD-2 : Search and Sort Algorithms

#### Skeleton_ex1 : Search Algorithms
**Objective** : Implement and compare different search methods
- **Linear search** : Sequential traversal - O(n), works on any array
- **Jump search** : Divides array into blocks - O(√n), requires sorted array
- **Binary search** : Divide and conquer - O(log n), optimal for ordered data
- **Utilities** : Validation functions (check if array is sorted) and statistics

#### Skeleton_ex2 : Sorting Algorithms
**Objective** : Implement and analyze performance of different sorting algorithms
- **Selection sort** : O(n²), fewer memory swaps
- **Insertion sort** : O(n²), efficient for small arrays or partially sorted data
- **Bubble sort** : O(n²), simple but very inefficient
- **Merge sort** : O(n log n), stable and predictable algorithm
- **Comparative analysis** : Performance testing on different data sizes

---

### TD-3 : Graphs and Advanced Data Structures

#### Aladdin : Graph Problem and Traversal
**Objective** : Solve a complex problem involving graphs
- **Graph representation** : Adjacency list with linked node structure
- **Depth-first search (DFS)** : Complete graph exploration using stack
- **Breadth-first search (BFS)** : Level-by-level exploration using queue
- **Distance calculation** : Determine shortest paths between nodes
- **Validation** : Compare results with expected files through tests

#### InfiniteLibrary : AVL Tree (Self-Balancing Binary Search Tree)
**Objective** : Implement a self-balancing data structure
- **AVL binary search tree** : Structure guaranteeing balance with O(log n) for insertion/search/deletion
- **Balancing rotations** : Single and double rotations to maintain height invariant
- **Complex operations** : Efficient insertion, deletion, and search
- **Use cases** : Efficient data management with continuous fast access

---

### TD-6 : Palantir
Exercise on advanced structures and algorithms (file currently empty)

---

### TD-7 : HR Challenges and Pokémon
Advanced problem-solving exercises combining logic and algorithms :
- **HR.c** : Human resources management algorithms (parsing, calculations, optimization)
- **pokemon.c & pokemon_code.c** : Pokémon-related problems (simulation, game logic, data structures)

