# include<stdio.h>
# include<string.h>
# include<string>
# include<iostream>
# include<map>
# include<algorithm>
using namespace std;
char s[10010];
const int maxn=2100;
const int maxm=10100;
string s1,s2;
int n,cnt1,cnt2;
map<string,int> id1,id2;
int first[maxn],next[maxm],v[maxm],edge=0;
bool vis[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

void dfs(int x){
	if(vis[x]) return;
	vis[x]=1;
	for(int e=first[x];e!=-1;e=next[e]) dfs(v[e]);
}

int main(){
	int tcase,tnum=0,space,pos[120],t1,t2;pos[0]=-1;
	//freopen("out.txt","w",stdout);
	scanf("%d\n",&tcase);
	while(tcase--){
		printf("Case #%d: \n",++tnum);
		id1.clear();id2.clear();cnt1=0;cnt2=111;
		memset(first,-1,sizeof(first));edge=0;
		while(gets(s)){
			n=strlen(s);//ss=s;
			while(s[n-1]==' '){n--;s[n]=0;}
			space=0;for(int i=0;i<n;i++) if(s[i]==' ') pos[++space]=i;
			if(s[n-1]=='!'){ break;}
			else if(s[n-1]=='.'){
				s2="";s1="";
				for(int i=pos[space]+1;i<n-1;i++)
					s2=s2+s[i];
				for(int i=pos[space-2]+1;i<pos[space-1];i++)
					s1=s1+s[i];
				if(space==2){
					if(s[pos[space]-1]=='e'){
						if(!id1[s1]) id1[s1]=++cnt1;if(!id1[s2]) id1[s2]=++cnt1;
						t1=id1[s1];t2=id1[s2];
					}
					else{
						if(!id1[s1]) id1[s1]=++cnt1;if(!id2[s2]) id2[s2]=++cnt2;
						t1=id1[s1];t2=id2[s2];
					}
				}
				else{
					if(s[pos[space]-1]=='e'){
						if(!id2[s1]) id2[s1]=++cnt2;if(!id1[s2]) id1[s2]=++cnt1;
						t1=id2[s1];t2=id1[s2];
					}
					else{
						if(!id2[s1]) id2[s1]=++cnt2;if(!id2[s2]) id2[s2]=++cnt2;
						t1=id2[s1];t2=id2[s2];
					}
				}
				//cout<<"s1:"<<s1<<" s2:"<<s2 << endl;
				//printf("state t1:%d t2:%d\n",t1,t2);
				add_edge(t1,t2);
			}
			else{
				s2="";s1="";
				for(int i=pos[space]+1;i<n-1;i++)
					s2=s2+s[i];
				for(int i=pos[space-1]+1;i<pos[space];i++)
					s1=s1+s[i];
				if(space==2){
					if(!id1[s1]) id1[s1]=++cnt1;
					t1=id1[s1];
					if(s[0]=='a'){
						if(!id1[s2]) id1[s2]=++cnt1;
						t2=id1[s2];
					}
					else{
						if(!id2[s2]) id2[s2]=++cnt2;
						t2=id2[s2];
					}
				}
				else{
					if(!id2[s1]) id2[s1]=++cnt2;
					t1=id2[s1];
					if(s[0]=='c') {if(!id2[s2]) id2[s2]=++cnt2;t2=id2[s2];}
					else {
						if(!id1[s2]) id1[s2]=++cnt1;
						t2=id1[s2];
					}
				}
				//cout<<"s1:"<<s1<<" s2:"<<s2 << endl;
				//printf("ask t1:%d t2:%d\n",t1,t2);
				if(!t1) {printf("M");continue;}
				if(!t2) {printf("M");continue;}
				for(int i=1;i<=250;i++) vis[i]=false;
				dfs(t1);
				if(vis[t2]) printf("Y");
				else printf("M");
			}
		}
		printf("\n");
	}
	return 0;
}
