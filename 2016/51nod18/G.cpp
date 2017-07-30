/*#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<map>
#include<set>*/

#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define per(i,a,b) for (int i=(b);i>=(a);i--)
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)x.size())
typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;
//head

const int maxn = 305555;
int n;
void read(ll &x){
    int ch;
    while (!isdigit(ch = getchar()));
    x = ch - '0';
    while (isdigit(ch = getchar()))
        x = x * 10 + ch - '0';
}

struct node{
	node *c[2],*f;
	int dat,siz,sum;
}SC[maxn * 4], *root, *null;
int tot=-1;

node* New(int d, node *fa){
	node *e=&SC[++tot];
	e->siz = 1;
	e->f = fa;
	e->dat = d;
	e->sum = d;
	e->c[0] = e->c[1] = null;
	return e;
}

void Update(node *v){
	if (v==null) return;
	v->siz = v->c[0]->siz + v->c[1]->siz + 1;
	v->sum = v->c[0]->sum + v->c[1]->sum + v->dat;
}

void Rotate(node *x,int o){
	node *y=x->f;
	y->c[o]=x->c[!o];
	x->c[!o]->f=y;
	x->c[!o]=y;
	x->f=y->f;y->f=x;
	if (x->f->c[0]==y) x->f->c[0]=x;
	else x->f->c[1]=x;
	if (root==y) root=x;
	Update(y);
}

void Splay(node *x,node *fa){
	while (x->f!=fa){
		if (x->f->f==fa)
			if (x->f->c[0]==x)
				Rotate(x,0);
			else
				Rotate(x,1);
		else
			if (x->f->f->c[0]==x->f)
				if (x->f->c[0]==x)
					Rotate(x->f,0),Rotate(x,0);
				else
					Rotate(x,1),Rotate(x,0);
			else
				if (x->f->c[1]==x)
					Rotate(x->f,1),Rotate(x,1);
				else
					Rotate(x,0),Rotate(x,1);
	}
	Update(x);
}

void Select(int k,node *fa){ // Splay kth node
	node *t=root;
	while (1){
		if (t->c[0]->siz + 1 == k) break;
		if (t->c[0]->siz >= k) t = t->c[0];
		else k -= t->c[0]->siz + 1, t = t->c[1];
	}
	Splay(t,fa);
}


void Insert(int x, int d){ // Add a node behind x (x + 1)
	Select(x + 1, null); Select(x + 2, root);
	root->c[1]->c[0] = New(d, root->c[1]);
	Splay(root->c[1]->c[0], null);
}
int Erase(int x){// Erase xth node
    Select(x, null); Select(x + 2, root);
    int ret = root->c[1]->c[0]->dat;
    root->c[1]->c[0] = null;
    Update(root->c[1]);
    Update(root);
    return ret;
}


void Prepare(){
	null = New(0, NULL);
	null->siz = 0;
	root = New(0, null);
	root->c[1] = New(0, root);
	Update(root);
}

void Query(int l, int r){
    if (Erase(r) != 1){
        if (root->c[1]->sum != 0){
            node *p = root->c[1];
            while (1){
                if (p->dat == 1 && p->c[0]->sum == 0){
                    p->dat = 0;
                    Splay(p, root);
                    break;
                }
                if (p->c[0]->sum != 0) p = p->c[0];
                else p = p->c[1];
            }
        }
    }
    Insert(l - 1, 1);
}

ll l[maxn], r[maxn];
void Solve(){
    Prepare();
    node *t = root->c[1];
    rep(i, 0, n){
        t->c[0] = New(0, t);
        t = t->c[0];
    }
    Splay(t, null);
    rep(i, 1, n){
        Query(l[i], r[i]);
    }
    cout<<root->sum<<endl;
}


int main(){
    cin>>n;
    rep(i, 1, n){
        read(l[i]);
        read(r[i]);
        l[i]++;
        r[i]++;
    }

    Solve();
    return 0;
}
