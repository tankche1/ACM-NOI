#include<stdio.h>
# include<math.h>
# include<vector>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxb=400;
int n,c,m;
int A[maxn];
int ans=0;
int stack[maxn],top=-1;
int cal[maxb][maxb];
int start[maxb],end[maxb];
int num[maxn];
int C[maxn];
int st[maxn],ed[maxn];
int b[maxn];
int vis[maxn];

void clear(){
	while(top>=0)
		vis[stack[top--]]=false;
}

int find(int key,int rL,int rR){
	int L=st[key],R=ed[key];
	while(L<=R){
		int M=(L+R)>>1;
		if(b[M]>=rL) R=M-1;
			else L=M+1;
	}
	int t=R+1;
	L=st[key],R=ed[key];
	while(L<=R){
		int M=(L+R)>>1;
		if(b[M]<=rR) L=M+1;
			else R=M-1;
	}
	int tt=L-1;
	//printf("key:%d rL:%d rR:%d t:%d tt:%d tot:%d\n",key,rL,rR,t,tt,tt-t+1);
	return tt-t+1;
}

int main(){
//freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	int L,R,l,r,now=1;
	scanf("%d%d%d",&n,&c,&m);
	
	memset(C,0,sizeof(C));
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),C[A[i]]++;
	for(int i=1;i<=c;i++) st[i]=now,ed[i]=now+C[i]-1,now+=C[i];
	for(int i=1;i<=c;i++) num[i]=st[i];
	for(int i=1;i<=n;i++)
		b[num[A[i]]++]=i;
	//for(int i=1;i<=n;i++) printf("b[%d]:%d\n",i,b[i]);
	
	int len=sqrt(n),bcnt=ceil(n/(len*1.0));
	for(int i=1;i<bcnt;i++) start[i]=(i-1)*len+1,end[i]=i*len;
	start[bcnt]=(bcnt-1)*len+1;end[bcnt]=n;
	for(int i=1;i<=bcnt;i++){
		memset(num,0,sizeof(num));ans=0;
		for(int j=i;j<=bcnt;j++){
			for(int k=start[j];k<=end[j];k++){
				num[A[k]]++;if(!(num[A[k]]&1)) ans++;else if(num[A[k]]!=1) ans--;
			}
			cal[i][j]=ans;
			//printf("cal[%d][%d]:%d st[j]:%d ed[j]:%d\n",i,j,ans,start[j],end[j]);
		}
	}
	
	ans=0;
	memset(vis,false,sizeof(vis));
	for(int tt=1;tt<=m;tt++){
		scanf("%d%d",&l,&r);
		L=(l+ans)%n+1;R=(r+ans)%n+1;
		if(L>R) swap(L,R);
		int pos1=ceil(L/(len*1.0)),pos2=ceil(R/(len*1.0));
		ans=0;
		clear();
		if(pos1+1>=pos2){
			for(int i=L;i<=R;i++)
				if(!vis[A[i]]) stack[++top]=A[i],vis[A[i]]=1;
				else vis[A[i]]++;
			for(int i=0;i<=top;i++){
				int x=stack[i];
				if((vis[x]&1)==0) ans++;
			}
		}
		else{
			ans=cal[pos1+1][pos2-1];
			for(int i=L;i<=end[pos1];i++)
				if(!vis[A[i]]) stack[++top]=A[i],vis[A[i]]=1;
				else vis[A[i]]++;
			for(int i=start[pos2];i<=R;i++)
				if(!vis[A[i]]) stack[++top]=A[i],vis[A[i]]=1;else vis[A[i]]++;
			for(int i=0;i<=top;i++){
				int x=stack[i];
				//int tot=find(x,L,R);
				int mid=find(x,start[pos1+1],end[pos2-1]);
				int tot=vis[x]+mid;
				//printf("x:%d tot:%d mid:%d cal:%d\n",x,tot,mid,cal[pos1+1][pos2-1]);
				if(mid>1&&(!(mid&1))) ans--;
				if(tot>1&&(!(tot&1))) ans++;
			}
			//printf("top:%d\n",top);
		}
		printf("%d\n",ans);
	}
	return 0;
}
