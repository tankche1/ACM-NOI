/*
其实不难啊 但当时没有想出来
当B想和A建立关系时，有对于所有满足d(A,C)<=d(A,B)的城市C，都有R(C)<=R(B). 
即对于所有R(C)>R(B) 有d(A,C)>d(A,B)
根据R值倒着枚举节点
lin[i]为R值大于当前R值的节点中到i的最小距离 dist[i]为当前节点到i的距离
当lin[i]>dist[i]时 x想和i建立关系
*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int main(){
	return 0;
}
