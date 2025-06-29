#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct GraphNode{
    int vertex;
    struct GraphNode *link;
}GraphNode;

typedef struct GraphType{
    int n;
    GraphNode *adj_list[MAX];
}GraphType;

void init(GraphType *g){
    int v;
    g->n = 0;
    for(v = 0; v < MAX; v++)
        g->adj_list[v] = NULL;
}

void insert_vertex(GraphType *g, int v){
    if(((g->n) + 1) > MAX){
        fprintf(stderr, "그래프 정점 개수 초과");
        return;
    }
    g->n++;
}
void insert_edge(GraphType *g, int u, int v){
    GraphNode *node;
    if(u >= g->n || v >= g->n){
        fprintf(stderr, "그래프 정점 번호 오류");
        return;
    }
    node = (GraphNode *)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

void print_adj_list(GraphType *g){
    int i = 0;
    for(i = 0; i<g->n; i++){
        GraphNode *p = g->adj_list[i];
        printf("정점 %d의 인접리스트 ", i);
        while(p != NULL){
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

int main(){
    GraphType *g;
    int i;
    g = (GraphType *)malloc(sizeof(GraphType));
    init(g);
    for(i = 0; i < 4; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 1);
    insert_edge(g, 1, 0);
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 3);
    insert_edge(g, 3, 0);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);

    print_adj_list(g);
    free(g);
    return 0;
}