#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
double F[102][65536];  
int N,K,t;  
int V[20];  
int D[20];  
int P[21];  
int main(){  
    for (int i=1;i<=20;i++) P[i]=1<<(i-1);  
    scanf("%d%d",&N,&K);  
    for (int i=1;i<=K;i++){  
        scanf("%d",V+i);  
        scanf("%d",&t);  
        while (t){  
            D[i]+=P[t];  
            scanf("%d",&t);  
        }  
    }  
    for (int i=N;i;i--)  
        for (int j=0;j<=P[K+1]-1;j++){  
            F[i][j]=0;  
            for (int k=1;k<=K;k++)  
                if ((D[k]&j)==D[k])  
                    F[i][j]+=max(F[i+1][j],F[i+1][j|P[k]]+V[k]);//如果可以吃掉k就考虑吃不吃  
                else  
                    F[i][j]+=F[i+1][j];//否则  
            F[i][j]/=double(K);  
        }  
    printf("%.6lf\n",F[1][0]);  
}  
