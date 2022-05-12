#include<stdio.h>

void pointer_test(int* number){
    *number=30;
}

int main(){
    int numbers=0;
    pointer_test(&numbers);
    printf("number: %d", numbers);
}