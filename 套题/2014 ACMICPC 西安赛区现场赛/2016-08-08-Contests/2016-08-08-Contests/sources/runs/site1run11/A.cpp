#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
int a[105];
bool check() {
	for(int i=1;i<=n;i++)
		if(a[i]%3!=0)return false;
	return true;
}
int main() {
	int tc;
	scanf("%d",&tc);
	for(int tt=1;tt<=tc;tt++) {
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		printf("Case #%d: ",tt);
		if(check()) 
			printf("Yes\n");
		else
			printf("No\n");
	}
}
