#include <cstdio>
#include <cstring>
#define  fr(i,x,y) for(i=x;i<=y;i++)
const int maxn=100010;
const int o=50;
int T,lena,lenb,cnt;
int son[o*maxn][10];
int who[o*maxn];
char a[100],b[100],c[100];
void Plus(){
	int pa,pb,pc,v;
	lena=strlen(a+1);
	lenb=strlen(b+1);
	for(pa=lena,pb=lenb,v=pc=0;pa||pb;pa--,pb--){
		if(pa)v+=a[pa]-'0';
		else pa++;
		v+=b[pb]-'0';
		c[++pc]=v%10+'0';
		v/=10;
	}
	if(v)c[++pc]=v+'0';
	memcpy(a+1,b+1,lenb*sizeof(char));lena=lenb;
	lenb=pc;
	fr(v,1,pc)b[v]=c[pc-v+1];
	if(lenb>o)lenb--,lena--;
	a[lena+1]=b[lenb+1]='\0';
}
void Insert(char *s,int num){
	int x;
	for(x=0;*s;s++){
		int &y=son[x][(*s)-'0'];
		if(!y)who[y=++cnt]=num;
		x=y;
	}
}
void Pretreat(){
	int i;
	a[1]=b[1]='1';
	a[2]=b[2]='\0';
	Insert(b+1,0);
	fr(i,2,99999){
		Plus();
		Insert(b+1,i);
	}
}
int Get(char *s){
	int x;
	for(x=0;*s;s++){
		int &y=son[x][(*s)-'0'];
		if(!y)return -1;
		x=y;
	}
	return who[x];
}
int main(){
	int t;
	Pretreat();
	scanf("%d",&T);
	fr(t,1,T){
		scanf("%s",c+1);
		printf("Case #%d: %d\n",t,Get(c+1));
	}
}