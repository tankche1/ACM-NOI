# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=25;
int n,m;
int a[maxn][maxn];int b[maxn][maxn];

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            b[i][j]=j;
        }
    }
}

bool check(){
    for(int i=1;i<=n;i++){
        int num=0;
        for(int j=1;j<=m;j++) if(a[i][j]!=b[i][j]) num++;
        if(num>2) return false;
    }
    return true;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    init();
    if(check()) {puts("YES");return 0;}
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            init();
            for(int k=1;k<=n;k++) swap(b[k][i],b[k][j]);
            if(check()) {puts("YES");return 0;}
        }
    }
    puts("NO");
    return 0;
}
