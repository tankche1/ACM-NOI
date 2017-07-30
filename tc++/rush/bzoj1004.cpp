# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int mod;
int length[70],num;
bool vis[70];

void Find_length(int n,int *A){
	num=0;
	memset(vis,false,sizeof(vis));
	for(int i=0;i<n;i++){
		if(!vis[i]){
			int j=i,cnt=0;
			do{
				vis[j]=false;
				j=A[j];
				cnt++;
			}while(j!=i);
			length[num++]=cnt;
		}
	}
}

int Add(int a,int b){
	return (a+b)%mod;
}

int f[2][21][21][21];
int DP(int Sr,int Sb,int Sg){
	memset(f,0,sizeof(f));
	f[1][0][0][0]=1;
	for(int i=0;i<num;i++){
		int now=i%2,last=(i%2)^1;
		memset(f[now],0,sizeof(f[now]));
		for(int sr=0;sr<=Sr;sr++)
			for(int sb=0;sb<=Sb;sb++)
				for(int sg=0;sg<=Sg;sg++){
					if(f[last][sr][sb][sg]){
						if(sr+length[i]<=Sr)
							f[now][sr+length[i]][sb][sg]=Add(f[now][sr+length[i]][sb][sg],f[last][sr][sb][sg]);
						if(sb+length[i]<=Sb)
							f[now][sr][sb+length[i]][sg]=Add(f[now][sr][sb+length[i]][sg],f[last][sr][sb][sg]);
						if(sg+length[i]<=Sg)
							f[now][sr][sb][sg+length[i]]=Add(f[now][sr][sb][sg+length[i]],f[last][sr][sb][sg]);
					}
				}
	}
	return f[(num-1)%2][Sr][Sb][Sg];
}

int Sr,Sb,Sg,m,p,n;
int A[70];
int main(){
	scanf("%d%d%d%d%d",&Sr,&Sb,&Sg,&m,&p);
	n=Sr+Sb+Sg;mod=(m+1)*p;
	int sum=0;
	for(int i=0;i<n;i++) A[i]=i;
	for(int i=0;i<=m;i++){
		if(i!=0){
			for(int i=0;i<n;i++) {scanf("%d",&A[i]);A[i]--;}
		}
		Find_length(n,A);
		sum=(sum+DP(Sr,Sb,Sg))%mod;
	}
	printf("%d\n",(sum/(m+1))%p);
	return 0;
}
/*
4 4 4 1 1707
3 5 2 4 1 8 11 6 12 9 10 7
*/
