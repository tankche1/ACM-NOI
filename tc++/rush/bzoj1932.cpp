# include<stdio.h>
# include<string.h>
# include<vector>
# include<map>
# include<stack>
# include<algorithm>
using namespace std;
typedef unsigned long long ull;
typedef vector<ull> set;
const int seed=99997,seed1=79;

ull Code(set s){
	ull res=0;
	for(int i=0;i<s.size();i++)
		res*=seed,res+=s[i]+seed1;
	return res;
}


void Normal(set s){
	sort(s.begin(),s.end());
}

int n;
char op[30];
stack<set> S;
map<ull,int> id1,id2;
int main(){
	scanf("%d",&n);
	set none;
	for(int i=1;i<=n;i++){
		scanf("%s",op);
		if(op[0]=='P')
			S.push(none);
		if(op[0]=='D')
			S.push(S.top());
		if(op[0]=='U'){
			set a=S.top();S.pop();set b=S.top();S.pop();
			for(int i=0;i<b.size();i++) a.push_back(b[i]);
			a.resize(unique(a.begin(),a.end())-a.begin());
			S.push(a);
		}
		if(op[0]=='I'){
			set a=S.top();S.pop();set b=S.top();S.pop();set c;
			id1.clear();
			for(int i=0;i<a.size();i++) id1[a[i]]=1;
			for(int i=0;i<b.size();i++) if(id1[b[i]]) c.push_back(b[i]);
			S.push(c);
		}
		if(op[0]=='A'){
			set a=S.top();S.pop();set b=S.top();S.pop();
			Normal(a);Normal(b);//printf("%d %d\n",a.size(),b.size());
			b.push_back(Code(a));b.resize(unique(b.begin(),b.end())-b.begin());
			S.push(b);
		}
		printf("%d\n",S.top().size());
	}
	return 0;
}

/*
5
PUSH
PUSH
ADD
DUP
UNION

*/

