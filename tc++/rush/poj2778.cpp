# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxnode=100+10;
const int mod=100000;

struct Matrix{
	int A[maxnode][maxnode];
};

int id(char c){
	if(c=='A') return 0;
	if(c=='C') return 1;
	if(c=='G') return 2;
	return 3;
}

struct ACmachine{
	int ch[maxnode][4];
	int sz;
	int f[maxnode],last[maxnode];
	int val[maxnode];
	
	void init(){
		sz=0;
		memset(ch[0],0,sizeof(ch[0]));
		val[0]=0;
	}
	
	void insert(char *s){
		int n=strlen(s);
		int u=0;
		for(int i=0;i<n;i++){
			int c=id(s[i]);
			if(!ch[u][c]){
				ch[u][c]=++sz;
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0;
			}
			u=ch[u][c];
		}
		val[u]=1;
	}
	
	void getFail(){
		queue<int> q;
		f[0]=last[0]=0;
		for(int i=0;i<4;i++){
			int u=ch[0][i];
			if(u){
				last[u]=0;f[u]=0;
				q.push(u);
			}
		}
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int c=0;c<4;c++){
				int u=ch[x][c];
				if(!u) {ch[x][c]=ch[f[x]][c];continue;}
				q.push(u);
				f[u]=ch[f[x]][c];
				last[u]=val[f[u]]?f[u]:last[f[u]];
			}
		}
		//printf("ch[1][1]:%d\n",ch[1][1]);
	}
	
};
ACmachine ac;
int num;

Matrix matrix_mul(Matrix A,Matrix B){
	Matrix C;
	long long sum;
	for(int i=0;i<num;i++)
		for(int j=0;j<num;j++){
			sum=0;
			for(int k=0;k<num;k++)
				sum=(sum+(LL)A.A[i][k]*B.A[k][j]);
			C.A[i][j]=((sum)%mod);
			//printf("sum:%lld C:%d\n",sum,C.A[i][j]);
		}
		return C;
}
Matrix B;
/*Matrix matrix_pow(Matrix A,LL k){
	printf("k:%lld\n",k);
	if(k==1) return A;
	B=matrix_pow(A,k/2);
	B=matrix_mul(B,B);
	if(k&1) B=matrix_mul(B,A);
	/*	printf("k:%d\n",k);
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++)
			printf("%d ",B.A[i][j]);
		printf("\n");
	}
	return B;
}*/

Matrix matrix_pow(Matrix A,int k){
	Matrix R,res;
	for(int i=0;i<num;i++) for(int j=0;j<num;j++){ res.A[i][j]=0;R.A[i][j]=A.A[i][j];}
	for(int i=0;i<num;i++) res.A[i][i]=1;
	while(k){
		if(k&1) res=matrix_mul(res,R);
		k>>=1;
		R=matrix_mul(R,R);
	}
	return res;
}

int m;
int n;
char s[11][11];
//int F[maxnode][4];
int bh[maxnode];
Matrix A;
int main(){
	scanf("%d%d",&m,&n);
	//printf("%d\n",n);
	ac.init();
	for(int i=0;i<m;i++)
	{scanf("%s",s[i]);ac.insert(s[i]);}
	ac.getFail();
	num=0;
	for(int i=0;i<=ac.sz;i++) if(ac.last[i]) ac.val[i]=1;
	for(int i=0;i<=ac.sz;i++){
		if(!ac.val[i]){
		bh[i]=num++;	
		}
	}
	//memset(F,0,sizeof(F));
	memset(A.A,0,sizeof(A.A));
	for(int i=0;i<=ac.sz;i++)
	if(!ac.val[i]){
		for(int j=0;j<4;j++){
			if(!ac.val[ac.ch[i][j]]){
			//F[bh[i]][j]=bh[ac.ch[i][j]];
				//printf("%d to %d\n",i,ac.ch[i][j]);
			//A.A[bh[ac.ch[i][j]]][bh[i]]++;
				A.A[bh[i]][bh[ac.ch[i][j]]]++;
			}
		}
	}
	/*for(int i=0;i<num;i++){
		for(int j=0;j<num;j++)
			printf("%d ",A.A[i][j]);
		printf("\n");
	}*/
	Matrix B=matrix_pow(A,n);
		/*for(int i=0;i<num;i++){
		for(int j=0;j<num;j++)
			printf("%d ",B.A[i][j]);
		printf("\n");
	}*/
	int a[maxnode];memset(a,0,sizeof(a));a[0]=1;
	long long sum=0;
	for(int i=0;i<num;i++){
		for(int k=0;k<num;k++){
			sum=(sum+a[k]*B.A[k][i]);
		}sum=sum%mod;
	}
	printf("%lld\n",sum);
	return 0;
}
/*
3
2000000000
CG
AT
G
*/