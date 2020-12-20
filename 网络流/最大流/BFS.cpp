/*
����dfsʱ�򣬷������߹��ĵ���ʵ�ǲ�������
��ô��ͺ�����bfs��ÿ�����������
��ô����һ��bfs�������ɣ�
����ǿ��еģ�
ͬʱ�ַ���bfs�������������ֲ��ˣ������Ļ�
�����Ƕ���ͼƥ�����⣬��ͽ����Ϊʲô���������Խ��ж���ͼƥ��
������Ϊƥ�����ⶼ�ǲ�״�ṹ�����Կ��Խ���ƥ��
 
*/

#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
typedef int T;
class Graph{
	private:
		T **capacity;
		T *flow;
		T *pre; //��¼ÿ�����ǰ��Ѱ��·�� 
		int n;
		queue<int> q;
		
	public:
		Graph(int n);
		~Graph();
		void addedge(int x,int y,T c);
		T maxFlow(int Vs,int Vt);//VsΪԭ�㣬VtΪ��� 
		
	private:
		int bfs(int Vs,int Vt);
		
};
Graph::Graph(int n)
{
	this->n=n;
	capacity = new T*[n+1];
	for(int i=0;i<=n;i++)
	{
		capacity[i] = new T[n+1];
	}
	flow=new T[n+1];
	pre =new T[n+1];
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
		{
			capacity[i][j]=0;
		}
	}
}
Graph::~Graph()
{
	for(int i=0;i<=n;++i)
	{
		delete[] capacity[i]; 
	}
	delete[] capacity;
	delete[] flow;
	delete[] pre;
}
void Graph::addedge(int x,int y,T c)
{
	if(x==y) return;
	capacity[x][y]+=c;
}
T Graph::maxFlow(int Vs,int Vt)
{
	T sumflow=0;//�����
	T increase=0;//����ֵ
	for(;increase=bfs(Vs,Vt)!=-1;)
	{
		int tmp=Vt;//Ѱ��·��
		while(tmp!=Vs)
		{
			int last= pre[tmp];
			//����·�� 
			capacity[last][tmp]-=increase;
			capacity[tmp][last]+=increase;
			tmp= last;
		} 
		sumflow+=increase;
	} 
	
	return sumflow;
} 
int Graph::bfs(int Vs,int Vt)
{
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;++i) pre[i]=-1;
	pre[Vs]=0;
	flow[Vs]=999999999;
	q.push(Vs);
	while(!q.empty())
	{
		int extend = q.front();
		q.pop();
		if(extend==Vt)
			break;
		for(int i=1;i<=n;++i)
		{
			if(i!=Vs&&capacity[extend][i]>0&&pre[i]==-1)//���ܼ�������ģ��������������ߵ� 
			{
				pre[i]=extend;
				flow[i]=min(capacity[extend][i],flow[extend]);
				q.push(i);
			}
		}
	}
	if(pre[Vt]==-1)//������·
		return -1;
	else
		return flow[Vt]; 
}
int main()
{
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	Graph *graph = new Graph(n);
	for(int i=1;i<=m;++i)
	{
		int x,y,z;
		cin>>x>>y>>z;
		graph->addedge(x,y,z);
	}
	cout<<graph->maxFlow(s,t);
	
	return 0;
} 
