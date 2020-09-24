#include<stdio.h>
#include<malloc.h>

#define MAX 100
#define MAXNUM 2147483647 

typedef struct EdgeType{
	
	int verNUM;//�ߵ������յ� 
	int edgeNUM;//�ߵ�Ȩֵ	
}type;


void Adjacency(int ar[][MAX], int ori, int side);//��������ת��Ϊ�ڽӾ���
int Dijskra(int ar[][MAX], int S[], int dith[], int path[], type infor);//�Ͻ�˹�����㷨
void Show(int S[], int dith[], int path[], type infor, int begin);//չʾ�������·���ľ���·�� 

int main()
{
	int S[MAX], U[MAX], dist[MAX], path[MAX], adj[MAX][MAX];
	int ver, edge, i, j, begin; 
	type infor;
	
	printf("�����붥������ͱߵĸ�����");
	scanf("%d %d", &ver, &edge);
	
	infor.verNUM = ver;
	infor.edgeNUM = edge;
	
	for(i = 0;i < ver;i++)//���顢�����ʼ�� 
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
void Adjacency(int adj[MAX][MAX], int ori, int side)//��������ת��Ϊ�ڽӾ��� 
{
	int ver, edge, ver1, edge2, weight, i, j;
	
	for(i = 0;i < side;i++)
	{
	
		printf("������ߵ������յ��Լ��ߵ�Ȩֵ��");
		scanf("%d %d %d",&ver, &ver1, &weight);
		if(ver < 0||ver >= ori||ver1 < 0||ver1 >= ori)//�жϵ��Ƿ��ڷ�Χ�� 
		{
			printf("������������յ��ֵ��0-%d\n",side-1);
			continue;
		}
		adj[ver][ver1] = weight;
	}
	for(i = 0;i < ori;i++)
	{	
		for(j = 0;j < ori;j++)
		{
			if(adj[i][j] == MAXNUM)
				printf(" ��");
			else
				printf(" %d",adj[i][j]);	
		}			
		printf("\n");
	}
}
int Dijskra(int adj[MAX][MAX], int S[MAX], int dist[MAX], int path[MAX], type infor)//Dijskra�㷨���� 
{
	int i, j, k, begin, med, mid;
	int som[infor.verNUM];
	
	printf("�����뿪ʼ��Դ�㣺");
	scanf("%d",&begin);
	
	for(i = 0;i < infor.verNUM;i++)//����dist������path���� 
	{
		if(adj[begin][i] != MAXNUM)	
			path[i] = begin; 
		dist[i] = adj[begin][i];
		S[begin] = 1;
	}	
			
	for(i = 0;i < infor.verNUM;i++)//Dijskra�㷨���� 
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
		if(med != MAXNUM)//���жϷ�ֹ����ĳЩ���޷������Ի�������� 
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
	
	printf("���յ�dist���飺");
	for(i = 0;i < infor.verNUM;i++)
		printf("%2d ",dist[i]);
	printf("\n");
	printf("���յ�path���飺");
	for(i = 0;i < infor.verNUM;i++)
		printf("%2d ",path[i]);
	printf("\n");
	return begin;
	
}
void Show(int S[MAX], int dist[MAX], int path[MAX], type infor, int begin)//չʾ·������ 
{
	int i, j, som;
	int xjm[MAX];//һ���򵥵�ջ 
	
	printf(" ��Դ�㵽�������·��Ϊ��\n");
	for(i = 0;i < infor.verNUM;i++)
	{
		if(path[i] != -1&&i != begin)
		{
			printf("  ·�����ȣ�%2d   ",dist[i]);
			printf("%d -> %d: ", begin, i);
			
			som = i;
			j = 0;
			
			do{
				xjm[j] = som;
				som = path[som];
				j++;
			}while(som != begin);//��ջ 
			
			xjm[j] = begin; 
	
			while(j >= 0)//����path����õ���·����ջ 
			{
				printf(" %d ",xjm[j]);
				j--;				
			}			
			printf("\n");
		}
	}
}
