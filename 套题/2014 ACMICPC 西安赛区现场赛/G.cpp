# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
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
}Tree1,Tree2;
char s1[maxn],s2[maxn];
int len1,len2;

LL ans=0;
void dfs(int x,int y){
    for(int i=0;i<26;i++){
        if(Tree1.ch[x][i]&&Tree2.ch[y][i]){
            ans+=(LL)Tree1.cnt[Tree1.ch[x][i]]*Tree2.cnt[Tree2.ch[y][i]];
            dfs(Tree1.ch[x][i],Tree2.ch[y][i]);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%s%s",s1,s2);
        len1=strlen(s1);
        len2=strlen(s2);
        Tree1.init();Tree2.init();

        for(int i=0;i<len1;i++) Tree1.add(s1[i]);
        for(int i=0;i<len2;i++) Tree2.add(s2[i]);

        Tree1.count();Tree2.count();ans=0;
        dfs(0,0);dfs(1,1);

        printf("Case #%d: ",Tcase);
        printf("%I64d\n",ans);
    }
    return 0;
}
