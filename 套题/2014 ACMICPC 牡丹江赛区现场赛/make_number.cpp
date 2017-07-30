# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
const int maxn=200010;

int n;
int p[maxn];

int find(int x){
    if(p[x]==x) return x;
    return p[x]=find(p[x]);
}

int main(){
    srand(time(NULL));
    n=10;
    printf("1\n%d\n",n);
    for(int i=1;i<=n;i++) p[i]=i;
    int a,b,pa,pb;

    for(int i=1;i<n;i++){
        a=rand()%n+1;
        pa=find(a);
        for(int j=1;j<=n;j++){
            pb=find(j);
            if(pa!=pb){
                p[pb]=pa;printf("%d %d\n",a,j);break;
            }
        }
    }
    return 0;
}
