#include<stdio.h>
#include<malloc.h>

#define MAX 100
#define MAXNUM 2147483647 

typedef struct EdgeType{
	
	int verNUM;//边的起点和终点 
	int edgeNUM;//边的权值	
}type;


void Adjacency(int ar[][MAX], int ori, int side);//输入数据转换为邻接矩阵
int Dijskra(int ar[][MAX], int S[], int dith[], int path[], type infor);//迪杰斯克拉算法
void Show(int S[], int dith[], int path[], type infor, int begin);//展示各个最短路径的具体路径 

int main()
{
	int S[MAX], U[MAX], dist[MAX], path[MAX], adj[MAX][MAX];
	int ver, edge, i, j, begin; 
	type infor;
	
	printf("请输入顶点个数和边的个数：");
	scanf("%d %d", &ver, &edge);
	
	infor.verNUM = ver;
	infor.edgeNUM = edge;
	
	for(i = 0;i < ver;i++)//数组、矩阵初始化 
	{
		path[i] = -1;
		dist[i] = MAXNUM;
		S[i] = 0; 
		
		for(j = 0;j < ver;j++)
			adj[i][j] = MAXNUM;
		adj[i][i] = 0;
	}
	
	Adjacency(adj, ver, edge);
	begin = Dijskra(adj, S, dist, path, infor);
	Show(S, dist, path, infor, begin); 
	
}
void Adjacency(int adj[MAX][MAX], int ori, int side)//输入数据转换为邻接矩阵 
{
	int ver, edge, ver1, edge2, weight, i, j;
	
	for(i = 0;i < side;i++)
	{
	
		printf("请输入边的起点和终点以及边的权值：");
		scanf("%d %d %d",&ver, &ver1, &weight);
		if(ver < 0||ver >= ori||ver1 < 0||ver1 >= ori)//判断点是否在范围内 
		{
			printf("请输入起点与终点的值在0-%d\n",side-1);
			continue;
		}
		adj[ver][ver1] = weight;
	}
	for(i = 0;i < ori;i++)
	{	
		for(j = 0;j < ori;j++)
		{
			if(adj[i][j] == MAXNUM)
				printf(" ∞");
			else
				printf(" %d",adj[i][j]);	
		}			
		printf("\n");
	}
}
int Dijskra(int adj[MAX][MAX], int S[MAX], int dist[MAX], int path[MAX], type infor)//Dijskra算法核心 
{
	int i, j, k, begin, med, mid;
	int som[infor.verNUM];
	
	printf("请输入开始的源点：");
	scanf("%d",&begin);
	
	for(i = 0;i < infor.verNUM;i++)//配置dist数组与path数组 
	{
		if(adj[begin][i] != MAXNUM)	
			path[i] = begin; 
		dist[i] = adj[begin][i];
		S[begin] = 1;
	}	
			
	for(i = 0;i < infor.verNUM;i++)//Dijskra算法核心 
	{
		mid = 0;
		med = MAXNUM;
		for(j = 0;j < infor.verNUM;j++)
		{
			if(med > dist[j]&&S[j] == 0)
			{
				med = dist[j];
				mid = j;		
			}
		}
		if(med != MAXNUM)//该判断防止出现某些点无法到达仍会计算的情况 
		{		
			S[mid] = 1;	
			for(j = 0;j < infor.verNUM;j++)
			{
				if(dist[mid] + adj[mid][j] < dist[j]&&adj[mid][j] != 0&&adj[mid][j] != MAXNUM)
				{
					path[j] = mid;
					dist[j] = dist[mid] + adj[mid][j];
				}
			}
		}
	}
	
	printf("最终的dist数组：");
	for(i = 0;i < infor.verNUM;i++)
		printf("%2d ",dist[i]);
	printf("\n");
	printf("最终的path数组：");
	for(i = 0;i < infor.verNUM;i++)
		printf("%2d ",path[i]);
	printf("\n");
	return begin;
	
}
void Show(int S[MAX], int dist[MAX], int path[MAX], type infor, int begin)//展示路径函数 
{
	int i, j, som;
	int xjm[MAX];//一个简单的栈 
	
	printf(" 从源点到各个点的路径为：\n");
	for(i = 0;i < infor.verNUM;i++)
	{
		if(path[i] != -1&&i != begin)
		{
			printf("  路径长度：%2d   ",dist[i]);
			printf("%d -> %d: ", begin, i);
			
			som = i;
			j = 0;
			
			do{
				xjm[j] = som;
				som = path[som];
				j++;
			}while(som != begin);//入栈 
			
			xjm[j] = begin; 
	
			while(j >= 0)//将由path数组得到的路径出栈 
			{
				printf(" %d ",xjm[j]);
				j--;				
			}			
			printf("\n");
		}
	}
}
