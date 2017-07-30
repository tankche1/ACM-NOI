# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=4010;
int n;
int v[maxn],d[maxn];LL p[maxn];
bool tp[maxn];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&v[i],&d[i],&p[i]);
    int x;
    int cure=0;
    int ans[maxn];ans[0]=0;
    for(int i=1;i<=n;i++){
        if(tp[i]==true) continue;
        cure++;ans[++ans[0]]=i;
        x=v[i];
        for(int j=i+1;x>0&&j<=n;j++){
            if(tp[j]) continue;
            p[j]-=x;
            x--;
        }
        for(int j=i+1;j<=n;j++){
            if(tp[j]) continue;
            if(p[j]<0){
                for(int k=j+1;k<=n;k++) p[k]-=d[j];
                tp[j]=1;
            }
        }

    }
    printf("%d\n",cure);printf("%d",ans[1]);
    for(int i=2;i<=ans[0];i++) printf(" %d",ans[i]);puts("");
    return 0;
}
