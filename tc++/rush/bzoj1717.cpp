# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
typedef unsigned long long ull;
const int seed=1000007;
map<ull,int> id;
ull power[20010];
int n,k;
int a[20010];

bool add(ull res){
	if(!id.count(res)) id[res]=1;
		else id[res]++;
	if(id[res]>=k) return true;
	return false;
}

bool check(int num){
	id.clear();
	ull res=0;
	for(int i=1;i<=num;i++)
		res=res*seed+a[i];
	if(add(res)) return true;
	for(int i=num+1;i<=n;i++){
		res-=power[num-1]*a[i-num];res*=seed;res+=a[i];
		if(add(res)) return true;
	}
	return false;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	power[0]=1;
	for(int i=1;i<=n;i++) power[i]=power[i-1]*seed;
	int L=1,R=n;
	while(L<=R){
		int M=(L+R)>>1;
		if(check(M)) L=M+1;
			else R=M-1;
	}
	printf("%d\n",L-1);
	return 0;
}
