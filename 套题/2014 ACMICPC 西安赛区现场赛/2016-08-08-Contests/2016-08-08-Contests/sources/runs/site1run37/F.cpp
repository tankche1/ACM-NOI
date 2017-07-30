#include <bits/stdc++.h>
using namespace std;
#define LL long long

const LL pp=(1e9)+7;

LL Test,N,M,K,ans,r1,r2;

LL quick(LL x,LL y){
	LL s=1,t=x;
	for (;y;y>>=1){
		if (y&1)s=s*t%pp;
		t=t*t%pp;
	}
	return s;
}

LL C(LL M,LL K){
	LL r1=1,r2=1;
	for (int i=0;i<K;i++)r1=r1*(M-i)%pp;
	for (int i=1;i<=K;i++)r2=r2*i%pp;
	r2=quick(r2,pp-2);
	r1=r1*r2%pp;
	return r1;
}

int main() {
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	cin >> Test;
	for (int tt=1;tt<=Test;tt++){
		cin >> N>> M >> K;
		cout << "Case #"<<tt<<": ";
		if (K==1){
			if (N==1)ans=M;
			else ans=0;
			cout<<ans<<endl;
			continue;
		}
		r1=C(M,K)*K%pp*quick(K-1,N-1)%pp;
		r2=C(M,K-1)*(K-1)%pp*quick(K-2,N-1)%pp;
		ans=r1-r2;
		if (ans<0)ans+=pp;
		cout<<ans<<endl;
	}
	return 0;
}
