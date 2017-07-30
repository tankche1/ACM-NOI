# include<stdio.h>
# include<string.h>
# include<queue>
# include<map>
# include<algorithm>
using namespace std;
map<int,int> all;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
struct state{
	map<int,int> id;
	int num;
	queue<int> Q;
	
	void init(){
		while(!Q.empty()) Q.pop();
		Q.push(num);
		id[num]=0;
	}
	
	void read(){
		num=0;
		char a;
		for(int i=0;i<16;i++)
		{while((a=getchar())&&a!='1'&&a!='0');num=(num<<1)+a-'0';}
	}
	
	int get(int i,int j,int s){
		return s&(1<<(16-((i-1)*4+j)));
	}
	
	int pos(int i,int j){
		return (1<<(16-((i-1)*4+j)));
	}
	
	bool expand(){
		int step=id[Q.front()];
		while(id[Q.front()]==step){
			int now=Q.front();Q.pop();
			//printf("now:%d\n",now);
			int news;
			for(int i=1;i<=4;i++)
				for(int j=1;j<=4;j++)
					if(get(i,j,now)){
						for(int to=0;to<4;to++){
							int nx=i+dx[to],ny=j+dy[to];
							if(nx>=1&&nx<=4&&ny>=1&&ny<=4)
							if(!get(nx,ny,now)){
								news=now-pos(i,j)+pos(nx,ny);
								if(!id.count(news)){
									if(all.count(news)) return true;
									id[news]=step+1;all[news]=step+1;
									Q.push(news);
								}
							}
						}
					}
		}
		return false;
	}
};
state S,T;

int double_BFS(){
	for(int i=1;;i++){
		//printf("i:%d\n",i);
		if(i&1) {if(S.expand()) return i;}
		else {if(T.expand()) return i;}
	}
}

int main(){
	S.read();
	T.read();
	S.init();
	T.init();
	if(S.num==T.num) puts("0");
		else printf("%d\n",double_BFS());
	return 0;
}
