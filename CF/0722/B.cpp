# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=200020;
const int mod1=9997;
const int mod2=100007;
unsigned long long hash1[maxn],hash2[maxn],c1[maxn],hash3[maxn],hash4[maxn],c2[maxn];
char s1[maxn],s2[maxn];
int n;

unsigned long long get(unsigned long long *hash,unsigned long long *c,int L,int R){
	unsigned long long ans=hash[R];
	if(L) ans-=hash[L-1];
	ans=ans*c[maxn-10-R];
	return ans;
}
unsigned long long t1,t2,t3,t4;
bool dfs(int L1,int R1,int L2,int R2){
	int len=R1-L1+1;
	t1=get(hash1,c1,L1,R1);t2=get(hash2,c2,L1,R1);t3=get(hash3,c1,L2,R2);t4=get(hash4,c2,L2,R2);
	if(t1==t3&&t2==t4) return true;
	if(len&1) return false;
	if(dfs(L1,L1+len/2-1,L2,L2+len/2-1)&&dfs(L1+len/2,R1,L2+len/2,R2)) return true;
	if(dfs(L1,L1+len/2-1,L2+len/2,R2)&&dfs(L1+len/2,R1,L2,L2+len/2-1)) return true;
	return false;
}

int main(){
	c1[0]=1;c2[0]=1;
	for(int i=1;i<maxn;i++)
		c1[i]=c1[i-1]*mod1,c2[i]=c2[i-1]*mod2;
	scanf("%s",s1);
	scanf("%s",s2);n=strlen(s1);
	hash1[0]=s1[0];hash2[0]=s1[0];
	for(int i=1;i<n;i++)
		hash1[i]=hash1[i-1]+c1[i]*s1[i],hash2[i]=hash2[i-1]+c2[i]*s1[i];
	hash3[0]=s2[0];hash4[0]=s2[0];
	for(int i=1;i<n;i++)
		hash3[i]=hash3[i-1]+c1[i]*s2[i],hash4[i]=hash4[i-1]+c2[i]*s2[i];
		
	if(dfs(0,n-1,0,n-1)) puts("YES");
	else puts("NO");
	return 0;
}
