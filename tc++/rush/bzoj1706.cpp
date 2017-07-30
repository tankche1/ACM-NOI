# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxt=102;
const int INF=~0U>>1;
typedef long long Matrix[maxt][maxt];
typedef LL Vector[maxt];
int g[maxt][maxt];
int n,t,s,e;
int bh[1010],bh_num;
int get(int x){
	if(bh[x]) return bh[x];
	return bh[x]=++bh_num;
}

void copy(Matrix A,Matrix C){
	for(int i=1;i<=bh_num;i++)
		for(int j=1;j<=bh_num;j++)
			A[i][j]=C[i][j];
}

inline int _min(int a,int b){
	if(a==-1) return b;
		return a<b?a:b;
}

void matrix_mul(Matrix A,Matrix B,Matrix res){
	Matrix C;
	for(int i=1;i<=bh_num;i++)
		for(int j=1;j<=bh_num;j++){
			C[i][j]=INF;
			for(int k=1;k<=bh_num;k++)
				C[i][j]=min(A[i][k]+B[k][j],C[i][j]);
		}
	copy(res,C);
}

void matrix_pow(Matrix A,int p,Matrix ans){
	Matrix res,mul;
	int num=1;
	copy(mul,A);
	for(int i=1;i<=bh_num;i++){
		for(int j=1;j<=bh_num;j++)
			res[i][j]=INF;
	}
	for(int i=1;i<=bh_num;i++) 
		res[i][i]=0;
	while(p>=num){
		if(p&num) matrix_mul(res,mul,res);
		num<<=1;matrix_mul(mul,mul,mul);
	}
	/*for(int i=1;i<=bh_num;i++){
		for(int j=1;j<=bh_num;j++)
			printf("%lld ",res[i][j]);puts("");
	}*/
	copy(ans,res);
}

void vector_mul(Vector A,Matrix B,Vector ans){
	Vector res;
	for(int i=1;i<=bh_num;i++){
		res[i]=INF;
		for(int j=1;j<=bh_num;j++){
			res[i]=min(res[i],A[j]+B[j][i]);
		}
	}
	/*for(int i=1;i<=bh_num;i++){
		printf("%d ",A[i]);
	}puts("");*/
	for(int i=1;i<=bh_num;i++){
		ans[i]=res[i];//printf("%d ",res[i]);
	}//puts("");
}

int main(){
	int c,a,b;
	scanf("%d%d%d%d",&n,&t,&s,&e);
	memset(bh,0,sizeof(bh));bh_num=0;
	memset(g,-1,sizeof(g));
	for(int i=1;i<=t;i++){
		scanf("%d%d%d",&c,&a,&b);
		a=get(a);b=get(b);
		g[a][b]=g[b][a]=_min(g[a][b],c);
	}
	Matrix A;Vector start;
	for(int i=1;i<=bh_num;i++)
		start[i]=INF;
	start[bh[s]]=0;
	for(int i=1;i<=bh_num;i++)
		for(int j=1;j<=bh_num;j++){
			if(g[i][j]==-1) A[i][j]=INF;
			else A[i][j]=(LL)g[i][j];
				//printf("A[%d][%d]:%lld\n",i,j,A[i][j]);
		}
	matrix_pow(A,n,A);
	vector_mul(start,A,start);
	printf("%lld\n",start[bh[e]]);
	return 0;
}
