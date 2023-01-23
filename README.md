# Streaming Fair DR-submodular Maximization over Integer Lattice
## Dataset preparing
### [ca-GrQc](http://snap.stanford.edu/data/ca-GrQc.html)
### 1.Extract n different FromNodeIDs from the ca-GrQc data as element e; The element is hashed and mapped to 1..... n.
### 2.A set in the submodule function which corresponds to each element FromNodeID is composed of ToNodeIDs corresponding to FromNodeID;
***
## Data Input
### 1. Input the number of elements *n* and the number of sets *m*
#### (Randomly assign n elements to m sets to ensure that each set does not intersect and there is at least one element); 
### 2. Input the elements of m sets 
### 3. Input the constraint k<sub>j</sub> of m sets 
### 4. Input the constraint vector b<sub>i</sub> of n elements;
### The required parameters of the sub-module function f (x): 
### 1. Input the elements of n sets
### 2. Input the overflow constraint d<sub>i</sub> of each element
***
### You can run the cpp file directly. The input data is in the input.txt file, and the result data is in the "algorithm name_output.txt" file. 
### You can change the input data by modifying the input.txt file.
***
