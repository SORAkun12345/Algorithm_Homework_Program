#include<stdio.h>

void sort(int N[],int n){
    for(int i=1;i<=n-1;i++){
        int key=N[i];
        int j=i-1;
        while(j>=0 && N[j]>key){
            N[j+1]=N[j];
            j--;
        }
        N[j+1]=key;
    }
}

void printPosition(int N[],int n,int key){
    int position = -1;
    for(int i=1;i<=n;i++){
        if(N[i]==key){
            position = i;
        }
    }
    printf("%d\n",position);
}

int main(){
    int n;
    scanf("%d",&n);

    int N[n+1];
    for(int i=1;i<=n;i++){
        scanf("%d",&N[i]);
    }

    sort(N,n);

    int m;
    scanf("%d",&m);

    for(int i=0;i<m;i++){
        int key;
        scanf("%d",&key);
        printPosition(N,n,key);
    }

    return 0;
}