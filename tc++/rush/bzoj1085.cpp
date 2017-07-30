# include<stdio.h>
# include<iostream>
# include<string.h>
# include<string>
# include<map>
# include<queue>
# include<algorithm>
using namespace std;
map<string,int> State;

int dx[8]={-2,-1,-2,-1,2,1,2,1},dy[8]={-1,-2,1,2,-1,-2,1,2};

struct BFS{
	queue<string> q;
	map<string,int> id;
	
	void init(string str){
		while(!q.empty()) q.pop();
		id.clear();
		q.push(str);id[str]=0;
	}
	
	bool bfs(){
		//puts("fuck");
		int pos;
		//printf("step:%d\n",step);
		//printf("%d\n",q.size());
		int step=id[q.front()];
		while(!q.empty()){
			string s=q.front();//cout<<s<<endl;
			if(id[s]!=step) break;
			q.pop();
			//cout<<s<<endl;
			for(int i=0;i<25;i++) if(s[i]=='*') {pos=i;break;}
			int x=pos/5,y=pos%5;
			for(int i=0;i<8;i++){
				int newx=x+dx[i],newy=y+dy[i];
				int newpos=newx*5+newy;
				//printf("pos:%d newpos:%d\n",pos,newpos);
				if(newx>=0&&newx<5&&newy>=0&&newy<5){
					string news=s;
					swap(news[pos],news[newpos]);
					//cout<<news<<endl;
					if(State.count(news)&&!id.count(news)) return true;
					else if(!id.count(news)){
						State[news]=1;
						id[news]=step+1;
						q.push(news);
						//puts("fuck");
					}
				}
			}
		}
		return false;
	}
};
BFS bfs1,bfs2;

string start,goal;

int calculate_step(){
	if(start==goal) return 0;
	State.clear();
	State[start]=1;State[goal]=1;
	bfs1.init(start);bfs2.init(goal);
	for(int i=1;i<=15;i++){
		if(bfs1.q.size()<bfs2.q.size())
		{//puts("a");
			if(bfs1.bfs()) return i;}
		else{//puts("b");
			if(bfs2.bfs()) return i;
		}
		//printf("%d %d\n",bfs1.q.size(),bfs2.q.size());
		//int a;//scanf("%d",&a);
		//printf("i:%d\n",i);
	}
	return -1;
}

char s[10];
int T;
int main(){
	scanf("%d",&T);
	goal="111110111100*110000100000";
	while(T--){
		start="";
		for(int i=1;i<=5;i++){
			scanf("%s",s);
			start+=s;
		}
		printf("%d\n",calculate_step());
	}
	return 0;
}
/*
1
01011
110*1
01110
01010
00100
*/
