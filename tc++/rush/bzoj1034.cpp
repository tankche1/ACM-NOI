# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int t1[maxn],t2[maxn];
int n;

int greedy(int *a,int *b){
	int ans=0;
	a[0]=1;a[n+1]=n;b[0]=1;b[n+1]=n;
	while(a[0]<=a[n+1]){
		 if(a[a[0]]>b[b[0]]){
			ans+=2;
			a[0]++;b[0]++;
		}
		else if(a[a[n+1]]>b[b[n+1]]) {ans+=2;
			a[n+1]--;b[n+1]--;
		}
		else{
			a[0]++;b[n+1]--;
			if(a[a[0]]==b[b[n+1]]) ans++;
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&t1[i]);
		for(int i=1;i<=n;i++) scanf("%d",&t2[i]);
			sort(t1+1,t1+n+1);sort(t2+1,t2+n+1);
	//
	
	
	printf("%d %d\n",greedy(t1,t2),2*n-greedy(t2,t1));
	return 0;
}
