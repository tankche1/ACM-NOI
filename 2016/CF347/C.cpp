# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=10000000;
int n,m;

int first[maxn],next[maxn<<1],v[maxn<<1],bh[maxn<<1],edge=0;
int col[maxn<<1];

bool vis[maxn];

void add_edge(int a,int b,int _bh){
    next[edge]=first[a];v[edge]=b;bh[edge]=_bh;first[a]=edge++;
}

int want;

void press(int x){
    for(int e=first[x];e!=-1;e=next[e]){
        col[bh[e]]^=1;
    }
}

int S[maxn],top=-1;
int S2[maxn],top2=-1;

void Backup(){
    while(top>=0){
        press(S[top--]);
    }
}

void backup2(){
    while(top2>=0){
        vis[S2[top2--]]=0;
    }
}

int dfs(int x){
    vis[x]=true;S2[++top2]=x;
    for(int e=first[x];e!=-1;e=next[e]){
        if(vis[v[e]]){
            if(col[bh[e]]!=want) return -1;
        }
        else{
            if(col[bh[e]]!=want){
                press(v[e]);S[++top]=v[e];
            }
            if(dfs(v[e])==-1) return -1;
        }
    }
    //vis[x]=false;
    return 0;
}

int tank1[maxn],tank2[maxn];

int main(){
    int a,b;
    char op;
    scanf("%d%d",&n,&m);
    memset(first,-1,sizeof(first));edge=0;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        add_edge(a,b,i);
        add_edge(b,a,i);
        while((op=getchar())&&op!='B'&&op!='R');
        col[i]=op=='B' ? 0 : 1;
    }

    int num1,num2;
    int ans[2];
    ans[0]=ans[1]=0;
    for(want=0;want<2;want++){
        memset(vis,false,sizeof(vis));
        bool ok=true;
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                top=-1;top2=-1;num1=dfs(i)==-1?INF:top+1;Backup();backup2();
                press(i);S[top=0]=i;top2=-1;
                num2=dfs(i)==-1?INF:top+1;Backup();
                if(num1==INF&&num2==INF) {ok=false;break;}
                else ans[want]+=min(num1,num2);
            }
        }
        if(!ok) ans[want]=INF;
    }

    if(ans[0]==INF&&ans[1]==INF) puts("-1");
    else{
        want=ans[0]<ans[1]?0:1;
        printf("%d\n",ans[want]);
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                top=-1;top2=-1;num1=dfs(i)==-1?INF:top+1;
                tank1[0]=0;for(int i=0;i<=top;i++) tank1[++tank1[0]]=S[i];
                Backup();backup2();
                press(i);S[top=0]=i;top2=-1;
                num2=dfs(i)==-1?INF:top+1;
                tank2[0]=0;for(int i=0;i<=top;i++) tank2[++tank2[0]]=S[i];
                Backup();

                if(tank1[0]<tank2[0]){
                    for(int i=1;i<=tank1[0];i++) printf("%d ",tank1[i]);
                }
                else{
                    for(int i=1;i<=tank2[0];i++) printf("%d ",tank2[i]);
                }
            }
        }
        puts("");
    }
    return 0;
}
