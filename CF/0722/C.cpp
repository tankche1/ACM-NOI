# include<stdio.h>
# include<string.h>
# include<iostream>
# include<math.h>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
typedef long long LL;
const int maxm=100010;
const int maxn=2010;
const int mod=1000000007;
int h,w,n;
pair<int,int> p[maxn];
LL f[maxn];
LL c[maxm<<1],d[maxm<<1];

LL pow(LL a,int b){
	//printf("a:%lld b:%d\n",a,b);
	//int cc;//scanf("%d",&cc);
	if(!b) return 1;
	LL half=pow(a,b>>1);
	half=half*half%mod;
	if(b&1) half=half*a%mod;
	return half;
}

void prepare(){
	c[0]=1;
	for(int i=1;i<=200000;i++)
		c[i]=c[i-1]*i%mod;
		//puts("hei");
	d[0]=1;
	for(int i=1;i<=200000;i++){
		//printf("c[%d]:%lld\n",i,c[i]);
		d[i]=pow(c[i],mod-2);
	}
		//puts("fuck");
}

LL C(LL x,LL y){//down x right y C(x+y,x)
	return ((c[x+y]*d[x])%mod)*d[y]%mod;
}

inline LL add(LL a,LL b) {return a+b>=mod?a+b-mod:a+b;}

int main(){
	prepare();
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].first,&p[i].second);
	p[++n].first=h;p[n].second=w;
	sort(p+1,p+n+1);
	//LL sum=0;
	f[1]=C(p[1].first-1,p[1].second-1);//sum=add(sum,f[1]);
	for(int i=2;i<=n;i++){
		f[i]=C(p[i].first-1,p[i].second-1);
		//printf("i:%d f:%I64d\n",i,f[i]);
		for(int j=1;j<i;j++){
			if(p[i].first>=p[j].first&&p[i].second>=p[j].second){
				f[i]=f[i]+mod-(f[j]*C(p[i].first-p[j].first,p[i].second-p[j].second)%mod);
				if(f[i]>=mod) f[i]-=mod;
			}
		}
		//printf("i:%d f:%I64d\n",i,f[i]);
	}
	//for(int i=1;i<=n;i++)
	//	cout << "i:"<< i <<"f:"<<f[i] << endl;
	cout << f[n] << endl;
	return 0;
}
