# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef unsigned long long LL;
LL n,k;
LL num[800000];
LL cnt;
vector<LL> A;

LL ans;

void check(){
	LL tot=0,now;
	for(int i=0;i<(int)A.size();i++){
		tot=0;
		now=A[i];
		while(1){
			if(now>n) break;
			tot+=n/now;
			if(n/A[i]>=now) now=(LL)now*A[i];
			else break;
			//printf("tot:%I64d now:%I64d\n",tot,now);
		}
		ans=min(ans,tot/num[i]);
	}
	//printf("true\n");
}

int main()
{
	//freopen("big.in","r",stdin);
	//freopen("big.out","w",stdout);
	LL Tcase;
	int t=0;
	scanf("%I64d",&Tcase);
	while(Tcase--){
		printf("Case %d: ",++t);
		cnt=0;
		scanf("%I64d%I64d",&n,&k);
		memset(num,0,sizeof(num));
		A.clear();
		for(LL i=2;(LL)i*i<=k;i++){
			if(k%i==0) {
				A.push_back(i),cnt++;}
			while(k%i==0) {k/=i,num[cnt-1]++;}
		}
		if(k!=1) {A.push_back(k);num[cnt]++;cnt++;}
		ans=n;
		check();
		printf("%I64d\n",ans);
	}
	return 0;
}
