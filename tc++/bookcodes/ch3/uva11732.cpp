// UVa11732 strcmp() Anyone?
// Rujia Liu
#include<cstring>
#include<vector>
using namespace std;

const int maxnode = 4000 * 1000 + 10;
const int sigma_size = 26;

// ��ĸ��Ϊȫ��Сд��ĸ��Trie
struct Trie {
  int head[maxnode]; // head[i]Ϊ��i����������ӱ��
  int next[maxnode]; // next[i]Ϊ��i���������ֵܱ��
  char ch[maxnode];  // ch[i]Ϊ��i������ϵ��ַ�
  int tot[maxnode];  // tot[i]Ϊ��i�����Ϊ��������������Ҷ�������
  int sz; // �������
  long long ans; // ��
  void clear() { sz = 1; tot[0] = head[0] = next[0] = 0; } // ��ʼʱֻ��һ�������

  // �����ַ���s����������'\0'������;����tot
  void insert(const char *s) {
    int u = 0, v, n = strlen(s);
    tot[0]++;
    for(int i = 0; i <= n; i++) {
      // ���ַ�a[i]
      bool found = false;
      for(v = head[u]; v != 0; v = next[v])
        if(ch[v] == s[i]) { // �ҵ���
          found = true;
          break;
        }
      if(!found) {
        v = sz++; // �½����
        tot[v] = 0;
        ch[v] = s[i];
        next[v] = head[u];
        head[u] = v; // ���뵽������ײ�
        head[v] = 0;
      }
      u = v;
      tot[u]++;
    }
  }

  // ͳ��LCP=u�����е��������ıȽϴ���֮��
  void dfs(int depth, int u) {
    if(head[u] == 0) // Ҷ���
      ans += tot[u] * (tot[u] - 1) * depth;
    else {
      int sum = 0;
      for(int v = head[u]; v != 0; v = next[v])
        sum += tot[v] * (tot[u] - tot[v]); // ����v��ѡһ������������������ѡһ��
      ans += sum / 2 * (2 * depth + 1); // ����2��ÿ��ѡ��ͳ��������
      for(int v = head[u]; v != 0; v = next[v])
        dfs(depth+1, v);
    }
  }

  // ͳ��
  long long count() {
    ans = 0;
    dfs(0, 0);
    return ans;
  }
};

#include<cstdio>
const int maxl = 1000 + 10;   // ÿ��������󳤶�

int n;
char word[maxl];
Trie trie;

int main() {
  int kase = 1;
  while(scanf("%d", &n) == 1 && n) {
    trie.clear();
    for(int i = 0; i < n; i++) {
      scanf("%s", word);
      trie.insert(word);
    }
    printf("Case %d: %lld\n", kase++, trie.count());
  }
  return 0;
}
