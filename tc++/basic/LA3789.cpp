# include<stdio.h>
# include<string.h>
# include<string>
# include<queue>
# include<map>
# include<algorithm>
using namespace std;
int n,m;
int goalx,goaly;
queue<string> q;
char link_r[260],link_l[256],clear_l[256],clear_r[256];
map<string,string> sol;

void init(){
memset(link_l, ' ', sizeof(link_l));
  link_l['O'] = ']'; link_l['['] = '=';
  memset(link_r, ' ', sizeof(link_r));
  link_r['O'] = '['; link_r[']'] = '=';
  memset(clear_l, ' ', sizeof(clear_l));
  clear_l[']'] = 'O'; clear_l['='] = '['; clear_l['O'] = 'O'; clear_l['['] = '[';
  memset(clear_r, ' ', sizeof(clear_r));
  clear_r['['] = 'O'; clear_r['='] = ']'; clear_r['O'] = 'O'; clear_r[']'] = ']';
}

string fall(string s){
	int i,j,kk,k;
	for(i=n-1;i>0;i--){
		for(j=0;j<m;j++){
			if(s[i*m+j]=='.'&&s[(i-1)*m+j]!='.'&&s[(i-1)*m+j]!='X'){
				if(s[(i-1)*m+j]=='@'||s[(i-1)*m+j]=='O'){
					for(k=i;k<n;k++) if(s[(k+1)*m+j]!='.') break;
					s[k*m+j]=s[(i-1)*m+j];
					s[(i-1)*m+j]='.';
				}
			else if(s[i*m+j]=='.'&&s[(i-1)*m+j]=='['){
				for(k=j+1;k<m;k++)
					if(s[(i-1)*m+k]=='X'||s[(i-1)*m+k]==']') break;
				if(s[(i-1)*m+k]=='X') continue;
				for(kk=i-1;kk<n;kk++){
					bool jump=true;
					for(int l=j;l<=k;l++) if(s[(kk+1)*m+l]!='.') {jump=false;break;}
					if(!jump) break;
				}
				if(kk!=i-1){
					for(int l=j;l<=k;l++)
					swap(s[kk*m+l],s[(i-1)*m+l]);
				}
			}
		}
		}
	}
	return s;
}

int h(string s){
	int x=s.find('@');
	int a=abs(goaly-x%m);
	int b=goalx<=(x/m)?(x/m)-goalx:1;
	return a>b?a:b;
}

bool expand(string s,char ch){
	string seq=sol[s]+ch;
	int x=s.find('@');
	
	if(ch=='<'||ch=='>'){
		int p=ch=='<'?x+m-1:x+m+1;
		if(s[p]=='X') return false;
		if(s[p]=='.'){
			s[p]='O';
			if(s[p-1]!='X'&&s[p-1]!='.') s[p-1]=link_r[s[p-1]];
			if(s[p-1]!='.') s[p]=link_l[s[p]];
			if(s[p+1]!='X'&&s[p+1]!='.') s[p+1]=link_l[s[p+1]];
			if(s[p+1]!='.') s[p]=link_r[s[p]];
		}
		else{
			s[p]='.';
			if(s[p-1]!='X'&&s[p-1]!='.') s[p-1]=clear_r[s[p-1]];
			if(s[p+1]!='X'&&s[p+1]!='.') s[p+1]=clear_l[s[p+1]];
		}
	}
	else{
		int p=ch=='L'?x-1:x+1,d=ch=='L'?-1:1;
		if(s[p]=='.') s[p]='@',s[x]='.';
		else if(s[p]=='X'||(s[p]!='X'&&s[p+d]!='.')) {
			if(s[p-m]=='.'&&s[x-m]=='.') s[p-m]='@',s[x]='.';
			else return false;
		}
		else{
			int j;
			for(j=p+d;;j+=d) if(s[j+d]!='.'||s[j+m]=='.') break;
			s[j]='O';s[p]='.';
		}
	}
	s=fall(s);
	if(h(s)+seq.length()>15) return false;
	if(!sol.count(s)) {sol[s]=seq;q.push(s);
	/*	if(seq.length()){
	printf("seq:%s\n",seq.c_str());
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			printf("%c",s[i*m+j]);printf("\n");}
		}*/
		}
	if(s.find('@')==(goalx*m+goaly)){
		printf("%s\n",seq.c_str());return true;
	}
	return false;
}

int main(){
	//freopen("input.txt","r",stdin);
	init();
	char map[20][20];
	int kase=0;
	while(scanf("%d%d",&n,&m)==2){
		if(!n) break;
		for(int i=0;i<n;i++)
			scanf("%s",map[i]);
		string s="";
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(map[i][j]=='#') {map[i][j]='.';goalx=i;goaly=j;}
				s+=map[i][j];
			}
		printf("Case %d: ", ++kase);
		sol.clear();
		q.push(s);
		sol[s]="";
		while(!q.empty()){
				string x=q.front();q.pop();
				if(expand(x,'<')) break; if(expand(x,'>')) break;
				if(expand(x,'L')) break; if(expand(x,'R')) break;
		}
		while(!q.empty()) q.pop();
	}
	return 0;
}
/*
3 8
XXXXXXXX
X@.O.#.X
XXXXXXXX
7 6
XXXXXX
X..@.X
X..X.X
X..XXX
X=XXXX
X...#X
XXXXXX
*/
