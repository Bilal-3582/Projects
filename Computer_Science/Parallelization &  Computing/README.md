Here's the revised proposal with the added explanation for the **Floyd-Warshall Algorithm** and the requested pseudocode. This version includes all sections in a more integrated and polished format.

---

# **Parallel and Distributed Computing**

## **Course Instructor**: Dr. Ghufran Ahmed  
## **Project Algorithms**:
1. N-Ary Search Array  
2. Floyd-Warshall Algorithm  

**Team Members**:  
- Bilal Bari (21K-3582)  
- Alyan (21K-3606)  
- Amna Farooq (21K-3575)  

---

## **Introduction**

### **N-Ary Search Algorithm**  
The N-ary search algorithm extends the classic binary search by dividing a sorted array into \( N \) subarrays instead of just two. This approach reduces the search space more quickly than binary search, particularly when the target element is closer to the start of the array. It is more efficient for larger datasets by narrowing down the search region in fewer iterations.

### **Floyd-Warshall Algorithm**  
The Floyd-Warshall algorithm is a dynamic programming solution used to find the shortest paths between all pairs of vertices in a weighted graph. Unlike single-source algorithms like Dijkstra’s or Bellman-Ford, Floyd-Warshall systematically updates the shortest paths for every pair of vertices by considering all possible intermediate vertices. This algorithm works on both directed and undirected graphs and can handle both positive and negative edge weights, provided there are no negative cycles in the graph.

---

## **Methodology**

### **Pseudocode for Serial Implementation**

#### **N-Ary Search Array**
```plaintext
Function NarySearch(arr, target, N):
    left = 0
    right = length(arr) - 1

    while left <= right:
        subarraySize = (right - left + 1) / N
        subarrayStart = left

        for i from 0 to N-1:
            subarrayEnd = min(subarrayStart + subarraySize - 1, right)

            if arr[subarrayEnd] == target:
                return subarrayEnd  
            elif arr[subarrayEnd] > target:
                right = subarrayEnd - 1 
                break
            else:
                subarrayStart = subarrayEnd + 1
        
        left = subarrayStart
    
    return -1
```

#### **Floyd-Warshall Algorithm**
```plaintext
Initialize Variables
- n ← size of rows
- D^(0) ← input distance matrix
- Π^(0) ← initialize precedence matrix

For k ← 1 to n do:
    For i ← 1 to n do:
        For j ← 1 to n do:
            - d^(k)_ij ← min(d^(k-1)_ij, d^(k-1)_ik + d^(k-1)_kj)

            - Update Precedence Matrix
                - If d^(k-1)_ij ≤ d^(k-1)_ik + d^(k-1)_kj then
                    π^(k)_ij ← π^(k-1)_ij
                - Else
                    π^(k)_ij ← π^(k-1)_kj

Return Final Matrices
- Return D^(n) and Π^(n)
```

---

### **Parallel Implementations**

#### **OpenMP Implementation**

##### **N-Ary Search (OpenMP)**
```plaintext
Function ParallelNarySearch(arr, target, N):
    left = 0
    right = length(arr) - 1
    result = -1

    #pragma omp parallel shared(result, left, right)
    {
        #pragma omp for nowait
        for i from 0 to N-1:
            subarraySize = (right - left + 1) / N
            subarrayStart = left + i * subarraySize
            subarrayEnd = min(subarrayStart + subarraySize - 1, right)

            if arr[subarrayEnd] == target:
                #pragma omp critical
                result = subarrayEnd
                break
            elif arr[subarrayEnd] > target:
                #pragma omp critical
                right = subarrayEnd - 1
                break
            else:
                #pragma omp critical
                left = subarrayEnd + 1
    }

    return result
```

##### **Floyd-Warshall (OpenMP)**
```plaintext
Function FloydWarshallOpenMP(D, Π, n):
    For k ← 1 to n do:
        #pragma omp parallel for
        for i ← 1 to n do:
            for j ← 1 to n do:
                - d^(k)_ij ← min(d^(k-1)_ij, d^(k-1)_ik + d^(k-1)_kj)

                - Update Precedence Matrix
                    - If d^(k-1)_ij ≤ d^(k-1)_ik + d^(k-1)_kj then
                        π^(k)_ij ← π^(k-1)_ij
                    - Else
                        π^(k)_ij ← π^(k-1)_kj
    Return D^(n) and Π^(n)
```

#### **MPI Implementation**

##### **N-Ary Search (MPI)**
```plaintext
Function MPINarySearch(arr, target, N):
    rank = MPI_rank()
    size = MPI_size()

    left = 0
    right = length(arr) - 1
    result = -1

    subarraySize = (right - left + 1) / size
    subarrayStart = left + rank * subarraySize
    subarrayEnd = min(subarrayStart + subarraySize - 1, right)

    MPI_Bcast(target)

    while left <= right and result == -1:
        for i from 0 to N-1:
            if arr[subarrayEnd] == target:
                result = subarrayEnd
                break
            elif arr[subarrayEnd] > target:
                right = subarrayEnd - 1
                break
            else:
                subarrayStart = subarrayEnd + 1
        
        MPI_Allreduce(MPI_IN_PLACE, result, 1, MPI_INT, MPI_MIN)
        MPI_Bcast(left)
        MPI_Bcast(right)

    return result
```

##### **Floyd-Warshall (MPI)**
```plaintext
Function FloydWarshallMPI(D, Π, n, pid, pN):
    For k ← 1 to n do:
        For i ← (pid * n) / pN to ((pid + 1) * n) / pN do:
            for j ← 1 to n do:
                - d^(k)_ij ← min(d^(k-1)_ij, d^(k-1)_ik + d^(k-1)_kj)

                - Update Precedence Matrix
                    - If d^(k-1)_ij ≤ d^(k-1)_ik + d^(k-1)_kj then
                        π^(k)_ij ← π^(k-1)_ij
                    - Else
                        π^(k)_ij ← π^(k-1)_kj

        Send and receive updated rows from other processes
    Return D^(n) and Π^(n)
```

---

## **Performance Comparison**

### **N-Ary Search Results**  
- **N=4**, Data Size: 10,000 Elements  
- **N=16**, Same Data Size  
  - The search times remain constant across different values of \(N\), indicating that only data size impacts performance, not the subdivision factor.

### **Floyd-Warshall Results**  
- **N=100 Vertices (10,000 Edges)**  
- **N=1000 Vertices (1 Million Edges)**  
  - OpenMP performs significantly better than MPI, with MPI facing communication overhead due to frequent inter-process data exchanges, especially for larger graphs.

---

## **Conclusion**  
For the **N-ary search algorithm**, dividing the array into subarrays processed by multiple threads or processes significantly speeds up the search. MPI outperformed OpenMP by about 5x because we focused purely on computation time, ignoring initial communication overhead. Once subarrays were broadcasted, no further communication was needed.

However, with the **Floyd-Warshall algorithm**, OpenMP consistently outperformed MPI. The nested loop structure in Floyd-Warshall benefits greatly from OpenMP's shared memory model, where collapsing the loops results in efficient parallel computation. In contrast, MPI's distributed memory model suffers due to communication overhead from frequent updates between processes, leading to diminished performance as the number of processes increases.

---

## **References**  
- [Floyd-Warshall Algorithm](https://www.hindawi.com/journals/am/2015/575687/)  
- [N-Ary Search](https://www.researchgate.net/publication/220284100_Parallel_Tree_Search_for_Combinatorial_Problems_a_Comparative_Study_between_OpenMP_and_MPI)  

---
