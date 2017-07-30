# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=300010;
const int SIGMA=26;
typedef long long LL;

struct Palindromic_Tree{
    int ch[maxn][SIGMA];
    int fail[maxn];
    int cnt[maxn];
    int num[maxn];
    int len[maxn];
    int S[maxn];
    int last;
    int n;
    int p;

    int newnode(int l){
        for(int i=0;i<SIGMA;i++) ch[p][i]=0;
        cnt[p]=num[p]=0;len[p]=l;
        return p++;
    }

    void init(){
        p=0;
        newnode(0);
        newnode(-1);
        last=0;
        n=0;
        S[n]=-1;
        fail[0]=1;
    }

    int get_fail(int x){
        while(S[n]!=S[n-len[x]-1]) x=fail[x];
        return x;
    }

    void add(int c){
        c-='a';
        S[++n]=c;
        int cur=get_fail(last);
        if(!ch[cur][c]){
            int now=newnode(len[cur]+2);
            fail[now]=ch[get_fail(fail[cur])][c];
            ch[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=ch[cur][c];
        cnt[last]++;
    }

    void count(){
        for(int i=p-1;i>=0;i--) cnt[fail[i]]+=cnt[i];
    }
}Tree;
char s[maxn];

int main(){
    scanf("%s",s);
    int n=strlen(s);
    Tree.init();
    for(int i=0;i<n;i++){
        Tree.add(s[i]);
    }
    Tree.count();

    LL ans=0;
    for(int i=0;i<Tree.p;i++){
        ans=max(ans,(LL)Tree.cnt[i]*Tree.len[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
