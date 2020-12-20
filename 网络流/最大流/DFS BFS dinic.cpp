/*
emmmm
dfs��bfs���Ǳ����������������
���ǻᷢ�������ж�����һЩû���õļ���
����˵bfs��Ҫÿһ�㶼��չ
��dfs�������ÿһ��ı߼���ܶ��
�����ʹ���������ٶ�
��Ȼ�Ѿ�֪���˸�ͼ��Ϊ�ֲ�ͼ����ô�ǲ��ǾͿ����ȷֲ�Ȼ��
��ÿһ������һ�����dfs���������Դ�����bfs��չ������ÿһ��bfs��Ҫ��չȫ��ǳ��˷�ʱ�䣬���������ͻή���� 
Ҳ����dfs��ȥ������ͬ�����ı��� 
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
		int *deep;//���� 
		int n;
		queue<int> q;
		
	public:
		Graph(int n);
		~Graph();
		void addedge(int x,int y,T c);
		T maxFlow(int Vs,int Vt);//VsΪԭ�㣬VtΪ��� 
		
	private:
		int bfs(int Vs,int Vt); 
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
	deep = new int[n+1];
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
	delete[] deep;
}
void Graph::addedge(int x,int y,T c)
{
	if(x==y) return;
	capacity[x][y]+=c;
}
T Graph::maxFlow(int Vs,int Vt)
{
	int sumflow=0;
	while(bfs(Vs,Vt)!=-1)
	{
		for(;;)
		{
			T tmp=dfs(Vs,Vt,100000000);
			if(tmp==0) break;
			sumflow+=tmp;
		}
	} 
	return sumflow;
} 
int Graph::bfs(int Vs,int Vt)
{
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;++i) deep[i]=-1;
	deep[Vs]=0;
	q.push(Vs);
	for(;!q.empty();)
	{
		int extend=q.front();
		q.pop();
		for(int i=1;i<=n;++i)
		{
			if(i!=Vs&&capacity[extend][i]>0&&deep[i]==-1)
			{
				deep[i]=deep[extend]+1;
				q.push(i);
			}
		}
	}
	return deep[Vt];
} 
T Graph::dfs(int extend,int Vt,int f)
{
	if(extend==Vt) return f;
	for(int i=1;i<=n;++i)
	{
		if(deep[extend]+1==deep[i]&&capacity[extend][i]>0)
		{
			T tmp=dfs(i,Vt,min(f,capacity[extend][i]));
			if(tmp>0)
			{
				capacity[extend][i]-=tmp;
				capacity[i][extend]+=tmp;
				return tmp;
			}
			
		}
	}
	return 0;
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
