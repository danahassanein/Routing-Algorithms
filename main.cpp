#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#define M 5
#define INF 9999

int nbClusters;
std::vector<std::vector<int>> clusters;


// Question 1 : Floyd Warshall


void FloydWarshall_Algo(int **MAT, int n){
    int **path = new int *[n];

    std::cout<<"\nQUESTION 1 :  \n";
    std::cout<<"Shortest path between any pairs of vertices\n\n";

    for (int i = 0; i<n; i++)
        path[i] = new int[n];
    for (int i=0; i<n ; i++)
        for (int j=0; j<n; j++){
            if (MAT[i][j] == 0)
                path[i][j] = INF;
            else
                path[i][j] = MAT[i][j];
        }
    for (int k=0; k<n; k++)
        for (int i =0;i<n; i++)
            for (int j = 0; j < n; j++)
                if (path[i][j]>path[i][k]+path[k][j] )
                    path[i][j] = path[i][k]+path[k][j];

    for (int i =0; i<n;i++){
        for (int j=0; j<n; j++){
            if (path[i][j] == INF)
                std::cout<<"INF  ";
            else
                std::cout<<path[i][j]<<"    ";
        }
        std::cout<<std::endl;
    }
}


//-----------------------------------------------------------------------------------------------
// Question 2 : Kruskal


class Edge{

public:
    int path_cost;
    int path_start;
    int path_end;

};

class Graph{

public:
    Edge *e;
    int a,b;

    Graph(int a, int b){
        e = new Edge[b];
        this->a = a;
        this->b = b;
    }

    void fillEdges(int **MAT, int a){

        int l = 0;
        for (int i = 0; i < a; i++){
            for (int j = 0; j < a; j++){

                if (l < a * a){
                    e[l].path_start = i;
                    e[l].path_end = j;
                    e[l].path_cost = MAT[i][j];
                    l++;
                }
            }
        }
    }
};


class Subset {
public:
    int n;
    int *rnk, *node_parent;

    Subset(int a) {
        n = a;
        node_parent = new int[n+1];
        rnk = new int[n+1];

        for (int i=0; i<=n; i++){
            rnk[i] = 0;
            node_parent[i] = i;
        }
    }

    int find(int u){
        if (u!= node_parent[u])
            node_parent[u] = find(node_parent[u]);
        return node_parent[u];
    }

