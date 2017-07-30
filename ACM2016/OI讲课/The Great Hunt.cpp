# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;
int qa[maxn],qb[maxn];

void add_edge(int a,int b){
    next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int dfn[maxn],col[maxn],c_cnt=0,dfs_clock,rfn[maxn],anc[maxn];

void dfs1(int x,int fa){
    col[x]=c_cnt;
    for(int e=first[x];e!=-1;e=next[e]){
        if(v[e]==fa) continue;
        dfs1(v[e],x);
    }
}

void dfs2(int x,int fa){
    dfn[x]=++dfs_clock;rfn[dfs_clock]=x;
    for(int e=first[x];e!=-1;e=next[e]){
        if(v[e]!=fa) dfs2(v[e],x);
    }
}

int bh;
struct SegmenTree{
    bool cover[maxn<<2];
    int T[maxn<<2];
    //bool T[maxn<<2],lazyT[maxn<<2];

    void build(int o,int L,int R){
        cover[o]=0;T[o]=0;
        if(L==R) return;
        int M=(L+R)>>1;
        build(o<<1,L,M);build(o<<1|1,M+1,R);
        cover[o]=cover[o<<1]&cover[o<<1|1];
    }

    void update1(int o,int L,int R,int pos){
        if(L==R) {cover[o]=1;return;}
        int M=(L+R)>>1;
        if(pos<=M) update1(o<<1,L,M,pos);
        else update1(o<<1|1,M+1,R,pos);
        cover[o]=cover[o<<1]&cover[o<<1|1];
    }

    void update2(int o,int L,int R,int pos){
        if(L==R) {T[o]=bh;return;}
        int M=(L+R)>>1;
        if(pos<=M) update2(o<<1,L,M,pos);
        else update2(o<<1|1,M+1,R,pos);
        T[o]=(T[o<<1]==T[o<<1|1])?T[o<<1]:0;
    }

    int find(int o,int L,int R,int qL,int qR){
        int p,M=(L+R)>>1;
        if(qL<=L&&qR>=R){
            if(cover[o]) return false;
            if(L==R) return L;
            p=find(o<<1,L,M,qL,qR);if(p) return p;
            p=find(o<<1|1,M+1,R,qL,qR);if(p) return p;
        }
        if(qL<=M){
            p=find(o<<1,L,M,qL,qR);if(p) return p;
        }
        if(qR>M){
            p=find(o<<1|1,M+1,R,qL,qR);if(p) return p;
        }
        return false;
    }

    int find2(int o,int L,int R,int qL,int qR){
        int p,M=(L+R)>>1;
        if(qL<=L&&qR>=R){
            if(T[o]==bh) return false;
            if(L==R) return L;
            p=find2(o<<1,L,M,qL,qR);if(p) return p;
            p=find2(o<<1|1,M+1,R,qL,qR);if(p) return p;
        }
        if(qL<=M){
            p=find2(o<<1,L,M,qL,qR);if(p) return p;
        }
        if(qR>M){
            p=find2(o<<1|1,M+1,R,qL,qR);if(p) return p;
        }
        return false;
    }
}seg;
int left[maxn];

bool find(int x){
    int pos;
    if(col[qa[x]]==col[qb[x]]){
        if(dfn[qa[x]]>dfn[qb[x]]) swap(qa[x],qb[x]);
        pos=seg.find(1,1,n,dfn[qa[x]],dfn[qb[x]]);
        if(pos){
            seg.update1(1,1,n,pos);left[rfn[pos]]=x;return true;
        }else{
            while(1){
                pos=seg.find2(1,1,n,dfn[qa[x]],dfn[qb[x]]);
                if(pos){
                    seg.update2(1,1,n,pos);
                    if(find(left[rfn[pos]])) {left[rfn[pos]]=x;return true;}
                }
                else break;
            }
        }
    }
    else{
        pos=seg.find(1,1,n,dfn[1],dfn[1]);
        if(pos) {seg.update1(1,1,n,pos);left[rfn[pos]]=x;return true;}
        pos=seg.find(1,1,n,dfn[anc[col[qa[x]]]],dfn[qa[x]]);
        if(pos) {seg.update1(1,1,n,pos);left[rfn[pos]]=x;return true;}
        pos=seg.find(1,1,n,dfn[anc[col[qb[x]]]],dfn[qb[x]]);
        if(pos) {seg.update1(1,1,n,pos);left[rfn[pos]]=x;return true;}

        while(1){
            pos=seg.find2(1,1,n,dfn[1],dfn[1]);
            if(pos){
                seg.update2(1,1,n,pos);
                if(find(left[rfn[pos]])) {left[rfn[pos]]=x;return true;}
            }
            else break;
        }
        while(1){
            pos=seg.find2(1,1,n,dfn[anc[col[qa[x]]]],dfn[qa[x]]);
            if(pos){
                seg.update2(1,1,n,pos);
                if(find(left[rfn[pos]])) {left[rfn[pos]]=x;return true;}
            }
            else break;
        }
        while(1){
            pos=seg.find2(1,1,n,dfn[anc[col[qb[x]]]],dfn[qb[x]]);
            if(pos){
                seg.update2(1,1,n,pos);
                if(find(left[rfn[pos]])) {left[rfn[pos]]=x;return true;}
            }
            else break;
        }
    }
    return false;
}

int print[maxn];
void solve(){
    bool ok=true;
    memset(left,-1,sizeof(left));
    for(int i=1;i<=n;i++){
        bh=i;
        if(!find(i)) {ok=false;break;}
    }
    if(!ok) puts("No");
    else{
        puts("Yes");
        for(int i=1;i<=n;i++) print[left[i]]=i;
        printf("%d",print[1]);
        for(int i=2;i<=n;i++)
            printf(" %d",print[i]);
        puts("");
    }
}

int main(){
    int a,b;
    scanf("%d",&n);
    edge=0;memset(first,-1,sizeof(first));
    for(int i=1;i<n;i++){
        scanf("%d%d",&a,&b);
        add_edge(a,b);add_edge(b,a);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d",&qa[i],&qb[i]);
    }
    for(int e=first[1];e!=-1;e=next[e]){
        ++c_cnt;
        dfs1(v[e],1);
        anc[c_cnt]=v[e];
    }

    dfs_clock=0;
    dfs2(1,1);

    seg.build(1,1,n);
    solve();
    return 0;
}
