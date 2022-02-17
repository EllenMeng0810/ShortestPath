#include <iostream>
#include <string>

using namespace std;

void shortestPath(int vertex, int sour, int dest, int matrix[20][20], int MaxC, int startC, int fuelS[], string city[])
{
	bool visited[20];     // 标记数组
	int dist[20];        // 源点到顶点 i 的最短距离
	int path[20];        // 记录最短路的路径
	int currC[20];
	int d[20];
	int p[20];
	int temp_d[20];

	if (fuelS[sour] == 1)
	{
		currC[sour] = MaxC;
	}
	else
	{
		currC[sour] = startC;
	}

	memset(visited, 0, sizeof(visited));  // 初始化标记数组
	visited[sour] = true;

	for (int i = 0; i < vertex; i++)
	{
		dist[i] = matrix[sour][i];
		path[i] = INT_MAX;
		if (dist[i] != INT_MAX)
		{
			path[i] = sour;
		}
	}

	int min;        // min cost权值最小
	int index = -1;  // min cost index 权值最小的下标(节点)

	for (int i = 1; i < vertex; i++)  // 找到源点到另外 vertex_num-1 个点的最短路径
	{
		min = INT_MAX;
		for (int j = 0; j < vertex; j++)
		{
			if (visited[j] == false && dist[j] < min)  // 找到权值最小
			{
				min = dist[j];
				index = j;
			}
		}

		if (visited[index] == false)
		{
			if (currC[path[index]] >= dist[index] - dist[path[index]])
			{
				if (fuelS[index] == 1)
				{
					currC[index] = MaxC;
				}
				else
				{
					currC[index] = currC[path[index]] - (dist[index] - dist[path[index]]);
				}
			}
			else
			{
				currC[path[index]] = currC[p[path[index]]] - temp_d[path[index]];
				path[path[index]] = p[path[index]];
				min = d[path[index]];
				index--;

				for (int i = index + 1; i < vertex; i++)
				{
					dist[i] = INT_MAX;
				}
			}
		}

		visited[index] = true;  // 该点已找到，进行标记

		for (int j = 0; j < vertex; j++)  // 更新 dist 数组
		{
			if (visited[j] == false && matrix[index][j] != INT_MAX) // 确保两点之间有边
			{
				if (matrix[index][j] + min < dist[j])
				{
					dist[j] = matrix[index][j] + min;
					path[j] = index;
				}
				else
				{
					d[j] = matrix[index][j] + min;
					p[j] = index;
					temp_d[j] = matrix[index][j];
				}
			}
		}
	}

	/*
	for (int j = 0; j < vertex; j++)
	{
		cout << dist[j] << ",";
	}
	cout << endl;

	for (int j = 0; j < vertex; j++)
	{
		cout << path[j] << ", ";
	}
	cout << endl;
	*/

	string origin = city[sour];
	string destination = city[dest];

	if (dest != sour)
	{
		cout << endl;
		cout << "The shorest path from " << origin << " to " << destination << ": " << endl;
		cout << destination;
		int t = path[dest];
		while (t != sour)
		{
			cout << " <-- " << city[t];
			t = path[t];
		}
		cout << " <-- " << origin << endl;
		cout << "The shortest distance is " << dist[dest] << endl;
	}
}


int main()
{
	cout << "Project3_Zhaoying Meng" << endl;
	cout << "Professor: Dr.Lin Chiu" << endl;
	cout << "COMP620-Q1FF" << endl;
	cout << "Apr 29, 2020" << endl;
	cout << endl;

	int vertex;      // 顶点数,城市数 6
	string city[20];    //城市名
	int matrix[20][20];//声明一个二维数组来存储邻接矩阵
	int fuelStation[20]; //声明一个一位数组来存储加油站 6
	string source;      //初始化源节点为0
	string destination; //初始化终点为0
	int fuelCapacity = 0; //初始化油箱油量为0
	int startFuel = 0;    //初始化油箱起始油量为0
	int number;
	int numID;
	int origin;
	int end;
	char flag;

	cout << "Enter the number of cities: " << endl;
	cin >> vertex;

	cout << endl;
	cout << "Enter the name of cities: " << endl;
	for (int i = 0; i < vertex; i++)
	{
		cin >> city[i];
	}

	cout << endl;
	cout << "Enter the Weighted Matrix for the graph: " << endl;
	for (int i = 0; i < vertex; i++)
	{
		for (int j = 0; j < vertex; j++)
		{
			cin >> number;
			matrix[i][j] = number;
			if (i == j)
			{
				matrix[i][j] = 0;
				continue;//跳过当前循环并开始下一次循环
			}
			if (matrix[i][j] == 0)
			{
				matrix[i][j] = INT_MAX;
			}
		}
	}

	cout << endl;
	cout << "Enter the fuel station identification separated by space :" << endl;
	cout << "(0 means No; 1 means Yes; the order corresponds to city order)" << endl;
	for (int i = 0; i < vertex; i++)
	{
		cin >> numID;
		fuelStation[i] = numID;
		//cout << fuelStation[i] << " " << endl;
	}

	do
	{
		cout << endl;
		cout << "Enter the source (choose from the name of cities): " << endl;
		cin >> source;
		//cout << "source: " << source << endl;

		for (int i = 0; i < vertex; i++)
		{
			if (source == city[i])
			{
				origin = i;
			}
		}

		cout << endl;
		cout << "Enter the destination (choose from the name of cities): " << endl;
		cin >> destination;
		//cout << "destination: " << destination << endl;

		for (int i = 0; i < vertex; i++)
		{
			if (destination == city[i])
			{
				end = i;
			}
		}

		cout << endl;
		cout << "Enter the tank max capacity: " << endl;
		cin >> fuelCapacity;
		//cout << "fuelCapacity: " << fuelCapacity << endl;

		cout << endl;
		cout << "Enter the starting fuel amount: " << endl;
		cin >> startFuel;
		//cout << "startFuel: " << startFuel << endl;

		shortestPath(vertex, origin, end, matrix, fuelCapacity, startFuel, fuelStation, city);

		cout << endl;
		cout << "Would you like to continue?(Y = yes or N = no): ";
		cin >> flag;
		if (flag == 'N' || flag == 'n')
		{
			cout << "Good Bye!!!" << endl;
		}
		cout << endl;

	} while (flag == 'Y' || flag == 'y');
	cout << endl;

	system("pause");
	return 0;
}
