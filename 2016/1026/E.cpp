# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;

int n,m;

int edge=0;
int u[100010],v[100010];
int p[100010];
int find(int x){
    if(x==p[x]) return x;
    return p[x]=find(p[x]);
}
int pos(int x,int y){
    return (x-1)*m+y;
}
void add_edge(int x1,int y1,int x2,int y2){
    if(x2>=1&&x2<=n&&y2>=1&&y2<=m){
        edge++;
        u[edge]=pos(x1,y1);v[edge]=pos(x2,y2);
    }
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
            long long ans=0;
    for(int a=1;a<=m;a++){
        for(int b=a+1;b<=m;b++){
            if((a+b)%2==0) continue;
            edge=0;

            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    add_edge(i,j,i-a,j-b);
                    add_edge(i,j,i-a,j+b);
                    add_edge(i,j,i-b,j-a);
                    add_edge(i,j,i-b,j+a);
                    add_edge(i,j,i+a,j-b);
                    add_edge(i,j,i+a,j+b);
                    add_edge(i,j,i+b,j-a);
                    add_edge(i,j,i+b,j+a);
                }
            }

            for(int i=1;i<=n*m;i++) p[i]=i;
            for(int i=1;i<=edge;i++){
                int px=find(u[i]),py=find(v[i]);
                if(px!=py) p[px]=py;
            }

            bool ok=true;
            for(int i=2;i<=n*m;i++) if(find(i)!=find(1)) {ok=false;break;}

            if(ok) ans++,printf("%d  %d\n",a,b);
        }
    }
    printf("%lld\n",ans);
    }
    return 0;
}
