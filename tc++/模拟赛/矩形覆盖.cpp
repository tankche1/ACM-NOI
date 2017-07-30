# include<stdio.h>
# include<string.h>
# include<map>
# include<stack>
# include<algorithm>
using namespace std;
const int maxn=250010;

map<int,int> id;
map<int,int> last;
int n,a,s[maxn];
int right[maxn],num[maxn];//i到right[i]中有num[i]个s[i] 且其他都大于s[i] 并且不存在j〉right[i]使s[j]=s[i]且都大于s[i]

int ans=0;

void add(int x,int bh){
	if(!id.count(x)) id[x]=1;
		else id[x]++;
	last[x]=bh;
}

void reduce(int x){
	if(id[x]>1) id[x]--;
		else id.erase(x);
}

stack<int> q;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a,&s[i]);
	for(int i=n;i>=1;i--){
		while((!q.empty())&&s[q.top()]>s[i]) {reduce(s[q.top()]);q.pop();}
		if(!id.count(s[i])) {right[i]=i,num[i]=1;}//puts("fu");}
			else {right[i]=right[last[s[i]]],num[i]=num[last[s[i]]]+1;}//puts("ck");}
		add(s[i],i);
		q.push(i);
	//	printf("right[%d]:%d num:%d\n",i,right[i],num[i]);
	}
	id.clear();
	for(int i=1;i<=n;i++){
		if((!id.count(s[i]))||(i>id[s[i]])){
			id[s[i]]=right[i];ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
/*
8
1 3
1 2
1 4
1 4
1 3
1 4
1 3
1 2

*/
