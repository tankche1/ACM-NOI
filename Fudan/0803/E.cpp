# include<stdio.h>
# include<string.h>
# include<math.h>
# include<stack>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
const LL INF=(LL)10000000090000;
int n,ed;
int first[maxn],nnext[maxn<<1],v[maxn<<1],edge;
bool vis[maxn];
LL val[maxn];
int id[maxn];
stack<int> st;

struct tank{
    LL cost,income;
    bool flag;
    tank() {}
    tank(LL cost,LL income,bool flag):cost(cost),income(income),flag(flag){}
    bool operator < (const tank &rhs)const{
        if(cost==rhs.cost) return rhs.income>income;
        return rhs.cost<cost;
    }
};

void add_edge(int a,int b){
    nnext[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs(int x,int fa){
    st.push(x);
    for(int e=first[x];e!=-1;e=nnext[e]){
        if(v[e]==fa) continue;
        dfs(v[e],x);
    }
}

priority_queue<tank> q[maxn];

int imerge(int a,int b){
    if(q[a].size()>q[b].size()) swap(a,b);
    while(!q[a].empty()){
        q[b].push(q[a].top());q[a].pop();
    }
    return b;
}
int main(){
    int tcase,a,b;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d",&n,&ed);
        for(int i=1;i<=n;i++)
            scanf("%I64d",&val[i]);
        memset(first,-1,sizeof(first));edge=0;
        for(int i=1;i<n;i++){
            scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
        }
        while(!st.empty()) st.pop();
        dfs(1,1);//uts("fuck");

        for(int i=1;i<=n;i++){
            id[i]=i;
            while(!q[i].empty()) q[i].pop();
        }
        memset(vis,false,sizeof(vis));
        int now;
        tank tmp,res;
        while(!st.empty()){
            now=st.top();st.pop();vis[now]=1;//printf("now:%d\n",now);
            for(int e=first[now];e!=-1;e=nnext[e]){
                if(!vis[v[e]]) continue;
                id[now]=imerge(id[now],id[v[e]]);
            }
            if(val[now]>=0) tmp=tank(0,val[now],0);
            else tmp=tank(-val[now],0,0);
            while(!q[id[now]].empty()){
                res=q[id[now]].top();
                if(tmp.income<=tmp.cost||tmp.cost>=res.cost){
                    if(res.cost<=tmp.income) tmp.income+=res.income-res.cost;
                    else{
                        tmp.cost+=res.cost-tmp.income;
                        tmp.income=res.income;
                    }
                    tmp.flag|=res.flag;
                }
                else break;
                q[id[now]].pop();
            }
            if(now==ed) tmp.income=INF,tmp.flag=1;
            if(tmp.cost<tmp.income)
                q[id[now]].push(tmp);
        }
        LL hp=0;bool flag=false;
        while(!q[id[1]].empty()){
            res=q[id[1]].top();q[id[1]].pop();
            if(hp>=res.cost) hp+=res.income-res.cost,flag|=res.flag;
            else break;
        }
        if(flag) puts("escaped");
        else puts("trapped");
    }
    return 0;
}
