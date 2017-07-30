#include<stdio.h>
#include<string.h>
# include<set>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=50010;
const LL INF=(LL)1<<60;
int n,cnt;
LL h[maxn];
LL sum=0;
LL ans[maxn];
LL Min[maxn],Max[maxn];
LL v[maxn];
LL key[maxn],root[maxn];
LL num[maxn<<2];
bool insert[maxn];

void special(){
	for(int i=3;i<=n-1;i++){
		LL t=sum-abs(h[2]-h[1])+abs(h[2]-h[i])-abs(h[i+1]-h[i])-abs(h[i]-h[i-1])+abs(h[1]-h[i-1])+abs(h[i+1]-h[1]);
		ans[1]=min(ans[1],t);ans[i]=min(ans[i],t);
	}
	for(int i=2;i<=n-2;i++){
		LL t=sum-abs(h[n]-h[n-1])+abs(h[n-1]-h[i])-abs(h[i+1]-h[i])-abs(h[i]-h[i-1])+abs(h[n]-h[i-1])+abs(h[i+1]-h[n]);
		ans[i]=min(ans[i],t);ans[n]=min(ans[n],t);
	}
	for(int i=2;i<=n-2;i++){
		LL  t=sum-abs(h[i]-h[i-1])-abs(h[i+2]-h[i+1])+abs(h[i-1]-h[i+1])+abs(h[i]-h[i+2]);
		ans[i]=min(ans[i],t);ans[i+1]=min(ans[i+1],t);
	}
	LL t=sum-abs(h[3]-h[2])+abs(h[3]-h[1]);ans[1]=min(ans[1],t);ans[2]=min(ans[2],t);
	t=sum-abs(h[n-2]-h[n-1])+abs(h[n-2]-h[n]);ans[n-1]=min(ans[n-1],t);ans[n]=min(ans[n],t);
}

struct Duty{
	int op,bh,val;
	Duty() {}
	Duty(int op,int bh,int val) :op(op),bh(bh),val(val) {}
};
Duty duty[maxn*3];
int cnum;

bool cmp(Duty A,Duty B){
	if(A.val==B.val) return A.op<B.op;
	return A.val<B.val;
}

bool cmp2(Duty A,Duty B){
	if(A.val==B.val) return A.op>B.op;
	return A.val<B.val;
}

multiset<LL>::iterator it;
multiset<LL> leave[maxn];

struct SegmenTree{
	LL _min[maxn<<2];
	
	void build(int o,int L,int R){
		_min[o]=INF;
		if(L==R) {leave[L].clear();return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);build(o<<1|1,M+1,R);
	}
	
	void update(int o,int L,int R,int pos,LL val){
		if(L==R){
			leave[L].insert(val);_min[o]=*leave[L].begin();return;
		}
		int M=(L+R)>>1;
		if(pos<=M) update(o<<1,L,M,pos,val);
		else update(o<<1|1,M+1,R,pos,val);
		_min[o]=min(_min[o<<1],_min[o<<1|1]);
	}
	
	void del(int o,int L,int R,int pos,LL val){
		if(L==R){
			it=leave[L].lower_bound(val);leave[L].erase(it);_min[o]=leave[L].empty()?INF:*leave[L].begin();return;
		}
		int M=(L+R)>>1;
		if(pos<=M) del(o<<1,L,M,pos,val);
		else del(o<<1|1,M+1,R,pos,val);
		_min[o]=min(_min[o<<1],_min[o<<1|1]);
	}
	
	LL query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R) return _min[o];
		int M=(L+R)>>1;LL ans=INF;
		if(qL<=M) ans=min(ans,query(o<<1,L,M,qL,qR));
		if(qR>M) ans=min(ans,query(o<<1|1,M+1,R,qL,qR));
		//if(L==1&&R==cnt&&ans!=INF) printf("qL:%d qR:%d ans:%lld\n",qL,qR,ans);
		return ans;
	}
}seg;

