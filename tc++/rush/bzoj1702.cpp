# include<stdio.h>
# include<string.h>
# include<map>
# include<string>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxk=31;
int n,k;
int a[maxn][maxk];
typedef pair<int,int> pi;
map<string,int> seq;
int read(){
	char t;
	while((t=getchar())&&(t<'0'||t>'9'));
	int num=t-'0';
	while((t=getchar())&&(t>='0'&&t<='9'))
		num=num*10+t-'0';
	return num;
}

char str[220];

string change(int *a){
	string S;
	int t=0;
	for(int i=1;i<=k;i++){
		str[t++]='A';
		int tmp=a[i];
		if(!tmp) str[t++]='0';
		while(tmp){
			str[t++]=(tmp%10)+'0';
			tmp/=10;
		}
	}
	str[t++]='\0';
	return str;
}

int main(){
	int spe;
	n=read();k=read();
	memset(a[0],0,sizeof(a[0]));
	for(int i=1;i<=n;i++){
		spe=read();
		for(int j=1;j<=k;j++){
			a[i][j]=a[i-1][j];
			if(spe&(1<<(j-1))) a[i][j]++;
		}
		for(int j=2;j<=k;j++)
			a[i][j]-=a[i][1];
		a[i][1]=0;
		/*for(int j=1;j<=k;j++)
			printf("%d ",a[i][j]);
		puts("");*/
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		string s=change(a[i]);
		if(!seq.count(s))
			seq[s]=i;
		else ans=max(ans,i-seq[s]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
5 2
2
1
3
3
2
*/
