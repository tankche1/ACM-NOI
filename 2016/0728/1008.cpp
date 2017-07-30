# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int mod=1000000007;

struct State{
    int tmp,cost;
    State() {}
};

vector<State> go[1<<4][1<<4];

int ans[5][11][41];

int main(){
    for(int w=1;w<=4;w++){
        for(int from=0;from<(1<<4);from++){
            for(int board=0;board<(1<<4);board++){
                go[from][board].clear();
                for(int tmp=0;tmp<(1<<4);tmp++){

                }
            }
        }
    }
    return 0;
}
