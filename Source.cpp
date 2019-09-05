#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <unordered_map>
#include <sstream>
#include <stack>
using namespace std;

long long InversePairsCore(vector<int> &data, vector<int> &copy, int start, int end)
{
	if (start == end)
	{
		copy[start] = data[start];
		return 0;
	}
	int length = (end - start) / 2;
	long long left = InversePairsCore(copy, data, start, start + length);
	long long right = InversePairsCore(copy, data, start + length + 1, end);

	int i = start + length;
	int j = end;
	int indexcopy = end;
	long long count = 0;
	while (i >= start && j >= start + length + 1)
	{
		if (data[i] > data[j])
		{
			copy[indexcopy--] = data[i--];
			count = count + j - start - length;          //count=count+j-(start+length+1)+1;
		}
		else
		{
			copy[indexcopy--] = data[j--];
		}
	}
	for (; i >= start; i--)
		copy[indexcopy--] = data[i];
	for (; j >= start + length + 1; j--)
		copy[indexcopy--] = data[j];
	return left + right + count;
}
int InversePairs(vector<int> &data) {
	int length = data.size();
	if (length <= 0)
		return 0;
	//vector<int> copy=new vector<int>[length];
	vector<int> copy;
	for (int i = 0; i < length; i++)
		copy.push_back(data[i]);
	long long count = InversePairsCore(data, copy, 0, length - 1);
	//delete[]copy;
	return count % 1000000007;
}

int GetNumberOfK(vector<int> data, int k) {
	unordered_map<int, int> ma;
	for (int i = 0; i < data.size(); ++i)
	{
		ma[data[i]]++;
	}
	auto i = ma.find(k);
	return i->second;
}

class A {
public:
	A() = default;
	virtual void fun() {
		cout << "a" << endl;
	}
};
class B :public A
{
public:
	B() = default;
	//void fun() override { cout << "C" << endl; }
	void fun() { cout << "b" << endl; }
};
string LeftRotateString(string str, int n) {
	if (str.empty()) return "";
	int length = str.size();

	if (n <= length)
		return str.substr(n, str.size() - n) + str.substr(0, n );
}

bool IsContinuous(vector<int> num) {
	if (num.size() != 5)return false;
	sort(num.begin(), num.end());
	if (num[0] < 0 || num[4]>13) return false;

	int count_Zero = 0;
	for (int i = 0; i < num.size() - 1; ++i)
	{
		if (num[i] == 0) count_Zero++;
		if (num[i] != 0 && num[i] == num[i + 1])
			return false;
	}

	int max = num[4];
	int min = num[count_Zero];
	if (max - min <= 4)
		return true;
	return false;
}

