# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
# define pb push_back
const int maxn=1010;
vector<int> prime;
int n,d[maxn];
int ans[100010];

bool IsPrime(int x){
	if(x==2) return true;
	if(x%2==0) return false;
	for(int i=3;i*i<=x;i+=2)
		if(x%i==0) return false;
	return true;
}

void GetPrime(){
	for(int i=2;i<=n;i++)
		if(IsPrime(i)) prime.pb(i);
}

struct BigNum{
	int h[400];
	
	BigNum() {memset(h,0,sizeof(h));}
	
	void mul(int x){
		for(int i=0;i<prime.size()&&x>1;i++){
			while(x%prime[i]==0){
				//printf("i:%d prime[i]:%d\n",i,prime[i]);
				x/=prime[i];
				h[i]++;
			}
		}
	}
	
	void div(int x){
		for(int i=0;i<prime.size()&&x>1;i++){
			while(x%prime[i]==0){
				x/=prime[i];
				h[i]--;
			}
		}
	}
	
	void print(){
		int x,last;
		memset(ans,0,sizeof(ans));
		ans[last=0]=1;
	//	puts("fuck");
		for(int i=0;i<prime.size();i++){
			//printf("prime[%d]:%d\n",i,prime[i]);
			for(int j=1;j<=h[i];j++){
				x=prime[i];int d=0;
				for(int k=0;k<=last;k++){
					d+=ans[k]*x;
					ans[k]=d%10;
					d/=10;
				}
				while(d) {ans[++last]=d%10;d/=10;}
			}
		}
		if(ans[0]==1&&last==0) printf("%d\n",0);
		else{
		for(int i=last;i>=0;i--)
			printf("%d",ans[i]);
		printf("\n");
		}
	}
	
};

int main(){
	//freopen("input.txt","r",stdin);
	int NoLimit=0,S=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&d[i]);
		if(d[i]<0) NoLimit++;
			else S+=d[i]-1;
	}
	GetPrime();
	BigNum ans;
	if(S>n-2) {printf("0\n");return 0;}
	//printf("%d\n",S);
	for(int i=n-2-S+1;i<=n-2;i++)
	{ans.mul(i);}
	//ans.print();
    for(int i=1;i<=n;i++)
    {
        if(d[i]>0)
            for(int j=1;j<=d[i]-1;j++)
                ans.div(j);
    }//ans.print();
  //  for(int i=1;i<=n-2-S;i++)
  //      ans.div(i);
    for(int i=0;i<n-2-S;i++) ans.mul(NoLimit);
	//ans.print();
	//printf("n-2-sum:%d NoLimit:%d\n",n-2-sum,NoLimit);
	//for(int i=1;i<=n-2-sum;i++)
	//	ans.mul(NoLimit);
	ans.print();
	return 0;
}
