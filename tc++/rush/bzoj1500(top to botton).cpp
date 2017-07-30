# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
struct Node{
	int x;
};
int main(){
	Node *a=new Node();
	delete(a);
	return 0;
}
