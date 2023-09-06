#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main()
{
    float x=11;
    float y=15;

    float sum=x+y;

    for(int i=1;i<=10;i++){
        printf("%d\n",i);
    }
    int j=0;
    while(j<5){
        printf("%d",j);
        j++;
    }
    if(x!=10){
        printf("%f",x);
        printf("HelloWorld");
    }
    else{
        printf("TataWorld");
    }

    return 0;
}