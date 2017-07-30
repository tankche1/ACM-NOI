# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxa=1010;
const int INF=~0U>>1;
int A[maxa][maxa],row_max[maxa][maxa],row_min[maxa][maxa];

int a,b,n;
int q_max[maxa],q_min[maxa];
int ans_max[maxa][maxa],ans_min[maxa][maxa];
int main(){
	scanf("%d%d%d",&a,&b,&n);
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			scanf("%d",&A[i][j]);
	for(int i=1;i<=a;i++){
		q_max[0]=0;q_min[0]=0;
		int tail_max=1,tail_min=1;
		for(int j=1;j<=b;j++){
			//printf("%d\n",A[i][j]);
			while(q_max[0]>=tail_max&&A[i][q_max[q_max[0]]]<=A[i][j]) q_max[0]--;
			q_max[++q_max[0]]=j;
			while(q_min[0]>=tail_min&&A[i][q_min[q_min[0]]]>=A[i][j]) q_min[0]--;
			q_min[++q_min[0]]=j;
			while(q_max[tail_max]+n-1<j) tail_max++;
			while(q_min[tail_min]+n-1<j) tail_min++;
			
			if(j>=n) {//for(int j=tail_max;j<=q_max[0];j++) printf("%d ",q_max[j]);printf("\n");
				row_max[i][j-n+1]=A[i][q_max[tail_max]],row_min[i][j-n+1]=A[i][q_min[tail_min]];
				//printf("row_max[%d][%d]:%d row_min[%d][%d]:%d\n",i,j-n+1,row_max[i][j-n+1],i,j-n+1,row_min[i][j-n+1]);
			}
		}
	}
	/*for(int i=1;i<=a;i++){
		for(int j=1;j<=b-n+1;j++)
			printf("%d ",row_max[i][j]);printf("\n");
	}*/
	int ans=INF;
	for(int j=1;j<=b-n+1;j++){
		q_max[0]=0;q_min[0]=0;
		int tail_max=1,tail_min=1;
		for(int i=1;i<=a;i++){
			while(q_max[0]>=tail_max&&row_max[q_max[q_max[0]]][j]<=row_max[i][j]) q_max[0]--;
			q_max[++q_max[0]]=i;
			while(q_min[0]>=tail_min&&row_min[q_min[q_min[0]]][j]>=row_min[i][j]) q_min[0]--;
			q_min[++q_min[0]]=i;
			while(q_max[tail_max]+n-1<i) tail_max++;
			while(q_min[tail_min]+n-1<i) tail_min++;
			if(i>=n) {
			//	for(int j=tail_max;j<=q_max[0];j++) printf("%d ",q_max[j]);printf("\n");
				ans_max[i-n+1][j]=row_max[q_max[tail_max]][j],ans_min[i-n+1][j]=row_min[q_min[tail_min]][j];
				//printf("ans_max[%d][%d]:%d\n",i-n+1,j,ans_max[i-n+1][j]);
				if(ans_max[i-n+1][j]-ans_min[i-n+1][j]<ans) ans=ans_max[i-n+1][j]-ans_min[i-n+1][j];
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
