#include<stdio.h>
#include<string.h>
# include<map>
# include<vector>
# include<math.h>
#include<algorithm>
using namespace std;
typedef long long LL;
LL P,K,A;
int g,j;//g^j=a

void gcd(LL a,LL b,LL &d,LL &x,LL &y){
	if(b==0){
		d=a;x=1;y=0;return;
	}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}

LL inv(LL a,LL n){
	LL d,x,y;
	gcd(a,n,d,x,y);
	return d==1?(x+n)%n:-1;
}

LL pow_mod(LL a,LL m,LL n){
	if(m==0) return 1;
	LL half=pow_mod(a,m>>1,n);
	half=half*half%n;
	if(m&1) half=half*a%n;
	return half;
}

LL log_mod(LL a,LL b,LL n){
	LL m,v,e=1;
	m=(LL)sqrt(n+0.5);
	v=inv(pow_mod(a,m,n),n);
	map<int,int> x;
	x[1]=0;
	for(int i=1;i<m;i++){
		e=e*a%n;
		if(!x.count(e)) x[e]=i;
	}
	for(int i=0;i<m;i++){
		if(x.count(b)) return i*m+x[b];
		b=b*v%n;
	}
	return -1;
}
vector<LL> f;

bool check(LL g,LL p){
	for(LL i=0;i<f.size();i++){
		if(pow_mod(g,(p-1)/f[i],p)==1) 
			return 0;
	}
	return 1;
}

LL find_PrimitiveRoot(LL n){
	LL tmp=n-1;
	f.clear();
	for(LL i=2;i*i<=tmp;i++){
		if(tmp%i==0){
			f.push_back(i);
			while(tmp%i==0)
				tmp/=i;
		}
	}
	if(tmp>1) f.push_back(tmp);
	LL g=0;
	while(++g){
		if(check(g,n)) return g;
	}
}
vector<LL> ans;

void Line_mod(LL a,LL b,LL n){//ax=b(mod n)
	LL d,x,y;
	gcd(a,n,d,x,y);
	if(b%d) return;
	x%=n;x+=n;x%=n;
	ans.push_back(x*(b/d)%(n/d));
	for(LL i=1;i<d;i++)
		ans.push_back((ans[0]+i*(n/d))%n);
}

int main(){
	scanf("%lld%lld%lld",&P,&K,&A);
	if(A==0) {puts("1");puts("0");return 0;}
	g=find_PrimitiveRoot(P);
	j=log_mod(g,A,P);
	Line_mod(K,j,P-1);
	for(int i=0;i<ans.size();i++)
		ans[i]=pow_mod(g,ans[i],P);
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%lld\n",ans[i]);
	return 0;
}
