# include<stdio.h>
# include<string>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
map<string,int> id;
char s[100];

struct Team{
    string name;
    int point;
    int win,lose_win;
    int score,lose_score;
    int set,lose_set;

    void init() {
        point=win=lose_win=score=lose_score=set=lose_set=0;
    }
}team[25];

struct Match{
    bool happen;
    int setA,setB;
    int scoreA,scoreB;
    Match(){}
}match[25][25];

bool cmp(int a,int b){
    if(team[a].point!=team[b].point) return team[a].point>team[b].point;
    if(team[a].win!=team[b].win) return team[a].win>team[b].win;
    if(team[a].score*team[b].lose_score!=team[b].score*team[a].lose_score) return team[a].score*team[b].lose_score>team[b].score*team[a].lose_score;
    return team[a].set*team[b].lose_set>=team[b].set*team[a].lose_set;
}

int bhA[10],bhB[10],bhC[10],bhD[10],bhE[10],bhF[10],bhG[10],bhH[10];

void Fight(int a,int b){
    if(!match[a][b].happen) swap(a,b);
    if(match[a][b].setA==3) team[a].win++,team[b].lose_win++;
    else team[b].win++,team[a].lose_win++;

    if(match[a][b].setA==3&&match[a][b].setB<=1) team[a].point+=3;
    else if(match[a][b].setA==3) team[a].point+=2,team[b].point++;
    else if(match[a][b].setA<=1) team[b].point+=3;
    else team[a].point++,team[b].point+=2;

    team[a].score+=match[a][b].scoreA;team[a].lose_score+=match[a][b].scoreB;
    team[b].score+=match[a][b].scoreB;team[b].lose_score+=match[a][b].scoreA;
    team[a].set+=match[a][b].setA;team[a].lose_set+=match[a][b].setB;
    team[b].set+=match[a][b].setB;team[b].lose_set+=match[a][b].setA;
}

void Battle(int *bh,int n){

    for(int i=1;i<=n;i++) team[bh[i]].init();
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            Fight(bh[i],bh[j]);
        }
    }
}

void first_Round(){
    Battle(bhA,6);
    Battle(bhB,6);
    Battle(bhC,6);
    Battle(bhD,6);

    sort(bhA+1,bhA+6+1,cmp);
    sort(bhB+1,bhB+6+1,cmp);
    sort(bhC+1,bhC+6+1,cmp);
    sort(bhD+1,bhD+6+1,cmp);

    for(int i=1;i<=4;i++) bhE[i]=bhA[i];
    for(int i=5;i<=8;i++) bhE[i]=bhD[i-4];

    for(int i=1;i<=4;i++) bhF[i]=bhB[i];
    for(int i=5;i<=8;i++) bhF[i]=bhC[i-4];
}

void second_Round(){
    Battle(bhE,8);
    Battle(bhF,8);

    sort(bhE+1,bhE+8+1,cmp);
    sort(bhF+1,bhF+8+1,cmp);

    for(int i=1;i<=3;i++) bhA[i]=bhE[i];
    for(int i=4;i<=6;i++) bhA[i]=bhF[i-3];

    sort(bhA+1,bhA+6+1,cmp);

    bhG[1]=bhA[1];bhG[2]=bhA[4];bhG[3]=bhA[6];
    bhH[1]=bhA[2];bhH[2]=bhA[3];bhH[3]=bhA[5];

}

void third_Round(){
    int a,b,c;
    Battle(bhG,3);
    Battle(bhH,3);

    sort(bhG+1,bhG+3+1,cmp);
    sort(bhH+1,bhH+3+1,cmp);

    team[bhG[1]].init();team[bhH[1]].init();team[bhG[2]].init();team[bhH[2]].init();

    Fight(bhG[1],bhH[2]);if(cmp(bhG[1],bhH[2])) a=bhG[1];else a=bhH[2];
    Fight(bhG[2],bhH[1]);if(cmp(bhG[2],bhH[1])) b=bhG[2];else b=bhH[1];

    team[a].init();team[b].init();
    Fight(a,b);
    if(cmp(a,b)) c=a;else c=b;
    printf("%s\n",team[c].name.c_str());

}

char s1[100],s2[100];

int main()
{
    int a,b,c,d;
    for(int i=1;i<=24;i++){
        scanf("%s",s);
        id[string(s)]=i;
        team[i].name=string(s);
        team[i].init();
    }
    for(int i=1;i<=24;i++) for(int j=1;j<=24;j++) match[i][j].happen=false;

    for(int t1=1;t1<=23;t1++){
        for(int t2=t1+1;t2<=24;t2++){
            scanf("%s%s",s1,s2);
            a=id[string(s1)];b=id[string(s2)];
            match[a][b].happen=1;
            scanf("%d-%d",&match[a][b].setA,&match[a][b].setB);
            match[a][b].scoreA=match[a][b].scoreB=0;
            for(int t=1;t<=match[a][b].setA+match[a][b].setB;t++){
                scanf("%d-%d",&c,&d);
                match[a][b].scoreA+=c;match[a][b].scoreB+=d;
            }
        }
    }

    for(int i=1;i<=6;i++) bhA[i]=i;
    for(int i=7;i<=12;i++) bhB[i-6]=i;
    for(int i=13;i<=18;i++) bhC[i-12]=i;
    for(int i=19;i<=24;i++) bhD[i-18]=i;

    first_Round();
    second_Round();
    third_Round();

}
