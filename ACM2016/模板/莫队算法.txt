# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
int weight=800,block=300;
vector<int> large;

struct Query{
    int l,r,l_bh,bh;
    Query(){}
}Q[maxn];

bool cmp(Query A,Query B){
    if(A.l_bh!=B.l_bh){
        return A.l_bh<B.l_bh;
    }
    return A.r>B.r;
}

int n,q;
int a[maxn],num[maxn],cnt[maxn],tmp[maxn];
int ans[maxn];
bool vis[maxn];

void reverse(int x){
    int c=a[x];
    if(vis[x]){
        --num[cnt[c]];cnt[c]--;++num[cnt[c]];
    }
    else{
        --num[cnt[c]];cnt[c]++;++num[cnt[c]];
    }
    vis[x]^=1;
}

void move(int &x,int pos){
    while(x<pos){
        x++;
        reverse(x);
    }
    while(x>pos){
        reverse(x);x--;
    }
}

struct HeapNode{
    int x;
    HeapNode(int x=0):x(x) {}
    bool operator < (const HeapNode &rhs)const{
        return x>rhs.x;
    }
};

priority_queue<HeapNode> H;

int get_ans(){
    int res=0;
    int t=1;
    for(int i=1;i<=2*block;i++) tmp[i]=num[i];
    for(int i=1;i<=block;i++){
        if(tmp[i]==0) continue;
        tmp[i*2]+=tmp[i]/2;res+=i*2*(tmp[i]/2);
        tmp[i]=tmp[i]&1;
        if(tmp[i]){
            tmp[i]=0;t=max(t,i+1);
            while(t+i<=2*block&&tmp[t]==0) t++;
            if(t+i<=2*block) tmp[t+i]++,tmp[t]--,res+=t+i;
            else tmp[i]++;
        }
    }

    for(int i=1;i<=2*block;i++){
        for(int j=0;j<tmp[i];j++){
            H.push(HeapNode(i));
        }
    }
    for(int e=0;e<(int)large.size();e++) if(cnt[large[e]]>2*block) H.push(HeapNode(cnt[large[e]]));

    int a,b;
    while(!H.empty()){
        a=H.top().x;H.pop();
        if(H.empty()) break;
        b=H.top().x;H.pop();
        res+=a+b;
        H.push(HeapNode(a+b));
    }

    return res;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),cnt[a[i]]++;

    for(int i=1;i<=100000;i++) if(cnt[i]>block*2) large.push_back(i);
    memset(cnt,0,sizeof(cnt));
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);Q[i].bh=i;
        Q[i].l_bh=Q[i].l/block;
    }
    sort(Q+1,Q+q+1,cmp);

    int l=0,r=0;
    for(int i=1;i<=q;i++){
        move(l,Q[i].l-1);move(r,Q[i].r);
        ans[Q[i].bh]=get_ans();
    }

    for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
    return 0;
}
