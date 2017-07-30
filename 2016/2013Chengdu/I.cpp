# include<stdio.h>
# include<string.h>
# include<vector>
# include<string>
# include<map>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=50010;
map<string,int> name_id;
string str;
int name_cnt=0;

struct Team{
    string name;
    int bh;
    int penalty,num;
    int last_solve;
    bool solve[27];
    bool frozen[27];
    int ti[27];
    int nbs[27];//no before solve
    int afs[27];//after frozen submit
    int no[27];
    Team() {}
    void init(){
        memset(solve,0,sizeof(solve));memset(frozen,0,sizeof(frozen));//memset(add,0,sizeof(add));
        memset(nbs,0,sizeof(nbs));memset(afs,0,sizeof(afs));memset(no,0,sizeof(no));
        penalty=num=0;last_solve=0;
    }

    bool operator < (const Team &rhs)const{
        if(num!=rhs.num) return num<rhs.num;
        if(penalty!=rhs.penalty) return penalty>rhs.penalty;
        if(last_solve!=rhs.last_solve) return last_solve>rhs.last_solve;
        return name<rhs.name;
    }
}team[maxn];

int get(char *s){
    int len=strlen(s);str="";
    for(int i=0;i<len;i++) str+=s[i];
    if(!name_id.count(str)) {
        name_id[str]=++name_cnt;team[name_cnt].name=str;
        team[name_cnt].bh=name_cnt;
        return name_cnt;
    }
    else return name_id[str];
}

int n,m,T,frozen_T;

struct Submit{
    int team_bh,prob,ti,result;
    Submit() {}
    void get_result(char *s){
        if(s[0]=='Y') result=1;else if(s[0]=='N') result=0;else result=-1;
    }
}sub[maxn];

bool cmp(Submit A,Submit B){
    if(A.ti!=B.ti) return A.ti<B.ti;
    return A.result<B.result;
}

bool cmp2(Team A,Team B){
    if(A.num!=B.num) return A.num>B.num;
    if(A.penalty!=B.penalty) return A.penalty<B.penalty;
    if(A.last_solve!=B.last_solve) return A.last_solve<B.last_solve;
    return A.name>B.name;
}

bool cmp3(Team A,Team B){
    return A.bh<B.bh;
}

void get_init(){
    int x,b;
    for(int i=1;i<=name_cnt;i++) team[i].init();

    int i;
    for(i=1;i<=n;i++){
        if(sub[i].ti>=frozen_T) break;
        x=sub[i].team_bh;b=sub[i].prob;
        if(sub[i].result==1){
            if(team[x].solve[b]) continue;
            team[x].penalty+=sub[i].ti+team[x].nbs[b]*20;
            team[x].solve[b]=1;team[x].num++;
            team[x].last_solve=sub[i].ti;
        }
        else if(sub[i].result==0){
            if(!team[x].solve[b]) team[x].nbs[b]++;
            team[x].no[b]++;
        }
    }

    for(;i<=n;i++){
        x=sub[i].team_bh;b=sub[i].prob;
        team[x].afs[b]++;
        if(!team[x].solve[b]) team[x].frozen[b]=1;
    }

    //for(int i=1;i<=name_cnt;i++) ans[i]=team[i];
    sort(team+1,team+name_cnt+1,cmp2);

    for(int i=1;i<=name_cnt;i++){
        printf("%s %d %d %d",team[i].name.c_str(),i,team[i].num,team[i].penalty);
        for(int j=1;j<=m;j++){
            printf(" ");
            if(team[i].solve[j]){
                printf("+");
                if(team[i].nbs[j]>0) printf("%d",team[i].nbs[j]);
            }
            else{
                if(!team[i].frozen[j]){
                    if(team[i].no[j]==0) printf(".");
                    else printf("-%d",team[i].no[j]);
                }
                else{
                    if(team[i].no[j]==0) printf("0/%d",team[i].afs[j]);
                    else printf("-%d/%d",team[i].no[j],team[i].afs[j]);
                }
            }
        }puts("");
    }


}

