# include<stdio.h>
# include<string.h>
# include<bitset>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=30010;

bitset<32> bit(0);
bitset<32> bit_ip;
int n;
int a[maxn][5];
bool root[maxn*32];
int L[maxn*32],R[maxn*32],cnt;
vector<pair< bitset<32> , int> > ans;

void insert(const bitset<32> &bit_ip,int u,int dep,int maxdep){
    if(dep==maxdep){
        root[u]=true;return;
    }
    if(bit_ip[32-dep-1]==1){
            //printf("R\n");
        if(R[u]==-1){cnt++;L[cnt]=R[cnt]=-1;root[cnt]=0;R[u]=cnt;}
        insert(bit_ip,R[u],dep+1,maxdep);
    }
    else{
        //printf("L\n");
        if(L[u]==-1) {cnt++;L[cnt]=R[cnt]=-1;root[cnt]=0;L[u]=cnt;}
        insert(bit_ip,L[u],dep+1,maxdep);
    }
    return;
}
int hei;

void query(int u,int dep){
    if(root[u]) return;
    if(u==-1){
        //for(int i=31;i>=0;i--) hei=bit[i],printf("%d",hei);
        //puts("");
        ans.push_back(make_pair(bit,dep));return;
    }

    bit[32-dep-1]=1;
    query(R[u],dep+1);
    bit[32-dep-1]=0;
    query(L[u],dep+1);
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        printf("Case #%d:\n",Tcase);
        cnt=0;root[0]=0;L[0]=R[0]=-1;
    //memset(root,0,sizeof(root));memset(L,-1,sizeof(L));memset(R,-1,sizeof(R));

        scanf("%d",&n);
        if(n==0){
            printf("1\n0.0.0.0/0\n");continue;
        }

        LL tmp;
        for(int i=1;i<=n;i++){
            tmp=0;
            scanf("%d.%d.%d.%d/%d",&a[i][0],&a[i][1],&a[i][2],&a[i][3],&a[i][4]);
            for(int j=0;j<4;j++)
                tmp=tmp*256+a[i][j];
            //printf("tmp:%I64d\n",tmp);
            //bit_ip=bitset<32> (tmp);
            bitset<32> bit_ip(tmp);
            //for(int i=32;i>=1;i--) hei=bit_ip[i],printf("%d",hei);

            insert(bit_ip,0,0,a[i][4]);
        }
        ans.clear();
        query(0,0);
        int res=0;
        printf("%d\n",(int)ans.size());
        for(int i=0;i<(int)ans.size();i++){
            for(int j=3;j>=0;j--){
                res=0;
                for(int k=7;k>=0;k--)
                    res=(res<<1)+ans[i].first[j*8+k];
                printf("%d",res);if(j>0) printf(".");
            }
            printf("/%d\n",ans[i].second);
        }
    }
    return 0;
}
