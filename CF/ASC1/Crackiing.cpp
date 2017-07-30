# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=110;
int num[310],len;
int t,m;
int A[maxn][maxn];
int C[maxn][maxn];
int prime[maxn];

int gaoss(){
	int line=1,row=1,k;
	bool flag;
	while(line<=t&&row<=m){
		if(A[line][row]==0){
			flag=false;
			for(int j=line+1;j<=t;j++)
				if(A[j][row]==1) {
					flag=true;
					for(k=row;k<=m;k++)
						swap(A[line][k],A[j][k]);
					break;
				}
			if(!flag) {row++;continue;}
		}
			for(int j=line+1;j<=t;j++)
				if(A[j][row]){
					for(k=row;k<=m;k++) A[j][k]^=A[line][k];
			}
		line++;row++;
	}
	return m-line+1;
}

void mutiply_2(){
	for(int i=0;i<len;i++)
		num[i]*=2;
	for(int i=0;i<len;i++)
		if(num[i]>=10) num[i+1]+=num[i]/10,num[i]%=10;
	while(num[len]>0) num[len+1]+=num[len]/10,num[len]%=10,len++;
	return;
}

void minus_1(){
	num[0]--;
	for(int i=0;num[i]<0;i++){
		num[i]+=10;num[i+1]--;
	}
	while(len>1&&num[len-1]==0) len--;
	return;
}

int main()
{
	freopen("rsa.in","r",stdin);
	freopen("rsa.out","w",stdout);
	bool ok;
	int b;
	scanf("%d%d",&t,&m);
	prime[1]=2;
	for(int i=2;i<=t;i++){
		for(int j=prime[i-1]+1;;j++){
			ok=true;
			for(int k=1;k<i;k++)
				if(j%prime[k]==0) {ok=false;break;}
			if(ok) {prime[i]=j;break;}
		}
		//printf("%d ",prime[i]);
	}//puts("");
	memset(C,0,sizeof(C));
	for(int i=1;i<=m;i++){
		scanf("%d",&b);
		for(int j=1;j<=t;j++){
			while(b%prime[j]==0) b/=prime[j],C[j][i]^=1;
		}
	}
	for(int i=1;i<=t;i++){
		for(int j=1;j<=m;j++)
			A[i][j]=C[i][j];
	}
	/*for(int i=1;i<=t;i++){
		for(int j=1;j<=m+1;j++)
			printf("%d ",A[i][j]);
			puts("");
		}*/
	//puts("fuck");
	int free=gaoss();//printf("free:%d\n",free);
	if(free==0) {puts("0");return 0;}
	memset(num,0,sizeof(num));
	num[0]=1;len=1;
	for(int i=1;i<=free;i++)
		mutiply_2();
	minus_1();
	for(int i=len-1;i>=0;i--) printf("%d",num[i]);puts("");
	return 0;
}
