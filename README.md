# Routing-Algorithms
We model a computer network with a directed graph where we are only concerned whether there is at least one link from a data center to another data center. 

We use a binary matrix A (composed of 0 and 1) of size n × n where the indices of rows and columns correspond to different numbers of data centers encountered. A 1 at the location (i, j) of the matrix means that there is a link from data center i to the data center j. If there is no link between these two data centers, then A(i, j) = 0. Adjacency matrix A may be read in a file as given below :

```
0 1 1 0 0 0 0 0 0 0 0 0 0
0 0 0 1 1 0 0 0 0 0 0 0 0
0 1 0 1 0 0 0 1 0 0 0 0 0
1 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 1 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1 0 0 0
```
