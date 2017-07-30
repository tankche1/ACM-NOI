#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;

template<int MAXN, int SIGMA> class PalindromeTree {
public:
	struct TNODE {
		int len;
		TNODE* suffLink;
		TNODE* child[SIGMA];

		/* Extra fields */
		ll cnt;
		/* ------------ */
	};

	char text[MAXN]; int textLen;
	TNODE NPool[MAXN+2];
	TNODE* NPTop, *Last, *Root_Guard, *Root_Empty;

	PalindromeTree() { reset(); }
	int reset() {
		NPTop = NPool; textLen = 0;
		Root_Guard = NPTop++; Root_Empty = NPTop++;
		memset(Root_Guard,0,sizeof(TNODE));
		memset(Root_Empty,0,sizeof(TNODE));
		Root_Guard->len = -1; Root_Empty->len = 0;
		Root_Guard->suffLink = Root_Empty->suffLink = Root_Guard;
		Last = Root_Empty;
		return 0;
	}

	// return 0 or 1, indicating new (distinct) palindrome substring count.
	int feed(int ch) {
		text[textLen++] = ch;

		TNODE* cur = Last;
		while(textLen-1-1-cur->len < 0 || text[textLen-1-1-cur->len] != ch) cur = cur->suffLink;
		if(cur->child[ch]) { Last = cur->child[ch]; Last->cnt++; return 0; }

		TNODE* x = NPTop++;
		memset(x,0,sizeof(TNODE));
		Last = x;
		x->len = cur->len + 2;
		cur->child[ch] = x;
		if(x->len == 1) { // from -1 root
			x->suffLink = Root_Empty;
		} else {
			cur = cur->suffLink;
			while(textLen-1-1-cur->len < 0 || text[textLen-1-1-cur->len] != ch)
				cur = cur->suffLink;
			x->suffLink = cur->child[ch];
		}
		// maintain additional field here.
		x->cnt = 1;
		return 1;
	}

	int uplink() {
		for(int i = NPTop-NPool-1;i > 1;i--) {
			TNODE* x = NPool+i;
			x->suffLink->cnt += x->cnt;
		}
		return 0;
	}
};


const int MAXN = 222222;
const int MAXSIGMA = 26;

char strA[MAXN];
char strB[MAXN];

PalindromeTree<MAXN,MAXSIGMA> TreeA;
PalindromeTree<MAXN,MAXSIGMA> TreeB;
typedef pair<PalindromeTree<MAXN,MAXSIGMA>::TNODE*,PalindromeTree<MAXN,MAXSIGMA>::TNODE*> state;

ll bfs(const state& initial) {
	queue<state> qst;
	qst.push(initial);
	ll ans = 0;
	while(!qst.empty()) {
		state now = qst.front(); qst.pop();
		if(now.first->len && now.second->len) ans += now.first->cnt * now.second->cnt;
		for(int i = 0;i < MAXSIGMA;i++) {
			if(now.first->child[i] && now.second->child[i]) {
				qst.push(state(now.first->child[i],now.second->child[i]));
			}
		}
	}
	return ans;
}

int main(void) {
	int T = 0;
	int TK = 0;
	scanf("%d",&T);
	while(T--) {
		printf("Case #%d: ",++TK);
		scanf("%s %s",strA,strB);

		int lenA = strlen(strA);
		int lenB = strlen(strB);
		TreeA.reset(); TreeB.reset();
		for(int i = 0;i < lenA;i++) TreeA.feed(strA[i] - 'a');
		for(int i = 0;i < lenB;i++) TreeB.feed(strB[i] - 'a');

		TreeA.uplink(); TreeB.uplink();

		ll ans = bfs(state(TreeA.Root_Empty,TreeB.Root_Empty)) + bfs(state(TreeA.Root_Guard,TreeB.Root_Guard));
		printf("%lld\n",ans);
	}
	while(getchar() != EOF);
	return 0;
}
