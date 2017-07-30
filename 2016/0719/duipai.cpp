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
const LL P[] = {435617, 999983, 327827, 674249, 986191}; //һ��5������
const LL mod = 1e9+7;
string a1[maxn],a2[maxn];//��վ�±꣬��Ӧ�ĳ�վ��

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

LL get(char s[])	//�ж�����ַ����Ƿ���ֹ��������������ӽ�map,����������ַ�����Ӧ������
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

LL dp(int now, vector<LL> g[], LL f[], int fa)	//��һ���������ĵĳ���
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
		//�����и��������塣�����ж��Ƿ�ΪҶ�ӽڵ㣬������size=0������size=1����������ڵ�Ϊ���ס�
	{
		return f[now] = 1;
	}
	LL hash = 0;
	tmp[now].clear();
	for (int i = 0; i != g[now].size(); ++ i)
	{
		int will = g[now][i];
		if (will == fa)	continue;
		LL t = heav(will, g, f, now, h);	//�õ����ӽڵ��hashֵ���������ʱ�����У�Ϊ�����¹�ͼ�á�
		tmp[now].push_back(node(t,will));
	}
	sort(tmp[now].begin(), tmp[now].end());//���ݶ��ӽڵ�Ĺ�ϣֵ����

	for (int i = 0; i != tmp[now].size(); ++ i)//���ݶ��ӽڵ�Ĺ�ϣֵ�������Լ��ڵ�Ĺ�ϣֵ
	{
		h[now].push_back(tmp[now][i].id);
		hash += powMod(P[i%5], i + 1, mod) * tmp[now][i].hash;
		hash %= mod;
	}
	f[now] = hash;
	return f[now];
}

void pg(int a, int b)	//��һ������a�ڵ㣬�ڶ�������b�ڵ㣬��2���ڵ�˴˶�Ӧ��ͬʱ������������������ǡ�
{
	printf("%s %s\n", a1[a].c_str(), a2[b].c_str());
	//����a1,a2������Ǳ�Ŷ�Ӧ���ַ��� ��Ŀ������a,b,c֮����ַ�����Ȼ���ַ�������Ϊ�����֣�����Ҫ��������ַ���
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
	//ȥ�����һ��������aΪ����g1����ĵ�һ�����ıߵ������f1�Ƿ���ÿ���ڵ�Ĺ�ϣֵ�� 0��ʾ���ף�Ϊ�˱�����������ʵ����ס� g3Ϊ����һ���и�����
	heav(b, g2, f2, 0, g4);
	//����ڶ���������Ϣ

	if (f1[a] == f2[b]) //�ж��������ĸ��ڵ�Ĺ�ϣֵ�Ƿ���ͬ
	{
		pg(a,b); //��ͬ���������
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
