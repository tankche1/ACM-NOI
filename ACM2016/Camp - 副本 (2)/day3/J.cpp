# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,len;
int A[1010];
int top=0;
int G[1010][1010];

bool Area(int x,int y,int l){
    for(int i=x;i<=x+l-1;i++){
        for(int j=y;j<=y+l-1;j++){
            if(G[i][j]!=0) return false;
        }
    }return 1;
}

void Cover(int x,int y,int l,int col){
    for(int i=x;i<=x+l-1;i++){
        for(int j=y;j<=y+l-1;j++){
            G[i][j]=col;
        }
    }
}

bool dfs2(int cur){
    if(cur==0){
            printf("Possible\n");
            printf("%d\n",len);
        for(int i=1;i<=len;i++){
            for(int j=1;j<=len;j++){
                printf("%d ",G[i][j]);
            }puts("");
        }
        //puts("");
        //int tt;scanf("%d",&tt);
        return true;
    }
    for(int i=1;i<=len;i++){
        for(int j=1;j<=len;j++){
            if(i+A[cur]-1<=len&&j+A[cur]-1<=len){
                if(Area(i,j,A[cur])){
                    Cover(i,j,A[cur],cur);
                    if(dfs2(cur-1)) return true;
                    Cover(i,j,A[cur],0);
                }
            }
        }
    }
    return false;
}

bool dfs(int cur,int S){
    if(S==0&&cur==n+1) {
        if(A[n]+A[n-1]>len) return false;
        /*printf("len:%d\n",len);
        for(int i=1;i<cur;i++)
            printf("%d ",A[i]);puts("");*/
        //puts("");//top++;
        if(dfs2(n)) return true;
    }
    else if(cur>n) return false;
    for(int i=A[cur-1];i*i<=S;i++){
        A[cur]=i;
        if(dfs(cur+1,S-i*i)) return true;
    }
    return false;
}
int main(){
    scanf("%d",&n);
    if(n==1) {printf("Possible\n1\n1\n");return 0;}
    if(n==2||n==3||n==5) {printf("Impossible");return 0;}
        //scanf("%d",&n);
        A[0]=1;top=0;
        for(len=1;;len++){
            memset(G,0,sizeof(G));
            if(dfs(1,len*len)) break;
            //if(len>500) {puts("Impossible");break;}
        }
    return 0;
}
