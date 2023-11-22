#include <iostream>
#include "PQueue.cpp"
#include "List.cpp"
#include "Graph.cpp"

void relax(int** matrix, int* pred, int* shortest, int u, int v);
void dijkstra(Graph graph, int starting_vertex);
void BF(Graph graph, int starting_vertex);
void FU(Graph graph);
void primMST(Graph graph);
void kruskalMST(Graph graph);
void mirrored(Graph graph);
bool checking(Graph graph);
void print_result(int* shortest, int* pred, int vertex);
bool search(Graph graph, const int* pred, const int* shortest);