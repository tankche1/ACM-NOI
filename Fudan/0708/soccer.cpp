# include<stdio.h>
# include<map>
# include<iostream>
# include<algorithm>
using namespace std;
map<string,int> id;
string name[40];
string s1,s2;

int testcase,now=0;
int a[20],b[20],c[20];

int find(int x){
	for(int i=1;i<=16;i++){
		if(a[i]==x){
			if(c[i]==1) continue;
			else return find(b[i]);
		}
		else if(b[i]==x){
			if(c[i]==0) continue;
			else return find(a[i]);
		}
	}
	return x;
}

int main(){
	int t1,t2,ans;
	scanf("%d",&testcase);
	while(testcase--){
		id.clear();now=0;
		for(int i=1;i<=16;i++){
			cin>>s1>>s2;
			if(!id.count(s1)) id[s1]=++now,name[now]=s1;
			if(!id.count(s2)) id[s2]=++now,name[now]=s2;
			scanf("%d%d",&t1,&t2);
			a[i]=id[s1];b[i]=id[s2];
			if(t1>t2) c[i]=1;else c[i]=0;
		}
		ans=find(1);
		cout<<name[ans]<<endl;
	}
	return 0;
}
