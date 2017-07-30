# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int mod=1000000009;
int m,n;
int a[5][5];
bool used[1<<8];

typedef long long LL;
int maxl;
typedef LL Matrix[1<<9][1<<9];
typedef LL Vector[1<<9];

Matrix g,ans,mem;
Vector init;

/*void copy(Matrix A,Matrix B){
	for(int i=1;i<=maxl;i++)
		for(int j=1;j<=maxl;j++)
			A[i][j]=B[i][j];
}

void Matrix_mul(Matrix A,Matrix B,Matrix ans){
	Matrix C;
	for(int i=1;i<=maxl;i++){
		for(int j=1;j<=maxl;j++){
			C[i][j]=0;
			for(int k=1;k<=maxl;k++){
				C[i][j]+=A[i][k]*B[k][j];
				if(C[i][j]>=mod) C[i][j]%=mod;
			}
		}
	}
		copy(ans,C);
}*/

Matrix half,C;

void Matrix_pow(int p){
   // printf("p:%d\n",p);
    for(int i=1;i<=maxl;i++) for(int j=1;j<=maxl;j++) ans[i][j]=mem[i][j];
	if(p==0) {return;}

	for(int i=1;i<=maxl;i++) for(int j=1;j<=maxl;j++) half[i][j]=g[i][j];
	while(p){
        if(p&1){
            for(int i=1;i<=maxl;i++){
                for(int j=1;j<=maxl;j++){
                    C[i][j]=0;
                    for(int k=1;k<=maxl;k++){
                        C[i][j]+=ans[i][k]*half[k][j];
                        if(C[i][j]>=mod) C[i][j]%=mod;
                    }
                }
            }
            for(int i=1;i<=maxl;i++) for(int j=1;j<=maxl;j++) ans[i][j]=C[i][j];

            //for(int i=1;i<=maxl;i++) {for(int j=1;j<=maxl;j++) printf("%d",ans[i][j]);puts("");}
        }
        p>>=1;

        for(int i=1;i<=maxl;i++){
                for(int j=1;j<=maxl;j++){
                    C[i][j]=0;
                    for(int k=1;k<=maxl;k++){
                        C[i][j]+=half[i][k]*half[k][j];
                        if(C[i][j]>=mod) C[i][j]%=mod;
                    }
                }
            }
            for(int i=1;i<=maxl;i++) for(int j=1;j<=maxl;j++) half[i][j]=C[i][j];

	}

	return;
}

void Vector_mul(Vector A,Matrix B,Vector ans){
	Vector C;
	for(int i=1;i<=maxl;i++){
		C[i]=0;
		for(int j=1;j<=maxl;j++)
			C[i]+=A[j]*B[j][i];
		C[i]%=mod;
	}
	for(int i=1;i<=maxl;i++)
		ans[i]=C[i];
}

bool tank(int x,int y){
    if(x>=1&&x<=3&&y>=1&&y<=3){
        return a[x][y]==1;
    }
    else return false;
}

void prepare(){
    memset(a,0,sizeof(a));
    memset(g,0,sizeof(g));

    for(int st1=0;st1<maxl;st1++){
        for(int st2=0;st2<maxl;st2++){
            if((st1>>m)!=(st2&((1<<m)-1))) continue;
            //printf("st1:%d st2:%d %d %d\n",st1,st2,(st2>>(1+m-1))&1,(st2>>(2+m-1))&1);
            bool ok=true;
            for(int i=1;i<=m;i++) a[1][i]=(st1>>(i-1))&1;
            for(int i=1;i<=m;i++) a[2][i]=(st1>>(i+m-1))&1;
            for(int i=1;i<=m;i++) a[3][i]=(st2>>(i+m-1))&1;

            /*if(st1==2&&st2==8){
                for(int i=3;i>=1;i--){
                    for(int j=1;j<=m;j++) printf("%d",a[i][j]);puts("");
                }
            }*/

            for(int i=1;i<=3;i++){
                for(int j=1;j<=m;j++){
                    if(!a[i][j]) continue;
                    if(tank(i+1,j+2)||tank(i+1,j-2)||tank(i-1,j+2)||tank(i-1,j-2)) ok=false;
                    if(tank(i+2,j-1)||tank(i+2,j+1)||tank(i-2,j-1)||tank(i-2,j+1)) ok=false;
                }
            }
            //if(st1==2&&st2==8) printf("ok:%d\n",ok);
            g[st1+1][st2+1]=ok;
        }
    }
}
Vector _end;

int main(){
    int Tcase;
    scanf("%d",&Tcase);
    for(int T=1;T<=Tcase;T++){
        scanf("%d%d",&m,&n);
        maxl=1<<(2*m);
        prepare();
        memset(mem,0,sizeof(mem));
        for(int i=1;i<=maxl;i++) mem[i][i]=1;
        //puts("fuck");
        /*for(int i=1;i<=maxl;i++){
        for(int j=1;j<=maxl;j++){
            printf("%d",g[i][j]);
        }puts("");
        }*/

        memset(init,0,sizeof(init));init[1]=1;
       // puts("fuck");
        Matrix_pow(n);
       // puts("fuck");
        //Vector_mul(init,ans,_end);puts("fuck");
        LL _ans=0;
        //for(int i=1;i<=maxl;i++) {for(int j=1;j<=maxl;j++) printf("%d",ans[i][j]);puts("");}
        for(int i=1;i<=maxl;i++) _ans+=ans[1][i];
        _ans%=mod;
        printf("%I64d\n",_ans);
    }
    return 0;
}
