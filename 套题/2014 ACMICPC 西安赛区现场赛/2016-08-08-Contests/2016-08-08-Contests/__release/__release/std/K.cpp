#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <set>

#ifndef PRId64
#define PRId64 "lld"
#endif

using namespace std;

int64_t a,b,res;
set<int64_t> S;
int l,ls;
int64_t st[9999],en[9999],d[9999],s[9999];

int main(){
	int test_count;
	scanf("%d", &test_count);
	for (int test = 1; test <= test_count; ++ test) {
		scanf("%" PRId64 "%" PRId64, &a, &b);
		S.clear();
		S.insert(a);
		S.insert(b);
		l=0;
		while(1){
			if(a>=b*2){
				if(b==0){
					S.insert(a);
					S.insert(0);
					break;
				}
				int64_t _a=a%(2*b);
				st[l]=a;
				en[l]=_a;
				d[l]=b;l++;
				a=_a;
				S.insert(a);
			}else{
				a-=b;
				if(a<0)a=-a;
				swap(a,b);
				S.insert(b);
			}
		}
		ls=0;
		for(set<int64_t>::iterator it=S.begin(); it!=S.end(); it++)
			s[ls++]=*it;
		res=ls;
		for(int i=0; i<l; i++){
			res+=(st[i]-en[i])/d[i]+1;
			for(int j=0; j<ls; j++){
				int64_t x=s[j];
				if(x<=st[i] && x>=en[i] && (st[i]-x)%d[i]==0)
					res--;
			}
		}
		printf("Case #%d: %" PRId64 "\n", test, res);
	}
	return 0;
}
