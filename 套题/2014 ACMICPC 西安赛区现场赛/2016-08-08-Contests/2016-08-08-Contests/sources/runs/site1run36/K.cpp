#include<bits/stdc++.h>
using namespace std;
#define LL long long

int main()
{
	int ca;
	cin>>ca;
	for(int t=1;t<=ca;t++)
	{
		LL A,B,Ans=1;
		cin>>A>>B;
		if(A<B)swap(A,B);
		if((A==0 || B==0) && A!=B)Ans++;
		while(A && B)
		{
			Ans+=A/B;
			A%=B;
			swap(A,B);
		}
		printf("Case #%d: ",t);
		cout<<Ans<<endl;
	}
	return 0;
}
