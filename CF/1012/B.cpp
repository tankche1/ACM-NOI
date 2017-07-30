# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
#define LL long long
bool flag;
int N,K,tank;
bool f[210][3];
char s[3][210];
int main(){
    int Tcase;
	scanf("%d",&Tcase);
	while (Tcase--){
		scanf("%d%d",&N,&K);
		for (int i=0;i<3;i++)scanf("%s",s[i]);
		memset(f,0,sizeof(f));
		for (int i=0;i<3;i++)
			if (s[i][0]=='s')f[0][i]=1;
		for (int i=N;i<N+10;i++)
			for (int j=0;j<3;j++)s[j][i]='.';
		for (int i=0;(tank=i)<=N;i+=3)
		for (int j=0;j<3;j++)
		if (f[i][j]){
			if (s[j][i+1]!='.')continue;
			for (int k=0;k<3;k++)
				if (abs(k-j)<2)
					if (s[k][i+1]=='.'&&s[k][i+2]=='.'&&s[k][i+3]=='.')
						f[i+3][k]=1;
		}
		flag=0;
		for (int j=0;j<3;j++)
			if (f[tank][j])flag=1;
		if (flag)printf("YES\n");
		else printf("NO\n");
	}
}
