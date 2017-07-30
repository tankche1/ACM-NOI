# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
int now,num;
const int mod=1000000;
set<int> s;
typedef set<int>::iterator it;
int n,a,op;
bool zero;
int result=0;
int main(){
	scanf("%d",&n);
	zero=true;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&op,&a);
		if(zero){
			s.insert(a);num++;zero=false;now=op;
		}
		else if(now!=op){
			//printf("shit\n");
			it p=s.lower_bound(a);
			int ans=-1;
			if(p!=s.end()) ans=*p;
			if(p!=s.begin()) {p--;if(ans==-1||abs(a-*p)<=abs(a-ans)) ans=*p;}
			//printf("%d\n",ans);
			s.erase(ans);
			result=(result+abs(a-ans))%mod;
			if(--num==0) zero=true;
		}
		else{
			s.insert(a);num++;
		}
	}
	printf("%d\n",result);
	return 0;
}
