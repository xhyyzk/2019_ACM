Every_SG
    这类游戏规定，对于还没有结束的单一游戏， 游戏者必须对该游戏进行进一步决策。
    规则还是一样，一人一步。
    策略：贪心
      先手必胜的游戏步数尽量长，先手必败的游戏步数尽量短。
    对于SG值为0的点，需要知道最快几步能将游戏带入终止状态；
    对于SG值非0的点，需要知道最慢几步游戏会被带入终止状态。
    用step函数来表示。
                0                 u为终止状态
    step(u) =   max{step(v)} + 1  sg(u) != 0 ^ v为u的后继 ^sg(v) = 0
                min{step(v)} + 1  sg(u) == 0 ^ v为u的后继

  结论：对于Every-SG游戏先手必胜当且仅当单一游戏中的最大step值为奇数

  hdu 3595
  在两堆石子可以进行这样的操作：在一堆中选择x个，在另外一堆中除去k*x个。
  现在有n对这样的石子，问先手输赢。
  把这N对石子的step的最大值求出来判断奇偶即可。

  代码：
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1010;

int step[MAX][MAX];
int sg[MAX][MAX];//0表示先手必败，1表示先手必胜

int EverySG(int a, int b)
{
	if (sg[a][b] >= 0) return sg[a][b];
	if (a < b) swap(a, b);
	int mi = 0x3f3f3f3f;
	int ma = 0;
	for (int i = b; i <= a; i += b){
		if (EverySG(b, a - i) == 0){//后继状态为先手必败，那该状态为先手必胜，求step最大值
			ma = max(ma, step[b][a - i]);
			sg[a][b] = sg[b][a] = 1;
		}
		else mi = min(mi, step[b][a - i]);//否则求step最小值
	}
	if (sg[a][b] == 1){
		step[a][b] = step[b][a] = ma + 1;
		return 1;
	}
	step[a][b] = step[b][a] = mi + 1;
	return sg[a][b] = sg[b][a] = 0;
}



int main(void)
{
	int n;
	memset(sg, -1, sizeof(sg));
	for (int i = 0; i < MAX; ++i)
		step[i][0] = step[0][i] = sg[i][0] = sg[0][i] = 0;//初始化
	while (scanf("%d", &n) != EOF){
		int mm = 0;
		while (n--){
			int a, b;
			scanf("%d %d", &a, &b);
			EverySG(a, b);
			mm = max(mm, step[a][b]);
		}
		printf((mm & 1) ? "MM\n" : "GG\n");
	}
	return 0;
}
