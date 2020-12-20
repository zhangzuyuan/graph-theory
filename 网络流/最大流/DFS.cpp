/*
首先考虑dfs做法
不就是每次都进行找到增广路进行修改吗
那么我每次都dfs到终点，改不就完了 
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
		T *pre; //每个点是否已经走过 
		int n;
		queue<int> q;
		
	public:
		Graph(int n);
		~Graph();
		void addedge(int x,int y,T c);
		T maxFlow(int Vs,int Vt);//Vs为原点，Vt为汇点 
		
	private:
		int dfs(int Vs,int Vt,T f);
		
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
	for(int i=1;i<=n;++i) pre[i]=0;
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
	T sumflow=0;
	for(;;)
	{
		for(int i=1;i<=n;++i) pre[i]=0;
		int tmp=dfs(Vs,Vt,100000000);
		if(tmp==0) return sumflow;
		sumflow += tmp;
	}
} 
T Graph::dfs(int extend,int Vt,T f)
{
	if(extend==Vt) return f;//到终点了
	int bo=0;
	for(int i=1;i<=n;++i)
	{
		if(capacity[extend][i]>0&&pre[i]==0)
		{
			bo=1;
			pre[i]=1;
			int tmp = dfs(i,Vt,min(f,capacity[extend][i]));
			if(tmp>0)
			{
				capacity[extend][i]-=tmp;
				capacity[i][extend]+=tmp;
				return tmp;
			}
		}
	} 
	if(bo==0) return 0;
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
