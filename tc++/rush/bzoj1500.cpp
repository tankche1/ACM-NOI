# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int MAXN=500010,MAXL=500010,INF=1001;
bool vis[MAXL];
char Ctrl[20];

struct Node{
	Node *ch[2],*fa;
	int value,size,sum,maxsum,mls,mrs,bh;
	bool rev,same;
	
	void update(){
		size=ch[0]->size+ch[1]->size+1;
		sum=ch[0]->sum+ch[1]->sum+value;
		maxsum=max(max(ch[0]->maxsum,ch[1]->maxsum),value+ch[0]->mrs+ch[1]->mls);
		mls=max(ch[0]->mls,ch[0]->sum+value+ch[1]->mls);
		mrs=max(ch[1]->mrs,ch[1]->sum+value+ch[0]->mrs);
	}
	
	void pushdown(){
		//Node *p=ch[0]->fa;
		if(rev){
			if(ch[0]->size!=0)
			ch[0]->rev=!ch[0]->rev;
			if(ch[1]->size!=0)
			ch[1]->rev=!ch[1]->rev;
			if(ch[0]->size!=0){
			Node *o=ch[0];
			swap(o->ch[0],o->ch[1]);
			o->update();}
			if(ch[1]->size!=0){
			Node *o=ch[1];
			swap(o->ch[0],o->ch[1]);
			o->update();}
			rev=!rev;
		}
		if(same){
			same=0;
			ch[0]->same=1;
			ch[1]->same=1;
			ch[0]->value=ch[1]->value=value;
			ch[0]->sum=ch[0]->maxsum=ch[0]->mls=ch[0]->mrs=max(0,ch[0]->size*value);
			ch[1]->sum=ch[1]->maxsum=ch[1]->mls=ch[1]->mrs=max(0,ch[1]->size*value);
		}
	}
	
};
Node seq[MAXN];
int seq_cnt=0;
int C[MAXL];
Node *null;

void add(int &x){
	x++;if(x==MAXL) x=0;
}

Node *New(int x){
	while(vis[seq_cnt]) add(seq_cnt);
	Node *o=&seq[seq_cnt];vis[seq_cnt]=true;o->bh=seq_cnt;add(seq_cnt);
	o->value=o->sum=x;o->mls=o->mrs=o->maxsum=max(x,0);
	o->ch[0]=o->ch[1]=null;o->fa=null;o->size=1;
	
	return o;
}

Node *build(int left,int right){
	int mid=(left+right)>>1;
	Node *o=New(C[mid]);
	if(mid>left)
	{o->ch[0]=build(left,mid-1);o->ch[0]->fa=o;}
	if(right>mid) {o->ch[1]=build(mid+1,right);o->ch[1]->fa=o;}
	o->update();
	return o;
}

struct SplayTree{
	Node *root;
	
	void rotate(Node *x,int o){
		Node *y=x->fa;
		//y->pushdown();
		x->pushdown();
		y->ch[o]=x->ch[!o];
		y->ch[o]->fa=y;
		x->fa=y->fa;
		if(x->fa->ch[0]==y) x->fa->ch[0]=x;
			else x->fa->ch[1]=x;
		x->ch[!o]=y;
		y->fa=x;
		y->update();
		x->update();
		if(y==root) {root=x;}
	}
	
	void splay(Node *x,Node *y){
		while(x->fa!=y){
			if(x->fa->fa==y){
				x->fa->pushdown();
				int d=x->fa->ch[0]==x?0:1;
				rotate(x,d);
			}
			else{
				x->fa->fa->pushdown();
				x->fa->pushdown();
				int dd=x->fa->fa->ch[0]==x->fa?0:1;
				int d=x->fa->ch[0]==x?0:1;
				if(d==dd){
					rotate(x->fa,dd);
					rotate(x,d);
				}
				else{
					//puts("fuck");
					rotate(x,d);
					//if(Ctrl[0]=='M') {print(root);puts("");}
					//if(x->fa==root) puts("shit");
					//if(x->fa->ch[dd]==x) puts("shitt");
					rotate(x,dd);
					//if(Ctrl[0]=='M') {print(root);puts("");}
				}
			}
		}
	}
	
