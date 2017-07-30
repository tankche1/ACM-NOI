/*
花了n多时间 从RE到WA 最后发现是写论文那货的程序有问题。。
*/
# include<stdio.h>
# include<string.h>
# include<time.h>
using namespace std;
const int BLOCKSIZE=20000;
const int MAXL=1024*1024*2+200;
const int MAXBLOCK=MAXL/BLOCKSIZE*2+100;
int sum=0;
int min(int a,int b) {return a<b?a:b;}
int n;
char str[MAXL];
char data[MAXBLOCK][BLOCKSIZE];
int next[MAXBLOCK];
int freelist[MAXBLOCK],free_pos;
int count[MAXBLOCK];
int head=0;
int shit=0;

void find(int &p,int &b){
	for(b=head;b!=-1&&count[b]<p;b=next[b]) {//printf("b:%d %d\n",b,count[b]);if(++shit>0) printf("shit:%d b:%d\n",shit,b);
		p-=count[b];}
}

int newnode(){return freelist[free_pos++];}
void delnode(int t) {if(t==head) head=next[t];freelist[--free_pos]=t;}

void fillblock(int b,int n,char str[],int _next){
	if(b==-1) return;
	memcpy(data[b],str,n);
	next[b]=_next;
	count[b]=n;
}

void maintainlist(int b){
	int t;
	for(;b!=-1;b=next[b]){
		for(t=next[b];t!=-1&&count[b]+count[t]<=BLOCKSIZE;t=next[t]){
			memcpy(data[b]+count[b],data[t],count[t]);
			count[b]+=count[t];
			next[b]=next[t];
			delnode(t);
		}
	}
}

void splite(int b,int p){
	if(b==-1||count[b]==p) return;
	int t=newnode();
	fillblock(t,count[b]-p,data[b]+p,next[b]);
	next[b]=t;count[b]=p;
}

void Insert(int p,int n,char str[]){
	sum+=n;
	int b,t,i;//puts("fuck");
	find(p,b);//puts("fuck");
	splite(b,p);//puts("fuck");
	for(i=0;i+BLOCKSIZE<=n;i+=BLOCKSIZE,b=next[b]){
		t=newnode();
		fillblock(t,BLOCKSIZE,str+i,next[b]);
		next[b]=t;
	}
	if(n-i){
		t=newnode();fillblock(t,n-i,str+i,next[b]);
		next[b]=t;
	}
	maintainlist(b);
}

void Delete(int p,int n){
	int b,t;
	n=min(sum-p,n);sum-=n;
	find(p,b);//printf("count[b]:%d\n",count[b]);
	splite(b,p);//printf("count[b]:%d\n",count[b]);
	//printf("b:%d %d %d\n",b,count[b],count[next[b]]);
	for(t=next[b];t!=-1&&count[t]<n;t=next[t]) {n-=count[t];}
		//printf("t:%d next[t]:%d\n",t,next[t]);
	splite(t,n);
	t=next[t];
	for(int e=next[b];e!=t;e=next[e])
		delnode(e);
	next[b]=t;//printf("next[b]:%d sum:%d\n",next[b],sum);
	maintainlist(b);
}

void Get(int p,int n,char str[]){
	int b,t,i;n=min(sum-p,n);
	find(p,b);
	splite(b,p);
	t=next[b];
	for(i=0;t!=-1&&i+count[t]<=n;i+=count[t],t=next[t]){
		memcpy(str+i,data[t],count[t]);
	}
	if(n-i&&t!=-1)
		memcpy(str+i,data[t],n-i);
	maintainlist(b);
	str[n]='\0';
}

/*	int b,t,i;
	find(p,b);
	printf("count:%d\n",count[b]);
	i=min(n, count[b]-p);
	memcpy(str, data[b]+p, i);
	for(t=next[b]; t!=-1 && i + count[t] <= n; i+=count[t],t=next[t])
		memcpy(str+i, data[t], count[t]);
	if(n-i && t!=-1)memcpy(str+i, data[t], n-i);
	str[n]='\0';
}*/

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	free_pos=1;
	for(int i=1;i<MAXBLOCK;i++) freelist[i]=i;
		count[0]=0;next[0]=-1;
	char op[20];
	int num;
	scanf("%d",&num);
	int cur=0,k;
	while(num--){
		scanf("%s",op);
		if(cur>sum) cur=sum;
		if(cur<0) cur=0;
		if(op[0]=='M') scanf("%d",&k),cur=k;
			else if(op[0]=='N') cur++;
				else if(op[0]=='P') cur--;
					else if(op[0]=='I'){
						scanf("%d",&n);
						for(int i=0;i<n;i++){
							scanf("%c",&str[i]);
							if(str[i]<32||str[i]>126) i--;
						}
						Insert(cur,n,str);
					}
					else if(op[0]=='D'){
						scanf("%d",&n);
						Delete(cur,n);
					}
					else if(op[0]=='G'){
						scanf("%d",&n);
						Get(cur,n,str);
						printf("%s\n",str);
					}
	}
	//printf("shit:%d\n",shit);
	return 0;
}
/*
1000
Insert 6
aaaaac
Move 5
Delete 1
*/
