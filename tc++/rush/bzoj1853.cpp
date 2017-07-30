#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
LL A,B;
int tot=-1;
LL pnum[1000*1000];
LL num[1000*1000],cnt=-1;

void getp(LL x){
	if(x>B) return;
	pnum[++tot]=x;
	getp(x*10+6);getp(x*10+8);
}

LL gcd(LL a,LL b){
	if(!a) return b;
	return gcd(b%a,a);
}

LL dfs(int i,LL now){
	if(i>cnt) return B/now-A/now;
	LL ans=dfs(i+1,now);
	
	LL d=gcd(now,num[i]);
	if(now/d<=B/num[i])
		ans-=dfs(i+1,now/d*num[i]);
	return ans;
}

int main(){
	scanf("%lld%lld",&A,&B);A--;
	getp(6);getp(8);
	sort(pnum,pnum+tot+1);
	for(int i=tot;i>=0;i--){
		bool ok=true;
		for(int j=0;j<i;j++){
			if(pnum[i]%pnum[j]==0){
				ok=false;break;
			}
		}
		if(ok) {num[++cnt]=pnum[i];}
	}
	
	printf("%lld\n",B-A-dfs(0,1));
	return 0;
}
