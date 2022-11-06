/**
 * 实现朴素Prim算法，并分析其正确性和算法复杂度。
 * Prim算法的复杂度主要依赖于点，适合点少边多的稠密图
 * */
#include <iostream>
#include <vector>
using namespace std;

void prim(vector<vector<int>>& VGraph, vector<int>& lowcost, vector<int>& closest, vector<bool>& visited)
{
    int size = lowcost.size(); //M
    visited[0] = true;  //从顶点0出发构造最小生成树
    for (int i = 1; i < size; i++)
    {
        lowcost[i] = VGraph[0][i];  //初始化为顶点0到其他顶点i的权
        closest[i] = 0;  //i节点依附的节点
        visited[i] = false;
    }
    int weight = 0; //最小生成树权值

    cout << "输出生成树上各条边：" << endl;
    //m-1条边，循环m-1次，每次找到一条边
    for (int i = 0; i < size-1; i++)
    {
        int min = 99999;
        int index = 1;
        //寻找具有最小代价的边
        for (int j = 0; j < size; j++)
        {
            //从刚并入U的顶点到其他点j (j必须未被访问过)的权中选出具有最小代价的边
            if (lowcost[j] < min && !visited[j])
            {
                min = lowcost[j];
                index = j;
            }
        }
        weight += min;
        //打印每次选择的边
        cout << "(" << closest[index] << "," << index << ")" << endl;

        visited[index] = true;
        //因为新加入了index点,所以要查找新加入的index点到未在S中的点K中的权值是不是可以因此更小
        for (int j = 1; j < size; j++)
        {
            if ((VGraph[index][j] < lowcost[j]) && (!visited[j]))  //lowcost表示从已知树到某一点所需付出的最小权值
            {
                lowcost[j] = VGraph[index][j]; //更新刚加入的index点到其他j点的权值
                closest[j] = index;  //将j节点依附的节点修改为index
            }
        }
    }
    cout << "\n最小生成树权值为:" << weight << endl;
}
int main()
{
    int M, N;   //M为顶点数  N为边数
    cin >> M >> N;
    vector<vector<int>> VGraph(M,vector<int>(M)); //图的邻接矩阵
    vector<int> lowcost(M);  //刚选中并入U的顶点到其他顶点的权,初始为顶点0到其他点的权，因为从0出发
    vector<int> closest(M);  //记录每个节点依附的具有最小代价的节点,由此可得到最小生成树上的所有边
    vector<bool> visited(M);  //标记节点是否已访问
    //数组表示  邻接矩阵初始化
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++)
        {
            VGraph[i][j] = 99999;
        }
    }
    for (int i = 0; i < N; i++)
    {
        int a, b;  //两个顶点
        cin >> a >> b;
        int length;  //权
        cin >> length;
        VGraph[a][b] = VGraph[b][a] = length; //初始化图各条边
    }
    prim(VGraph, lowcost, closest, visited);
}
// 0 1 6 0 2 1 0 3 5 1 2 5 1 4 3 2 3 5 2 4 6 2 5 4 3 5 2 4 5 6
