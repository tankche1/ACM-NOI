// UVa10572 Black and White
// Rujia Liu
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int nrows, ncols, has_sol;
char partial[8][9]; // ��������
char grid[8][8], sol[8][8]; // ��ǰ�����������ͽ�����

struct State {
  char color[8];       // ���и�����ɫ
  char up_left;        // ���Ϸ�������ɫ�������ж��Ƿ����2x2ͬɫ������
  char comp[8];        // ��������ͨ����
  char ncomp;          // ��ͨ��������
  char ncolor_comp[2]; // ����ͨ���������ͺ���ͨ��������

  // ����״̬����С��ʾ
  void normalize() {
    int rep[10];
    memset(rep, -1, sizeof(rep));
    ncomp = ncolor_comp[0] = ncolor_comp[1] = 0;
    for (int i = 0; i < ncols; i++) {
      if (rep[comp[i]] < 0) {
        rep[comp[i]] = ncomp++;
        ncolor_comp[color[i]]++;
      }
      comp[i] = rep[comp[i]];
    }
  }

  // �����б��Ϊb����ͨ�����ĳ�a
  void merge(int a, int b) {
    if (a == b) return;
    for (int i = 0; i < ncols; i++)
      if (comp[i] == b) comp[i] = a;
  }

  // ���ò�����32λ�޷���������Χ
  unsigned int encode() {
    unsigned int key = 0;
    for (int i = 0; i < ncols; i++)
      key = key * 16 + color[i] * 8 + comp[i];
    return key;
  }
};

// ��̬�滮����״ֵ̬��ֻ��¼�˲�ǿ��Ϳɫ����force_color<0��ʱ��ֵ
map<unsigned, int> memo[8][8][2]; 

const int ch[] = { 'o', '#' };

// ��ǰҪͿ����(row, col)��״̬ΪS������Ϳforce_color��ɫ�����ؽ�ĸ���
int rec(int row, int col, State& S, int force_color) {
  if (col == ncols) { col = 0; row++; }
  S.normalize(); // ������С��ʾ

  if (row == nrows) {
    if (S.ncolor_comp[0] > 1 || S.ncolor_comp[1] > 1) return 0;
    if (has_sol == 0) {
      has_sol = 1;
      for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
          sol[i][j] = grid[i][j];
    }
    return 1;
  }

  // �������Ӻ��ϸ�����ɫ��ͬ�������Ϸ����ӵ���ɫ���޹ؽ�Ҫ�ģ�ͳһ��Ϊ0������״̬
  if (row > 0 && col > 0 && S.color[col] != S.color[col-1])
    S.up_left = 0;

  // ֻ�в�ǿ��Ϳɫ��force_color<0��ʱkey��������
  unsigned int key;
  if (force_color < 0) {
    key = S.encode();
    if (memo[row][col][S.up_left].count(key) != 0)
      return memo[row][col][S.up_left][key];
  }

  int res = 0;

  // ��ǰ����Ϳcolor������ɫ
  for(int color = 0; color < 2; color++) {
    if (force_color == 1 - color) continue; // ��force_colorì��
    if (partial[row][col] == ch[1-color]) continue; // ������ì��
    if (row > 0 && col > 0 && S.color[col-1] == color && S.color[col] == color && S.up_left == color) continue; // ����2x2ͬɫ������

    State T = S;
    T.color[col] = color;
    T.up_left = S.color[col];
    T.comp[col] = (row > 0 && S.color[col] == color) ? S.comp[col] : S.ncomp; // ��ʼ����״̬��col�е���ͨ�������
    if (col > 0 && T.color[col-1] == color) T.merge(T.comp[col-1], T.comp[col]); // �����ɫ���������ͬ��������Ϊ����ӵ���ͨ����

    grid[row][col] = ch[color];

    if (row > 0 && S.color[col] == 1-color) { // ����Ϸ������Ƿ�Ϊ������ͨ����      
      if (find(T.comp, T.comp+ncols, S.comp[col]) == T.comp+ncols) { // ����ͨ�����Ѿ���ʧ
        if (S.ncolor_comp[1-color] > 1 || row < nrows-2) continue; // ���color����������ͨ�������ڣ��������ٻ���������ҪͿ�����޷�����
        res += rec(row, col+1, T, color); // ���Լ��������Ժ�ǿ��Ϳcolor
        continue;
      }
    }

    res += rec(row, col+1, T, force_color);
  }

  if (force_color < 0)
    memo[row][col][S.up_left][key] = res;
  return res;
}


int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &nrows, &ncols);
    for(int i = 0; i < nrows; i++) scanf("%s", partial[i]);

    State S;
    memset(&S, 0, sizeof(S));
    S.normalize();
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        for (int k = 0; k < 2; k++)
          memo[i][j][k].clear();

    has_sol = 0;
    printf("%d\n", rec(0, 0, S, -1));
    if (has_sol) {
      for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++)
          putchar(sol[i][j]);
        putchar('\n');
      }
    }
    printf("\n");
  }
  return 0;
}
