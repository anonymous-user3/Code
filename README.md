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
### 2. Input the overflow constraint of elements *d*
***
## Testing process
### The input and output data of our experiments are provided in the ‘data appendix’ folder according to the specific experiment and setting. The input data is pre-processed in the respective ‘SAMPLE’ folder from the original ‘DATA.txt’, while other folders of ‘OFFLINE’, ‘RANDOM’, and ‘STREAM’ hold output results from the respective algorithm. For each experiment, under each size of data (e.g., n=200), we average over 10 runs of data (e.g., 1.txt, 2.txt, …, 10.txt) with different randomly generated/simulated constraints. To witness the result as claimed in the paper, the user needs to make sure that the C++ ‘freopen’ function in the source codes selects the correct input data file path (e.g., "data appendix\real_world_data(figure-d,e,f)\n=200\SAMPLE\1.txt").
***
## Sample
### Download the code and run the STREAM.cpp, OFFLINE.cpp, RANDOM.cpp, or OPTIMUM.cpp directly. 
### In this test sample，the input data is in the input.txt file, and the result data is in the "algorithm name_output.txt" file. 
***
