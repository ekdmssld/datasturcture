#include <stdio.h>
#include <stdlib.h>
#define MAX 50

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
void print_adj_mat(GraphType *g){
    int i, j;
    for(i = 0; i < g->n; i++){
        for(j = 0; j < g->n; j++)
            printf("%2d ", g->adj_mat[i][j]);

        printf("\n");
    }
}

int main(){
    GraphType *g;
    int i = 0;
    g = (GraphType *)malloc(sizeof(GraphType));

    init(g);
    for(i = 0; i < 4; i++)
        insert_vertex(g, i);
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    print_adj_mat(g);

    free(g);
    return 0;

}