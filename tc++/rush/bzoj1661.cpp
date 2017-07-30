# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
#define dist(a,b,c,d) (c-a)*(c-a)+(d-b)*(d-b)
# define Legel(a,b) (a>=1&&a<=n&&b>=1&&b<=n)
using namespace std;
const int maxn=1005;
int n;
char A[maxn][maxn];
int ans=0;
int dx[2]={1,-1},dy[2]={-1,1};
int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d",&n);
	//for(int i=0;i<=n+2;i++) for(int j=0;j<=n+2;j++) A[i][j]='W';
	for(int i=1;i<=n;i++)
		scanf("%s",A[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(A[i][j]!='B')
			for(int x1=1;x1<=n;x1++)
				for(int y1=1;y1<=n;y1++){
					if(A[x1][y1]!='J') continue;
					if(i==x1&&j==y1) continue;
					for(int tt=0;tt<2;tt++){
						int newx=dx[tt]*(y1-j)+i,newy=dy[tt]*(x1-i)+j;
						if(!Legel(newx,newy)) continue;
						//if(i==3&&j==4) printf("i:%d j:%d x1;%d y1:%d newx:%d newy:%d\n",i,j,x1,y1,newx,newy);
						//printf("%d %d\n",newx,newy);
						if(A[newx][newy]!='J') continue;
						int x2=newx+x1-i,y2=newy+y1-j;
						if(!Legel(x2,y2)) continue;
						if(A[x2][y2]!='J') continue;
						ans=max(ans,dist(x1,y1,i,j));
					}
				}
		}
	}
	printf("%d\n",ans);
	return 0;
}
