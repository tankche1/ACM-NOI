# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef pair<int,int> pi;
vector<pi> print;
int f[16][16][16][2][2][230],pre[16][16][16][2][2][230];
int n,m,k;
int a[16][16];
int val[16][16][16];
int main(){
    //freopen("input.txt","r",stdin);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);

    for(int i=1;i<=n;i++){
        for(int l=1;l<=m;l++){
            for(int r=l;r<=m;r++){
                if(l==r) val[i][l][r]=a[i][r];
                else val[i][l][r]=val[i][l][r-1]+a[i][r];
            }
        }
    }

    int tmp=0;
    memset(f,-1,sizeof(f));

    for(int i=1;i<=n;i++){
        //printf("i:%d\n",i);
        for(int l=1;l<=m;l++){
            for(int r=l;r<=m;r++){
                //printf("l:%d r:%d\n",l,r);
                if(r-l+1<=k) f[i][l][r][1][1][r-l+1]=val[i][l][r];
                if(i==n) continue;
                for(int canl=0;canl<=1;canl++){
                    for(int canr=0;canr<=1;canr++){
                        for(int s=0;s<k;s++){
                            //printf("s:%d\n",s);
                            if(f[i][l][r][canl][canr][s]==-1) continue;
                            for(int l1=canl?1:l;l1<=r;l1++){
                                for(int r1=canr?m:r;r1>=l&&r1>=l1;r1--){
                                    if(r1-l1+1+s<=k){
                                        if(f[i+1][l1][r1][canl&(l1<=l)][canr&(r1>=r)][s+r1-l1+1]==-1||f[i+1][l1][r1][canl&(l1<=l)][canr&(r1>=r)][s+r1-l1+1]<f[i][l][r][canl][canr][s]+val[i+1][l1][r1])
                                        f[i+1][l1][r1][canl&(l1<=l)][canr&(r1>=r)][s+r1-l1+1]=f[i][l][r][canl][canr][s]+val[i+1][l1][r1],
                                        pre[i+1][l1][r1][canl&(l1<=l)][canr&(r1>=r)][s+r1-l1+1]=canr+(canl<<1)+(r<<2)+(l<<6);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int ans=0,ai,al,ar,acanl,acanr,as;
    for(int i=1;i<=n;i++){
        for(int l=1;l<=m;l++){
            for(int r=l;r<=m;r++){
                for(int canl=0;canl<=1;canl++){
                    for(int canr=0;canr<=1;canr++){
                        if(f[i][l][r][canl][canr][k]>ans){
                            ans=f[i][l][r][canl][canr][k];
                            ai=i;al=l;ar=r;acanl=canl;acanr=canr;as=k;
                        }
                    }
                }
            }
        }
    }

    int code;
    printf("Oil : %d\n",ans);
    while(as>0){
           // printf("ai:%d al:%d ar:%d as:%d\n",ai,al,ar,as);
        for(int pos=al;pos<=ar;pos++)
            print.push_back(make_pair(ai,pos));
        code=pre[ai][al][ar][acanl][acanr][as];
        as=as-(ar-al+1);
        acanr=code&1;code>>=1;
        acanl=code&1;code>>=1;
        ar=code&15;code>>=4;
        al=code&15;code>>=4;
        ai=ai-1;

    }

    sort(print.begin(),print.end());
    for(int i=0;i<(int)print.size();i++)
        printf("%d %d\n",print[i].first,print[i].second);
    return 0;
}
