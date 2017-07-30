#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
# include<cstring>
using namespace std;
//pos一开始写成了x*n+y 然后各种诡异错误 不懂
# define pos(x,y) ((x)*n+(y))
const int maxn=1030;
int n;

int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}

int lcm(int a,int b){
	return a/gcd(a,b)*b;
}

int newpos(int x,int y,const char *op){
	//printf("x:%d y:%d newx:%d newy:%d pos:%d\n",x,y,n-1-y,x,pos(n-1-y,x));
	if(op[0]=='i') return pos(x,y);
	if(op[0]=='r') return pos(n-1-y,x);
	if(op[0]=='s') return pos(x,n-1-y);
	if(op[0]=='b'&&op[1]=='h') return x<n/2?pos(x,y):pos(x,n-1-y);
	if(op[0]=='b'&&op[1]=='v') return x<n/2?pos(x,y):pos(n/2+n-1-x,y);
	if(op[0]=='d') return (x%2==0)?pos(x/2,y):pos(n/2+x/2,y);
	if(op[0]=='m'){
		int k=x/2;
		if(y<=n/2-1){
			if(x%2==0) return pos(2*k,y*2);
				return pos(2*k,y*2+1);
		}
		else{
			return x%2==0?pos(2*k+1,(y-(n/2))*2):pos(2*k+1,(y-(n/2))*2+1);
		}
	}
}

int ori[maxn*maxn];

void change_square(int *image,const char *op){
	for(int i=0;i<n*n;i++) ori[i]=image[i];
	bool splay=op[strlen(op)-1]=='-';
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int p1=pos(i,j);int p2=newpos(i,j,op);
			//printf("i:%d j:%d p1:%d p2:%d\n",i,j,p1,p2);
			if(!splay) image[p2]=ori[p1];
				else image[p1]=ori[p2];
		}
	}
	/*printf("ori:\n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) printf("%d ",ori[pos(i,j)]);
			printf("\n");
	}
	printf("image:\n");
		for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) printf("%d ",image[pos(i,j)]);
			printf("\n");
	}*/
	return;
}

int cur[maxn*maxn];
int cnt[maxn*maxn];
bool vis[maxn*maxn];

void get_cnt(){
	memset(cnt,0,sizeof(cnt));
	memset(vis,false,sizeof(vis));
	for(int i=0;i<n*n;i++) {if(vis[cur[i]]) {printf("!!\n");}vis[cur[i]]=true;}
	//int a;scanf("%d",&a);
	memset(vis,false,sizeof(vis));
	int j,nn,a;
	for(int i=0;i<n*n;i++){
		if(!vis[i]){
			j=i;nn=0;
			do{
				vis[j]=true;
				nn++;
				j=cur[j];
			}while(j!=i);
			cnt[nn]++;
		//	if(nn!=4) {printf("a!nn:%d\n",nn);scanf("%d",&a);}
			//printf("nn:%d cnt:%d\n",nn,cnt[nn]);
		}
	}
	/*for(int i=1;i<=n*n;i++)
		if(cnt[i]>0){
			printf("cnt[%d]:%d\n",i,cnt[i]);
		}
	scanf("%d",&a);*/
}

int main(){
	int T,n2;
	scanf("%d",&T);	
	scanf("%d",&n);	
	while(T--){
		vector<string> ops;
		while(1){
			string op;
			if(!(cin>>op)) break;
			if(isdigit(op[0])){
				sscanf(op.c_str(),"%d",&n2);break;
			}
			ops.push_back(op);
		}
		for(int i=0;i<n*n;i++) cur[i]=i;
		for(int i=ops.size()-1;i>=0;i--){
			change_square(cur,ops[i].c_str());
		}
		//printf("aa");
		get_cnt();
		int ans=1;
		for(int i=1;i<=n*n;i++){
			if(cnt[i]){
				//printf("cnt[%d]:%d\n",i,cnt[i]);
				ans=lcm(ans,i);
			}
		}
		printf("%d\n",ans);
		//printf("n:%d\n",n);
	//	int a;//scanf("%d",&a);
		/*for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%d ",cur[pos(i,j)]);
			}
			printf("\n");
		}*/
		n=n2;
		if(T) printf("\n");
	}
	return 0;
}
/*
rot- mix div bvsym rot id bhsym mix sym- div-
1024
*/