int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&h[i]);if(i!=1) sum+=abs(h[i]-h[i-1]);
		num[i]=h[i];
	}cnt=n+1;
	for(int i=1;i<=n;i++) ans[i]=sum;
	special();//printf("shit:%lld\n",ans[4]);
	for(int i=2;i<n;i++){
		Min[i]=min(h[i-1],h[i+1]);
		Max[i]=max(h[i-1],h[i+1]);
		v[i]=abs(h[i]-h[i-1])+abs(h[i+1]-h[i]);
		num[cnt++]=Min[i],num[cnt++]=Max[i];
	}
	
	sort(num+1,num+cnt);
	cnt=unique(num+1,num+cnt)-(num+1);
	for(int i=1;i<=n;i++)
		h[i]=lower_bound(num+1,num+n+1,h[i])-num;
	for(int i=2;i<n;i++) Min[i]=lower_bound(num+1,num+cnt+1,Min[i])-num,Max[i]=lower_bound(num+1,num+cnt+1,Max[i])-num;
	
	cnum=0;
	for(int i=2;i<n;i++){
		duty[cnum++]=Duty(-1,i,Min[i]);
		duty[cnum++]=Duty(0,i,h[i]);
		duty[cnum++]=Duty(1,i,Max[i]);
	}
	sort(duty,duty+cnum,cmp);
	//1
	for(int i=2;i<n;i++){
		root[i]=num[Min[i]]+num[Max[i]]-2*num[h[i]]-v[i];
		key[i]=num[Min[i]]+num[Max[i]]-2*num[h[i]]-v[i];
	}
	seg.build(1,1,cnt);
	memset(insert,false,sizeof(insert));
	//printf("cnt:%d\n",cnt);
	for(int i=cnum-1;i>=0;i--){
		if(duty[i].op==-1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,1,Min[duty[i].bh])+sum+root[duty[i].bh]);
			//printf("ans[%d]:%lld query:%lld root:%lld\n",duty[i].bh,seg.query(1,1,cnt,1,Min[duty[i].bh])+sum+root[duty[i].bh],seg.query(1,1,cnt,1,Min[duty[i].bh]),root[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		}
	}
	//puts("GO");
	//2
	for(int i=2;i<n;i++){
		key[i]=num[Min[i]]+num[Max[i]]-v[i];
		root[i]=num[Max[i]]-num[Min[i]]-2*num[h[i]]-v[i];
	}
	seg.build(1,1,cnt);
	memset(insert,false,sizeof(insert));
	for(int i=cnum-1;i>=0;i--){
		if(duty[i].op==-1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0) {
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,Min[duty[i].bh],Max[duty[i].bh])+sum+root[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		}
	}
	
	//3
	for(int i=2;i<n;i++){
		key[i]=num[Min[i]]+num[Max[i]]+2*num[h[i]]-v[i];
		root[i]=-num[Max[i]]-num[Min[i]]-2*num[h[i]]-v[i];
	}
	seg.build(1,1,cnt);
	memset(insert,false,sizeof(insert));
	for(int i=cnum-1;i>=0;i--){
		if(duty[i].op==-1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0) {
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,Max[duty[i].bh],cnt)+sum+root[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		}
	}
	//puts("GO");
	//4
	for(int i=2;i<n;i++){
		key[i]=num[Max[i]]-num[Min[i]]-2*num[h[i]]-v[i];
		root[i]=num[Max[i]]+num[Min[i]]-v[i];
	}
	seg.build(1,0,cnum-1);
	memset(insert,false,sizeof(insert));
	for(int i=cnum-1;i>=0;i--){
		//printf("i:%d bh: %d op:%d\n",i,duty[i].bh,duty[i].op);
		if(duty[i].op==1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			//	puts("hei");
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,1,Min[duty[i].bh])+sum+root[duty[i].bh]);
			//printf("query:%lld root:%lld\n",seg.query(1,1,cnt,1,Min[duty[i].bh]),root[duty[i].bh]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
		}
		else if(duty[i].op==-1) insert[duty[i].bh]=0,seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
	}
	//puts("GO");
	//5
	for(int i=2;i<n;i++){
		key[i]=num[Max[i]]-num[Min[i]]-v[i];
		root[i]=num[Max[i]]-num[Min[i]]-v[i];
	}
	seg.build(1,0,cnum-1);
	memset(insert,false,sizeof(insert));
	for(int i=cnum-1;i>=0;i--){
		if(duty[i].op==1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,0,cnum-1,Min[duty[i].bh],Max[duty[i].bh])+sum+root[duty[i].bh]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
		}
		else if(duty[i].op==-1) insert[duty[i].bh]=0,seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
	}
