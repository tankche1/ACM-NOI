# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=100010;
int m;
char s[maxn];
int n;

inline int lowbit(int x){
    return x&(-x);
}

struct FenwickTree{
    int C[maxn],n;
    void init(int nn) {
        n=nn;for(int i=1;i<=n;i++) C[i]=0;
    }

    void insert(int x,int val){
        while(x<=n) {
            C[x]+=val;x+=lowbit(x);
        }
    }

    int sum(int x){
        int res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
        }
        return res;
    }
}fwt,fwt1;

int now[26];
int num[26];
int _left[27][maxn];

int main(){
    scanf("%d",&m);
    scanf("%s",s+1);n=strlen(s+1);

    memset(now,0,sizeof(now));
    for(int i=1;i<=n;i++){
        now[s[i]-'a']=i;
        for(int c=0;c<26;c++) _left[c][i]=now[c];
    }

    fwt1.init(n);fwt.init(n);

    memset(num,0,sizeof(num));
    for(int c=0;c<26;c++){
        for(int i=1;i<=n;i++) fwt.C[i]=fwt1.C[i];

        int cnt=0;
        for(int i=1;i<=n;i++) if(s[i]=='a'+c) fwt.insert(i,1),cnt++;

        bool ok=false;
        for(int i=1;i<=n-m+1;i++) if(fwt.sum(i+m-1)-fwt.sum(i-1)==0) {ok=true;break;}
        if(ok) {num[c]=cnt;for(int i=1;i<=n;i++) fwt1.C[i]=fwt.C[i];}
        else{
            num[c]=0;
            for(int i=1;i<=n;i++) fwt.C[i]=fwt1.C[i];
            for(int i=1;i<=n-m+1;i++){
                if(fwt.sum(i+m-1)-fwt.sum(i-1)==0){
                    int pos=_left[c][i+m-1];
                    fwt.insert(pos,1);num[c]++;
                }
            }
            break;
        }
    }

    for(int c=0;c<26;c++){
        for(int i=0;i<num[c];i++) printf("%c",'a'+c);
    }puts("");
    return 0;
}
