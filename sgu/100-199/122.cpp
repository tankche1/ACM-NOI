/*
sgu122 搞满足有ore性质的图的哈密尔顿圈
Ore性质：图H中任意两个不相邻的顶点x,y,都有deg(x)+deg(y)>=n,则H具有Ore性质。deg表示该点的度。
具有Ore性质的图是连通的。
若简单图G满足Ore性质，且阶数n>=3,则这个图有汉密尔顿圈。
*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int a[maxn][maxn];
int n;

bool vis[maxn];
int link[maxn],tp;

bool find_right(){
	for(int i=1;i<=n;i++)
		if(!vis[i]&&a[link[tp]][i]){
			link[++tp]=i;vis[i]=1;return true;
		}
	return false;
}

bool find_left(){
	for(int i=1;i<=n;i++)
		if(!vis[i]&&a[link[0]][i]){
			vis[i]=1;
			for(int j=tp+1;j>1;j--)
				link[j]=link[j-1];
			link[1]=i;tp++;return true;
		}
	return false;
}

void adjust(){
	for(int i=2;i<n-1;i++)
		if(a[link[1]][link[i+1]]&&a[link[i]][link[tp]]){
			for(int j=i+1;j<(tp-(j-(i+1)));j++)
				swap(link[j],link[tp-(j-(i+1))]);
			break;
		}
	return;
}

int main(){
	int to;char t;
	memset(a,0,sizeof(a));
	scanf("%d",&n);getchar();
	for(int i=1;i<=n;i++){
		while(scanf("%d%c",&to,&t)!=EOF){
			a[i][to]=a[to][i]=1;
			if(t=='\n') break;
		}
	}
	link[1]=1;vis[1]=1;tp=1;
	while(1){//这样写比较快 注释掉的TLE了... 这丧心病狂的卡时
		/*if(find_right()) continue;
		if(find_left()) continue;
		adjust();
		if(tp>=n) break;*/
		 if(find_right())continue;
            else
            {
                for(int k=1;k<=tp+1-k;k++)
                    swap(link[k],link[tp+1-k]);
                if(find_right())continue;
            }
            
            if(find_left())continue;
            adjust();//,i--;
			if(tp>=n) break;
	}
	
	int pos;
	for(pos=1;pos<=n;pos++) if(link[pos]==1) break;
	for(int i=pos;i<=n;i++) printf("%d ",link[i]);
	for(int i=1;i<pos;i++) printf("%d ",link[i]);
	printf("1\n");
	return 0;
}
