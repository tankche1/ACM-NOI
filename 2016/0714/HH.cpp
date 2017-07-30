# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=1000010<<1;
pair<int,int> road[maxm];
int l[maxn],r[maxn];
int n,m;
queue<int> Q;
void del(int i){
    r[l[i]]=r[i];l[r[i]]=l[i];
}

int main(){
    int Tcase=0;
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0&&m==0) break;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&road[i].first,&road[i].second);
            road[m+i].first=road[i].second;road[m+i].second=road[i].first;
            //if(road[i].first>road[i].second) swap(road[i].first,road[i].second);
        }

        m=2*m;
        sort(road+1,road+m+1);
        //for(int i=1;i<=m;i++) printf("%d - %d \n",road[i].first,road[i].second);
        for(int i=1;i<=n+1;i++) l[i]=i-1;l[0]=0;
        for(int i=0;i<n+1;i++) r[i]=i+1;r[n+1]=n+1;

        int ans=0;
        while(!Q.empty()) Q.pop();
        del(1);Q.push(1);
        while(!Q.empty()){
            int x=Q.front();Q.pop();
            int now=lower_bound(road+1,road+m+1,make_pair(x,0))-road;
            //printf("x:%d now:%d\n",x,now);
            for(int i=r[0];i!=n+1;i=r[i]){
                while(road[now].first==x&&road[now].second<i) now++;
                if(road[now].first==x&&road[now].second==i) {now++;continue;}
                del(i);Q.push(i);ans++;
            }
        }

        printf("Case %d: ",++Tcase);
        printf("%d\n",ans);
    }
    return 0;
}
