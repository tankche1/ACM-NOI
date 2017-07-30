# include<stdio.h>
# include<string.h>
# include<map>
# include<string>
# include<vector>
# include<algorithm>
using namespace std;
const int mod=1000000007;
const int maxn=100010;
typedef long long LL;
int n;
vector<int> G1[maxn],G2[maxn];
//int P[5]={331,997,1007,10007,99991};
int P[5]={435617, 999983, 327827, 674249, 986191};
char s1[12],s2[12];
char print1[maxn][12],print2[maxn][12];
string S1,S2;
map<string,int> id1,id2;
int id1_cnt,id2_cnt;

int dp1[maxn],dp2[maxn],size[maxn];

void get_dp(int dp[],int x,int fa,vector<int> G[]){
    size[x]=1;dp[x]=0;
    for(int e=0;e<(int)G[x].size();e++){
        if(G[x][e]==fa) continue;
        get_dp(dp,G[x][e],x,G);
        size[x]+=size[G[x][e]];
        dp[x]=max(dp[x],size[G[x][e]]);
    }
    dp[x]=max(dp[x],n-size[x]);
}

struct Node{
    int u,val;
    Node(){}
    Node(int u,int val):u(u),val(val) {}

    bool operator < (const Node &rhs)const{
        return val<rhs.val;
    }
};

vector<Node> H1[maxn],H2[maxn];
int _hash1[maxn],_hash2[maxn];

int fast_pow(int a,int b){
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) {res=res*tmp%mod;}
        tmp=tmp*tmp%mod;
        b>>=1;
    }
    return (int)res;
}

void dfs(int x,int fa,vector<Node> H[],vector<int> G[],int _hash[]){
    H[x].clear();
    for(int e=0;e<G[x].size();e++){
        if(G[x][e]==fa) continue;
        dfs(G[x][e],x,H,G,_hash);
        H[x].push_back(Node(G[x][e],_hash[G[x][e]]));
    }
    sort(H[x].begin(),H[x].end());
    _hash[x]=0;
    for(int e=0;e<H[x].size();e++){
        _hash[x]=((LL)_hash[x]+(LL)fast_pow(P[e%5],(e+1))*H[x][e].val)%mod;
    }
    if(H[x].size()==0) _hash[x]=1;
}

bool check(int root1,int root2){
    dfs(root1,0,H1,G1,_hash1);
    dfs(root2,0,H2,G2,_hash2);
    return _hash1[root1]==_hash2[root2];
}

void print(int a,int b){
    printf("%s %s\n",print1[a],print2[b]);
    for(int e=0;e<H1[a].size();e++){
        print(H1[a][e].u,H2[b][e].u);
    }
}

vector<int> root1,root2;

void solve(){
    get_dp(dp1,1,0,G1);
    get_dp(dp2,1,0,G2);
    int small=n;
    for(int i=1;i<=n;i++) small=min(small,dp1[i]);

    root1.clear();root2.clear();
    for(int i=1;i<=n;i++){
        if(dp1[i]==small) root1.push_back(i);
        if(dp2[i]==small) root2.push_back(i);
    }

    for(int i=0;i<(int)root1.size();i++){
        for(int j=0;j<(int)root2.size();j++){
            if(check(root1[i],root2[j])){
                print(root1[i],root2[j]);
                return;
            }
        }
    }
}

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("shishi.out","w",stdout);
    int len1,len2,a,b;
    while(scanf("%d",&n)!=EOF){
        id1_cnt=id2_cnt=0;id1.clear();id2.clear();
        for(int i=1;i<=n;i++) G1[i].clear(),G2[i].clear();
        for(int i=1;i<n;i++){
            scanf("%s %s",s1,s2);len1=strlen(s1);len2=strlen(s2);
            S1="";S2="";
            for(int i=0;i<len1;i++) S1+=s1[i];
            for(int i=0;i<len2;i++) S2+=s2[i];
            if(!id1.count(S1)) {
                id1[S1]=a=++id1_cnt;
                for(int i=0;i<len1;i++) print1[id1_cnt][i]=s1[i];print1[id1_cnt][len1]='\0';
            }
            else a=id1[S1];

            if(!id1.count(S2)){
                    id1[S2]=b=++id1_cnt;
                    for(int i=0;i<len2;i++) print1[id1_cnt][i]=s2[i];print1[id1_cnt][len2]='\0';
            }
            else b=id1[S2];
            G1[a].push_back(b);G1[b].push_back(a);
        }

        for(int i=1;i<n;i++){
            scanf("%s %s",s1,s2);len1=strlen(s1);len2=strlen(s2);
            S1="";S2="";
            for(int i=0;i<len1;i++) S1+=s1[i];
            for(int i=0;i<len2;i++) S2+=s2[i];
            if(!id2.count(S1)) {
                id2[S1]=a=++id2_cnt;
                for(int i=0;i<len1;i++) print2[id2_cnt][i]=s1[i];print2[id2_cnt][len1]='\0';
            }
            else a=id2[S1];

            if(!id2.count(S2)){
                id2[S2]=b=++id2_cnt;
                for(int i=0;i<len2;i++) print2[id2_cnt][i]=s2[i];print2[id2_cnt][len2]='\0';
            }
            else b=id2[S2];
            G2[a].push_back(b);G2[b].push_back(a);
        }

        solve();
    }
    return 0;
}
