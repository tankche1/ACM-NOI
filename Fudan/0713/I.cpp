# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

struct Node{
	char t;
	int size;
	bool rev;
	Node *ch[2];
	int cmp(int x){if(x==ch[0]->size+1) return -1;return x<=ch[0]->size?0:1;}
	
	Node(){}
	void maintain(){size=ch[0]->size+1+ch[1]->size;}
	void pushdown() {
		if(rev){
			swap(ch[0],ch[1]);
			ch[0]->rev^=1;ch[1]->rev^=1;
			rev=false;
		}
	}
	//Node(char t,int size,bool rev) {}
};
Node *null;
Node seq[maxlen];int seq_cnt=0;

Node *New(char t){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;o->t=t;o->rev=false;o->size=1;
	return o;
}

int main(){
	return 0;
}
