# include<stdio.h>
# include<string.h>
# include<vector>
# include<math.h>
# include<algorithm>
using namespace std;
const int INF=100000;
const int UP=1;
const int DOWN=2;
const int FLOOR=0;
int m,num[30];

struct State{
	int card[8],type[8];
	int hold[2];
	int score;
	int pos;
	
	State(){
		hold[0]=hold[1]=score=0;
	}
	
	void getscore(int a,int b,int c){
		int k=0;
		if(a>0) k++;if(b>0) k++;if(c>0) k++;
		int ret=abs(a)+abs(b)+abs(c);
		if(k>1) score+=ret;
		else score-=ret;
	}
	
	bool isfinal(){
		if(pos==2*m){
			score+=hold[0]+hold[1];
			hold[0]=hold[1]=0;
			return true;
		}
		return false;
	}
	
	State child(){
		State ret;
		for(int i=0;i<8;i++) {ret.card[i]=card[i];ret.type[i]=type[i];}
		ret.hold[0]=hold[0];ret.hold[1]=hold[1];
		ret.score=score;
		ret.pos=pos+1;
		return ret;
	}
	
	void expand(int player,vector<State>& ret){
		int cur=pos;
		//1
		if(!hold[player]){
			State S=child();
			S.hold[player]=num[cur];
			ret.push_back(S);
		}
		//2
		for(int i=0;i<7;i++){
			if(type[i]==DOWN&&type[i+1]==UP){
				//new card
				State S=child();
				S.type[i]=S.type[i+1]=FLOOR;
				S.card[i]=S.card[i+1]=num[cur];S.getscore(card[i],card[i+1],num[cur]);
				ret.push_back(S);
				//hold
				if(hold[player]){
					State S=child();
					S.type[i]=S.type[i+1]=FLOOR;
					S.card[i]=S.card[i+1]=hold[player];
					S.hold[player]=num[cur];S.getscore(S.card[i],card[i],card[i+1]);
					ret.push_back(S);
				}
			}
		}
		//3
		if(hold[player]){
			for(int i=0;i<7;i++){
				if(type[i]==FLOOR&&type[i+1]==FLOOR&&card[i]==card[i+1]){
					State S=child();
					S.type[i]=UP;S.type[i+1]=DOWN;
					S.getscore(hold[player],num[cur],card[i]);
					//hold-up
					S.card[i]=hold[player];S.card[i+1]=num[cur];S.hold[player]=0;
					ret.push_back(S);
					//hold-down
					swap(S.card[i],S.card[i+1]);
					ret.push_back(S);
				}
			}
		}
	}
	
};

int alphebeta(State& S,int player,int alpha,int beta){
	if(S.isfinal()) return S.score;
	
	vector<State> children;
	S.expand(player,children);
	
	for(int i=0;i<children.size();i++){
		int v=alphebeta(children[i],player^1,alpha,beta);
		if(!player) alpha=max(alpha,v);else beta=min(beta,v);
		
		if(beta<=alpha) break;
	}
	return player==0?alpha:beta;
}

int main(){
	char name[20],t;
	int kase=0;
	while(scanf("%s",name)!=EOF){
		if(name[0]=='E') break;
		
		scanf("%d",&m);
		for(int i=0;i<2*m;i++){
			scanf("%d",&num[i]);//printf("%d \n",num[i]);
			while((t=getchar())&&t!='R'&&t!='B');
			if(t=='B') num[i]=-num[i];
		}
		
		State S;
		S.pos=8;
		for(int i=0;i<8;i++){
			S.type[i]=i%2==0?UP:DOWN;
			S.card[i]=num[i];
		}
		
		int ans=alphebeta(S,num[0]>0?0:1,-INF,INF);

		printf("Case %d: ",++kase);
		if(ans==0) printf("Axel and Birgit tie\n");
		else{
			printf("%s ",name);
			if((ans>0&&name[0]=='A')||(ans<0&&name[0]=='B')) printf("wins ");
			else printf("loses ");
			printf("%d\n",abs(ans));
		}
	}
	return 0;
}
