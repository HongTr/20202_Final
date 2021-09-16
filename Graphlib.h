#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "dllist.h"
#include "fields.h"
#define INFINITIVE_VALUE 100000
typedef struct Graph{
    JRB edges;
    JRB vertices;
} Graph;
struct Queue{
    int info;
    double priority;
    struct Queue* link;
};
typedef struct Queue* Queue;
typedef struct index{
    int* pre;
    int* post;
}index;
//Graph
Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge1(Graph graph, int v1, int v2, double trongso);
void addEdge2(Graph graph, int v1, int v2, float trongso);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int* input);
int outdegree(Graph graph, int v, int* output);
int getAdjacentVertices (Graph graph, int v, int* adj);
int NumberVertex(Graph graph);
int DAG(Graph graph);
double getEdgeValue(Graph graph, int v1, int v2);
void dropGraph(Graph graph);

double dijkstra(Graph graph, int start, int stop, int* path, int* length);
void DFS(Graph graph, int start, int stop);
void BFS(Graph graph, int v1, int v2);
int weak_connect(Graph graph, int v1, int v2);
//P_Queue
Queue createQueue();
int IsQueueEmpty(Queue queue);
Queue Enqueue(Queue queue, int item, double priority);
Queue Dequeue(Queue queue, int* output);

//for test
void addVertex_int(Graph graph, int id, int name);
int getVertex_int(Graph graph, int id);
int return_ID(Graph graph, char* name);
void Print_Graph_Map(Graph graph);
void Print_Graph_Vertex(Graph graph);

typedef struct Info{
    double score;
    int count;
    int line;
    double tong_diem;
}Info;

typedef struct Noi_dung{
    int line;
    char cau[1000];
}Noi_dung;