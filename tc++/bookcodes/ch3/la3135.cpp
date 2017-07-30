// LA3135 Argus
// Rujia Liu
#include<cstdio>
#include<queue>
using namespace std;

// ���ȶ����е�Ԫ��
struct Item { 
  int QNum, Period, Time;
  // ��Ҫ�����ȼ��ȽϺ��������ȼ��ߵ��ȳ���
  bool operator < (const Item& a) const { // �����const�ز����٣������ע��
    return Time > a.Time || (Time == a.Time && QNum > a.QNum);
  }
};

int main() {
  priority_queue<Item> pq;
  char s[20];

  while(scanf("%s", s) && s[0] != '#'){
    Item item;
    scanf("%d%d", &item.QNum, &item.Period);
    item.Time = item.Period; // ��ʼ������һ���¼���ʱ�䡱Ϊ��������
    pq.push(item); 
  }

  int K;
  scanf("%d" , &K);
  while(K--) {    
    Item r = pq.top(); // ȡ��һ���¼�
    pq.pop();
    printf("%d\n" , r.QNum);    
    r.Time += r.Period; // ���¸ô������ġ���һ���¼�����ʱ�� 
    pq.push(r); // ���²������ȶ���
  }
  return 0;
}
