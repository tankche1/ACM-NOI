#include<cstdio>     
int sol(int x,int y){  
	int t,n=31;   
	for(int m=30;m;--m){  
		t=1<<m;     if(x<=t&&y<=t)n=m;  
			if(x>t)x-=t;     if(y>t)y-=t;   }   
			return (x==1&&y==1)?0:n; }     
			int main(){  
				int T,n,s,x,y;   scanf("%d",&T);   
				while(T--){     scanf("%d",&n),n>>=1;     for(s=0;n--;){       scanf("%d%d",&x,&y);       s^=sol(x,y);     }     puts(s?"YES":"NO");   }   return 0; }