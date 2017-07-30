#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <string>
#include <map>
#include <cstdlib>
#include <cassert>
#include <vector>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;
const int INF = ~0U >> 1;
int globalTime = 0;
const int SEED = 133331;
const int MAX_LEN=10+1;

struct Node {
	int size;
	int score, time;
	char name[MAX_LEN];
	Node*ch[2], *p;
	Node() {
		size = 0;
	}
	void set(Node*c, bool d) {
		ch[d] = c;
		c->p = this;
	}
	bool dir() {
		return this == p->ch[1];
	}
	void update() {
		size = ch[0]->size + ch[1]->size + 1;
	}
} nullData, *null = &nullData;

Node*newNode(int score,const char name[]) {
	Node*t = new Node;
	t->ch[0] = t->ch[1] = null;
	t->size = 1;
	t->score = score;
	strcpy(t->name,name);
	return t;
}

void clear(Node*t) {
	t->ch[0] = t->ch[1] = null;
	t->size = 1;
}

int hashCode(const char name[]) {
	const char*it=name;
	int code=0;
	while(*it!='\0')
		code=code*SEED+*it++;
	return code;
}

map<int, Node*> nameToNode;

Node* getId(const char name[]) {
	int code = hashCode(name);
	if (nameToNode.count(code))
		return nameToNode[code];
	Node*t = newNode(-INF, name);
	return nameToNode[code] = t;
}

bool compare(Node*a, Node*b) {
	if (a->score != b->score)
		return a->score > b->score;
	return a->time < b->time;
}

struct Splay {
	Node*root;

	void rotate(Node*t) {
		Node*p = t->p;
		bool d = t->dir();
		p->p->set(t, p->dir());
		p->set(t->ch[!d], d);
		t->set(p, !d);
		p->update();
		if (root == p)
			root = t;
	}

	void splay(Node*t, Node*f = null) {
		while (t->p != f) {
			if (t->p->p == f)
				rotate(t);
			else
				(t->dir() == t->p->dir()) ? (rotate(t->p), rotate(t))
						: (rotate(t), rotate(t));
		}
		t->update();
	}

	Node*getKth(int kth) {
		for (Node*t = root;;) {
			int cnt = t->ch[0]->size;
			if (kth == cnt)
				return t;
			t = t->ch[kth > cnt];
			if (kth > cnt)
				kth -= cnt + 1;
		}
	}

	void insert(Node*ins) {
		clear(ins);
		for (Node*t = root;;) {
			bool dir = compare(t, ins);
			if (t->ch[dir] == null) {
				t->set(ins, dir);
				splay(ins);
				return;
			}
			t = t->ch[dir];
		}
	}

	Node*rightMost(Node*t) {
		while (t->ch[1] != null)
			t = t->ch[1];
		return t;
	}

	Node*leftMost(Node*t){
		while (t->ch[0] != null)
			t=t->ch[0];
		return t;
	}

	void erase(Node*t) {
		splay(t);
		Node*prev = rightMost(t->ch[0]);
		Node*next= leftMost(t->ch[1]);
		splay(prev);
		splay(next,prev);
		next->set(null,0);
		splay(next);
	}

	void write(Node*t) {
		if (t == null)
			return;
		write(t->ch[0]);
		//		assert(false);
		printf("%s ",t->name);
		write(t->ch[1]);
	}

	void write(int l, int r) {
		//		cout<<l<<" "<<r<<endl;
		Node*Left = getKth(l - 1);
		splay(Left);
		Node*Right = getKth(r + 1);
		splay(Right, Left);
		write(Right->ch[0]);
	}

	int rank(Node*t) {
		splay(t);
		return t->ch[0]->size;
	}

	Splay() {
		char name[MAX_LEN]="?";
		Node*begin = newNode(INF,name);
		root = begin;
		root->p = null;
		Node*end = newNode(-INF,name);
		begin->set(end, 1);
		splay(end);
	}

	int size() {
		return root->size - 2;
	}
};

void solve() {
	Splay*splay = new Splay;

	int nOpt;
	scanf("%d", &nOpt);
	char name[MAX_LEN];
	for (int step = 0; step < nOpt; ++step) {
		scanf(" ");
		char cmd;
		while(cmd=getchar(),cmd!='+' && cmd !='?');
		Node*t;
		//		cout<<splay->size()<<endl;
		//		cout << cmd << endl;
		switch (cmd) {
		case '+':
			scanf(" ");
			scanf("%s",name);
			//			cout << name << endl;
			int score;
			scanf("%d", &score);
			t = getId(name);
			if (t->score == -INF) {
				t->score = score;
				t->time = globalTime++;
				splay->insert(t);
			} else {
				splay->erase(t);
				t->score = score;
				t->time = globalTime++;
				splay->insert(t);
			}
			break;
		case '?':
			int index;
			char c;
			while(c=getchar(),c==' '||c=='\n');
			ungetc(c,stdin);
			if (isdigit(c)) {
				scanf("%d",&index);
				int l = index;
				int r = min(l + 9, splay->size());
				splay->write(l, r);
				printf("\n");
			} else {
				scanf("%s",name);
				t = getId(name);
				printf("%d\n", splay->rank(t));
			}
			break;
		default:
			break;
		}
	}
}

int main() {
//	freopen("input.txt","r",stdin);
//	runTest();
//	cout<<INF<<endl;
	solve();
}