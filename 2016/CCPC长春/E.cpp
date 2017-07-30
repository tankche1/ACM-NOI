# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
int first[maxn],_next[maxn<<1],v[maxn<<1],edge;
int n;
bool isloop[maxn];
int S[maxn],top;
int huan[maxn],cnt;
bool in[maxn],used[maxn<<1];
int fa[maxn];

void add_edge(int a,int b){
    _next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void find_loop(){
    memset(isloop,0,sizeof(isloop));
    memset(in,false,sizeof(in));
    memset(used,false,sizeof(used));
    top=-1;cnt=0;
    S[++top]=1;in[1]=1;
    int u=1;
    while(1){
        Loop:
        u=S[top];//printf("u:%d\n",u);int cc;scanf("%d",&cc);
        for(int e=first[u];e!=-1;e=_next[e]){
            if(used[e]) continue;
            if(in[v[e]]){
                while(S[top]!=v[e]){
                    huan[++cnt]=S[top--];
                }
                huan[++cnt]=S[top--];
                return;
            }
            used[e]=used[e^1]=1;
            S[++top]=v[e];in[v[e]]=1;goto Loop;
        }
        top--;
    }

}

struct Tank{
    int dis,u;
    Tank(int dis=0,int u=0):dis(dis),u(u) {}
    bool operator >(const Tank &rhs)const{
        if(dis!=rhs.dis) return dis>rhs.dis;
        return u<rhs.u;
    }
};
Tank down[maxn];
struct Ans{
    int dis,u,v;
    Ans(int dis=0,int u=0,int v=0):dis(dis),u(u),v(v) {}

    bool operator >(const Ans &rhs)const{
        if(dis!=rhs.dis) return dis>rhs.dis;
        if(u!=rhs.u) return u<rhs.u;
        if(v!=rhs.v) return v<rhs.v;
    }

    bool operator <(const Ans &rhs)const{
        if(dis!=rhs.dis) return dis<rhs.dis;
        if(u!=rhs.u) return u<rhs.u;
        if(v!=rhs.v) return v<rhs.v;
    }
};
Ans dia[maxn],ans;

Tank to;
Ans to2;

void Tree_dp(int x,int anc){

    down[x]=Tank(0,x);
    for(int e=first[x];e!=-1;e=_next[e]){
        if(isloop[v[e]]||v[e]==fa[x]) continue;
        fa[v[e]]=x;
        Tree_dp(v[e],anc);
        to=Tank(down[v[e]].dis+1,down[v[e]].u);

        to2=Ans(to.dis+down[x].dis,min(down[x].u,to.u),max(down[x].u,to.u));
        if(to2>dia[anc]) dia[anc]=to2;
        if(to>down[x]) down[x]=to;
    }
    //printf("down[%d]:%d\n",x,down[x].dis);
}




int main(){
    int Case,a,b;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d",&n);
        memset(first,-1,sizeof(first));
        edge=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
        }

        find_loop();//for(int i=1;i<=cnt;i++) printf("huan[%d]:%d\n",i,huan[i]);
        for(int i=1;i<=cnt;i++) isloop[huan[i]]=1;

        for(int i=1;i<=cnt;i++) dia[huan[i]]=Ans(0,huan[i],huan[i]),Tree_dp(huan[i],huan[i]);

        //for(int i=1;i<=cnt;i++) printf("x:%d dia:%d\n",huan[i],dia[huan[i]]);

        ans=Ans(3*n,1,1);
        for(int u=1;u<=cnt;u++){
            to2=Ans(2*n-cnt-dia[huan[u]].dis,dia[huan[u]].u,dia[huan[u]].v);
           // printf("%d\n",2*n-cnt-dia[huan[u]].dis);
            if(to2<ans) ans=to2;
        }

        //printf("Case #%d: %d %d %d\n",Tcase,ans.dis,ans.u,ans.v);

        Tank big1,big2;big1=Tank(-3*n,0);big2=Tank(-3*n,0);
        for(int u=1;u<=cnt;u++){
            if(u>1){
                to2=Ans(2*n-2-down[huan[u]].dis-u-big1.dis,min(down[huan[u]].u,big1.u),max(down[huan[u]].u,big1.u));
                if(to2<ans) ans=to2;
               // printf("to1:%d\n",2*n-2-down[huan[u]].dis-u-big1.dis);

                to2=Ans(2*n-2-cnt-down[huan[u]].dis+u-big2.dis,min(down[huan[u]].u,big2.u),max(down[huan[u]].u,big2.u));
                //printf("to2:%d\n",2*n-2-cnt-down[huan[u]].dis+u-big2.dis);
                if(to2<ans) ans=to2;
            }
            to=Tank(down[huan[u]].dis-u,down[huan[u]].u);
            if(to>big1) big1=to;

            to=Tank(down[huan[u]].dis+u,down[huan[u]].u);
            if(to>big2) big2=to;


        }

        printf("Case #%d: %d %d %d\n",Tcase,ans.dis,ans.u,ans.v);
    }
    return 0;
}
