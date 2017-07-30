#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=110;
const int maxm=maxn*100;
int a[maxn],n;
int pp[maxm],qq[maxm];
int mod[10]={1117009,1333001,3770007,100000007,7393,7395,7394,7399,10001,8317};
LL powerp[maxm],powerq[maxm];
int cnt=0;

struct state{
	int p,q;
	state() {}
	state(int p,int q):p(p),q(q) {}
};
state ans[maxm];

bool cmp(state A,state B){
	bool ok=A.q*B.q<0;
	return ok?A.p*B.q>B.p*A.q:A.p*B.q<B.p*A.q;
}

inline int gcd(int a,int b){
	if(a==0) return b;
	return gcd(b%a,a);
}

int main(){
	int x=0,y=0;
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=n;i++){
		if(a[i]!=0) {x=abs(a[i]);break;}
	}
	if(x==0) {printf("1\n0\n");return 0;}
	for(int i=n;i>=0;i--)
		if(a[i]!=0) {y=abs(a[i]);break;}
	pp[0]=qq[0]=0;
	
	for(int i=1;i*i<=x;i++)
		if(x%i==0) {pp[++pp[0]]=i,pp[++pp[0]]=-i;if(i*i!=x) pp[++pp[0]]=x/i,pp[++pp[0]]=-x/i;}
	
	for(int i=1;i*i<=y;i++)
		if(y%i==0) {qq[++qq[0]]=i;if(i*i!=y) qq[++qq[0]]=y/i;}
	
		//for(int i=1;i<=pp[0];i++) printf("p:%d\n",pp[i]);
	for(int i=1;i<=pp[0];i++)
		for(int j=1;j<=qq[0];j++)
			if(gcd(abs(pp[i]),abs(qq[j]))==1){
				int p=pp[i],q=qq[j];
				//printf("p:%d q:%d\n",p,q);
				bool ok=true;
				for(int m=0;m<10;m++){
					powerp[0]=1;powerq[0]=1;
					for(int t=1;t<=n;t++)
						powerp[t]=powerp[t-1]*p%mod[m],powerq[t]=powerq[t-1]*q%mod[m];
					LL res=0;
					for(int i=0;i<=n;i++)
						res=(res+powerp[i]*powerq[n-i]%mod[m]*a[i]%mod[m])%mod[m];
					if(res!=0) {ok=false;break;}
				}
				if(ok) ans[cnt++]=state(p,q);
			}
	if(a[0]==0) ans[cnt++]=state(0,3);
	sort(ans,ans+cnt,cmp);
	printf("%d\n",cnt);
	for(int i=0;i<cnt;i++){
		if(ans[i].q==1||ans[i].p==0) printf("%d\n",ans[i].p);
		else printf("%d/%d\n",ans[i].p,ans[i].q);
	}
	return 0;
}
