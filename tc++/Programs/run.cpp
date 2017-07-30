
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

void Error()
  {
    printf("Wrong input!!\n");
    printf("Please read readme.txt carefully!\n");
    system("pause");
    exit(0);
  }

int main()
  {
    int t, i, n, m, q1, q2, flag;
    char str[100];
    
    FILE *in = fopen("config.txt", "r");
    
    for (fscanf(in, "%d", &t), i = 1; i <= t; i ++)
      {
        fscanf(in, "%d%d%d%d%d", &n, &m, &q1, &q2, &flag);
        if (flag != 1 && flag != 0) Error();
        if (n > 100000 || m > 1000000) Error();
        if (q1 + q2 > 100000) Error();
        if (q2 + n - 1 > m) Error();
        if (m > (long long)(n) * (n - 1) / 2) Error();
        FILE *out = fopen("tmp.txt", "w");
        fprintf(out, "%d %d %d %d %d", n, m, q1, q2, flag);
        fclose(out);
        printf("Now it's making testcase %d\n", i);
        printf("N = %d, M = %d, Q1 = %d, Q2 = %d, Flag = %d\n\n", n, m, q1, q2, flag);
        memset(str, 0, sizeof(str));
        sprintf(str, "gen tube%d.in", i);
        system(str);
        memset(str, 0, sizeof(str));
        sprintf(str, "tube tube%d.in tube%d.ans", i, i);
        system(str);
      }
    
    fclose(in);
    system("del tmp.txt");
    
    printf("The work has finished!\n");
    system("pause");
    
    return 0;
  }
