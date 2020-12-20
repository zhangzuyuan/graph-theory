#include<cstdio>
#include<iostream>
#include<map>
#include<set>
#include<queue>
using namespace std;
typedef int T;
class unionFind
{
	private:
		map<int,int> father;
	public:
		void add(int x);	
		int find_father(int x);
		bool unionFather(int x,int y);
	private:
		int findFather(int x);
};
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
class Graph
{
	private:
		map<int,set<pair<int,T>>> point;
		struct edge{
			int x;
			int y;
			T length=0;
			friend bool operator < (const edge x,const edge y){
				return x.length>y.length;
			} 
		};
		vector<edge> Edge;
		priority_queue<edge> q;
		unionFind *unionFindSet = new unionFind();
		
	public:
		void addedge(int x,int y,T z);
		T kruskal();
};
void Graph::addedge(int x,int y,T z)
{
	point[x].insert(pair<int,T>(y,z));
	point[y].insert(pair<int,T>(x,z));
	edge tmp;
	tmp.x=x;tmp.y=y;tmp.length=z;
	Edge.push_back(tmp);
	q.push(tmp);
	unionFindSet->add(x);
	unionFindSet->add(y);
}
T Graph::kruskal()
{
	int num=0;
	T ans=0;
	while(q.empty()==false)
	{
		edge tmp=q.top();
		q.pop();
		if(unionFindSet->unionFather(tmp.x,tmp.y)){
			num++;
			ans+=tmp.length;
		}
		if(num==Edge.size()-1) break;
	}
	return ans;
}
int main()
{
	Graph *graph=new Graph();
	graph->addedge(1,2,12);
	graph->addedge(1,6,16);
	graph->addedge(1,7,14);
	graph->addedge(2,3,10);
	graph->addedge(2,6,7);
	graph->addedge(3,6,6);
	graph->addedge(3,5,5);
	graph->addedge(3,4,3);
	graph->addedge(4,5,4);
	graph->addedge(5,6,2);
	graph->addedge(5,7,8);
	graph->addedge(6,7,9);
	
	T ans=0;
	ans = graph->kruskal();
	cout<<ans<<endl; 
	return 0;
} 
