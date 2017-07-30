# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int size=19021;
const int INF=~0U>>1;
const int seed=131;
const int maxn=10010;
typedef unsigned long long ull;

struct Hash{
	
	struct node{
		ull key;
		int num;
		node *next;
		node(ull _key,int _num,node * _n):key(_key),num(_num),next(_n) {}
	}*H[size];
	Hash() {memset(H,0,sizeof(H));}
	int find(ull code){
		int h=code%size;
		for(node *i=H[h];i;i=i->next) if(i->key==code) return i->num;
		return -1;
	}
	
	void insert(ull code,int num){
		int h=code%size;
		H[h]=new node(code,num,H[h]);
	}
}hash;
ull Code(char *s){
	ull res=0;
	while(*s) res*=seed,res+=*s++;
	return res;
}

int n,m;
char s[30],ns[30];
bool used[maxn];
ull Left[30],Right[30];
ull power[30];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		hash.insert(Code(s),i);
		//printf("%d\n",hash.find(Code(s)));
		//printf("%llu\n",Code(s));
	}
	power[0]=1;
	for(int i=1;i<=25;i++) {power[i]=power[i-1]*seed;}//printf("%llu\n",power[i]);}
	for(int _l=1;_l<=m;_l++){
		memset(used,0,sizeof(used));
		scanf("%s",s);int len=strlen(s),ans=0;
		if(hash.find(Code(s))!=-1) {printf("-1\n");continue;}
		//Replace
		ull T=Code(s);int tmp;
		//printf("T:%llu\n",T);
		for(int j=1;j<=len;j++){
			for(char c='a';c<='z';c++){
				if((tmp=hash.find(T+(c-s[j-1])*power[len-j]))!=-1){
					//puts("fuck");
					if(!used[tmp]) ans++,used[tmp]=1;
				}
				//if(_l==3&&c=='e') printf("%llu %llu %d\n",T+(c-s[j-1])*power[len-j],T,tmp);
			}
		}
		
		Left[0]=0;Right[len+1]=0;
		for(int i=1;i<=len;i++)
			Left[i]=Left[i-1]*seed+s[i-1];
		for(int i=len;i>=1;i--)
			Right[i]=Right[i+1]+s[i-1]*power[len-i];
		
		//Delete
		for(int i=1;i<=len;i++){
			if((tmp=hash.find(ull(Right[i+1]+Left[i-1]*power[len-i])))!=-1){
					if(!used[tmp]) ans++,used[tmp]=1;
				}
		}
		//Insert
		for(int i=1;i<=len+1;i++){
			for(char c='a';c<='z';c++){
			if((tmp=hash.find(ull((Left[i-1]*seed+c)*power[len-i+1]+Right[i])))!=-1){
					if(!used[tmp]) ans++,used[tmp]=1;
				}
				//if(_l==2&&i==1&&c=='a')
				//	printf("T:%llu %llu\n",T,ull((Left[i-1]*seed+c)*power[len-i+1]+Right[i]));
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
