#include<iostream>
#include<cstring> 
using namespace std;
const int maxsize = 100;
long long p[maxsize]{71048, 47356, 1383, 82762, 75138, 55089, 45196, 19829, 71323, 56242, 64531};
long long m[maxsize][maxsize], s[maxsize][maxsize];//m[i][j]存储最优解
int n = 10;

void MatrixChain()
{
	int i, r, j, k;
	for (int i = 1; i <= n; i++) 
	{     
		m[i][i] = 0;//对角线为0；规模为1时；
	}
	for (r = 2; r <= n; r++)//矩阵连乘的规模为r ，从2开始
	{
		for (i = 1; i <= n - r + 1; i++)//最大可起始点
		{
			j = i + r - 1;//j-i=r-1；
			m[i][j] = LLONG_MAX;//另开始时m[i][j]为无穷大；
			s[i][j] = i;//s[][]存储各子问题的决策点，即一开始k为该点。
			for (k = i; k < j; k++)//寻找最优值
			{
				long long t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];//求出分割点为k时的乘积
				if (t < m[i][j])//求出最小值，将分割点s[i][j]设置为k；
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}

void print(int i, int j)
{
	if (i == j)//回归条件
	{
		cout << "A" << i << "";
		return;
	}
	cout << "(";
	print(i, s[i][j]);
	print(s[i][j] + 1, j);//递归1到s[1][j]
	cout << ")";
}

int main()
{
	MatrixChain();
	print(1, n);
	cout << endl;
	cout << m[1][n] << endl;
	printf("%lld\n", m[1][n]);
}
