# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int a[20];
int main(){
	int tcase,num;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&num);
		for(int i=1;i<=10;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+11);
		printf("%d %d\n",num,a[8]);
	}
	return 0;
}
