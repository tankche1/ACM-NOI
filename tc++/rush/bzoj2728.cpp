#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int Step=60;
const int maxn=1010;
LL Two[70];
LL n,k,L,R;
LL A[maxn];
bool isfirst[70];
int pre[70];
int col[70];
int g[70][70];

LL cal(LL R){
	if(R<0) return 0;
	LL ans=0;
	memset(col,-1,sizeof(col));
	LL now=0;
	for(int bit=k;bit>=1;bit--){
		if(isfirst[bit]){
			if(now+Two[bit-1]<=R){
				col[bit]=1;
				int D=0;
				for(int i=bit-1;i>=1;i--)
					if(isfirst[i]) D++;
				ans+=Two[D];
				now+=Two[bit-1];
			}
			else{
				col[bit]=0;
			}
		}
		else{
			int fa=col[pre[bit]];
			if(fa==1){
				if(now+Two[bit-1]<=R)
					col[bit]=1,now+=Two[bit-1];
				else break;
			}
			else{
				if(now+Two[bit-1]<=R){
					int D=0;
					for(int i=bit-1;i>=1;i--)
						if(isfirst[i]) D++;
					ans+=Two[D];break;
				}
				else{
					col[bit]=0;
				}
			}
		}
		if(bit==1) ans++;
	}
	//printf("R:%lld ans:%lld\n",R,ans);
	return ans;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	Two[0]=1;
	for(int i=1;i<=Step;i++)
		Two[i]=Two[i-1]<<1;
	scanf("%lld%lld%lld%lld",&n,&k,&L,&R);
	if(R>=Two[k]) R=Two[k]-1;
	if(L>=Two[k]) L=Two[k];
	for(int i=1;i<=n;i++)
		scanf("%lld",&A[i]);
	for(int i=1;i<=k;i++)
		for(int j=i+1;j<=k;j++){
			bool ok=true;
			for(int l=1;l<=n;l++)
				if(((A[l]>>(i-1))&1)==((A[l]>>(j-1))&1))
					continue;
				else {ok=false;break;}
			g[i][j]=g[j][i]=ok;
			//	printf("g[%d][%d]:%d\n",i,j,g[i][j]);
		}
	for(int i=1;i<=k;i++){
		isfirst[i]=1;
		for(int j=k;j>=i+1;j--)
			if(g[i][j]){
				isfirst[i]=false;pre[i]=j;break;
			}
		//	printf("isfirst[%d]:%d pre[%d]:%d\n",i,isfirst[i],i,pre[i]);
		}
	printf("%lld\n",cal(R)-cal(L-1));
	return 0;
}
/*
2 4 1 16
5 11
*/
