# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=202;
const int maxm=50012;
int n,m,q;
int p[maxn][maxm];
int a[maxn][maxm];
int input[maxm][5];
int op[maxm];

int find(int i,int x){ return p[i][x]==x?x:p[i][x]=find(i,p[i][x]);
}
char s[maxn];

bool cir(LL a,LL b,LL c,LL d,LL r){
	return (a-c)*(a-c)+(b-d)*(b-d)<=r*r;
}

void cover(int row,int L,int R,int c){
	int x=L;x=find(row,x);
	while(x<=R){
		a[row][x]=c;p[row][x]=x+1;
		x=find(row,x);
	}
}

int num[10];
int main(){
while(scanf("%d %d %d\n",&n,&m,&q)!=EOF){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+5;j++)
			p[i][j]=j,a[i][j]=0;
	int xc,yc,c,l,w;int r;
	for(int tt=1;tt<=q;tt++){
		scanf("%s",s);scanf("%d%d%d%d",&input[tt][0],&input[tt][1],&input[tt][2],&input[tt][3]);
		if(s[0]=='C'){
			op[tt]=1;
		}
		else if(s[0]=='D') op[tt]=2;
		else if(s[0]=='R') op[tt]=3,scanf("%d",&input[tt][4]);
		else op[tt]=4;
	}
	int j,L,R;
	for(int tt=q;tt>=1;tt--){
		//printf("tt:%d op[tt]:%d\n",tt,op[tt]);
		xc=(int)input[tt][0];yc=input[tt][1];xc++;yc++;
		if(op[tt]==1){
			r=input[tt][2];c=input[tt][3];
			for(int i=max(1,xc-r);i<=xc+r&&i<=n;i++){
				j=r*r-(i-xc)*(i-xc);
				L=max(1,yc-(int)sqrt(j));
				R=min(yc+(int)sqrt(j),m);
				//printf("i:%d L:%d R:%d\n",i,L,R);
				cover(i,L,R,c);
			}
		}
		else if(op[tt]==2){
			r=input[tt][2];c=input[tt][3];
			for(int i=max(1,xc-r);i<=xc+r&&i<=n;i++){
				L=max(1,yc-(r-abs(i-xc)));R=min(m,yc+(r-abs(i-xc)));
				cover(i,L,R,c);
			}
		}
		else if(op[tt]==3){
			l=input[tt][2];w=input[tt][3];c=input[tt][4];
			L=yc;R=min(m,yc+w-1);
			for(int i=xc;i<=n&&i<=xc+l-1;i++){
				cover(i,L,R,c);
			}
		}
		else{
			w=input[tt][2];c=input[tt][3];
			l=yc-(w+1)/2+1;r=yc+(w+1)/2-1;
			for(int i=xc;i<=n&&l<=r;l++,r--,i++){
				L=max(1,l);R=min(m,r);
				cover(i,L,R,c);
			}
		}
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				printf("%d ",a[i][j]);puts("");
			}puts("");*/
	}
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			num[a[i][j]]++;
	for(int i=1;i<9;i++) printf("%d ",num[i]);printf("%d\n",num[9]);
}
	return 0;
}
