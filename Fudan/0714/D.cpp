# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=10010;
multiset<int> s;
multiset<int>::iterator it;
int a[maxn];
int main(){
	int tcase,num,n,b,c,mid;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&num,&n);
		printf("%d %d\n",num,n/2+1);
		s.clear();
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		b=a[1];
		mid=b;s.insert(b);
		printf("%d ",b);
		it=s.find(b);
		for(int i=3;i<=n;i+=2){
			//printf("i:%d\n",i);
			b=a[i-1];c=a[i];
			s.insert(b);s.insert(c);
			if((b<=mid&&c>=mid)||(b>=mid&&c<=mid)) printf("%d ",mid);
			else if(b<=mid&&c<=mid) {
				it--;mid=*it;
				printf("%d ",mid);
			}
			else if(b>=mid&&c>=mid){
				it++;mid=*it;
				printf("%d ",mid);
			}if(((i+1)/2)%10==0) puts("");
		}
		if(((n+1)/2)%10) puts("");
	}
	return 0;
}
