# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxnode=1024*15*2+31770*2+10;
typedef long long LL;
LL req[maxnode],req_cnt;


struct Line{
	LL l,r;
};
Line line[1030][16];
int num[1030];
int order[32770],delet[32770];
int n=0,maxid=0;
bool used[1030];
Line query[32770];
int same[maxnode<<2][1040/16];

void update(int o,int l,int r,int ql,int qr,int col){
	if(ql<=l&&qr>=r){
		same[o][(col-1)/16+1]|=1<<(((col-1)%16));
		return;
	}
	int M=(l+r)>>1;
	if(ql<=M) update(o<<1,l,M,ql,qr,col);
	if(qr>M) update(o<<1|1,M+1,r,ql,qr,col);
}

void Delete(int o,int l,int r,int ql,int qr,int col){
	if(ql<=l&&qr>=r){
		same[o][(col-1)/16+1]^=1<<(((col-1)%16));
		return;
	}
	int M=(l+r)>>1;
	if(ql<=M) Delete(o<<1,l,M,ql,qr,col);
	if(qr>M) Delete(o<<1|1,M+1,r,ql,qr,col);
}

int have[1040/16];bool onSeg;
int tt;

bool _query(int o,int L,int R,int qnode){
	for(int i=1;i<=tt;i++) {if(have[i]&same[o][i]) return true;have[i]|=same[o][i];}
	if(L==R) return false;
	int M=(L+R)>>1;
	if(qnode<=M) return _query(o<<1,L,M,qnode);
	else return _query(o<<1|1,M+1,R,qnode);
//	return false;
}

int place(LL x){
	//onSeg=false;
	//printf("x:%d\n",x);
	int L=1,R=req_cnt;
	while(L<=R){
		int M=(R+L)>>1;
		//if(req[M]==x) return M;
		if(x>=req[M]) L=M+1;
			else R=M-1;
	}
	//printf("pos:%d\n",L-1);
	//if(req[L-1]==x) onSeg=true;
	return L-1;
}

int ans[32770];
/*bool test(){
	for(int i=1;i<=maxid;i++) if(have[i]>1) return true;
		return false;
}*/

int bh[32770];

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	char op[20];
	int id;req_cnt=1;
	memset(used,false,sizeof(used));
//	for(int i=1;i<=1024;i++) used[i]=1;
	memset(num,0,sizeof(num));
	while(scanf("%s",op)!=EOF){
		n++;	
		if(op[0]=='E'){
			order[n]=1;
			scanf("%d",&id);used[id]=1;bh[n]=id;
			//printf("id:%d\n",id);
			maxid=max(maxid,id);
			scanf("%d",&num[id]);
			//printf("num:%d\n",num[id]);
			for(int i=1;i<=num[id];i++){
				scanf("%lld%lld",&line[id][i].l,&line[id][i].r);
			//	printf("%d %d\n",line[id][i].l,line[id][i].r);
			}
		}
		else if(op[0]=='F'){
			order[n]=2;scanf("%lld%lld",&query[n].l,&query[n].r);
			req[req_cnt++]=query[n].l,req[req_cnt++]=query[n].r;
		}
		else{
			//puts("shit");
			order[n]=3;
			scanf("%d",&delet[n]);
			used[delet[n]]=false;
		}
	}
	tt=(maxid-1)/16+1;
	for(int i=1;i<=maxid;i++){
		for(int j=1;j<=num[i];j++){
			req[req_cnt++]=line[i][j].l,req[req_cnt++]=line[i][j].r;
		//	printf("%d %d\n",line[i][j].l,line[i][j].r);
		}
	}
	sort(req+1,req+req_cnt);
	//for(int i=1;i<req_cnt;i++) printf("%d\n",req[i]);
	req_cnt=unique(req+1,req+req_cnt)-req-1;
	//for(int i=1;i<=req_cnt;i++) printf("%d\n",req[i]);
	for(int i=1;i<=maxid;i++){
		for(int j=1;j<=num[i];j++){
			line[i][j].l=place(line[i][j].l);line[i][j].r=place(line[i][j].r);
			}
	}
	
	memset(same,false,sizeof(same));
	
	for(int i=1;i<=maxid;i++){
		if(used[i]){
			//printf("i:%d\n",i);
			for(int j=1;j<=num[i];j++){
				update(1,1,req_cnt,line[i][j].l,line[i][j].r,i);
				//printf("%d %d\n",line[i][j].l,line[i][j].r);
			}
		}
	}
	
	ans[0]=0;
	
	for(int i=n;i>=1;i--){
		if(order[i]==1){
			int id=bh[i];
			for(int j=1;j<=num[id];j++)
				Delete(1,1,req_cnt,(int)(line[id][j].l),(int)(line[id][j].r),id);
		}
		else if(order[i]==2){
			memset(have,0,sizeof(have));
			int pos1=place(query[i].l);_query(1,1,req_cnt,pos1);
			int pos2=place(query[i].r);ans[++ans[0]]=_query(1,1,req_cnt,pos2);
		}
		else{
			for(int j=1;j<=num[delet[i]];j++){
			update(1,1,req_cnt,line[delet[i]][j].l,line[delet[i]][j].r,delet[i]);
			//printf("%d %d\n",line[delet[i]][j].l,line[delet[i]][j].r);
			}
		}
	}
	
	for(int i=ans[0];i>=1;i--)
		if(ans[i]) puts("F");
			else puts("D");
	
	return 0;
}
