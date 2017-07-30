# include<stdio.h>
# include<string.h>
# include<math.h>
# include<map>
# include<set>
# include<algorithm>
using namespace std;
const int MOD=100000007;
typedef long long LL;

LL mul_mod(LL a,LL b){
	return (a*b)%MOD;
}

LL pow_mod(LL a,LL x){
	if(x==0) return 1;
	LL half=pow_mod(a,x/2);
	LL ans=mul_mod(half,half);
	if(x%2==1) ans=mul_mod(ans,a);
	return ans;
}

LL inv(LL a){
	return pow_mod(a,MOD-2);
}

LL log_mod(LL a,LL b){//a^x%m==b
	map<LL,LL> x;
	x[1]=0;
	LL p=1;
	int m=(int)sqrt(MOD);
	for(int i=1;i<m;i++){
		p=mul_mod(p,a);
		if(!x.count(p)) x[p]=i;
	}
	LL v=inv(mul_mod(p,a));//a^(-m)
	for(int i=0;i<m;i++){
		if(x.count(b)) return i*m+x[b];
		b=mul_mod(b,v);
	}
	return -1;
}

LL N,K,B,R,bigm;
LL x[510],y[510];
set<pair<LL,LL> > bset;

LL count(){
	LL ans=0;LL c=0;
	for(int i=1;i<=B;i++){
		if(x[i]!=bigm&&!bset.count(make_pair(x[i]+1,y[i]))){
			c++;
		}
		if(x[i]==1) c--;
	}
	c+=N;
	ans=mul_mod(pow_mod(K-1,bigm*N-c-B),pow_mod(K,c));
	return ans;
}

LL solve(){
	LL cnt=count(),c=0;
	if(cnt==R) return bigm;
	for(int i=1;i<=B;i++)
	if(x[i]==bigm) c++;
	cnt=mul_mod(cnt,mul_mod(pow_mod(K,c),pow_mod(K-1,N-c)));
	//if(cnt==R) return bigm+1;
	LL v=mul_mod(inv(cnt),R);
	LL P=pow_mod(K-1,N);
	return log_mod(P,v)+bigm+1;
}

int main(){
	//freopen("in.txt","r",stdin);
	LL T;
	scanf("%lld",&T);
	for(int kase=1;kase<=T;kase++){
		scanf("%lld%lld%lld%lld",&N,&K,&B,&R);
		bset.clear();bigm=1;
		for(int i=1;i<=B;i++){
			scanf("%lld%lld",&x[i],&y[i]);
			bigm=max(bigm,x[i]);
			bset.insert(make_pair(x[i],y[i]));
		}
		printf("Case %d: %lld\n",kase,solve());
	}
	return 0;
}
