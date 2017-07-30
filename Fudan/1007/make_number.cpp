/*# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;

int main(){
    srand(time(NULL));
    int n=10000;
    puts("5");
    for(int i=1;i<=5;i++){
        int m=rand()%1000000000+1;
        printf("%d %d\n",n,m);
        for(int i=1;i<=n;i++)
            printf("%d ",rand()%1000000000);puts("");
        int q=rand()%10000+1;
        for(int i=1;i<=q;i++){
            if(i&1){
                    printf("M ");
                int len=rand()%n+1;
                int L=rand()%(n-len+1)+1;
                int x=rand()%1000000000;
                printf("%d %d %d\n",L,L+len-1,x);
            }
            else{
                int len=rand()%n+1;
                int L=rand()%(n-len+1)+1;
             printf("Q %d %d\n",L,L+len-1);
            }
        }
    }
    return 0;
}*/
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define LL long long
using namespace std;
char ch;
int Test,N,M,Q,l,r;
LL a[10010],ans,x;
LL gcd(LL a,LL b){
	if (!b)return a;
	return gcd(b,a%b);
}
int main(){
	srand(time(0));
	//freopen("E.in","w",stdout);
	int Test=1;
	printf("%d\n",Test);
	while (Test--){
		N=5;
		M=6;
//		M=(((LL)rand()<<15)^rand())%100000000+1;
		printf("%d %d\n",N,M);
		for (int i=1;i<=N;i++){
			//a[i]=(((LL)rand()<<15)^rand())%100000000;
			a[i]=rand()%6;
			printf("%lld ",a[i]);
		}
		printf("\n");
		Q=5;
		printf("%d\n",Q);
		for (int i=1;i<=Q;i++){
			int t=rand()%3;
//			int t=rand()%2;
			if (t==0){
				l=rand()%N+1,r=rand()%N+1;
				if (l>r)swap(l,r);
				printf("Q %d %d\n",l,r);
			}else if (t==1){
				l=rand()%N+1,r=rand()%N+1;
				if (l>r)swap(l,r);
				x=rand()%3+1;
				bool flag=0;
				for (int j=l;j<=r;j++)
					if (a[j]>1e16)flag=1;
//				x=(((LL)rand()<<15)^rand())%100000000;
				if (flag)x=1;
				for (int j=l;j<=r;j++)a[j]=a[j]*x;
				printf("M %d %d %lld\n",l,r,x);
			}else if (t==2){
				l=rand()%N+1,r=rand()%N+1;
				if (l>r)swap(l,r);
				x=a[l];
				for (int j=l;j<=r;j++){
					x=gcd(x,a[j]);
				}
				if (x==0)x=1;
				for (int j=l;j<=r;j++)a[j]=a[j]/x;
				printf("D %d %d %lld\n",l,r,x);
			}
/*			if (i%3==1){
				l=rand()%N+1,r=rand()%N+1;
				if (l>r)swap(l,r);
				x=(((LL)rand()<<15)^rand())%100000000;
				printf("M %d %d %lld\n",l,r,x);
			}
			if (i%3==2){
				printf("D %d %d %lld\n",l,r,x);
			}
			if (i%3==0){
				l=rand()%N+1,r=rand()%N+1;
				if (l>r)swap(l,r);
				printf("Q %d %d\n",l,r);
			}*/
		}
	}
}
