#include<cstdio>

const int MAX=15;
const int INF=90000000;
int n,m,K;
int f[MAX][MAX][MAX][MAX*MAX][4];
int map[MAX][MAX];
int oil[MAX][MAX];
int sum[MAX][MAX];
int answer;

//f[i][l][r][k][s]第i行，左l，右r，用k个，边界可否增加，0:00，1:01，2:10，3:11  1不可

int lastl[MAX][MAX][MAX][MAX*MAX][4];
int lastr[MAX][MAX][MAX][MAX*MAX][4];
int lasts[MAX][MAX][MAX][MAX*MAX][4];
int fi=-1,fl=-1,fr=-1,fs=-1,fk=-1;
int ans[MAX][3],tot;

int main()
{
   freopen("input.txt","r",stdin);
    scanf("%d %d %d",&n,&m,&K);
    if(K==0)
    {
        printf("Oil : 0\n");
        return 0;
    }
    int i,j,l,r,k,s,lr,ll,len,v,ns;
    for(i=0;i<n;++i)
        for(j=0;j<m;++j)
            scanf("%d",&map[i][j]);
    for(i=0;i<n;++i)
        for(j=0;j<m;++j)
            sum[i][j]=sum[i][j-1]+map[i][j];
    for(i=0;i<n;++i)
        for(l=0;l<m;++l)
            for(r=l;r<m;++r)
                for(k=0;k<=K;++k)
                    for(s=0;s<4;++s)
                        f[i][l][r][k][s]=-INF;
    for(l=0;l<m;++l)
        for(r=l;r<m;++r)
        {
            for(s=0;s<4;++s)
            {
                f[0][l][r][r-l+1][s]=sum[0][r]-sum[0][l-1];
                if(r-l+1<=K && (answer<f[0][l][r][r-l+1][s]||(answer==f[0][l][r][r-l+1][s]&&r-l+1>fk)) )
                {
                    answer=f[0][l][r][r-l+1][s];
                    fi=0,fl=l,fr=r,fs=s,fk=r-l+1;
                }
            }
        }
    for(i=1;i<n;++i)
        for(l=0;l<m;++l)
            for(r=l;r<m;++r)
            {
                len=r-l+1;
                v=sum[i][r]-sum[i][l-1];
                f[i][l][r][len][0]=v;lastl[i][l][r][len][0]=lastr[i][l][r][len][0]=lasts[i][l][r][len][0]=-1;
                for(k=len;k<=K;++k)
                    for(ll=0;ll<m;++ll)
                        for(lr=ll;lr<m;++lr)
                        {
                            if(lr<l)continue;
                            if(ll>r)continue;
                            for(s=0;s<4;++s)
                            {
                                for(ns=0;ns<4;++ns)
                                {
                                    if(l<ll &&(ns&2)==2 )continue;
                                    if(lr<r &&(ns&1)==1 )continue;
                                    if(ll<l &&(s&2)!=2 )continue;
                                    if(r<lr &&(s&1)!=1 )continue;
                                    if( ( (ns&1)==1) && ((s&1)==0))continue;
                                    if( ( (ns&2)==2) && ((s&2)==0))continue;
                                    if(f[i][l][r][k][s]<f[i-1][ll][lr][k-len][ns]+v)
                                    {
                                        f[i][l][r][k][s]=f[i-1][ll][lr][k-len][ns]+v;
                                        lasts[i][l][r][k][s]=ns;
                                        lastl[i][l][r][k][s]=ll;
                                        lastr[i][l][r][k][s]=lr;
                                    }
                                }
                                if( answer<f[i][l][r][k][s]||(answer==f[i][l][r][k][s]&&k>fk))
                                {
                                    answer=f[i][l][r][k][s];
                                    fi=i,fl=l,fr=r,fs=s,fk=k;
                                }
                            }
                        }
            }
    int tl,tr,ts,tk;
    while(fl!=-1&&fi>=0)
    {
        ans[++tot][0]=fl;
        ans[tot][1]=fr;
        ans[tot][2]=fi;
        i=i-1;
        tl=lastl[fi][fl][fr][fk][fs];
        tr=lastr[fi][fl][fr][fk][fs];
        ts=lasts[fi][fl][fr][fk][fs];
        tk=fk-(fr-fl+1);
        fl=tl,fk=tk,fr=tr,fs=ts;
        --fi;
    }
    printf("Oil : %d\n",answer);
    for(i=1;i<=tot;++i)
        for(j=ans[i][0];j<=ans[i][1];++j)
            oil[ans[i][2]][j]=1;
    for(i=0;i<n;++i)
        for(j=0;j<m;++j)
            if(oil[i][j])
                printf("%d %d\n",i+1,j+1);
    return 0;
}