bool isNumeric(const char* s)
{
	if (strlen(s) == 0)
		return false;

	bool sign = false, dec = false, hasE = false;
	int length = strlen(s);

	for (int i = 0; i < length; ++i)
	{
		if (s[i] == 'e' || s[i] == 'E')
		{
			if (hasE) return false; 
			if (i == length - 1) return false;
			hasE = true;
		}
		else if (s[i] == '+' || s[i] == '-')
		{
			if (sign == false && i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') return false;
			if (sign && s[i - 1] != 'e' && s[i - 1] != 'E') return false;
			sign = true;
		}
		else if (s[i] == '.')
		{
			if (hasE || dec) return false;
			dec = true;
		}
		else if (s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}
int longestValidParentheses(string s) 
{
	int n = s.length(), longest = 0;
	stack<int> st;
	for (int i = 0; i < n; i++) 
	{
		if (s[i] == '(') 
			st.push(i);
		else 
		{
			if (!st.empty()) 
			{
				if (s[st.top()] == '(') 
					st.pop();
				else 
					st.push(i);
			}
			else 
				st.push(i);
		}
	}
	if (st.empty()) 
		longest = n;
	else 
	{
		int a = n, b = 0;
		while (!st.empty()) 
		{
			b = st.top(); 
			st.pop();
			longest = max(longest, a - b - 1);
			a = b;
		}
		longest = max(longest, a);
	}
	return longest;
}
int longestValidParentheses1(string s) 
{
	stack<int> stk;
	stk.push(-1);
	int ans = 0;
	for (int i = 0; i < s.size(); i++) 
	{
		if (s[i] == '(') 
			stk.push(i);
		else 
		{
			stk.pop();
			if (stk.empty()) 
				stk.push(i);
			else 
			ans = max(ans, i - stk.top());
		}
	}
	return ans;
}


//vector<int> maxInWindows(const vector<int>& num, unsigned int size)
//{
//	vector<int> res;
//	deque<int> s;
//	for (unsigned int i = 0; i < num.size(); ++i) 
//	{
//		while (s.size() && num[s.back()] <= num[i])//从后面依次弹出队列中比当前num值小的元素，同时也能保证队列首元素为当前窗口最大值下标
//			s.pop_back();
//		while (s.size() && i - s.front() + 1 > size)//当当前窗口移出队首元素所在的位置，即队首元素坐标对应的num不在窗口中，需要弹出
//			s.pop_front();
//		s.push_back(i);//把每次滑动的num下标加入队列
//		if (size&&i + 1 >= size)//当滑动窗口首地址i大于等于size时才开始写入窗口最大值
//			res.push_back(num[s.front()]);
//	}
//	return res;
//}
vector<int> maxInWindows(const vector<int>& num, unsigned int size)
{
	vector<int> res;
	deque<unsigned> s;
	for (unsigned i = 0; i < num.size(); ++i)
	{
		while (s.size() && num[s.back()] < num[i])
			s.pop_back();
		while (s.size() && i - s.front() + 1 > size)
			s.pop_front();
		s.push_back(i);
		if (size && i + 1 >= size)
			res.push_back(num[s.front()]);
	}
	return res;
}



bool findpath(const char *matrix, int rows, int cols, int row, int col, int& pathlength, bool *serve, const char *str)
{
	if (str[pathlength] == '\0')
		return true;
	bool getpath = false;
	if (row >= 0 && col >= 0 && rows > row && cols > col &&
		str[pathlength] == matrix[row * cols + col]
		&& serve[row * cols + col] == false)
	{
		++pathlength;
		serve[row * cols + col] = true;
		getpath = findpath(matrix, rows, cols, row + 1, col, pathlength, serve, str)
			|| findpath(matrix, rows, cols, row - 1, col, pathlength, serve, str)
			|| findpath(matrix, rows, cols, row, col + 1, pathlength, serve, str)
			|| findpath(matrix, rows, cols, row, col - 1, pathlength, serve, str);
		if (getpath == false)
		{
			--pathlength;
			serve[row * cols + col] = false;
		}
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			cout << serve[i * cols + j] << ' ';
		cout << endl;
	}
	cout << endl;
	return getpath;
}

bool hasPath(const char* matrix, int rows, int cols, const char* str)
{
	if (matrix == NULL || rows < 1 || cols < 1 || str == NULL)
		return false;
	bool* serve = new bool[rows * cols];
	memset(serve, 0, rows * cols);
	int pathlength = 0;
	for (int i = 0; i < rows; ++i)//行
		for (int j = 0; j < cols; ++j)//列
			if (findpath(matrix, rows, cols, i, j, pathlength, serve, str))
				return true;
	delete[] serve;
	return false;

}

int tableTwo[10][100];
int flag[10] = { -1 };

//背包容量为c
//v单个价值
//w单个重量
//n商品种类
int backpack(vector<int> v, vector<int> w, int c, int n)
{
	int jMax = min(w[n] - 1, c);
	for (int j = 0; j < jMax; ++j) tableTwo[n][j] = 0;
	for (int j = w[n]; j <= c; ++j) tableTwo[n][j] = v[n];

	for (int i = n - 1; i > 1; --i)
	{
		jMax = min(w[i], c);
		for (int j = 0; j <= jMax; ++j) 
			tableTwo[i][j] = tableTwo[i + 1][j];
		for (int j = w[i]; j <= c; ++j) 
			tableTwo[i][j] = max(tableTwo[i + 1][j], tableTwo[i + 1][j - w[i]] + v[i]);
	}
	tableTwo[1][c] = tableTwo[2][c];
	if (c >= w[1])
		tableTwo[1][c] = max(tableTwo[1][c], tableTwo[2][c - w[1]] + v[1]);
	return tableTwo[1][c];

}

void Trackback(vector<int> w, int c, int n)
{
	for (int i = 1; i < n; ++i)
	{
		if (tableTwo[i][c] == tableTwo[i + 1][c])
			flag[i] = 0;
		else
		{
			flag[i] = 1;
			c -= w[i];
		}
	}
	flag[n] = tableTwo[n][c] ? 1 : 0;
}


int main()
{
	int num;//商品数量
	int sum;//背包可容纳总重量
	cin >> num >> sum;
	vector<int> weight;//商品的重量
	vector<int> price;//商品的价格

	cout << "请依次输入物品的重量：";
	weight.push_back(0);
	price.push_back(0);
	for (int i = 0; i < num; i++)
	{
		int tmp1;
		cin >> tmp1;
		weight.push_back(tmp1);//把重量的数据存入到数组中
	}
	cout << endl;

	cout << "请依次输入物品的价格：";
	for (int i = 0; i < num; i++)
	{
		int tmp2;
		cin >> tmp2;
		price.push_back(tmp2);//把价格的数据存入到数组中
	}
	cout << endl;

	cout << "总价值最大为：" << backpack(price, weight, sum, num) << endl;
	Trackback(weight, sum, num);
	cout << "最优值的解：";
	for (int i = 1; i < num + 1; i++)cout << flag[i] << " ";
	cout << endl;

	const char* a{ "ABCESFCSADEE" };
	const char* b{ "ABCCED" };
	bool c = hasPath(a, 3, 4, b);
	/*string s("((())");
	string s1(")()())");
	int i = longestValidParentheses1(s1);*/
	/*while (cin >> s)
	{

		int a1 = 0;
		char op1, op2, op3;
		if (!isdigit(s[0]) && s[0] != '-')
		{
			cerr << "input error" << endl;
			exit(1);
		}
		op1 = '+';
		int j = 0;
		while (op1 != '=')
		{			
			int a2 = 0;
			int symbol = 1;
			if (s[j] == '-')
			{
				symbol = -1;
				j++;
			}
			while (isdigit(s[j]) != 0)
			{				
				a2 = a2 * 10 + (s[j] - '0') ;
				++j;
			}
			op2 = s[j];
			a2 = symbol * a2;
			symbol = 1;
			++j;
			while (op2 == '*' || op2 == '/')
			{
				int a3 = 0;
				if (s[j] == '-')
				{
					symbol = -1;
					j++;
				}
				while (isdigit(s[j]) != 0)
				{					
					a3 = a3 * 10 + (s[j] - '0');
					++j;
				}
				a3 = symbol * a3;
				op3 = s[j];
				++j;
				if (op2 == '*')
					a2 *= a3;
				else if (op2 == '/')
					a2 /= a3;
				op2 = op3;
			}
			if (op1 == '+')
				a1 += a2;
			else if (op1 == '-')
				a1 -= a2;
			op1 = op2;
			
		}
		cout << a1 << endl;
	}*/
	return 0;
}
