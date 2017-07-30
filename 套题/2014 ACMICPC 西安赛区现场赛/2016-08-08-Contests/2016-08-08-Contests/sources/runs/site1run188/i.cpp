#include <cstdio>
#include <cstring>
#define  son(x,w) tr[x].son[w]
#define  is_leaf(x) tr[x].is_leaf
#define  fr(i,x,y) for(i=x;i<=y;i++)
#define  frd(i,x,y) for(i=x;i>=y;i--)
const int maxn=30010;
struct Node{int son[2];bool is_leaf;}tr[maxn*65];
int T,n,cnt;
int arr[40];
int ans0,ans[35*maxn][6];
int root=1;
int Get(int &x)
{
	if(!x)
	{
		cnt++;
		son(cnt,0)=son(cnt,1)=0;
		is_leaf(cnt)=false;
		x=cnt;
	}
	return x;
}
void Read()
{
	int i,j,a,b,c,d,l,x,y;
	scanf("%d",&n);
	root=cnt=1;
	tr[root].son[0]=tr[root].son[1]=0;
	tr[root].is_leaf=false;
	fr(i,1,n)
	{
		scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&l);
		arr[0]=0;
		frd(j,8,1)arr[++arr[0]]=a>>(j-1)&1;
		frd(j,8,1)arr[++arr[0]]=b>>(j-1)&1;
		frd(j,8,1)arr[++arr[0]]=c>>(j-1)&1;
		frd(j,8,1)arr[++arr[0]]=d>>(j-1)&1;
		x=root;
		fr(j,1,l)
		{
			y=arr[j];
			x=Get(son(x,y));
		}
		fr(i,l+1,arr[0])
		{
			y=arr[i];
			if(y==0)is_leaf(Get(son(x,1)))=true;
			x=Get(son(x,y));
		}
		is_leaf(x)=true;
	}
}
void Update()
{
	int i,x;
	ans0++;
	ans[ans0][0]=0;
	x=0;
	fr(i,1,arr[0])
	{
		x=(x<<1)+arr[i];
		if(i%8==0)
		{
			ans[ans0][++ans[ans0][0]]=x;
			x=0;
		}
	}
	if(x)
	{
		fr(i,1,8-arr[0]%8)x<<=1;
		ans[ans0][++ans[ans0][0]]=x;
	}
	while(ans[ans0][0]<4)ans[ans0][++ans[ans0][0]]=0;
	ans[ans0][++ans[ans0][0]]=arr[0];
}
void Dfs(int x)
{
	if(is_leaf(x))return;
	
	arr[++arr[0]]=0;
	if(!son(x,0))Update();
	else Dfs(son(x,0));
	arr[0]--;
	
	arr[++arr[0]]=1;
	if(!son(x,1))Update();
	else Dfs(son(x,1));
	arr[0]--;
}
void Solve()
{
	int i;
	if(son(root,0)==0&&son(root,1)==0)
	{
		printf("1\n0.0.0.0/0\n");
		return;
	}
	arr[0]=0;
	ans0=0;
	Dfs(root);
	printf("%d\n",ans0);
	fr(i,1,ans0)printf("%d.%d.%d.%d/%d\n",ans[i][1],ans[i][2],ans[i][3],ans[i][4],ans[i][5]);
}
int main()
{
	//freopen("i.in","r",stdin);
	//freopen("i.out","w",stdout);
	int t;
	scanf("%d",&T);
	fr(t,1,T)
	{
		printf("Case #%d:\n",t);
		Read();
		Solve();
	}
}
