/*
ºó×ºÊý×é
*/

#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=200010;
char s[maxn];
int n;
int Step=17;

int sa[maxn],t1[maxn],t2[maxn],c[maxn],height[maxn],rank[maxn];

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
	//for(int i=1;i<n;i++)
		//printf("height[%d]:%d\n",i,height[i]);
}
int dp[maxn][20];

void prepare(){
    for(int i=1;i<n;i++){
        dp[i][0]=height[i];
    }

    for(int j=1;j<=Step;j++){
        for(int i=1;i<n;i++){
            dp[i][j]=dp[i][j-1];
            if((i)+(1<<(j-1))<n) dp[i][j]=min(dp[i][j],dp[i+(1<<(j-1))][j-1]);
        }
    }

}

int get_LCP(int a,int b){
    if(a>b) swap(a,b);
    int res=n+1;
    for(int j=Step;j>=0;j--){
        if(a+1+(1<<j)-1<=b) res=min(res,dp[a+1][j]),a+=(1<<j);
    }
    return res;
}

struct SegmenTree{
    int _min[maxn<<2];

    void build(int o,int L,int R){
        _min[o]=n+1;
        if(L==R) return;
        int M=(L+R)>>1;
        build(o<<1,L,M);
        build(o<<1|1,M+1,R);
    }

    void insert(int o,int L,int R,int pos,int val){
        if(L==R) {_min[o]=val;return;}
        int M=(L+R)>>1;
        if(pos<=M) insert(o<<1,L,M,pos,val);
        else insert(o<<1|1,M+1,R,pos,val);
        _min[o]=min(_min[o<<1],_min[o<<1|1]);
    }

    int query(int o,int L,int R,int qL,int qR){
        if(qL<=L&&qR>=R) return _min[o];
        int M=(L+R)>>1;
        int res=n+1;
        if(qL<=M) res=min(res,query(o<<1,L,M,qL,qR));
        if(qR>M) res=min(res,query(o<<1|1,M+1,R,qL,qR));
        return res;
    }
}seg;

int main(){
    scanf("%d",&n);
	scanf("%s",s);
	n=strlen(s);
	get_sa('z'+1);
	get_height();

	prepare();

	int ans=1;
	seg.build(1,1,n);
	seg.insert(1,1,n,rank[n-1]+1,n-1);

	int from,to,j;

	for(int i=n-2;i>=0;i--){
        int cur=1,res=1;
        //printf("i:%d\n",i);
        while(1){
            from=to=rank[i];

            for(int j=Step;j>=0;j--){
                if(from-(1<<j)+1>=1&&dp[from-(1<<j)+1][j]>=cur) from-=(1<<j);
            }

            for(int j=Step;j>=0;j--){
                if(to+(1<<j)<n&&dp[to+1][j]>=cur) to+=(1<<j);
            }

            //printf("from:%d to:%d cur:%d\n",from,to,cur);


            int wh=seg.query(1,1,n,from+1,to+1);
            //printf("wh:%d\n",wh);
           // int gg;scanf("%d",&gg);
            if(wh>n) break;

            int real=get_LCP(rank[i],rank[wh]);

            int num=(real-cur)/(wh-i)+1;

            res+=num;
            cur+=num*(wh-i);
        }
        ans=max(ans,res);

        seg.insert(1,1,n,rank[i]+1,i);
	}

	printf("%d\n",ans);
	return 0;
}
