# include<stdio.h>
# include<queue>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int m,n;
int s[25];
bool f[maxn];
int step[maxn];
int cnt;
int main(){
	scanf("%d",&m);
	for(n=1;;n++){
		int g=n*n*n*n;
		if(g>m) break;
		s[n]=g;
	}n--;
	f[0]=1;step[0]=0;
	queue<int> q;q.push(0);
	for(cnt=1;;cnt++){
		int ste=step[q.front()];
		while(!q.empty()){
			int x=q.front();if(step[x]!=ste) break;//printf("%d\n",x);
			q.pop();
			for(int i=1;i<=n;i++)
				if(!f[s[i]+x]) {f[s[i]+x]=1;
					if(f[m]) {printf("%d\n",ste+1);return 0;}
					q.push(s[i]+x);step[s[i]+x]=ste+1;
				}
		}
	}
	return 0;
}
