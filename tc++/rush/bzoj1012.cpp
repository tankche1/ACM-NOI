# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int m,mod;

struct Stack{
	int pos,num;
};

Stack stack[200010];
int top=-1;
char op[10];
int x;
int main(){
	scanf("%d%d",&m,&mod);
	int t=0,len=0;
	while(m--){
		scanf("%s%d",op,&x);
		if(op[0]=='A'){
			x=(x+t)%mod;
			while(top>=0&&stack[top].num<=x) top--;
			stack[++top].num=x;stack[top].pos=++len;
		}
		else{
			int L=0,R=top,M;
			while(L<=R){
				M=(L+R)>>1;
				if(stack[M].pos>=(len-x+1)) R=M-1;
					else L=M+1;
			}
			M=R+1;
			printf("%d\n",stack[M].num);
			t=stack[M].num;
		}
	}
	return 0;
}
