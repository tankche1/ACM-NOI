#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int Mo = 1000000007;
const int M = 1000000;
LL n, m, k, T, J[M+10], IJ[M+10];

LL Pow(LL n, LL p){
	if (n == 0) return 0;
	int ret = 1;
	while (p > 0) {
		if (p%2 == 1) ret = (ret*n)%Mo;
		n = (n*n)%Mo;
		p = p/2;
	}
	return ret;
}

void pre_work(){
	J[0] = 1;
	for(int i = 1; i <= M; i++) J[i] = (J[i-1]*i)%Mo;
	IJ[M] = Pow(J[M],Mo-2);
	for(int i = M-1; i >= 0; i--) IJ[i] = (IJ[i+1]*(i+1))%Mo;
	IJ[0] = 1;
}

LL C(LL n, LL r){
	if (r > n) return 0;
	return J[n]*IJ[r]%Mo*IJ[n-r]%Mo;
}

int main(){
	//freopen("sample.in","r",stdin);
	//freopen("sample.out","w",stdout);
	pre_work();
	cin >> T;
	for(int cs = 1; cs <= T; cs++){
		printf("Case #%d: ", cs);
		cin >> n >> m >> k;
		LL ans = 0;
		ans = k*Pow(k-1,n-1)%Mo-k*(k-1)%Mo*Pow(k-2,n-1)%Mo;
		ans = ans*C(m,k)%Mo;
		cout << (ans%Mo+Mo)%Mo << endl;
	}
}
