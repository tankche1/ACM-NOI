#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

struct TNODE
{
	int cnt;
	bool routed;
	TNODE* child[2];
};

TNODE TPool[2333333];
TNODE* TPTop = TPool;

TNODE* Root = NULL;

vector<string> answers;
int insertty(uint ip, int mask)
{
	TNODE* now = Root;
	now->cnt++;
	for(int i = 31;i >= 32-mask;i--)
	{
		int bit = (ip >> i) & 1;
		if(!now->child[bit])
		{
			now->child[bit] = TPTop++;
			memset(now->child[bit],0,sizeof(TNODE));
		}
		now = now->child[bit];
		now->cnt++;
	}
	now->routed = true;
	return 0;
}

int dfs(TNODE* cur, uint ip=0, int mask=0)
{
	if(!cur)
	{
		int a,b,c,d;
		a = ip >> 24;
		b = (ip >> 16) & 0xFF;
		c = (ip >> 8) & 0xFF;
		d = (ip) & 0xFF;
		char result[64] = {0};
		sprintf(result,"%d.%d.%d.%d/%d",a,b,c,d,mask);
		answers.push_back(string(result));
		return 0;
	}
	if(cur->routed || mask == 32) return 0;
	for(int i = 0;i < 2;i++)
	{
		dfs(cur->child[i],ip | ((uint)i << (31-mask)),mask+1);
	}
	return 0;
}

int main(void)
{
	int T = 0;
	int TK = 0;
	scanf("%d",&T);
	while(T--)
	{
		printf("Case #%d:\n",++TK);
		int N = 0;
		scanf("%d",&N);
		
		if(N == 0)
		{
			puts("1");
			puts("0.0.0.0/0");
			continue;
		}

		TPTop = TPool;
		Root = TPTop++;
		memset(Root,0,sizeof(TNODE));
		for(int i = 0;i < N;i++)
		{
			int a,b,c,d;
			int mask = 0;
			scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&mask);
			assert(0 <= a && a < 256 && 0 <= b && b < 256 && 0 <= c && c < 256 && 0 <= d && d < 256);
			assert(0 <= mask && mask <= 32);
			uint ip = (uint)a << 24 | b << 16 | c << 8 | d;
			for(int i = 0;i < 32-mask;i++) assert(!(ip & (1u << i)));
			insertty(ip,mask);
		}
		answers.clear();
		dfs(Root);
		printf("%d\n",answers.size());
		for(int i = 0;i < answers.size();i++) puts(answers[i].c_str());
	}
	return 0;
}
