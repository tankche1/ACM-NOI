# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int MAXN=10010;
const int MAXC=50010;

int f[MAXN][1<<5];
int N,C;
int first[MAXN],next[MAXC],v[MAXC],edge;
int P[6];
int tot[MAXN][1<<5];

vector<int> Hate[MAXC],Like[MAXC];

void add_edge(int from,int to){
	next[edge]=first[from];
	v[edge]=to;
	first[from]=edge++;
}

int Calc(int num,int state){
	if(tot[num][state]!=-1) return tot[num][state];
	int &sum=tot[num][state];sum=0;
	//printf("num:%d state:%d bh:%d\n",num,state,1);
	for(int e=first[num];e!=-1;e=next[e]){
		int bh=v[e];
		bool flag=false;
		for(int i=0;i<Like[bh].size();i++){
			int st=Like[bh][i];
			if(!(P[st]&state)) flag=true;
		}
		for(int i=0;i<Hate[bh].size();i++){
			int st=Hate[bh][i];
			//if(num==1&&state==16) printf("st:%d\n",st);
			if(P[st]&state) flag=true;
		}
		//if(num==1&&state==16) printf("num:%d state:%d bh:%d flag:%d\n",num,state,bh,flag);
		sum+=flag;
	}
	return sum;
}

int main(){
	int E,F,L,a,ans=0;
	scanf("%d%d",&N,&C);
	edge=0;memset(first,-1,sizeof(first));
	for(int i=1;i<=C;i++){
		scanf("%d%d%d",&E,&F,&L);
		if(E+4>N) add_edge(E+4-N,i);
			else add_edge(E+4,i);
		for(int j=1;j<=F;j++){
			scanf("%d",&a);if(E+4>N&&a<5) a=N+a;a=a-E;
			Hate[i].push_back(a);
		}
		for(int j=1;j<=L;j++){
			scanf("%d",&a);if(E+4>N&&a<5) a=N+a;a=a-E;
			Like[i].push_back(a);
		//	printf("%d\n",Like[i][j-1]);
		}
	}
	P[0]=1;
	memset(tot,-1,sizeof(tot));
	for(int i=1;i<=5;i++) P[i]=P[i-1]<<1;
	for(int start=0;start<P[4];start++){
		memset(f,-1,sizeof(f));
		for(int j=0;j<=1;j++){
			f[1][start+P[4]*j]=Calc(1,start+P[4]*j);
		//if(start==0)	printf("f[%d][%d]:%d\n",1,start+P[4]*j,f[1][start+P[4]*j]);
		}
		for(int i=1;i<N;i++){
			for(int j=0;j<P[5];j++){
				if(f[i][j]!=-1){
					for(int k=0;k<=1;k++)
						f[i+1][(j>>1)+(P[4]*k)]=max(f[i+1][(j>>1)+(P[4]*k)],f[i][j]+Calc(i+1,(j>>1)+(P[4]*k)));
					//if(f[i][j]>0&&start==0)printf("f[%d][%d]:%d\n",i,j,f[i][j]);
				}
			}
		}
		//for(int j=0;j<P[5];j++) if(f[N][j]==6||j==(start<<1)||j==((start<<1)+1)) printf("f[%d][%d]:%d start:%d\n",N,j,f[N][j],start);
		ans=max(ans,f[N][start<<1]);ans=max(ans,f[N][(start<<1)+1]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
14 5

2 1 2 4 2 6

3 1 1 6 4

6 1 2 9 6 8

8 1 1 9 12

12 3 0 12 13 2
*/
