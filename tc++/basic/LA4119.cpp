# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;

int getnum(char *s,int len){
	int v=0;
	for(int i=0;i<len;i++)
		v=v*10+s[i]-'0';
	return v;
}

struct Poly{
	vector<int> a,b;
	
	void Get(char *s,int len){
		a.clear();b.clear();
		int i=0,j,k,v;
		while(i<len){
			int sign=1;
			if(s[i]=='+') i++;
			else if(s[i]=='-') i++,sign=-1;
			for(j=i;s[j]>='0'&&s[j]<='9';j++) {}
			v=getnum(&s[i],j-i);
			if(v==0) v=1;
			v=v*sign;
			a.push_back(v);
			i=j;
			if(i==len) {b.push_back(0);}
			else{
				if(s[i+1]!='^') b.push_back(1),i++;//一次
					else {
						for(j=i+2;s[j]>='0'&&s[j]<='9';j++) ;
						v=getnum(&s[i+2],j-(i+2));b.push_back(v);i=j;
					}
			}
		}
	}
	
	bool mod(int x,int mod){//f(x)%mod
		int ans=0;
		for(int i=0;i<a.size();i++){
			int m=1;
			for(int j=1;j<=b[i];j++) m=((long long)m*x)%mod;
			ans=((long long)ans+(((long long)a[i]*m)%mod))%mod;
		}
		return ans==0?true:false;
	}
};

bool check(char *s){
	int n=strlen(s),p;
	for(p=n-1;p>=0;p--)
		if(s[p]=='/') break;
	int D=getnum(&s[p+1],n-1-p);
		Poly poly;
		poly.Get(&s[1],p-2);
		/*for(int i=0;i<poly.a.size();i++){
			printf("%d %d\n",poly.a[i],poly.b[i]);
		}*/
	for(int i=1;i<=poly.b[0]+1;i++){
		if(!poly.mod(i,D)) return false;
	}
	return true;
}

int main(){
	//freopen("in.txt","r",stdin);
	char s[10000];
	int kase=0;
	while(scanf("%s",s)!=EOF){
		if(s[0]=='.') break;
		printf("Case %d: ",++kase);
		if(check(s)) printf("Always an integer\n");
			else printf("Not always an integer\n");
	}
	return 0;
}
