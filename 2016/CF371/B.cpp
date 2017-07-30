# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
int n;

/*int ask(int a,int b,int c,int d){
    int x;
    printf("? %d %d %d %d\n",a,b,c,d);
    fflush(stdout);
    scanf("%d",&x);
    return x;
}
*/

int ask(int a,int b,int c,int d)
{
	printf("? %d %d %d %d\n",a,b,c,d);
	fflush(stdout);
	int x;
	scanf("%d",&x);
	return x;
}

int ans[9],cnt=0;

void cal(int a,int b,int c,int d){
    int l=a,r=c,mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(ask(mid,b,c,d)) l=mid+1;
        else r=mid-1;
    }
    ans[cnt++]=l-1;

    l=b;r=d;
    while(l<=r){
        mid=(l+r)>>1;
        if(ask(a,mid,c,d)) l=mid+1;
        else r=mid-1;
    }
    ans[cnt++]=l-1;

    l=a;r=c;
    while(l<=r){
        mid=(l+r)>>1;
        if(!ask(a,b,mid,d)) l=mid+1;
        else r=mid-1;
    }
    ans[cnt++]=r+1;

    l=b;r=d;
    while(l<=r){
        mid=(l+r)>>1;
        if(!ask(a,b,c,mid)) l=mid+1;
        else r=mid-1;
    }
    ans[cnt++]=r+1;
}

void work(){
    int l=1,r=n,mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(!ask(1,1,n,mid)) l=mid+1;
        else r=mid-1;
    }
    if(ask(1,1,n,r+1)==1&&ask(1,r+2,n,n)==1){
        cal(1,1,n,r+1);cal(1,r+2,n,n);return;
    }
    //puts("fuck");
    l=1;r=n;
    while(l<=r){
        mid=(l+r)>>1;
        if(!ask(1,1,mid,n)) l=mid+1;
        else r=mid-1;
    }

    cal(1,1,r+1,n);cal(r+2,1,n,n);return;
}

int main(){
    scanf("%d",&n);
    work();printf("!");
    for(int i=0;i<8;i++) printf(" %d",ans[i]);puts("");
    return 0;
}
