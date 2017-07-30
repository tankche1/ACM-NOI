/*
ºó×ºÊý×é
*/
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010<<1;
const int INF=10*maxn;
char s[maxn];

int sa[maxn],t1[maxn],t2[maxn],c[maxn],height[maxn],rank[maxn];
int n,n1,n2;
int pre[maxn],nex[maxn];

void get_sa(int m){
	int *x=t1,*y=t2;
	for(int i=0;i<m;i++) c[i]=0;
	for(int i=0;i<n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i]+=c[i-1];
	for(int i=0;i<n;i++) sa[--c[x[i]]]=i;

	for(int k=1;;k<<=1){
		int p=0;
		for(int i=n-1;i+k>=n;i--) y[p++]=i;
		for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;

		for(int i=0;i<m;i++) c[i]=0;
		for(int i=0;i<n;i++) c[x[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];

		for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];

		swap(x,y);
		x[sa[0]]=p=0;
		for(int i=1;i<n;i++)
			x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p:++p;
		p++;
		if(p>=n) break;
		m=p;
	}
	//for(int i=0;i<n;i++)
		//printf("sa[%d]:%d\n",i,sa[i]);
}
int dp[maxn][22];
int step=20;

void get_height(){
	for(int i=0;i<n;i++) rank[sa[i]]=i;
	int k=0;
	for(int i=0;i<n;i++){
		if(k) k--;
		if(rank[i]==0) continue;
		int j=sa[rank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[rank[i]]=k;
	}
	pre[0]=-1;
	for(int i=1;i<n;i++){
        if(sa[i-1]>n1){
            pre[i]=i-1;
        }
        else pre[i]=pre[i-1];
	}
	nex[n-1]=n;
	for(int i=n-2;i>=0;i--){
        if(sa[i+1]>n1) nex[i]=i+1;
        else nex[i]=nex[i+1];
	}
	for(int i=1;i<n;i++){
        dp[i][0]=height[i];
	}
	for(int j=1;j<=step;j++){
        for(int i=1;i<n;i++){
            dp[i][j]=dp[i][j-1];
            if(i+(1<<(j-1))<n) dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
        }
	}
	//puts(s);
	/*for(int i=0;i<n;i++){
        printf("sa[%d]:%d\n",i,sa[i]);
	}
	for(int i=1;i<n;i++)
		printf("height[%d]:%d\n",i,height[i]);
    for(int i=0;i<n;i++){
        printf("pre[%d]:%d\n",i,pre[i]);
    }
    for(int i=0;i<n;i++){
        printf("nex[%d]:%d\n",i,nex[i]);
    }*/
}

int LCP(int L,int R){
    int len=R-L+1;
    int j=log(len)/log(2);
//    while(j>0&&(1<<j)>len) j--;
    //printf("LCP:%d %d %d\n",L,R,min(dp[L][j],dp[R-(1<<j)+1][j]));
    return min(dp[L][j],dp[R-(1<<j)+1][j]);
}

char s2[maxn>>1];

int main(){
	scanf("%s",s);
	scanf("%s",s2);
	n=n1=strlen(s);n2=strlen(s2);
	s[n]='#';
	for(int i=0;i<n2;i++)
        s[n+1+i]=s2[i];
    s[n+1+n2]=1;
    n=n+1+n2+1;
    s[n]='\0';
	get_sa('z'+1);
	get_height();
	int len,ans=-INF,ansl,ansr;
	for(int L=0;L<n1;L++){
        len=0;
        if(pre[rank[L]]!=-1) len=max(len,LCP(pre[rank[L]]+1,rank[L]));
        if(nex[rank[L]]!=n) len=max(len,LCP(rank[L]+1,nex[rank[L]]));
        if(len>0&&ans<len-max(L,n1-(L+len)))
            ans=len-max(L,n1-(L+len)),ansl=L,ansr=L+len-1;
	}
	if(ans==-INF){
        printf("-1 -1\n");
	}
	else{
        printf("%d %d\n",ansl,ansr);
	}
	return 0;
}
