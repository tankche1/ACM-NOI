# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=100010<<1;
int n;
int a[maxn];
int dpl[maxn],dpr[maxn],ansl[maxn],ansr[maxn];
typedef pair<int,int> pi;
set<pi> S;
set<pi> ::iterator it,it2;

int main(){
    freopen("input.txt","r",stdin);
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);a[n+i]=a[i];
        }
        int ans=0,t;

        for(int M=1;M<=2*n;M++){
            if(a[M]==10000){
                   // printf("M:%d\n",M);int aa;scanf("%d",&aa);

                S.clear();S.insert(make_pair(10000,0));
                ans=max(ans,10000);ansl[0]=0;

                t=1;
                for(int i=1;M-i>=1&&i<n;i++){
                    t=i;
                    if(a[M-i]==10000) {ansl[i]=ansl[i-1];continue;}
                    it=S.lower_bound(make_pair(a[M-i],0));
                    dpl[i]=it->second+a[M-i];

                    S.insert(make_pair(a[M-i],dpl[i]));//printf("it:%d %d\n",a[M-i],dpl[i]);

                    it=S.find(make_pair(a[M-i],dpl[i]));

                    while(it!=S.begin()){
                        it--;it2=it;it++;
                        if(it2->first<=it->first&&it2->second<=it->second) S.erase(it2);
                        else break;
                    }
                //    printf("dpl[%d]:%d\n",i,dpl[i]);
                    ansl[i]=max(ansl[i-1],dpl[i]);
                    t=i+1;
                }

                for(;t<n;t++) ansl[t]=ansl[t-1];

                S.clear();S.insert(make_pair(10000,0));ansr[0]=0;
                ans=max(ans,ansl[n-1]+10000);
                for(int i=1;M+i<=2*n&&i<n;i++){
                    if(a[M+i]==10000) {ansr[i]=ansr[i-1];continue;}
                    it=S.lower_bound(make_pair(a[M+i],0));
                    dpr[i]=it->second+a[M+i];

                    S.insert(make_pair(a[M+i],dpr[i]));
                    it=S.find(make_pair(a[M+i],dpr[i]));
                    while(it!=S.begin()){
                        it--;it2=it;it++;
                        if(it2->first<=it->first&&it2->second<=it->second) S.erase(it2);
                        else break;
                    }

                    ansr[i]=max(ansr[i-1],dpr[i]);
                    //printf("it:%d %d\n",a[M+i],dpr[i]);
                    //printf("dpr[%d]:%d\n",i,dpr[i]);
                    ans=max(ans,10000+ansr[i]+ansl[n-1-i]);
                }
               // printf("M:%d ans:%d\n",M,ans);
            }
        }

        printf("%d\n",ans);
    }
    return 0;
}
