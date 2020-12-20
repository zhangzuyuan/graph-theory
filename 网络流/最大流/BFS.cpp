/*
在做dfs时候，发现了走过的点其实是不再走了
那么这就很像是bfs的每层进行搜索，
那么就试一下bfs的做法吧，
结果是可行的，
同时又发现bfs做法把网络流分层了，这样的话
很像是二分图匹配问题，这就解决了为什么网络流可以进行二分图匹配
就是因为匹配问题都是层状结构，所以可以进行匹配
 
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
		T *pre; //记录每个点的前驱寻找路径 
		int n;
		queue<int> q;
		
	public:
		Graph(int n);
		~Graph();
		void addedge(int x,int y,T c);
		T maxFlow(int Vs,int Vt);//Vs为原点，Vt为汇点 
		
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
	T sumflow=0;//最大流
	T increase=0;//增广值
	for(;increase=bfs(Vs,Vt)!=-1;)
	{
		int tmp=Vt;//寻找路径
		while(tmp!=Vs)
		{
			int last= pre[tmp];
			//增广路径 
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
			if(i!=Vs&&capacity[extend][i]>0&&pre[i]==-1)//还能继续增广的，且沿着链继续走的 
			{
				pre[i]=extend;
				flow[i]=min(capacity[extend][i],flow[extend]);
				q.push(i);
			}
		}
	}
	if(pre[Vt]==-1)//无增广路
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
