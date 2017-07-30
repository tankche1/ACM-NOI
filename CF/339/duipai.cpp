//By--wintermelon
//#pragma comment(linker, "/STACK:102400000,102400000")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 1e5 + 10;
const ll inf = 1e12;
int n;
ll A, cf, cm, m;
struct xxx
{
	ll v;
	int id;
	bool operator < (const xxx &r)const
	{
		return v < r.v;
	}
} a[maxn];
ll psum[maxn];
ll res[maxn];
int bi(int en, ll x)
{
    int l = 1, r = en;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if(x >= psum[mid])
        {
            l = mid;
        }
        else
        {
            r = mid - 1;
        }
        if(l == r)
        {
            return l;
        }
        if(l + 1 == r)
        {
            if(x >= psum[r])
            {
                return r;
            }
            return l;
        }
    }
}
int main()
{
	while (~scanf("%d%I64d%I64d%I64d%I64d", &n, &A, &cf, &cm, &m))
	{
		for (int i = 1; i <= n; i++)
		{
			scanf("%I64d", &a[i].v);
			a[i].id = i;
		}
		sort(a + 1, a + n + 1);
        psum[0] = 0;
        ll sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += a[i].v;
            psum[i] = i * a[i].v - sum;
        }
        sum = 0;
        ll ans = -1;
        int anspos1, anspos2, anspos1val;
        a[n + 1].v = inf;
        if(m)
        for (int i = n; i >= 1; i--)
        {
            ll tail = A * (n - i) - sum;
            if (m >= tail)
            {
                ll pleft = m - tail;
                if(pleft)
                {
                    int pos = bi(i, pleft);
                    pleft -= psum[pos];
                    ll mi = a[pos].v;
                    ll cntmx = n - i;
                    if(pleft)
                    {
                        mi += pleft / pos;
                        if(mi > A)
                        {
                            mi = A;
                        }
                    }
                    ll Res = cntmx * cf + mi * cm;
                    if(Res > ans)
                    {
                        ans =Res;
                        anspos1 = pos;
                        anspos1val = mi;
                        anspos2 = i;
                    }
                }
            }
            else
            {
                continue;
            }
            sum += a[i].v;
        }
        if(m - (n * A - sum) >= 0)
        {
            ans = n * cf + A * cm;
            printf("%I64d\n", ans);
            for (int i = 1; i <= n; i++)
            {
                printf("%I64d ", A);
            }
            printf("\n");
            continue;
        }
        if(ans == -1)
        {
            int cnt = 0;
            ll _mi = inf;
            for(int i = 1; i <= n; i++)
            {
                res[a[i].id] = a[i].v;
                if(a[i].v == A)
                {
                    cnt++;
                }
                _mi = min(_mi, a[i].v);
            }
            printf("%I64d\n", cnt * cf + _mi * cm);
            for (int i = 1; i <= n; i++)
            {
                printf("%I64d ",res[i]);
            }
            printf("\n");
            continue;
        }
        printf("%I64d\n", ans);
        for (int i = 1; i <= anspos1; i++)
        {
            res[a[i].id] = anspos1val;
        }
        for (int i = anspos1 + 1; i <= anspos2; i++)
        {
            res[a[i].id] = a[i].v;
        }
        for (int i = anspos2 + 1; i <= n; i++)
        {
            res[a[i].id] = A;
        }
        for (int i = 1; i <= n; i++)
        {
            printf("%I64d ",res[i]);
        }
        printf("\n");
	}
	return 0;
}
