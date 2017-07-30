# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
int a[5][5],b[5][5];
# define check(i,j) (((a[i-1][j]>a[i][j])+(a[i][j-1]>a[i][j])+(a[i+1][j]>a[i][j])+(a[i][j+1]>a[i][j]))==b[i][j])
# define rep(i,j) for(a[i][j]=0;a[i][j]<=8;a[i][j]++)
int main(){
	memset(a,0,sizeof(a));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&b[i][j]);
	if(n==1){
		if(!b[1][1]) puts("0");
			else puts("NO SOLUTION");
	}
	else if(n==2){
		rep(1,2) rep(2,1) rep(1,1) if(check(1,1))
						rep(2,2)
							if(check(1,2)&&check(2,1)&&check(2,2)){
								printf("%d %d\n%d %d\n",a[1][1],a[1][2],a[2][1],a[2][2]);return 0;
							}
		puts("NO SOLUTION");
	}
	else{
		rep(1,2) rep(2,1) rep(2,3) rep(3,2){
			rep(1,1) if(check(1,1)) rep(1,3) if(check(1,3)) rep(3,1) if(check(3,1)) rep(3,3) if(check(3,3))
				rep(2,2) if(check(2,2)&&check(1,2)&&check(2,1)&&check(2,3)&&check(3,2)){
					for(int i=1;i<=n;i++){
		printf("%d %d %d\n",a[i][1],a[i][2],a[i][3]);
		}return 0;
	}
		}
		puts("NO SOLUTION");
	}
	return 0;
}
/*
2 2
1 0
1 0
*/
