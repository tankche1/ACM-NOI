#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
struct data
{
	int x,y;
	friend bool operator <(data a,data b){
		return min(a.x,b.y)<min(b.x,a.y);
	}
}a[28000];
int N,ans;

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;++i) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+1+N);
	int t(0);
	for(int i=1;i<=N;++i){
		t+=a[i].x;
		ans=max(ans,t)+a[i].y;
	}
	printf("%d\n",ans);
	return 0;
}