    void merge(int x, int y){
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            node_parent[y] = x;
        else
            node_parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};


int Comp(const void *s, const void *t){
    Edge *S = (Edge*)s;
    Edge *T = (Edge*)t;
    return S->path_cost > T->path_cost;
}

void Kruskal_Algo(Graph *GRAPH){
    int total=0;
    int A = GRAPH->a;
    Edge *num = new Edge[A];
    int s = 0;
    int i = 0;

    qsort(GRAPH->e, GRAPH->b, sizeof(GRAPH->e[0]), Comp);

    Subset *subset = new Subset(A);

    while (s < A - 1 && i < GRAPH->b){
        Edge next_edge = GRAPH->e[i++];
        int NextStart = subset->find(next_edge.path_start);
        int NextEnd = subset->find(next_edge.path_end );
        if (NextStart !=NextEnd){
            num[s++] = next_edge;
            subset->merge(NextStart ,NextEnd);
        }
    }
    std::cout <<  "\n\nQUESTION 2 :" <<std::endl;
    std::cout << "Which cables should be installed to link\nall data centers at minimum cost : \n" << std::endl;
    for (i=0; i<s; ++i){
        int cost = num[i].path_cost;
        int start = num[i].path_start;
        int end = num[i].path_end;
        total = total + cost;
        std::cout<<start<< " -- " <<end<< "  : " << cost <<std::endl;
    };

    std::cout << "Total cost = " << total << std::endl;
}


//-----------------------------------------------------------------------------------------------
// Question 3 : Trajan


void findSCC(std::stack<int>* st, int **MAT,bool stck[], int V, int u, int disc[], int low[]){
    static int time = 0;
    int CLUSTER;
    std::vector<int> vector;

    disc[u] = low[u] = ++time;
    st->push(u);
    stck[u] = true;

    for (int v = 0; v != V; v++){
        if (MAT[u][v]) {
            if (disc[v] == -1){
                findSCC(st,MAT, stck, V, v, disc, low);
                low[u] = std::min(low[u], low[v]);
            }
            else if (stck[v] == true)
                low[u] = std::min(low[u], disc[v]);
        }
    }
    if (low[u] == disc[u]){
        while (st->top() != u){
            CLUSTER = (int)st->top();
            std::cout<< CLUSTER <<" ";
            vector.push_back(CLUSTER);
            stck[CLUSTER] = false;
            st->pop();
        }
        CLUSTER = (int)st->top();
        vector.push_back(CLUSTER);
        clusters.push_back(vector);
        nbClusters++;
        stck[CLUSTER] = false;
        std::cout << CLUSTER << std::endl;
        st->pop();
    }
}

void Trajan_Algo( int **MAT, Graph *GRAPH)
{
    int* disc = new int[GRAPH->a];
    int* low = new int[GRAPH->a];
    bool* stck = new bool[GRAPH->a];
    std::stack<int>* st = new std::stack<int>();

    for (int i=0; i < GRAPH->a; i++){
        disc[i] = -1;
        low[i] = -1;
        stck[i] = false;
    }

    std::cout << "\n\nQUESTION 3 : " << std::endl;
    std::cout << "Determine clusters using Strongly Connected Components\n" << std::endl;

    for (int i = 0; i < GRAPH->a; i++)
        if (disc[i] == -1)
            findSCC(st, MAT, stck, GRAPH->a, i, disc, low );

    std::cout << "We have " << nbClusters << " clusters" << std::endl;
}


//-----------------------------------------------------------------------------------------------
//  QUESTION 4 : Graph


void graph(int** MAT){

    std::cout << "\n\nQUESTION 4 :\nGraph of clusters\n" << std::endl;
    int** graph_clusters = new int* [nbClusters];
    for (int i = 0; i < nbClusters; i++) {
        graph_clusters[i] = new int[nbClusters];
        for (int j = 0; j < nbClusters; j++)
            graph_clusters[i][j] = 0;
    }

    for (int i = 0; i < clusters.size(); i++) {
        for (int j = 0; j < clusters[i].size(); j++) {
            for (int n=0; n < clusters.size(); n++) {
                for (int m=0; m < clusters[n].size(); m++) {
                    if (MAT[clusters[i][j]][clusters[n][m]] != 0) {
                        bool not_in_same_cluster = true;
                        int a = clusters[n][m];
                        for (int u = 0; u < clusters[i].size(); u++) {
                            if (a == clusters[i][u]) {
                                not_in_same_cluster = false;
                            }
                        }
                        if (not_in_same_cluster) {
                            graph_clusters[i][n] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < nbClusters; i++){
        for (int j = 0; j < nbClusters; j++)
            std::cout << graph_clusters[i][j];
        std::cout << "\n";
    }
}





//-----------------------------------------------------------------------------------------------


int main() {

    int adj, cost, installCost;

    std::ifstream file("mat3.txt");
    std::ifstream file2("cost3.txt");
    std::ifstream file3("instal_cost3.txt");

    if(!file || !file2 || !file3){
        std::cerr << "Cannot open .txt files" << std::endl;
    }

    file >> adj;
    int **ADJ_MAT = new int *[adj];

    file2 >> cost;
    int **COST_MAT = new int *[cost];

    file3 >> installCost;
    int **INSTALL_MAT = new int *[installCost];


    for (int i=0; i<M; i++) {
        ADJ_MAT[i] = new int[adj];
        COST_MAT[i] = new int[cost];
        INSTALL_MAT[i] = new int[installCost];
        for (int j = 0; j < M; j++) {
            file >> ADJ_MAT[i][j];
            file2 >> COST_MAT[i][j];
            file3 >> INSTALL_MAT[i][j];
        }
    }


    file.close();
    file2.close();
    file3.close();


    Graph* g = new Graph(M,M*M);
    FloydWarshall_Algo(COST_MAT, M);
    g->fillEdges(INSTALL_MAT, M);
    Kruskal_Algo(g);
    Trajan_Algo(ADJ_MAT, g);
    graph(ADJ_MAT);

return 0;
}