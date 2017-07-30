#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
#define N 800100
#define LL long long
#define LEN 400000
using namespace std;
const int base=434992819;
int T, len1, len2, len, f[N], size, fa[N], sum[N], son[N], sum_data[N],pow[N], New[N];
char s1[N], s2[N], s[N];
int Hash[N];

map<int, int> id;

int Ins(int l, int r, int ll, int rr)
{
    if (l > r) return 0;
    int temp = Hash[r] - ((l)? Hash[l - 1] : 0);
    temp = temp * pow[LEN - r];
    int x = id[temp];
    if (!x || !New[x])
    {
        if (!x)
        {
            id[temp] = ++size;
            x = size;
        }
        New[x] = 1;
        fa[x] = Ins(l + 1, r - 1, ll, rr);
        son[fa[x]]++;
    }
    if (l == ll && r == rr) sum[x]++;
    return x;
}

void Manacher()
{
    int p = 0, l = 0, j;
    f[0] = 1;
    for (int i = 1; i < len; i++)
    {
        if (i > l)
        {
            f[i] = 1;
            while (i - f[i] >= 0 && i + f[i] < len && s[i + f[i]] == s[i - f[i]]) f[i]++;
            l = i + f[i] - 1;
            p = i;
            Ins(i - f[i] + 1, i + f[i] - 1, i - f[i] + 1, i + f[i] - 1);
            continue;
        }
        j = p * 2 - i;
        f[i] = f[j];
        if (i + f[i] - 1 > l) f[i] = l + 1 - i;
        while (i - f[i] >= 0 && i + f[i] < len && s[i + f[i]] == s[i - f[i]]) f[i]++;
        if (i + f[i] - 1 > l)
        {
            l = i + f[i] - 1;
            p = i;
        }
        Ins(i - f[i] + 1, i + f[i] - 1, i - f[i] + 1, i + f[i] - 1);
    }
}

int que[N], lead, tail, In[N];

void BFS()
{
    lead = 1; tail = 0;
    memset(In, 0, sizeof In);
    for (int i = 1; i <= size; i++) if (!son[i])
    {
        que[++tail] = i;
        In[i] = 1;
    }
    while (lead <= tail)
    {
        int node = que[lead++];
        sum[fa[node]] += sum[node];
        son[fa[node]]--;
        if (!son[fa[node]]) que[++tail] = fa[node];
    }
}

void Solve()
{
/*    memset(New, 0, sizeof New);
    memset(fa, 0, sizeof fa);
    memset(sum, 0, sizeof sum);
    memset(son, 0, sizeof son); */
    len1 = strlen(s1);
    len2 = strlen(s2);
    len = len1 * 2 + 1;
    for (int i = 0; i < len; i++)
        if (i & 1) s[i] = s1[i >> 1];
        else s[i] = '#';
    Hash[0] = s[0];
    for (int i = 1; i < len; i++) Hash[i] = Hash[i - 1] + s[i]*pow[i];
    Manacher();
    BFS();
    int temp = size;
/*    memcpy(sum_data, sum, sizeof sum);
    memset(New, 0, sizeof New);
    memset(fa, 0, sizeof fa);
    memset(sum, 0, sizeof sum);
    memset(son, 0, sizeof son); */
    for (int i = 1; i <= size; i++)
    {
        sum_data[i] = sum[i];
        New[i] = 0;
        fa[i] = 0;
        sum[i] = 0;
        son[i] = 0;
    }
    len = len2 * 2 + 1;
    for (int i = 0; i < len; i++)
        if (i & 1) s[i] = s2[i >> 1];
        else s[i] = '#';
    Hash[0] = s[0];
    for (int i = 1; i < len; i++) Hash[i] = Hash[i - 1] + s[i]*pow[i];
    Manacher();
    BFS();
    LL ans = 0;
    int x = '#';
    x = x * pow[LEN];
    x = id[x];
    sum[x] = 0;
    for (int i = 1; i <= temp; i++) ans += (LL)sum[i] * sum_data[i];
    ans /= 2;
    cout << ans << endl;
    for (int i = 1; i <= size; i++)
    {
        New[i] = fa[i] = sum[i] = son[i] = 0;
    }
}

void II()
{
    scanf("%d", &T);
    for (int I = 1; I <= T; I++)
    {
        id.clear();
        size = 0;
        scanf("%s%s", s1, s2);
        printf("Case #%d: ", I);
        Solve();
    }
}

int main()
{
    pow[0]=1;
    for(int i=1;i<=N-100;i++) pow[i]=pow[i-1]*base;
    II();
    return 0;
}
