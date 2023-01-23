# Streaming Fair DR-submodular Maximization over Integer Lattice
## Dataset preparing
### Dataset: [ca-GrQc](http://snap.stanford.edu/data/ca-GrQc.html)
### 1.Extract n different FromNodeIDs from the ca-GrQc data as element E. The element is hashed and mapped to 1..... n.
### 2.A set in the submodule function which corresponds to each element FromNodeID is composed of ToNodeIDs corresponding to FromNodeID;
***
## Data Input
### 1. Input the number of elements *n* and the number of sets *m*
#### (Randomly assign n elements to m sets to ensure that no two sets shall have common element and each set shall be assigned at least one element); 
### 2. Input the elements of m sets 
### 3. Input the constraint of m sets *k<sub>1</sub>...k<sub>m</sub>*
### 4. Input the constraint vector of n elements *b*
### The required parameters of the sub-module function f(x): 
### 1. Input the elements of n sets
### 2. Input the overflow constraint of each element *d*
***
## Testing process
### Run the STREAM.cpp, OFFLINE.cpp, RANDOM.cpp, and OPTIMUM.cpp directly. 
### The input data is in the input.txt file, and the result data is in the "algorithm name_output.txt" file. 
### Change the input data by modifying the input.txt file.
***
