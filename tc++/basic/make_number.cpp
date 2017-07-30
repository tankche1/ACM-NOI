# include<stdio.h>
# include<string.h>
# include<time.h>
# include<algorithm>
using namespace std;
int size[2]={-1,1};
int get(){
	return (rand()%21)*size[rand()%2];
}
int main(){
	srand(time(NULL));
	int tcase=rand()%1+1;
	printf("%d\n",tcase);
	while(tcase--){
		int x1,y1,z1,x2,y2,z2;
		for(int i=1;i<=2;i++){
			x1=get();x2=get();y1=get();y2=get();z1=get();z2=get();
			printf("%d %d %d %d %d %d\n",x1,y1,z1,x2,y2,z2);
		}
	}
	return 0;
}

