#include <bits/stdc++.h>

using namespace std;

int main(void)
{
	int T = 0;
	int TK = 0;
	scanf("%d",&T);
	while(T--)
	{
		printf("Case #%d: ",++TK);
		int N = 0;
		scanf("%d",&N);
		assert(N > 0 && N <= 100);

		bool okay = true;
		for(int i = 0;i < N;i++)
		{
			int x = 0;
			scanf("%d",&x);
			assert(x >= 1 && x <= 100000);
			if(x % 3) okay = false;
		}
		puts(okay ? "Yes" : "No");
	}
	return 0;
}
