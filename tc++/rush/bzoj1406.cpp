# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
int n;
typedef set<int>::iterator it;
int main(){
	scanf("%d",&n);
	set<int> s;
	for(int a=1;a*a<=n;a++)
		if(n%a==0){
		int b=n/a;
		for(int x=1;x<n;x+=b)
			if((x+1)%a==0)
				s.insert(x);
		for(int x=b-1;x<n;x+=b)
			if((x-1)%a==0)
				s.insert(x);
		}
		for(it i=s.begin();i!=s.end();i++)
			printf("%d\n",*i);
	return 0;
}
