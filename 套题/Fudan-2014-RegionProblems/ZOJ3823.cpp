# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int A[2010][2010];
int m;
int B[2010][2010];

void rotate1(int x1,int y1,int n){
    int t=A[x1][y1];
    for(int i=x1;i<x1+n;i++){
        for(int j=y1;j<y1+n;j++){
            B[i][j]=A[i][j];
        }
    }
    //printf("x1:%d y1:%d n:%d\n",x1,y1,n);
    for(int i=x1;i<x1+n;i++){
        for(int j=y1;j<y1+n;j++){
            A[x1+n-(j-y1+1)][y1+i-x1]=B[i][j];//printf("%d %d - %d %d\n",x1+n-(j-y1+1),i,i,j);
        }
    }

    for(int i=x1;i<x1+n;i++){
        for(int j=y1;j<y1+n;j++){
            A[i][j]=t+n*n-(A[i][j]-t+1);
        }
    }
}

void solve_even(int n,int bh,int line){
    if(n==2){
        A[line+1][1]=++bh;A[line+1][2]=++bh;
        A[line+2][2]=++bh;A[line+2][1]=++bh;
        //if(n!=m)
            rotate1(line+1,1,n);
        return;
    }
    for(int i=1;i<=n-2;i+=2){
        A[line+1][i]=++bh;A[line+2][i]=++bh;
        A[line+2][i+1]=++bh;A[line+1][i+1]=++bh;
    }
    for(int i=1;i<=n;i+=2){
        A[line+i][n-1]=++bh;A[line+i][n]=++bh;
        A[line+i+1][n]=++bh;A[line+i+1][n-1]=++bh;
    }
    solve_even(n-2,bh,line+2);
    if(n!=m) rotate1(line+1,1,n);
}

void solve_odd(int n,int bh,int line){
    if(n==1){
        A[line+1][1]=++bh;
        if(n!=m) rotate1(line+1,1,n);
        return;
    }

    for(int i=1;i<n;i+=2){
        A[line+1][i]=++bh;A[line+2][i]=++bh;
        A[line+2][i+1]=++bh;A[line+1][i+1]=++bh;
    }

    A[line+1][n]=++bh;A[line+2][n]=++bh;
    for(int i=3;i<n;i+=2){
        A[line+i][n]=++bh;A[line+i][n-1]=++bh;
        A[line+i+1][n-1]=++bh;A[line+i+1][n]=++bh;
    }
    A[line+n][n]=++bh;A[line+n][n-1]=++bh;
    solve_odd(n-2,bh,line+2);

    if(n!=m) rotate1(line+1,1,n);
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&m);
        if(m%2==0) solve_even(m,0,0);
        else solve_odd(m,0,0);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                printf("%d ",A[i][j]);
            }puts("");
        }

    }
    return 0;
}
