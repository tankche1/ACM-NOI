# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=50010;
const int maxm=33*maxn;
int n;
int a[maxn];
char s[maxn][33];
int cnt[maxn];
int print[maxn];

struct Trie{
    int ch[maxm][2],sz;
    bool val[maxm];

    void init(){
        ch[0][0]=ch[0][1]=0;sz=0;
    }

    void clear(){
        for(int i=0;i<=sz;i++) val[i]=0;
    }

    void insert(char *s,int n){
        int u=0,c;
        for(int i=0;i<n;i++){
            c=s[i]-'0';
            if(!ch[u][c]){
                ch[u][c]=++sz;ch[sz][0]=ch[sz][1]=0;
            }
            u=ch[u][c];
        }
    }

    bool find(char *s,int n,int limit,int i){
        int u=0,c,last=-1,now=0,tank;
        for(int i=0;i<n;i++){
            c=s[i]-'0';
            u=ch[u][c];now<<=1;if(c&1) now^=1;
            //printf("now:%d\n",now);
            if(now>limit) break;
            if(!val[u]) last=u,tank=now;
        }
        if(last==-1) return false;
        val[last]=1;print[i]=tank;//printf("%d last:%d\n",a[i],tank);
        return 1;
    }
}trie;


bool check(int limit){
    trie.clear();
    //printf("limit:%d\n",limit);
    for(int i=1;i<=n;i++){
        if(!trie.find(s[i],cnt[i],limit,i)) return false;
    }//puts("fuck");
    return true;
}

int main(){
    scanf("%d",&n);
    int big=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),big=max(big,a[i]);

    trie.init();
    int len,x;
    for(int i=1;i<=n;i++){
        len=0;x=a[i];
        while(x>0){
            if(x&1) s[i][len++]='1';
            else s[i][len++]='0';
            x>>=1;
        }
        for(int j=0;j<len&&j<len-1-j;j++){
            swap(s[i][j],s[i][len-1-j]);
        }
        s[i][len]='\0';//puts(s[i]);

        trie.insert(s[i],len);cnt[i]=len;
    }

    int L=n,R=big,M;
    while(L<=R){
        M=(L+R)>>1;
        if(!check(M)) L=M+1;
        else R=M-1;
    }
    //printf("ans:%d\n",R+1);
    check(R+1);
    for(int i=1;i<=n;i++) printf("%d ",print[i]);puts("");
    return 0;
}
