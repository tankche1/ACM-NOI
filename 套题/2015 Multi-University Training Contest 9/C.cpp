# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;


struct Node{
	Node *ch[2],*f,*p;
	int v,_min,bh;
	bool rev;
	Node() {}
};
Node *null;
Node seq[maxn];int seq_cnt=0;
bool ok=true;

Node *New(int bh,int val){
	Node *o=&seq[seq_cnt++];
	o->v=o->_min=val;o->bh=bh;
	o->ch[0]=o->ch[1]=o->f=null;
	o->p=o;o->rev=false;
	return o;
}

void maintain(Node *o){
	o->p=o;o->_min=o->v;
	if(o->ch[0]->_min<o->_min) o->_min=o->ch[0]->_min,o->p=o->ch[0]->p;
	if(o->ch[1]->_min<o->_min) o->_min=o->ch[1]->_min,o->p=o->ch[1]->p;
}

void pushdown(Node *o){
	if(o->rev){
		swap(o->ch[0],o->ch[1]);
		o->ch[0]->rev^=1;o->ch[1]->rev^=1;
		o->rev=false;
	}
}

struct LCT{
	Node *tree[maxn];

	bool havef(Node *o){
		return (o->f!=null)&&(o->f->ch[0]==o||o->f->ch[1]==o);
	}

	void Rotate(Node *p){
		int d=p->f->ch[1]==p?0:1;
		Node *o=p->f;
		o->ch[!d]=p->ch[d];p->ch[d]->f=o;
		if(havef(o)) o->f->ch[o->f->ch[1]==o]=p;
		p->ch[d]=o;
		p->f=o->f;
		o->f=p;
		maintain(o);maintain(p);
	}

	void splay(Node *o){
		Node *p;
		while(havef(o)){
			p=o->f;
			if(havef(p)){
				pushdown(p->f);
				pushdown(p);
				pushdown(o);
				p=p->f;
				int d=p->ch[1]==o->f;
				int dd=o->f->ch[1]==o;
				if(d==dd)
					Rotate(p->ch[d]),Rotate(o);
				else Rotate(o),Rotate(o);
			}
			else pushdown(p),pushdown(o),Rotate(o);
		}
	}

	void Access(Node *x){
		Node *y=null;
		while(x!=null){
			splay(x);
			pushdown(x);
			x->ch[1]=y;
			maintain(x);
			y=x;
			x=x->f;
		}
	}

	/*void print(Node *x){
		pushdown(x);
		if(x->ch[0]!=null&&x->ch[0]->f==x) print(x->ch[0]);
		if(x->ch[1]!=null&&x->ch[1]->f==x) print(x->ch[1]);
	}*/

	void makeroot(Node *x){
		Access(x);
		splay(x);
		x->rev^=1;
	}

	void Link(Node *x,Node *y){
	   // if(ok) printf("Link: %d %d \n",x->v,y->v);
		makeroot(x);
		x->f=y;
		Access(x);
	}

	void Cut(Node *x,Node *y){
	    //if(ok) printf("CUT %d %d\n",x->v,y->v);
		Access(x);
		splay(y);
		if(y->f==x){
			y->f=null;
		}
		else {
			Access(y);
			splay(x);
			if(x->f==y){
				x->f=null;
			}
		}
	}

	Node* query(Node *x,Node *y){
		makeroot(x);
		Access(y);
		splay(y);
		return y->p;
	}

	Node *getroot(Node *x){
		Access(x);splay(x);
		while(x->ch[0]!=null) x=x->ch[0];
		return x;
	}

};
LCT lct;

vector<int> G[maxn];
LL ans[maxn];
int tcase;
const int N=100000;

void prepare(){
    Node *p,*t;
    int v;
    for(int i=2;i<=100000;i++){
        for(int j=i;j<=100000;j+=i)
            G[j].push_back(i);
    }

    for(int i=1;i<=N;i++)
        lct.tree[i]=New(i,i);

    LL tmp=0;
    ans[1]=0;
    for(int i=2;i<=100000;i++){
        lct.Link(lct.tree[i],lct.tree[1]);tmp++;
        for(int e=0;e<(int)G[i].size();e++){
            v=G[i][e];
            p=lct.query(lct.tree[i],lct.tree[v]);
            if(p->v<v){
                tmp=tmp-p->v+v;
                /*lct.Access(p);
                if(p->ch[0]!=null){
                    t=p->ch[0];while(t->ch[1]!=null) t=t->ch[1];
                    lct.Cut(t,p);
                }
                else if(p->ch[1]!=null){
                    t=p->ch[1];while(t->ch[0]!=null) t=t->ch[0];
                    lct.Cut(p->ch[1],p);
                }
                lct.Link(lct.tree[v],lct.tree[i]);*/
                lct.splay(p);
                if(p->ch[0]!=null) p->ch[0]->f=null,p->ch[0]=null;
                else p->ch[1]->f=null,p->ch[1]=null;
                lct.Link(lct.tree[v],lct.tree[i]);
            }
            else continue;
        }
        ans[i]=tmp;
        //if(ok) printf("ans[%d]:%I64d\n",i,ans[i]);
        //if(i==12) ok=false;
    }
}



int main(){
    int x;
	null=new Node();null->v=null->_min=maxn;null->ch[1]=null->ch[0]=null->f=null->p=NULL;null->bh=999;
	prepare();
	while(scanf("%d",&x)!=EOF){
        printf("%I64d\n",ans[x]);
	}

	return 0;
}

