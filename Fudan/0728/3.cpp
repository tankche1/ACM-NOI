# include<stdio.h>
# include<string.h>
# include<math.h>
# include<string>
# include<map>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=1000000007;
typedef LL Matrix[60][60];
int n,m;

char s[60][20];
int len[60];
string str;
map<string,bool> id;
Matrix A;

void Copy(Matrix A,Matrix B){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			A[i][j]=B[i][j];
}
Matrix C;
void Matrix_mul(Matrix A,Matrix B,Matrix ans){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            C[i][j]=0;
            for(int k=1;k<=n;k++)
                C[i][j]+=A[i][k]*B[k][j]%mod;
            C[i][j]%=mod;
        }
    Copy(ans,C);
}

Matrix ret,now;
void Matrix_pow(Matrix A,int p,Matrix ans){
    memset(ret,0,sizeof(ret));for(int i=1;i<=n;i++) ret[i][i]=1;
    Copy(now,A);
    while(p){
        if(p&1) Matrix_mul(ret,now,ret);
        Matrix_mul(now,now,now);
        p>>=1;
    }
    Copy(ans,ret);
}

LL ans;
int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
            id.clear();
        scanf("%d%d",&n,&m);getchar();
        for(int i=1;i<=n;i++){
            scanf("%s",s[i]);
            len[i]=strlen(s[i]);str="";
            for(int j=0;j<len[i];j++)
                str=str+s[i][j];
            if(!id.count(str)){
                id[str]=1;
            }
            else{
                i--;n--;
            }
            //puts(s[i]);
        }
        memset(A,0,sizeof(A));
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if(len[i]>1&&len[j]>1){
                for(int k=len[i]-2;k>=0&&len[i]-k<=len[j];k--){
                    bool ok=true;
                    for(int l=k;l<len[i];l++)
                        if(s[i][l]!=s[j][l-k]) {ok=false;break;}
                    if(ok) {A[i][j]=1;break;}
                }
            }
        }
        /*for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) printf("%d ",A[i][j]);puts("");
        }*/
        Matrix_pow(A,m-1,A);/*puts("");
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) printf("%d ",A[i][j]);puts("");
        }*/
        ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                ans+=A[j][i];
        }
        ans%=mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
