#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
int n,sum1[maxn][maxn],sum2[maxn][maxn],sum3[maxn][maxn],sum4[maxn][maxn];
char s[maxn][maxn];
int h[maxn];
int stack[maxn],top;
int ans=0;
const int mod=10007;
int tot2[maxn][maxn],tot4[maxn][maxn];

void prepare(){
	//左上角
	int area;memset(h,0,sizeof(h));
	for(int i=n;i>=1;i--){
		top=-1;stack[++top]=n+1;area=0;
		for(int j=n;j>=1;j--){
			h[j]=s[i][j]=='W'?0:h[j]+1;
			area+=h[j];
			while(top&&h[j]<=h[stack[top]]){
				area-=(h[stack[top]]-h[j])*(stack[top-1]-stack[top]);
				top--;
			}
			stack[++top]=j;
			sum1[i][j]=area>0?(area-1)%mod:0;
			//printf("sum1[%d][%d]:%d h:%d area:%d \n",i,j,sum1[i][j],h[j],area);
		}
	}
	
	//左下角
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		stack[top=0]=n+1;area=0;
		for(int j=n;j>=1;j--){
			h[j]=s[i][j]=='W'?0:h[j]+1;
			area+=h[j];
			while(top&&h[j]<=h[stack[top]]){
				area-=(h[stack[top]]-h[j])*(stack[top-1]-stack[top]);
				top--;
			}
			stack[++top]=j;
			sum2[i][j]=area>0?(area-1)%mod:0;
		}
	}
	//右上角
	area=0;
	memset(h,0,sizeof(h));
	for(int i=n;i>=1;i--){
		stack[top=0]=0;area=0;
		for(int j=1;j<=n;j++){
			h[j]=s[i][j]=='W'?0:h[j]+1;
			area+=h[j];
			while(top&&h[j]<=h[stack[top]]){
				area-=(h[stack[top]]-h[j])*(stack[top]-stack[top-1]);
				top--;
			}
			stack[++top]=j;
			sum3[i][j]=area>0?(area-1)%mod:0;
		}
	}
	//右下角
	area=0;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		stack[top=0]=0;area=0;
		for(int j=1;j<=n;j++){
			h[j]=s[i][j]=='W'?0:h[j]+1;
			area+=h[j];
			while(top&&h[j]<=h[stack[top]]){
				area-=(h[stack[top]]-h[j])*(stack[top]-stack[top-1]);
				top--;
			}
			stack[++top]=j;
			sum4[i][j]=area>0?(area-1)%mod:0;
			//printf("sum4[%d][%d]:%d h:%d\n",i,j,sum4[i][j],h[j]);
		}
	}
}

void calc(){
	for(int i=1;i<=n;i++)
		for(int j=n;j>=1;j--){
			tot2[i][j]=tot2[i-1][j]+tot2[i][j+1]+sum2[i][j]-tot2[i-1][j+1];tot2[i][j]%=mod;
		}
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			tot4[i][j]=tot4[i-1][j]+tot4[i][j-1]+sum4[i][j]-tot4[i-1][j-1],tot4[i][j]%=mod;
	
	for(int i=2;i<=n;i++){
		int res=0;
		for(int j=1;j<=n;j++) res+=sum1[i][j];res%=mod;
		//printf("i:%d res:%d * %d\n",i,res,tot4[i-1][n]);
		ans=(ans+res*tot4[i-1][n])%mod;
	}
	
	for(int j=2;j<=n;j++){
		int res=0;
		for(int i=1;i<=n;i++) res+=sum1[i][j];res%=mod;
		ans=(ans+res*tot4[n][j-1])%mod;
	}
	
	for(int i=2;i<=n;i++)
		for(int j=2;j<=n;j++){
			int tt=tot4[i-1][j-1]*sum1[i][j]%mod;ans=(ans+mod-tt)%mod;
		}
		
	for(int i=2;i<=n;i++)
		for(int j=n-1;j>=1;j--){
			int tt=tot2[i-1][j+1]*sum3[i][j]%mod;ans=(ans+mod-tt)%mod;
		}
}

int main(){
	char t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			while((t=getchar())&&t!='B'&&t!='W');s[i][j]=t;
		}
	prepare();
	calc();
	printf("%d\n",ans);
	return 0;
}
