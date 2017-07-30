# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n,s;
int x[1010],y[1010],p[1010];
const double eps=1e-9;
const int want=1e+6;

bool check(double R){
	int sum=s;
	for(int i=1;i<=n;i++)
		if(x[i]*x[i]+y[i]*y[i]<=R*R) sum+=p[i];
	return sum>=want;
}

int main(){
	scanf("%d%d",&n,&s);
	int sum=s;
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&x[i],&y[i],&p[i]),sum+=p[i];
	if(sum<want) {puts("-1");return 0;}
	double L=0,R=20000;
	while(R-L>eps){
		double M=(L+R)/2.0;
		if(check(M)) R=M;
		else L=M;
	}
	printf("%.7lf\n",L);
	return 0;
}
