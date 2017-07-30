# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int n;
double x[50],y[50];
double eps=0.00001;

struct tri{
	double s1,s2,s3;
	int a,b,c;
	void easy(){
		if(s2<s1) swap(s1,s2);
		if(s3<s1) swap(s1,s3);
		if(s3<s2) swap(s2,s3);
	}
};
tri t[800000];
int cnt=0;

inline double aaabs(double a) {return a<0?-a:a;}
bool cmp(tri a,tri b){
	if(aaabs(a.s2-b.s2)>eps) return a.s2<b.s2;
	return a.s3<b.s3;
}

bool equal(tri a,tri b){
	return aaabs(a.s2-b.s2)<eps&&aaabs(a.s3-b.s3)<eps;
}
bool vis[300][300];

int main(){
	int a,b;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
			memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a,&b);x[i]=(double)a;y[i]=(double)b;
			a+=105;b+=105;
			if(vis[a][b]) i--,n--;
			vis[a][b]=1;
			//scanf("%lf%lf",&x[i],&y[i]);
			//,x[i]=x[i]*100,y[i]=y[i]*100;
		}
		cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=j+1;k<=n;k++){
					if((y[j]-y[i])*(x[k]-x[j])==(y[k]-y[j])*(x[j]-x[i])) continue;
					//	printf("shit i:%d j:%d k:%d\n",i,j,k);
					cnt++;
					t[cnt].s1=(double)sqrt((double)(x[i]-x[j])*(x[i]-x[j])+(double)(y[i]-y[j])*(y[i]-y[j]));
					t[cnt].s2=(double)sqrt((double)(x[i]-x[k])*(x[i]-x[k])+(double)(y[i]-y[k])*(y[i]-y[k]));
					t[cnt].s3=(double)sqrt((double)(x[k]-x[j])*(x[k]-x[j])+(double)(y[k]-y[j])*(y[k]-y[j]));
					t[cnt].easy();
					t[cnt].s2=t[cnt].s2*10000.0/t[cnt].s1;
					t[cnt].s3=t[cnt].s3*10000.0/t[cnt].s1;
					t[cnt].s1=10000.0;
					t[cnt].a=i;t[cnt].b=j;t[cnt].c=k;
				}
		//memset(vis,false,sizeof(vis));
		sort(t+1,t+cnt+1,cmp);
		int ans=0,j;
		for(int i=1;i<=cnt;i++){
			j=i;
			while(j<cnt&&equal(t[j+1],t[i])) j++;
				//printf("i:%d j:%d\n",i,j);
				//if(j-i+1==9){
					//for(int k=i;k<=j;k++)
					//	printf("%d %d %d\n",t[k].a,t[k].b,t[k].c);
				//}
			ans=max(ans,j-i+1);
			i=j;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
