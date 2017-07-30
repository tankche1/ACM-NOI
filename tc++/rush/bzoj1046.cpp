# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int inf=1<<30;

int n,m;
int a[maxn],f[maxn];
int maxlen;

void DP(){
	maxlen=0;
	int q[maxn];q[0]=0;
	q[++q[0]]=0;
	f[0]=0;a[0]=inf;
	for(int i=1;i<=n;i++){
		int L=1,R=q[0];
		while(L<=R){
			int M=(L+R)>>1;
			if(a[q[M]]>a[i]) L=M+1;
				else R=M-1;
		}
		f[i]=f[q[L-1]]+1;
		if(f[i]>maxlen){
			maxlen=f[i];
			q[++q[0]]=i;
		}
		else{
			int L=1,R=q[0];
			while(L<=R){
				int M=(L+R)>>1;
				if(f[q[M]]<=f[i]) L=M+1;
					else R=M-1;
			}
			q[L-1]=i;
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[n-i+1]);
	DP();
	//printf("%d\n",maxlen);
	scanf("%d",&m);
	int L;
	int ans[maxn];
	while(m--){
		scanf("%d",&L);
		int l=L;ans[0]=0;
		if(L>maxlen) puts("Impossible");
			else{
				for(int i=n;i>=1;i--){
				//	printf("f[%d]:%d\n",i,f[i]);
					if(f[i]>=l&&(ans[0]==0||ans[ans[0]]<a[i])){
						//printf("hey\n");
						ans[++ans[0]]=a[i];
						if(--l==0) break;
					}
				}
				for(int i=1;i<ans[0];i++)
					printf("%d ",ans[i]);
				printf("%d\n",ans[ans[0]]);
			}
	}
	return 0;
}
