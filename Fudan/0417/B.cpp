# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
const int maxn=5010;
char s[maxn];

struct Tank{
    int a[15];
    Tank() {memset(a,0,sizeof(a));}
    void clear() {memset(a,0,sizeof(a));}

    bool operator < (const Tank &rhs)const{
        for(int i=0;i<15;i++) if(a[i]!=rhs.a[i]) return a[i]<rhs.a[i];
        return 0;
    }
};

map<Tank,int> id;
int n,m;
Tank C[maxn];
char name[maxn][maxn];

int main(){
    //Tank tmp;
    int cnt=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s);cnt=0;
        for(int j=0;j<=m;j++) name[i][j]=s[j];
        for(int j=0;j<m;j++){
            if(s[j]-'0'==1){
                cnt++;
            }
        }
        if(cnt<8||cnt>15) {C[i].a[0]=-1;continue;}
        cnt=0;C[i].clear();
        for(int j=0;j<m;j++){
            if(s[j]-'0'==1){
                C[i].a[cnt]=j+1;
                cnt++;
            }
        }
        if(!id.count(C[i])) id[C[i]]=1;
        else id[C[i]]++;
    }
    int ans=0,pos=-1;

    for(int i=1;i<=n;i++){
        if(C[i].a[0]==-1) continue;
        if(id[C[i]]>ans) ans=id[C[i]],pos=i;
    }
    //printf("ans:%d pos:%d\n",ans,pos);
    if(pos!=-1)
        puts(name[pos]);
    else{
        for(int i=0;i<8;i++) printf("1");
        for(int i=8;i<m;i++) printf("0");puts("");
    }
    return 0;
}
