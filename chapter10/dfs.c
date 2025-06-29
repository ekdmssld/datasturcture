#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 50

typedef struct GraphNode{
    int vertex;
    struct GraphNode *link;
}GraphNode;

typedef struct GraphType{
    int n;
    int adj_mat[MAX][MAX];
}GraphType;


void init(GraphType *g){
    int r, c;
    g->n = 0;
    for(r = 0; r < MAX; r++){
        for(c = 0; c < MAX; c++)
            g->adj_mat[r][c] = 0;
    }
}

void insert_vertex(GraphType *g, int v){
    if(((g->n) + 1) > MAX){
        fprintf(stderr, "그래프 정점 개수 초과");
        return;
    }
    g->n++;
}
void insert_edge(GraphType *g, int start, int end){
    if(start >= g->n || end >= g->n){
        fprintf(stderr, "그래프 정점 번호 오류");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

int visited[MAX];

void dfs_mat(GraphType *g, int v){
    int w;
    visited[v] = TRUE;
    printf("정점 %d -> ", v);
    for(w = 0; w<g->n; w++){
        if(g->adj_mat[v][w] && !visited[w])
            dfs_mat(g,w);
    }
}

int main(){
    GraphType *g;
    int i;

    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for(i = 0; i < 4; i++)
        insert_vertex(g,i);

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    printf("깊이 우선 탐색 \n");
    dfs_mat(g, 0);
    printf("\n");
    free(g);
    return 0;
}