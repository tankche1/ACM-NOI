# include<stdio.h>
# include<string.h>
typedef long long LL;
const int Bit=1000;
int m,mod;
int two;
typedef LL Matrix[33][33];
Matrix A,C;
char s[1000];

int B[100];
struct Big{
	int A[100],Len;
	
	void minus(int a){
		int i,j;
		for(int i=0;i<Len;i++) B[i]=A[i];
		B[Len-1]=B[Len-1]-a;
		for(j=Len-1;j>=0;j--)
			if(B[j]<0) B[j]+=1000,B[j-1]--;
			else break;
		for(j=0;j<Len;j++)
			if(B[j]!=0) break;
		for(i=0;j<Len;j++,i++)
			A[i]=B[j];
		Len=i;
	}
	
	void divide(int a){
		int j=0,t=0,i;
		for(i=0;i<Len;i++){
			t=t*1000+A[i];
			if(t>=a) break;
		}
		for(;i<Len;i++){
			B[j++]=t/a;t=t%a;
			t=t*1000+A[i+1];
		}
		Len=j;
		for(int i=0;i<Len;i++) A[i]=B[i];
	}
	
	void print(){
		printf("%d",A[0]);
		for(int i=1;i<Len;i++){
			if(A[i]<100) {printf("0");if(A[i]<10) printf("0");}
			printf("%d",A[i]);
		}
		puts("");
	}
}N;

void Copy(Matrix A,Matrix B){
	for(int i=1;i<=two;i++)
		for(int j=1;j<=two;j++)
			A[i][j]=B[i][j];
}

void Matrix_mul(Matrix A,Matrix B,Matrix ans){
	for(int i=1;i<=two;i++)
		for(int j=1;j<=two;j++){
			C[i][j]=0;
			for(int k=1;k<=two;k++)
				C[i][j]+=A[i][k]*B[k][j];
			C[i][j]%=mod;
		}
	Copy(ans,C);
}

void Matrix_pow(Matrix A,Big P,Matrix ans){
	if(P.Len==1&&P.A[0]==1) {Copy(ans,A);return;}
	Matrix half;
	int t=P.A[P.Len-1]&1;
	//printf("t:%d\n",t);
	P.divide(2);
	Matrix_pow(A,P,half);
	//puts("\\\\\\\\\\\\\\\\\\\\");
	//printf("half:\n");
	/*for(int i=1;i<=two;i++){
		for(int j=1;j<=two;j++)
			printf("%I64d ",half[i][j]);puts("");
		}*/
	Matrix_mul(half,half,ans);
	if(t) Matrix_mul(A,ans,ans);
	return;
}



int main()
{
	freopen("nice.in","r",stdin);
	freopen("nice.out","w",stdout);
	int t,len,j;
	scanf("%s",s);
	len=strlen(s);
	N.Len=(len+2)/3;
	for(int i=N.Len-1;i>=0;i--){
		t=0;j=len-(N.Len-i)*3;
		if(j<0) j=0;
		for(;j<len-(N.Len-i)*3+3;j++)
			t=t*10+s[j]-'0';
		N.A[i]=t;
	}
	//N.print();
	
	scanf("%d%d",&m,&mod);
	two=1<<m;
	for(int i=0;i<two;i++){
		for(int j=0;j<two;j++){
			A[i+1][j+1]=1;
			for(int k=0;k<m-1;k++){
				t=1<<k;
				if((i&t)==(j&t)&&(i&t)==((i>>1)&t)&&(i&t)==((j>>1)&t)){
					//printf("i:%d j:%d\n",i,j);
					A[i+1][j+1]=0;break;
				}
			}
			//printf("%I64d ",A[i+1][j+1]);
		}//puts("");
	}
	//puts("\\\\\\");
	if(N.Len==1&&N.A[0]==1) {printf("%d\n",two);return 0;}
	N.minus(1);
	//	N.print();
	Matrix ansA;
	Matrix_pow(A,N,ansA);
	/*for(int i=1;i<=two;i++){
		for(int j=1;j<=two;j++)
			printf("%I64d ",ansA[i][j]);puts("");
	}*/
	LL ans=0;
	for(int i=1;i<=two;i++){
		for(int j=1;j<=two;j++)
			ans+=ansA[j][i];
		ans%=mod;
	}
	printf("%I64d\n",ans);
	return 0;
}
