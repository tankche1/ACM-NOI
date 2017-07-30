# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2010;
int a[maxn],ini[maxn],n,r;
//int table[maxn*maxn];
int nowt;
bool ok;
int table1,table2,tablesize1,tablesize2,num2,num3;
bool check(int t){
	//printf("t:%d\n",t);
	//for(int i=1;i<=t;i++) table[i]=r;
	for(int i=1;i<=n;i++) a[i]=ini[i];
	num2=num3=0;
	for(int i=1;i<=n;i++){
		if(a[i]&1) num3++,a[i]-=3;
	}
	if(r&1) table1=t,table2=0,tablesize1=r,tablesize2=r-3;
	else table1=0,table2=t,tablesize1=0,tablesize2=r;
	//先把桌子容量变为偶数
	if(table1){
		if(num3>=table1){//3 比较多
			num3-=table1;table2+=table1;table1=0;
		}
		else{//奇数桌子比较多
			if(num3+1<table1){//cut 6
				for(int i=1;i<=n;i++){
					while(a[i]>=6){
						a[i]-=6;num3+=2;
						if(num3+1>=table1) break;
					}
					if(num3+1>=table1) break;
				}
			}
			table1-=num3;table2+=num3;num3=0;
		}
	}
	//此时1.桌子有奇数座位 2.桌子没有奇数座位 团队有肯能有奇数个人
	for(int i=1;i<=n;i++) num2+=a[i]/2;
	if(table1){//1.桌子有奇数座位 团队没有奇数个人
		while(table1--){
			num2-=tablesize1/2;
			if(num2<=0) return true;
		}
		while(table2--){
			num2-=tablesize2/2;
			if(num2<=0) return true;
		}
	}
	else{ //2.桌子没有奇数座位 团队有可能有奇数个人 先把偶数个三搞进去 在插2 最后插孤独的3
		int f3=tablesize2/3;//每张桌子可以插f3个3人
		if(f3&1) f3--;
		int now;
		while(table2--){
			if(num3<=f3){
				now=tablesize2-3*num3;num3=0;
			}
			else{
				num3-=f3;now=tablesize2-3*f3;
			}
			if(now/2>=num2){
				now=now-num2*2;num2=0;
			}
			else{
				num2-=now/2;now-=now/2*2;
			}
			while(num3&&now>=3){
				now-=3;num3--;
			}
			if(!num2&&!num3) return true;
		}
	}
	return false;
}

int main(){
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++)
		scanf("%d",&ini[i]);
	int L=1,R=4000000,M;
	while(L<=R){
		M=(L+R)>>1;
		//printf("L:%d R:%d M:%d\n",L,R,M);
		if(check(M)) R=M-1;
		else L=M+1;
	}
	printf("%d\n",R+1);
	return 0;
}
