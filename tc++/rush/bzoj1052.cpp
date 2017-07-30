# include<stdio.h>
# include<string.h>
# include<algorithm>
# define FUCK printf("fuck\n");
using namespace std;
typedef long long LL;
const int maxn=20010;
const int INF=(~0U>>1)-2;
int n;
LL x[maxn],y[maxn];
bool cut[4][maxn];

bool dfs(int num,LL L){
	//if(L==3){
	//printf("num:%d\n",num);
//	for(int i=1;i<=n;i++) printf("cut[%d]:%d\n",i,cut[num][i]);//}
	bool ok=true;
	for(int i=1;i<=n;i++)
		if(!cut[num][i]) ok=false;
	if(ok) return true;
	if(num==3){
		return false;
	}
	LL max_x=-INF,max_y=-INF,min_x=INF,min_y=INF;
	for(int i=1;i<=n;i++)
		if(!cut[num][i]){
			max_x=max(max_x,x[i]);min_x=min(min_x,x[i]);
			min_y=min(min_y,y[i]);max_y=max(max_y,y[i]);
		}//FUCK
	for(int i=0;i<4;i++){
		//printf("i:%d\n",i);
		LL lx,ly;
		if(i==0) lx=min_x,ly=max_y;
		else if(i==1) lx=max_x-L,ly=max_y;
			else if(i==3) lx=min_x,ly=min_y+L;
				else lx=max_x-L,ly=min_y+L;
		for(int j=1;j<=n;j++) cut[num+1][j]=cut[num][j];
		for(int j=1;j<=n;j++)
			if(x[j]>=lx&&x[j]<=(LL)(lx+L)&&y[j]<=ly&&y[j]>=(LL)(ly-L))
				cut[num+1][j]=1;
		if(dfs(num+1,L)) return true;
	}
	return false;
}

bool can(LL L){
	//printf("L:%lld\n",L);
	memset(cut,0,sizeof(cut));
	return dfs(0,L);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&x[i],&y[i]);
	}
	LL L=1,R=2000000001;
	while(L<=R){
		LL M=(L+R)>>1;
		if(can(M)) R=M-1;
			else L=M+1;
	}
	printf("%lld\n",R+1);
	return 0;
}
