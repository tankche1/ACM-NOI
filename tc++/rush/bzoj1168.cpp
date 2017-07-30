# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=22;
typedef long long LL;
const LL INF=1LL<<60;
int col[2][maxn];
int n;
typedef pair<LL,LL> pi;
pi A[1<<20];
int num=0;
int q[1<<20],top;
int main(){
	scanf("%d",&n);
	LL lsum=0,rsum=0;
	for(int c=0;c<2;c++)
		for(int i=1;i<=n;i++){
			scanf("%d",&col[c][i]);//if(c==1) sum+=col[1][i];
			if(!c) lsum+=col[0][i];else rsum+=col[1][i];
		}
	for(int state=0;state<(1<<(n));state++){
		pi p;p.first=p.second=0;
		for(int j=1;j<=n;j++)
			if((state&(1<<(j-1)))==0) p.first+=col[0][j];
				else p.second+=col[1][j];
		A[num++]=p;
				//printf("%lld %lld\n",p.first,p.second);
	}
	sort(A,A+num);top=-1;
	
	for(int i=0;i<num;i++){
		while(top>=0&&A[i].second>=A[q[top]].second) top--;
		q[++top]=i;
	}
	LL l=INF,r=INF;
	//for(int i=0;i<=top;i++)
	//	printf("%lld %lld\n",A[q[i]].first,A[q[i]].second);
	for(int i=0;i<top;i++){
		LL a=A[q[i]].first+1,b=A[q[i+1]].second+1;
		if(!(a<=lsum&&b<=rsum)) continue;
		if(a+b<l+r) l=a,r=b;
		if(a+b==l+r&&a<l) l=a,r=b;
	}
	printf("%lld %lld\n",l,r);
	return 0;
}
