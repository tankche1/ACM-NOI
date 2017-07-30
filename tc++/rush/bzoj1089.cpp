# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxnum=10000;
struct bign{
	int len,s[maxnum];
	bign() {memset(s,0,sizeof(s));len=1;}
};

bign operator + (const bign &A,const bign &B){
	bign c;
	int n=max(A.len,B.len);
	for(int i=0;i<n;i++){
		c.s[i]+=A.s[i]+B.s[i];
		c.s[i+1]+=c.s[i]/10;
		c.s[i]%=10;
	}
	c.len=n;
	if(c.s[n]) c.len++;
	return c;
}

bign operator -  (const bign &A,const bign &B){
	bign c;
	for(int i=0;i<B.len;i++){
		c.s[i]+=A.s[i]-B.s[i];
		if(c.s[i]<0) c.s[i]+=10,c.s[i+1]--;
	}
	for(int i=B.len;i<A.len;i++) c.s[i]+=A.s[i];
	for(int i=B.len;c.s[i]<0;i++){
		c.s[i]+=10;
		c.s[i+1]--;
	}
	for(int i=A.len-1;i>0;i--)
		if(c.s[i]>0) {c.len=i+1;break;}
	return c;
}

bign operator * (const bign &A,const bign &B){
	bign c;
	for(int i=0;i<A.len;i++)
		for(int j=0;j<B.len;j++){
			c.s[i+j]+=A.s[i]*B.s[j];
		}
	for(int i=0;i<A.len+B.len-1;i++){
		c.s[i+1]+=c.s[i]/10;
		c.s[i]%=10;
	}
	for(c.len=A.len+B.len-1;c.s[c.len]>0;c.len++){
		c.s[c.len+1]+=c.s[c.len]/10;
		c.s[c.len]%=10;
	}
	return c;
}

bign fast_pow(const bign A,const int B){
	if(B==0) {bign ans;ans.s[0]=1;
		return ans;
	}
	bign H=fast_pow(A,B/2);
	bign ans=H*H;
	if(B&1) ans=ans*A;
	/*	printf("B:%d\n",B);
	for(int i=ans.len-1;i>=0;i++)
		printf("%d",ans.s[i]);
	printf("\n");*/
	return ans;
}
bign f[20];

int n,k;
int main(){
	scanf("%d%d",&n,&k);
	f[0].s[0]=1;f[19].s[0]=1;
	if(k==0) {printf("1\n");return 0;}
	for(int i=1;i<=k;i++){
		//printf("i:%d\n",i);
		f[i]=fast_pow(f[i-1],n)+f[19];//printf("i:%d\n",i);
		/*for(int ii=f[i].len-1;ii>=0;ii--)
		printf("%d",f[i].s[ii]);
	printf("\n");*/
	}
	bign ans=f[k]-f[k-1];
	for(int i=ans.len-1;i>=0;i--)
		printf("%d",ans.s[i]);
	printf("\n");
	return 0;
}
