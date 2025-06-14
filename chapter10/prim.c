#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
#define INF 1000L

typedef struct GraphType {
    int n;
    int weight[MAX][MAX];
}GraphType;

int selected[MAX];
int distance[MAX];

int get_min_vertex(int n){
    int v, i;
    for(i = 0; i < n; i++){
        if(!selected[i]){
            v = i;
            break;
        }
    }for (i = 0; i < n; i++){
        if(!selected[i] && (distance[i] < distance[v]))
            v = i;
    }
    return v;
}

void prim(GraphType *g, int s){
    int i, u, v;
    for(u = 0; u < g->n; u++)
        distance[u] = INF;
    distance[s] = 0;
    for(i = 0; i < g->n; i++){
        u = get_min_vertex(g->n);
        selected[u] = TRUE;
        if(distance[u] == INF) return ;
        printf("정점 %d 추가\n", u);
        for(v = 0; v<g->n; v++){
            if(g->weight[u][v] != INF){
                if(!selected[v] && g-> weight[u][v] < distance[v])
                    distance[v] = g->weight[u][v];
            }
        }
    }
}