	void select(int k,Node *y){
		Node *x=root;
		while(1){
			x->pushdown();
			//printf("%d lsize:%d k:%d\n",x->value,x->ch[0]->size,k);
			if(k==x->ch[0]->size+1) break;
			if(k<=x->ch[0]->size) {x=x->ch[0];}
			else {k=k-x->ch[0]->size-1;x=x->ch[1];}
		}
		//print(x);
		splay(x,y);
	}
	
	void Insert(int pos,int tot){
		Node *o=build(1,tot);
	//	print(o);puts("");
		select(pos+1,null);//puts("b");
		select(pos+2,root);//puts("c");
		root->ch[1]->ch[0]=o;
		o->fa=root->ch[1];
		o->fa->update();o->fa->fa->update();
		//print(root);puts("");
		splay(o,null);
		//print(root);puts("");
	}
	
	void erase(Node *o){
		if(o->ch[0]!=null) erase(o->ch[0]);
		vis[o->bh]=false;
		if(o->ch[1]!=null) erase(o->ch[1]);
	}
	
	void Delete(int pos,int tot){
		select(pos,null);
		select(pos+tot+1,root);
		Node *o=root->ch[1]->ch[0];
		erase(o);
		root->ch[1]->ch[0]=null;
		splay(root->ch[1],null);
	}
	
	void MakeSame(int pos,int tot,int value){
		select(pos,null);
		select(pos+tot+1,root);
		Node *o=root->ch[1]->ch[0];
		o->value=value;o->sum=o->size*value;o->maxsum=o->mls=o->mrs=max(0,o->sum);
		o->same=1;
		o->fa->update();
		o->fa->fa->update();
		//print(root);puts("");
		splay(o,null);
	}
	
	void Reverse(int pos,int tot){
		select(pos,null);
		select(pos+tot+1,root);
		Node *o=root->ch[1]->ch[0];
		//print(o);puts("");
		swap(o->ch[0],o->ch[1]);
		o->update();//print(o);puts("");
		o->rev=!o->rev;
		o->fa->update();
		o->fa->fa->update();
		//print(o);puts("");
		splay(o,null);
		//print(root);puts("");
	}
	
	int GetSum(int pos,int tot){
		select(pos,null);//puts("?");
	//	printf("%d\n",root->size);
		select(pos+tot+1,root);//puts("?");
		int ans=root->ch[1]->ch[0]->sum;
		splay(root->ch[1]->ch[0],null);
		return ans;
	}
	
	int MaxSum(){
		return root->maxsum;
	}
	
	void init(){
		null=New(0);null->size=0;
		root=New(0);
		root->ch[1]=New(0);
		root->ch[1]->fa=root;
		root->update();
	}
	
	void print(Node *o){
		o->pushdown();
		if(o->ch[0]!=null) print(o->ch[0]);
			printf("v:%d size:%d sum:%d maxsum:%d mls:%d mrs:%d \n",o->value,o->size,o->sum,o->maxsum,o->mls,o->mrs);
		if(o->ch[1]!=null) print(o->ch[1]);
	}
}Splay;
int N,M,pos,i,j,A;
int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
    Splay.init();
    scanf("%d%d",&N,&M);
    for (i=1;i<=N;i++)
        scanf("%d",&C[i]);
    Splay.Insert(0,N);
	
    for (i=1;i<=M;i++)
    {
		//Splay.print(Splay.root);
        scanf("%s",Ctrl);
        switch (Ctrl[0])
        {
            case 'I':
                scanf("%d%d",&pos,&N);
                for (j=1;j<=N;j++)
                    scanf("%d",&C[j]);
                Splay.Insert(pos,N);
                break;
            case 'D':
                scanf("%d%d",&pos,&N);
                Splay.Delete(pos,N);
                break;
            case 'R':
                scanf("%d%d",&pos,&N);
                Splay.Reverse(pos,N);
                break;
            case 'G':
                scanf("%d%d",&pos,&N);
                A=Splay.GetSum(pos,N);
                printf("%d\n",A);
                break;
            case 'M':
                if (Ctrl[2]=='K')
                {
                    scanf("%d%d%d",&pos,&N,&C[0]);
                    Splay.MakeSame(pos,N,C[0]);
                }
                else
                    printf("%d\n",Splay.MaxSum());
                break;
        }
    }
    return 0;
}
