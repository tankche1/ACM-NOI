#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int sa[maxn],t1[maxn],t2[maxn],c[maxn],height[maxn],_rank[maxn];
int n;
char s[maxn];

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
	//	printf("sa[%d]:%d\n",i,sa[i]);
}

void get_height(){
	for(int i=0;i<n;i++) _rank[sa[i]]=i;
	int k=0;
	for(int i=0;i<n;i++){
		if(k) k--;
		if(_rank[i]==0) continue;
		int j=sa[_rank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		height[_rank[i]]=k;
	}
	//for(int i=1;i<n;i++)
	//	printf("height[%d]:%d\n",i,height[i]);
}

int Step=17;
int dp[maxn][20];

void Prepare(){
    for(int i=1;i<n;i++) dp[i][0]=height[i];
    for(int j=1;j<=Step;j++){
        for(int i=1;i<n;i++){
            dp[i][j]=dp[i][j-1];
            if(i+(1<<(j-1))<n) dp[i][j]=min(dp[i][j],dp[i+(1<<(j-1))][j-1]);
        }
    }
}

int query(int L,int R){
    //printf("L:%d R:%d\n",L,R);
    if(L>R) swap(L,R);
    int j;
    for(j=Step;j>0&&((1<<j)>(R-L));j--);
    return min(dp[L+1][j],dp[R-(1<<(j))+1][j]);
}

//typedef pair<int,int> pi;
//pi ans,res;
int ans_len,ans_pos;
int ans_num;
int ans[maxn],cnt=0;

int main(){
    int Tcase=0;
	while(scanf("%s",s)!=EOF){
        if(s[0]=='#') break;
        //ans=make_pair(-1,-1);
        n=strlen(s);
        s[n++]='a'-1;
	    get_sa('z'+1);
        get_height();
        Prepare();
        ans_num=cnt=0;

        for(int L=1;2*L<=n;L++){
           // printf("L:%d \n",L);
            for(int i=0;(i+1)*L<n;i++){
               // printf("i:%d\n",i);
                int k=query(_rank[i*L],_rank[(i+1)*L]);
                //res=make_pair(k/L+1,-_rank[i*L]);
               // printf("k:%d num:%d \n",k,k/L+1);
                if(k/L+1>ans_num){
                    ans_num=k/L+1;ans[cnt=0]=L;
                }
                else if(k/L+1==ans_num)
                    ans[++cnt]=L;

                if(k%L){
                    int pos=i*L-(L-k%L);
                    if(pos>=0){
                        k=query(_rank[pos],_rank[pos+L]);
                        if(k/L+1>ans_num){
                            ans_num=k/L+1;ans[cnt=0]=L;
                        }
                        else if(k/L+1==ans_num)
                            ans[++cnt]=L;
                    }
                }
            }
        }
        //printf("ans_num:%d\n",ans_num);
        //for(int i=0;i<=cnt;i++) printf("ans:%d\n",ans[i]);
        bool ok=false;
        for(int i=1;i<n;i++){
            for(int j=0;j<=cnt;j++){
                int k=query(_rank[sa[i]],_rank[sa[i]+ans[j]]);
                //printf("sa[%d]:%d k:%d rank:%d rank:%d\n",i,sa[i],k,_rank[sa[i]],_rank[sa[i]+ans[j]]);
                if(k/ans[j]+1>=ans_num){
                    ans_pos=sa[i];ans_len=ans_num*ans[j];ok=true;break;
                }
            }if(ok) break;
        }

        printf("Case %d: ",++Tcase);
        for(int i=ans_pos;i<ans_pos+ans_len;i++) printf("%c",s[i]);
        puts("");
	}


	return 0;
}
