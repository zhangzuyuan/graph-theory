/*
ʹ�õ���map��ͼ��������ǽڵ㲻���������Σ�����ڵ㲻������vector��ͼ�Ƚ��˷ѿռ�
point�����ÿ���ڵ��Ӧ�ı�
dis�����ÿ���ڵ㵽���ľ��룬������ǰ����ʲô
pending�Ǵ�����Ƿ�Ϊ�м�ڵ� 
exist ����� �Ƿ��Ѿ����м�ڵ�������

������
addedgeΪ��ӱ�˳������˵㣬
show()չʾ�������е㵽source��ľ��� 
showPath()չʾ����ĳ�㵽source ������·��·���� 
*/

#include<cstdio>
#include<iostream>
#include<map>
#include<set>
#include<queue>
using namespace std;
typedef int T;
class Graph
{
	private:
		
		map<int,set<pair<int,T>>> point;
		map<int,pair<T,int>> dis;
		map<int,bool> exist;
		priority_queue<pair<T,int>,vector<pair<T,int>>,greater<pair<T,int>>> pending; 
		
	public:
		void addedge(int x,int y,int z);//��ʼ�㣬��ֹ��ͱ�Ȩ 
		void dijkstra(int start);
		void dfs(int x);
		void show();
		void showPath(int x);
		
	private:
		void dfsPath(int x);
};
void Graph::addedge(int x,int y,T z)
{
	point[x].insert(pair<int,T> (y,z));
	dis[x].first=1000000;
	dis[y].first=1000000;
	dis[x].second=-1;
	dis[y].second=-1;
	exist[x]=exist[y]=false;
} 
void Graph::dfs(int x)
{
	for(set<pair<int,T>>::iterator it=point[x].begin();it!=point[x].end();it++)
	{
		cout<<it->second<<endl;
		dfs(it->first);
	}
}
void Graph::dijkstra(int start)
{
	dis[start].first=0;
	dis[start].second=-1;
	exist[start]=true;
	pending.push(pair<T,int> (0,start));
	while(!pending.empty())
	{
		pair<T,int> extend=pending.top();
		pending.pop();
		for(set<pair<int,T>>::iterator it=point[extend.second].begin();it!=point[extend.second].end();it++)
		{
			if(dis[it->first].first>dis[extend.second].first+it->second)
			{
				dis[it->first].first=dis[extend.second].first+it->second;
				int a=dis[it->first].first;
				int b=it->first;
				int c =extend.second;
				dis[it->first].second=extend.second;
				if(!exist[it->first])
				{
					exist[it->first]=true;
					pending.push(pair<T,int> (dis[it->first].first,it->first));
				}
			}
		}
	}
} 
void Graph::show()
{
	for(map<int,pair<T,int>>::iterator it=dis.begin();it!=dis.end();it++)
	{
		cout<<"source�㵽"<<it->first<<"�ľ���Ϊ:"<<it->second.first<<"��ǰ��Ϊ:"<<it->second.second<<endl; 
	}
}
void Graph::showPath(int x)
{
	dfsPath(x);
	cout<<endl;
}
void Graph::dfsPath(int x)
{
	cout<<x<<" ";
	if(dis[x].second==-1) return;	
	dfsPath(dis[x].second);
}
int main()
{
	Graph* graph = new Graph();
	graph->addedge(0,1,5);
	graph->addedge(0,2,2);
	graph->addedge(0,3,6);
	graph->addedge(1,4,1); 
	graph->addedge(2,1,1);
	graph->addedge(2,4,5);
	graph->addedge(2,3,3);
	graph->addedge(3,4,2); 
	//graph->addedge(0,1,15);
	//graph->addedge(1,3,20);
	//graph->addedge(1,2,50);
	//graph->addedge(2,10,2); 
	//graph->show();
	graph->dijkstra(0);
	graph->showPath(4);
	graph->show();
	return 0;
}
