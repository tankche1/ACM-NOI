#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
using namespace std;
const int MAXN = 100010;
long long gcd(long long a,long long b){
	if(b == 0)return a;
	return gcd(b,a%b);
}
int F[MAXN];
int find(int x){
	if(F[x] == -1)return x;
	return F[x] = find(F[x]);
}
void bing(int x,int y){
	int t1 = find(x);
	int t2 = find(y);
	if(t1 != t2)F[t2] = t1;
}
int a[MAXN];
struct Node1{
	int r1,r2;
	int val;
	Node1(int _r1 = 0,int _r2 = 0,int _val = 0){
		r1 = _r1;
		r2 = _r2;
		val = _val;
	}
	bool operator <(const Node1 &b)const{
		if(r1 != b.r1)return r1 < b.r1;
		else r2 < b.r2;
	}
};
vector<Node1>vec1[MAXN];
struct Node2{
	int l,r1,r2;
	long long sum;
	Node2(int _l = 0,int _r1 = 0,int _r2 = 0){
		l = _l;
		r1 = _r1;
		r2 = _r2;
	}
	bool operator <(const Node2 &b)const{
		if(l != b.l)return l < b.l;
		else return r1 < b.r1;
	}
};
vector<Node2>vec2[MAXN];
int num1[MAXN];
int b[MAXN];
int main()
{
    //freopen("A.in","r",stdin);
    //freopen("A.out","w",stdout);
    int T;
	scanf("%d",&T);
	assert(T <= 10);
	int n,Q;
	int iCase = 0;
	while(T--){
		iCase++;
		printf("Case #%d:\n",iCase);
		scanf("%d%d",&n,&Q);
		assert(n >= 1 && n <= 100000 && Q >= 1 && Q <= 100000);
		int Max = 1;
		for(int i = 1;i <= n;i++){
			scanf("%d",&a[i]);
			assert(a[i] >= 1 && a[i] <= 100000);
			vec1[i].clear();
			Max = max(Max,a[i]);
		}
		for(int i = 1;i <= Max;i++)vec2[i].clear();
		F[n+1] = -1;
		for(int i = n;i >= 1;i--){
			F[i] = -1;
			int start = i;
			int pre = i;
			b[i] = a[i];
			for(int j = find(i+1);j <= n;j = find(j+1)){
				b[j] = gcd(a[i],b[j]);
				if(b[j] != b[pre]){
					vec1[i].push_back(Node1(start,pre,b[pre]));
					vec2[b[pre]].push_back(Node2(i,start,pre));
					start = pre+1;
				}
				else bing(j,pre);
				pre = j;
			}
			vec1[i].push_back(Node1(start,n,b[n]));
			vec2[b[n]].push_back(Node2(i,start,n));
			sort(vec1[i].begin(),vec1[i].end());
			/*
			printf("i  %d\n",i);
			int sz = vec1[i].size();
			for(int j = 0;j < sz;j++)
				printf("%d %d %d\n",vec1[i][j].r1,vec1[i][j].r2,vec1[i][j].val);
				*/
		}
		num1[0] = 0;
		for(int i = 1;i <= Max;i++){
			sort(vec2[i].begin(),vec2[i].end());
			int sz = vec2[i].size();
			if(sz)num1[i] = num1[i-1]+1;
			else num1[i] = num1[i-1];
			for(int j = 0;j < sz;j++){
				if(j == 0)vec2[i][j].sum = 0;
				else vec2[i][j].sum = vec2[i][j-1].sum;
				vec2[i][j].sum += vec2[i][j].r2-vec2[i][j].r1+1;
			}
			/*
			printf("i: %d\n",i);
			printf("num1:%d\n",num1[i]);
			for(int j = 0;j < sz;j++)
				printf("%d %d %d %I64d\n",vec2[i][j].l,vec2[i][j].r1,vec2[i][j].r2,vec2[i][j].sum);
				*/
		}
		char op[20];
		long long k1,k2;
		while(Q--){
			scanf("%s%I64d%I64d",op,&k1,&k2);
			if(op[0] == 'R'){
				assert(k1 >= 1 && k1 <= k2 && k2 <= n);
				int id ;
				int sz = vec1[k1].size();
				int l = 0, r = sz-1;
				while(l <= r){
					int mid = (l+r)/2;
					if(vec1[k1][mid].r1 <= k2 && k2 <= vec1[k1][mid].r2){
						id = mid;
						break;
					}
					else if(vec1[k1][mid].r2 < k2)l = mid+1;
					else r = mid-1;
				}
				int val = vec1[k1][id].val;
				int ans1 = num1[val];
				id = lower_bound(vec2[val].begin(),vec2[val].end(),Node2(k1,0,0)) - vec2[val].begin();
				long long ans2;
				if(id == 0)ans2 = k2 - vec2[val][id].r1 + 1;
				else ans2 = vec2[val][id-1].sum + k2 - vec2[val][id].r1 + 1;
				printf("%d %I64d\n",ans1,ans2);
			}
			else {
				assert(k1 >= 1 && k1 <= (long long)n*(n+1)/2 && k2 >= 1 && k2 <= (long long)n*(n+1)/2);
				int id1 = lower_bound(num1+1,num1+Max+1,k1) - num1;
				if(id1 > Max || num1[id1] != k1){
					printf("-1\n");
					continue;
				}
				int sz = vec2[id1].size();
				if(k2 > vec2[id1][sz-1].sum){
					printf("-1\n");
					continue;
				}
				int l = 0, r = sz-1;
				int id2 = 0;
				while(l <= r){
					int mid = (l+r)/2;
					long long ss = vec2[id1][mid].sum - (vec2[id1][mid].r2 - vec2[id1][mid].r1 + 1);
					if(k2 > ss){
						id2 = mid;
						l = mid+1;
					}
					else r = mid-1;
				}
				k2 -= vec2[id1][id2].sum - (vec2[id1][id2].r2 - vec2[id1][id2].r1 + 1);
				printf("%d %d\n",vec2[id1][id2].l,(int)(vec2[id1][id2].r1 + k2 - 1));
			}
		}
	}
    return 0;
}