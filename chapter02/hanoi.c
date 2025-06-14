#include <stdio.h>

void hanoi_tower(int n, char from, char tmp, char to){
    if(n==1)
        printf("원판 1을 %c에서 %c로 이동함 \n", from, to);
    else{
        hanoi_tower(n-1, from, to, tmp);
        printf("원판 %d를 %c에서 %c로 이동함 \n", n, from, to);
        hanoi_tower(n-1, tmp, from, to);
    }
    return ;
}

int main(){
    int n;
    printf("탑 높이를 입력하세요 : ");
    scanf("%d", &n);
    printf("\n\n");

    hanoi_tower(n, 'A', 'B', 'C');
    return 0;
}