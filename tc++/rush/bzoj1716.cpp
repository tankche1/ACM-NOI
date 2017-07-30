# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10000+120*120+10;
const int INF=~0U>>1;
int n,m;
int v[110],c[110],t;
int f1[maxn],f2[maxn];

struct que{
	int v,cnt;
};
que q[10010];

int main(){
	m=0;
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++)
		scanf("%d",&v[i]);
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
		if(c[i]&&v[i]*v[i]>m) m=v[i]*v[i];
	}
	for(int i=0;i<=m;i++)
		f1[i]=-1;
	f1[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j+v[i]<=m;j++)
			if(f1[j]!=-1){
				if(f1[j+v[i]]==-1||f1[j+v[i]]>f1[j]+1)
					f1[j+v[i]]=f1[j]+1;
			}
	}
	//for(int i=0;i<=100;i++) printf("f1[%d]:%d\n",i,f1[i]);
	m=m+t;
	memset(f2,-1,sizeof(f2));
	f2[0]=0;
	for(int i=1;i<=n;i++){
		//printf("i:%d\n",i);
		for(int j=0;j<v[i];j++){
			//if(f2[j]==-1) continue;
			int l=0,r=0;
			q[l].v=f2[j];q[l].cnt=0;
			if(f2[j]==-1) r=-1;
			for(int k=1,p=j+v[i];p<=m;k++,p+=v[i]){
				while(l<=r&&k-q[l].cnt>c[i]) l++;
			//	if(l>r) break;
				int val=f2[p]==-1?-INF:f2[p]-k;//if(i==6&&val==-6) printf("p:%d f2:%d\n",p,f2[p]);
				if(l<=r&&(f2[p]==-1||q[l].v+k<f2[p])) f2[p]=q[l].v+k;
					if(val!=-INF){
						while(l<=r&&val<=q[r].v) r--;
						q[++r].v=val;q[r].cnt=k;
					}
					//if(f2[p]<=0) printf("f2[%d]:%d %d\n",p,f2[p],q[l].v);
			}
		}
	}
	//printf("m:%d\n",m);
	//for(int i=0;i<=m;i++)
	//	if(f2[i]!=-1) printf("f2[%d]:%d\n",i,f2[i]);
	int ans=INF;
	for(int i=t;i<=m;i++){
		if(f2[i]!=-1&&f1[i-t]!=-1) ans=min(ans,f2[i]+f1[i-t]);
	}
	if(ans==INF) puts("-1");
		else
	printf("%d\n",ans);
	return 0;
}
