# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int a[70],b[70],c[70];
int lena,lenb,lenc;

int son[100010*51][10],num[100010*51],cnt=0;

void insert(int *s,int n,int bh){
	int x=0;
	for(int i=0;i<n&&i<40;i++){
		if(!son[x][s[i]]) son[x][s[i]]=++cnt,num[cnt]=bh;
		x=son[x][s[i]];
	}
}

void plus(){
	for(int i=0;i<lenb;i++){
		if(lena-1-i>=0) c[i]=a[lena-1-i];else c[i]=0;
		c[i]+=b[lenb-1-i];
	}
	lenc=lenb;c[lenc]=0;
	for(int i=0;i<lenc;i++){
		if(c[i]>=10) c[i+1]++,c[i]-=10;
	}
	if(c[lenc]>0) lenc++;
	lena=lenb;for(int i=0;i<lena;i++) a[i]=b[i];
	for(int i=0;i<lenc;i++)
		b[lenc-1-i]=c[i];
	lenb=lenc;
	while(lena>55) lena--,lenb--;
}

int find(int *a,int lena){
	int x=0;
	for(int i=0;i<lena;i++){
		x=son[x][a[i]];
		if(!x) return -1;
	}
	return num[x];
}

int main(){
	memset(num,-1,sizeof(num));
	lena=1;a[0]=1;lenb=1;b[0]=1;
	insert(a,lena,0);
	for(int i=2;i<100000;i++){
		plus();
		/*if(i<=20){
			for(int j=0;j<lenb;j++) printf("%d",b[j]);puts("");
		}*/
		insert(b,lenb,i);
	}
	int tcase,tnum=0;
	char t;
	scanf("%d\n",&tcase);
	while(tcase--){
		while((t=getchar())&&(t<'0'||t>'9'));
		a[0]=t-'0';lena=1;
		while((t=getchar())&&t>='0'&&t<='9') a[lena++]=t-'0';
		printf("Case #%d: %d\n",++tnum,find(a,lena));
	}
	return 0;
}
