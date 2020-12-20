/*

*/ 
#include<iostream>
#include<cstdio>
#include<map>
#include<cstdio>
#include<set> 
#include<stack>
using namespace std;
typedef int T;
class unionFind
{
	private:
		map<int,int> father;
	public:
		void clear();
		void add(int x);	
		int find_father(int x);
		bool unionFather(int x,int y);
	private:
		int findFather(int x);
};
void unionFind::clear()
{
	for(map<int,int>::iterator it=father.begin();it!=father.end();it++)
	{
		it->second=it->first;
	}
}
void unionFind::add(int x)
{
	father[x]=x;
}
int unionFind::find_father(int x)
{
	return findFather(x);
}
int unionFind::findFather(int x)
{
	if(father[x]!=x) return father[x] = findFather(father[x]);
	return father[x];
}
bool unionFind::unionFather(int x,int y)
{
	int r1=findFather(x);
	int r2=findFather(y); 
	if(r1==r2)
	{
		return 0;//不能合并 
	}
	else 
	{
		father[r2]=r1;
		return 1;//可以合并 
	}
}


class Graph{
	private:
		int n;
		T **points;
		int *du;
		unionFind *unionFindSet = new unionFind();
		
		stack<int> ans;
	
	public:
		Graph(int n);
		~Graph();
		void addedge(int x,int y,T z);
		void fleury();
		void show();
	private:
		void dfs(int x);

};
Graph::Graph(int n)
{
	this->n=n;
	points=new T*[n+1];
	for(int i=0;i<=n;++i)
	{
		points[i]=new T[n+1];
	}
	du=new int[n+1];
	for(int i=1;i<=n;++i)
	{
		du[i]=0;
		for(int j=1;j<=n;++j)
		{
			points[i][j]=0;
		} 
	}
}
Graph::~Graph()
{
	for(int i=0;i<=n;++i)
	{
		delete points[i];
	}
	delete du;
}
void Graph::addedge(int x,int y,T z)
{
	points[x][y]=z;
	points[y][x]=z;
	du[x]++;
	du[y]++;
}
void Graph::fleury()
{
	int flag=1;
	int sum=0;
	for(int i=1;i<=n;++i)
	{
		if(du[i]%2==1)
		{
			flag=i;
			sum++;
		} 
	}
	if(sum==0||sum==2)
	{
		dfs(flag);
	} 
} 
void Graph::dfs(int x)
{
	ans.push(x); 
	for(int i=1;i<=n;i++)
	{
		if(points[x][i]>0)
		{
			points[x][i]=0;
			points[i][x]=0;
			du[x]--;
			du[i]--;
			unionFindSet->clear();
			for(int q=1;q<=n;++q)
			{
				for(int w=1;w<=n;++w)
				{
					if(points[q][w]>0)
					{
						unionFindSet->unionFather(q,w);
					}
				}
			}
			int flag=0;
			int r1=0;
			int r2;
			for(int q=1;q<=n;++q)
			{
				
				if(du[q]>0)
				{
					r2=unionFindSet->find_father(q);
				}
				if(r1==0) r1=r2;
				else if(r1!=r2) 
				{
					flag=1;
					break;
				}
			}
			if(flag==0) dfs(i);
			else if(flag==1)
			{
				points[x][i]=1;
				points[i][x]=1;
				du[x]++;
				du[i]++;
			}
		}
	} 
}
void Graph::show()
{
	
	while(ans.empty()==false)
	{
		cout<<ans.top()<<" ";
		ans.pop();
	}
}
int main()
{
	Graph *graph=new Graph(7);
	graph->addedge(1,4,1);
	graph->addedge(1,5,1);
	graph->addedge(2,5,1);
	graph->addedge(2,6,1);
	graph->addedge(2,4,1);
	graph->addedge(2,7,1);
	graph->addedge(3,7,1);
	graph->addedge(3,4,1);
	graph->addedge(4,6,1);
	graph->addedge(5,6,1);
	graph->addedge(5,7,1);
	graph->addedge(6,7,1);
	graph->fleury();
	graph->show();
	return 0;
} 
