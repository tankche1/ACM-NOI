#include<cstdio>
# include<time.h>
#include<algorithm>
using namespace std;

int n=7,m=12,K=10,len,x=5;

int main()
{
 //freopen("input.txt","w",stdout);
 int i,a,b,num=0,d;
 printf("%d %d\n",n,m);
 srand(time(0));
 for(i=1;i<=m;++i)
 {
 a=rand()%n+1,b=rand()%n+1;
 while(a==b)
 {
 a=rand()%n+1,b=rand()%n+1;
 }
 if(a>b)swap(a,b);
 printf("%d %d\n",a,b);
 }
 printf("%d\n",K);
while(K--)
{
len=rand()%10+1;
int p,last;
d=0;num=0;
for(i=1;i<=len||!d;++i)
{
p=rand();
if(!d && rand()%3==0)printf("%c",rand()%x+'A'),d=1,last=8;
if(p%7==0)
{
if(last==8)
{
--i;
continue;
}
printf("("),++num;
}else if(p%7==1)
{
if(!num || !d)
{
--i;
continue;
}
printf(")");
--num;
}else if(p%7==2)
{
if(d)
{
--i;
continue;
}
printf("~");
d=0;
}else if(p%7==3)
{
if(!d)
{
--i;
continue;
}
printf("&");
d=0;
}else if(p%7==4)
{
if(!d)
{
--i;
continue;
}
printf("=>");
d=0;
}else if(p%7==5)
{
if(!d)
{
--i;
continue;
}
printf("|");
d=0;
}else if(p%7==6)
{
if(!d)
{
--i;
continue;
}
printf("=");
d=0;
}
}
last=p%7;
while(num)
{
printf(")");
--num;
}
printf("\n");
}
}
