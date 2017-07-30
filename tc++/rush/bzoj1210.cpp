# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
int m,n;
typedef long long LL;
map<unsigned int,LL> hash[22][12];


struct state{
	int up[10],left;
	state() {}
	
	unsigned int encode(){
		unsigned int res=0;
		res=res*3+left;
		for(int i=0;i<n;i++)
			res=res*3+up[i];
		return res;
	}
	
	bool next(state &T,int row,int col,int U,int D,int L,int R){
		if(up[col]==0&&U) return false;
		if(!U&&up[col]) return false;
		if(left&&(!L)) return false;
		if(!left&&L) return false;
		if(row==m-1&&D) return false;
		if(col==n-1&&R) return false;
		memcpy(T.up,up,sizeof(up));T.left=left;
		if(U&&L){
			if(left==1&&up[col]==1){//((
				T.left=0,T.up[col]=0;int now=0;
				for(int i=col+1;i<n;i++){
					if(up[i]==1) now++;
						else if(up[i]==2) now--;
							if(now==-1) {T.up[i]=1;break;}
				}
				return true;
			}
			if(left==1&&up[col]==2){//()
				if(!(col==n-1&&row==m-1)) return false;
				T.left=0,T.up[col]=0;return true;
			}
			if(left==2&&up[col]==1){//)(
				T.up[col]=T.left=0;return true;
			}
			if(left==2&&up[col]==2){//))
				T.left=0;T.up[col]=0;int now=0;
				for(int i=col-1;i>=0;i--){
					if(up[i]==1) now++;
						else if(up[i]==2) now--;
							if(now==1) {T.up[i]=2;break;}
				}
				return true;
			}
		}
		if(U&&D)
			return true;
		if(U&&R){
			T.up[col]=0;T.left=up[col];return true;
		}
		if(D&&L){
			T.up[col]=left;T.left=0;return true;
		}
		if(D&&R){
			T.up[col]=1;T.left=2;return true;
		}
		if(L&&R){
			T.left=left;return true;
		}
	}
};

LL rec(int row,int cal,state S){
	unsigned int key=S.encode();
	if(hash[row][cal].count(key)) return hash[row][cal][key];
	LL &res=hash[row][cal][key];res=0;
	if(cal==n) row++,cal=0;
	if(row==m) return res=1;
	state T;
	if(S.next(T,row,cal,1,1,0,0)) res+=rec(row,cal+1,T);
	if(S.next(T,row,cal,1,0,1,0)) res+=rec(row,cal+1,T);
	if(S.next(T,row,cal,1,0,0,1)) res+=rec(row,cal+1,T);
	if(S.next(T,row,cal,0,1,1,0)) res+=rec(row,cal+1,T);
	if(S.next(T,row,cal,0,1,0,1)) res+=rec(row,cal+1,T);
	if(S.next(T,row,cal,0,0,1,1)) res+=rec(row,cal+1,T);
	return res;
}

int main(){
	scanf("%d%d",&m,&n);
	swap(m,n);
	state S;
	memset(S.up,0,sizeof(S.up));S.left=0;
	
	printf("%lld\n",rec(0,0,S)*2);
	return 0;
}
