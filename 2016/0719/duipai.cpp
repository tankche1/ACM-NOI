#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
#include <string>
using namespace std;

typedef long long LL;
const int maxn = 100000 + 100;
int n;

map<string,LL>mp;
int mp_tail=0;
vector<LL> g1[maxn];
vector<LL> g2[maxn];
const LL P[] = {435617, 999983, 327827, 674249, 986191}; //一共5个素数
const LL mod = 1e9+7;
string a1[maxn],a2[maxn];//车站下标，对应的车站名

LL powMod( LL a , LL b , LL p = mod )//a^b % p
{
    LL r = 1 ;
    a %= p ;
    while( b )
    {
        if( b&1 ) r = r*a%p ;
        b >>= 1 ;
        a = a*a%p ;
    }
    return r ;
}

LL get(char s[])	//判断这个字符串是否出现过，并根据情况添加进map,并返回这个字符串对应的数字
{
	string x="";
	for (int i = 0; s[i]!=0; x+=s[i++]);
	//cout<<"!!!"<<x<<endl;

	if (mp.find(x) == mp.end())
	{
		mp[x]= ++mp_tail;
	}else return mp[x];
	return mp_tail;
}

void init()
{
	for (int i = 0; i<= n; ++ i)
	{
		g1[i].clear();
		g2[i].clear();
	}
	mp.clear();
	mp_tail=0;
	char a[100],b[100];

	for (int i = 1; i < n; ++ i)
	{
		scanf("%s%s",a, b);
		LL A = get(a);
		a1[A]=a;
		LL B = get(b);
		a1[B]=b;
		g1[A].push_back(B);
		g1[B].push_back(A);
	}
	for (int i = 1; i < n; ++ i)
	{
		scanf("%s%s",&a, &b);
		LL A = get(a);
		a2[A]=a;
		LL B = get(b);
		a2[B]=b;
		g2[A].push_back(B);
		g2[B].push_back(A);
	}
}

LL dp(int now, vector<LL> g[], LL f[], int fa)	//求一棵树的重心的程序
{
	LL sum = 0;
	f[now] =0;
	if (g[now].size()==0)
	{
		return 1;
	}
	for (int i = 0; i != g[now].size(); ++ i)
	{
		int will = g[now][i];
		if (will == fa)	continue;
		LL tmp =dp(will, g, f, now);
		sum += tmp;
		f[now] = max(f[now], tmp);
	}
	if (now != fa)	f[now] = max(f[now], n - sum - 1);
	return sum + 1;
}

LL f1[maxn], f2[maxn];
LL f3[maxn];
vector<LL>zhong1;
vector<LL>zhong2;



struct node
{
	LL hash, id;
	node(){}
	node(LL _hash, LL _id)
	{
		hash = _hash;
		id = _id;
	}
};

bool operator < (node a, node b)
{
	return a.hash < b.hash;
}

vector<node> tmp[maxn];
vector<LL>g3[maxn], g4[maxn];

LL heav(int now, vector<LL> g[], LL f[], int fa, vector<LL> h[])
{
	if (g[now].size() == 1 && g[now][0] == fa)
		//这里有个程序陷阱。。。判断是否为叶子节点，并不是size=0，而是size=1，并且这个节点为父亲。
	{
		return f[now] = 1;
	}
	LL hash = 0;
	tmp[now].clear();
	for (int i = 0; i != g[now].size(); ++ i)
	{
		int will = g[now][i];
		if (will == fa)	continue;
		LL t = heav(will, g, f, now, h);	//得到儿子节点的hash值，保存进临时数组中，为了重新构图用。
		tmp[now].push_back(node(t,will));
	}
	sort(tmp[now].begin(), tmp[now].end());//根据儿子节点的哈希值排序

	for (int i = 0; i != tmp[now].size(); ++ i)//根据儿子节点的哈希值，计算自己节点的哈希值
	{
		h[now].push_back(tmp[now][i].id);
		hash += powMod(P[i%5], i + 1, mod) * tmp[now][i].hash;
		hash %= mod;
	}
	f[now] = hash;
	return f[now];
}

void pg(int a, int b)	//第一棵树在a节点，第二课树在b节点，这2个节点彼此对应，同时遍历两棵树，输出他们。
{
	printf("%s %s\n", a1[a].c_str(), a2[b].c_str());
	//这里a1,a2保存的是编号对应的字符。 题目给的是a,b,c之类的字符串，然后字符串被化为了数字，这里要重新输出字符串
	for (int i = 0; i != g3[a].size(); ++ i)
	{
		int will1 = g3[a][i];
		int will2 = g4[b][i];
		pg(will1, will2);
	}
}


bool check(int a, int b)
{
	//cout<<a<<" "<<b<<endl;
	for (int i = 0; i <=n;++i)
	{
		g3[i].clear();
		g4[i].clear();
	}
	heav(a, g1, f1, 0, g3);
	//去计算第一棵树，以a为根，g1保存的第一棵树的边的情况，f1是返回每个节点的哈希值。 0表示父亲，为了遍历树避免访问到父亲。 g3为返回一棵有根树。
	heav(b, g2, f2, 0, g4);
	//计算第二颗数的信息

	if (f1[a] == f2[b]) //判断两棵树的根节点的哈希值是否相同
	{
		pg(a,b); //相同，则输出答案
		return 1;
	}
	return 0;
}

void doit()
{
	dp(1, g1, f1, 1);
	dp(1, g2, f2, 1);

	zhong1.clear();
	zhong2.clear();
	memmove(f3,f1,sizeof(f3));
	sort(f3+1,f3+1+n);
	int tmp = f3[1];
	for (int i = 1; i <= n; ++ i)
	{
		if (f1[i]==tmp)	zhong1.push_back(i);
		if (f2[i]==tmp) zhong2.push_back(i);
	}

	for (int i = 0; i != zhong1.size(); ++ i)
		for (int j = 0; j != zhong2.size(); ++ j)
		{
			if (check(zhong1[i], zhong2[j]))	return;
		}
}

int main()
{
    //freopen("input.txt","r",stdin);
	while (~scanf("%d", &n))
	{
		init();
		doit();
	}
	return 0;
}
