#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=20010;
int n;
int a[maxn];
bool check(int tot){
	int _min,_max,lastmin,lastmax;
	int one=a[1],two=tot-a[1];
	lastmin=lastmax=one;
	for(int i=2;i<=n;i++){
		_min=max(0,a[i]-(two-(a[i-1]-lastmax)));if(_min+lastmax>one) return false;
		_max=min(one-lastmin,a[i]);if((a[i]-_max)+(a[i-1]-lastmin)>two) return false;
		lastmin=_min;
		lastmax=_max;
	}
	return _min==0;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int L=1,R=3000000;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid)) R=mid-1;
			else L=mid+1;
	}
	printf("%d\n",R+1);
	return 0;
}
