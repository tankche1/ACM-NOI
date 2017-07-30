# include<stdio.h>
# include<string.h>
# include<string>
# include<map>
# include<iostream>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;
string s[4];
map<string,int> id;
int main(){
	int b;
	scanf("%d\n",&n);
	string t;
	for(int i=1;i<=n;i++){
		scanf("%d",&b);
		for(int k=0;k<b;k++){
			cin>>s[k];
		}
		for(int j=0;j<b-1;j++){
			for(int k=j+1;k<b;k++)
				if(s[j]>s[k]) swap(s[j],s[k]);
		}
		for(int bit=1;bit<(1<<b);bit++){
			t.clear();
			for(int j=0;j<b;j++)
				if(bit&(1<<j)) {
					t=t+s[j]+'#';
				}
			id[t]++;
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&b);
		for(int k=0;k<b;k++){
			cin>>s[k];
		}
		for(int j=0;j<b-1;j++){
			for(int k=j+1;k<b;k++)
				if(s[j]>s[k]) swap(s[j],s[k]);
		}
		t.clear();
		for(int j=0;j<b;j++)
			t=t+s[j]+'#';
		printf("%d\n",id[t]);
	}
	return 0;
}
