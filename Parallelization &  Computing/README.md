
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
- ![Chart _1](https://github.com/Bilal-3582/Projects/blob/main/Parallelization%20%26%20%20Computing/charts/Chart_01.jpg)
- **N=16**, Same Data Size
-   ![Chart_2](https://github.com/Bilal-3582/Projects/blob/main/Parallelization%20%26%20%20Computing/charts/Chart_02.jpg)

  - (We can see that value of n don’t make any difference only the data size effects the time, however the computation times remain equal for any number of cores)
- **N-Ary N=4** , Communication & Computation
- ![Chart_3](https://github.com/Bilal-3582/Projects/blob/main/Parallelization%20%26%20%20Computing/charts/Chart_03.jpg)

### **Floyd-Warshall Results**  
- **N=100 Vertices (10,000 Edges)**
-  ![Chart_4](https://github.com/Bilal-3582/Projects/blob/main/Parallelization%20%26%20%20Computing/charts/Chart_04.jpg)

- **N=1000 Vertices (1 Million Edges)**
- ![Chart_5](https://github.com/Bilal-3582/Projects/blob/main/Parallelization%20%26%20%20Computing/charts/Chart_05.jpg)

- **Floyd-Warshall N=100** Communication & Computation (X = Cores , Y = Time)
- ![Chart_6](https://github.com/Bilal-3582/Projects/blob/main/Parallelization%20%26%20%20Computing/charts/Chart_06.jpg)

  - THE Difference between OMP and MPI in Floyd Warshall is very high, so visible that the OMP on scale seems almost negligible.

---

## **Conclusion**  
Okay so, this is very straightforward for n-ary search algorithm, when we divide the array into subarrays onto different processes/threads, they automatically speedup, by a lot, the main thing to notice is that MPI was 5 times faster than OMP, this was the case here because we did not take into account the communication time in start, only the computation time, once broadcasted the subarrays there was no communication between processes in between of computing algorithm, hence we find a similar trend even when we increase number of processes.

However, this changes for Floyd Warshall. We can see that the trend is very abrupt however OMP runs faster ALWAYS than MPI here, and there is a stable trend in OMP because there is 3 nested loops in FW algorithm, One collapse clause does the trick neat and easy, hence a stable trend with no communication in between, just parallel computation. But in MPI when we divide the 2D arrays on different processes we need for n^2 to communicate with all other processes for updated data each iteration this becomes very communication intensive which does not provide us with our desired speedup, and as we increase the number of processes the time taken increases due to extreme communication overhead, for the same number of vertices !


---

## **References**  
- [Floyd-Warshall Algorithm](https://www.hindawi.com/journals/am/2015/575687/)  
- [N-Ary Search](https://www.researchgate.net/publication/220284100_Parallel_Tree_Search_for_Combinatorial_Problems_a_Comparative_Study_between_OpenMP_and_MPI)  

---