//	puts("GO");
	//6
	for(int i=2;i<n;i++){
		key[i]=num[Max[i]]-num[Min[i]]+2*num[h[i]]-v[i];
		root[i]=-num[Max[i]]-num[Min[i]]-v[i];
	}
	seg.build(1,0,cnum-1);
	memset(insert,false,sizeof(insert));
	for(int i=cnum-1;i>=0;i--){
		//printf("i:%d bh: %d op:%d\n",i,duty[i].bh,duty[i].op);
		if(duty[i].op==1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,Max[duty[i].bh],cnt)+sum+root[duty[i].bh]);
		//	printf("ans[%d]:%lld query:%lld root:%lld\n",duty[i].bh,seg.query(1,1,cnt,Max[duty[i].bh],cnt)+sum+root[duty[i].bh],seg.query(1,1,cnt,Max[duty[i].bh],cnt),root[duty[i].bh]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
		}
		else if(duty[i].op==-1) insert[duty[i].bh]=0,seg.del(1,0,cnum-1,h[duty[i].bh],key[duty[i].bh]);
	}
	
	//puts("GO");
	//
	sort(duty,duty+cnum,cmp2);
	//7
	for(int i=2;i<n;i++){
		key[i]=-num[Max[i]]-num[Min[i]]-2*num[h[i]]-v[i];
		root[i]=num[Max[i]]+num[Min[i]]+2*num[h[i]]-v[i];
	}
	seg.build(1,0,cnum-1);
	memset(insert,false,sizeof(insert));
	for(int i=2;i<n;i++){
		if(duty[i].op==1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,1,Min[duty[i].bh])+sum+root[duty[i].bh]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
		}
	}
	//8
	for(int i=2;i<n;i++){
		key[i]=-num[Max[i]]-num[Min[i]]-v[i];
		root[i]=num[Max[i]]-num[Min[i]]+2*num[h[i]]-v[i];
	}
	seg.build(1,0,cnum-1);
	memset(insert,false,sizeof(insert));
		for(int i=2;i<n;i++){
		if(duty[i].op==1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,Min[duty[i].bh],Max[duty[i].bh])+sum+root[duty[i].bh]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
		}
	}
	//9
	for(int i=2;i<n;i++){
		key[i]=-num[Max[i]]-num[Min[i]]+2*num[h[i]]-v[i];
		root[i]=-num[Max[i]]-num[Min[i]]+2*num[h[i]]-v[i];
	}
	seg.build(1,0,cnum-1);
	memset(insert,false,sizeof(insert));
		for(int i=2;i<n;i++){
		if(duty[i].op==1) insert[duty[i].bh]=1,seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
		else if(duty[i].op==0){
			if(insert[duty[i].bh-1]) seg.del(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.del(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
			if(insert[duty[i].bh]) seg.del(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			ans[duty[i].bh]=min(ans[duty[i].bh],seg.query(1,1,cnt,Max[duty[i].bh],cnt)+sum+root[duty[i].bh]);
			if(insert[duty[i].bh]) seg.update(1,1,cnt,h[duty[i].bh],key[duty[i].bh]);
			if(insert[duty[i].bh-1]) seg.update(1,1,cnt,h[duty[i].bh-1],key[duty[i].bh-1]);if(insert[duty[i].bh+1]) seg.update(1,1,cnt,h[duty[i].bh+1],key[duty[i].bh+1]);
		}
	}
	
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