set<Team> s;
set<Team> ::iterator it,it2;
void Gunbang(){
    Team wudi;wudi.init();wudi.num=100;
    s.insert(wudi);
    int i,x,b;
    for(i=1;i<=n;i++) if(sub[i].ti>=frozen_T) break;

    sort(team+1,team+name_cnt+1,cmp3);
    for(;i<=n;i++){
            //printf("i:%d\n",i);
        x=sub[i].team_bh;b=sub[i].prob;//printf("%s %c\n",team[x].name.c_str(),b+'A'-1);
        if(sub[i].result==1){
            //printf("%s %c\n",team[x].name.c_str(),b+'A'-1);
            if(team[x].solve[b]) continue;
            team[x].solve[b]=1,team[x].ti[b]=sub[i].ti;//puts("fuck");
        }
        else if(sub[i].result==0){
            if(!team[x].solve[b]) team[x].nbs[b]++;
        }
        else continue;
    }

    for(i=1;i<=name_cnt;i++) s.insert(team[i]);//team[i].bh=i;
    Team now;
    while(!s.empty()){
        it=s.begin();now=*it;s.erase(it);//puts("hei");
        if(now.num==100) break;

        for(int j=1;j<=m;j++){
            if(now.frozen[j]==1){
                now.frozen[j]=0;//puts("...");
                if(now.solve[j]){
                    //printf("%s %d\n",now.name.c_str(),j);
                    now.num++;now.penalty+=now.ti[j]+now.nbs[j]*20;
                    now.last_solve=max(now.last_solve,now.ti[j]);
                    it2=s.upper_bound(now);
                    if(it2==s.begin()) continue;
                    it2--;
                    printf("%s %s %d %d\n",now.name.c_str(),it2->name.c_str(),now.num,now.penalty);
                    s.insert(now);break;
                }
            }
        }
    }
}

void get_final(){
    int x,b;
    for(int i=1;i<=name_cnt;i++) team[i].init();

    for(int i=1;i<=n;i++){
        x=sub[i].team_bh;b=sub[i].prob;
        if(sub[i].result==1){
            if(team[x].solve[b]) continue;
            team[x].penalty+=team[x].nbs[b]*20+sub[i].ti;
            team[x].num++;
            team[x].last_solve=sub[i].ti;
            team[x].solve[b]=1;
        }
        else if(sub[i].result==0){
            if(!team[x].solve[b]) team[x].nbs[b]++;
        }
    }

    sort(team+1,team+name_cnt+1,cmp2);

    for(int i=1;i<=name_cnt;i++){
        printf("%s %d %d %d",team[i].name.c_str(),i,team[i].num,team[i].penalty);
        for(int j=1;j<=m;j++){
            printf(" ");
            if(team[i].solve[j]){
                printf("+");
                if(team[i].nbs[j]>0) printf("%d",team[i].nbs[j]);
            }
            else{
                if(!team[i].nbs[j]) printf(".");
                else printf("-%d",team[i].nbs[j]);
            }
        }
        puts("");
    }
}


int main(){
    int Case;
    char s[30],t;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        name_id.clear();name_cnt=0;
        scanf("%d%d%d%d",&n,&m,&T,&frozen_T);

        for(int i=1;i<=n;i++){
            scanf("%s",s);
            sub[i].team_bh=get(s);
            while((t=getchar())&&(t<'A'||t>'Z'));sub[i].prob=t-'A'+1;
            scanf("%d%s",&sub[i].ti,s);
            sub[i].get_result(s);
        }
        sort(sub+1,sub+n+1,cmp);

       // puts("**********");
        //for(int i=1;i<=n;i++) printf("%d %d %d %d\n",sub[i].team_bh,sub[i].prob,sub[i].ti,sub[i].result);
        printf("Case #%d:\n",Tcase);
        get_init();
        Gunbang();
        get_final();
    }
    return 0;
}
