#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <climits>
using namespace std;
bool is_assigned(csp *c)
{
	int i,n = c->no_nodes;
	for(i=0;i<n;i++)
	{
		if(c->assignment[i]==-1)
			return 0;
	}
	return 1;
}
int pick_unassigned_variable(csp *c)
{
	int i,n = c->no_nodes;
	for(i=0;i<n;i++)
	{
		if(c->assignment[i]==-1)
			return i;
	}

}
void backtracking(csp *c)
{
	//cout << "Assignments: " << c->assignment[0] << " " << c->assignment[1] << " " << c->assignment[2] << endl;
	//cout << "is_assigned: " << is_assigned(c) << endl;
	if(is_assigned(c))
		return;
	int unassigned = pick_unassigned_variable(c);
	//cout << "unassigned: " << unassigned << endl;
	vector<int>::iterator it;
	bool flag;
	for(it=c->domain[unassigned].begin();it!=c->domain[unassigned].end();it++)
	{
		c->assignment[unassigned] = *it;
		//cout << c->assignment[unassigned] << endl;
		flag = 1;
		vector<int>::iterator neighbours;
		for(neighbours=c->adjacent[unassigned].begin();neighbours!=c->adjacent[unassigned].end();neighbours++)
		{
			if(c->assignment[unassigned]==c->assignment[*neighbours])
			{
				flag = 0;
				c->assignment[unassigned] = -1;
				break;
			}
		}
		if(flag)
		{
			backtracking(c);
			break;
		}
	}
	//cout << "end" << endl;
	return;
}
bool check_consistency(int u,csp *c,int x)
{
	vector<int>::iterator neighbours;
	for(neighbours=c->adjacent[u].begin();neighbours!=c->adjacent[u].end();neighbours++)
	{
		if(x==c->assignment[*neighbours])
			return 0;
	}
	return 1;

}
bool backtracking_forward_checking(csp *c)
{
	if(is_assigned(c))
		return 1;
	int unassigned = pick_unassigned_variable(c);
	//cout << "unassigned: " << unassigned << endl;
	vector<int>::iterator it;
	bool flag;
	for(it=c->domain[unassigned].begin();it!=c->domain[unassigned].end();it++)
	{
		if(check_consistency(unassigned,c,*it))
		{
			c->assignment[unassigned] = *it;
			//vector<vector<int> > domain;
			//domain = c->domain;
			vector<int>::iterator neighbours;
			for(neighbours=c->adjacent[unassigned].begin();neighbours!=c->adjacent[unassigned].end();neighbours++)
			{
				if(c->assignment[*neighbours]==-1)
				{
					vector<int>::iterator n;
					for(n=c->adjacent[*neighbours].begin();n!=c->adjacent[*neighbours].end();n++)
					{
						c->domain[*neighbours].erase(remove(c->domain[*neighbours].begin(),c->domain[*neighbours].end(),c->assignment[*n]),c->domain[*neighbours].end());
					}
				}
			}
			bool empty=0;
			for(neighbours=c->adjacent[unassigned].begin();neighbours!=c->adjacent[unassigned].end();neighbours++)
			{
				if(c->domain[*neighbours].size()==0)
				{
					empty = 1;
					break;
				}
			}
			if(!empty)
			{
				bool result = backtracking_forward_checking(c);
				if(result)
					return result;
			}
			c->assignment[unassigned] = -1;

		}
	}
	return 0;
}
bool check_assignment(csp *c)
{
	int i,n = c->no_nodes;
	vector<int>::iterator it;
	for(i=0;i<n;i++)
	{
		for(it=c->adjacent[i].begin();it!=c->adjacent[i].end();it++)
		{
			if(c->assignment[i]==c->assignment[*it])
				return 0;
		}
	}
	return 1;
}
int Conflicts(csp *c,int var)
{
	int i,val,min=INT_MAX,count;
	vector<int>::iterator it;
	for(i=0;i<3;i++)
	{
		count=0;
		for(it=c->adjacent[var].begin();it!=c->adjacent[var].end();it++)
		{
			if(c->assignment[var]==c->assignment[*it])
				count++;
		}
		if(count<min)
		{
			min = count;
			val = i;
		}
	}
	return val;
}
bool min_conflicts(csp *c)
{
	int i,n = c->no_nodes;
	int max_steps = n;
	for(i=0;i<n;i++)
	{
		c->assignment[i] = rand()%3;
	}
	for(i=0;i<max_steps;i++)
	{
		if(check_assignment(c))
			return 1;
		int var = rand()%n;
		int value = Conflicts(c,var);
		c->assignment[var] = value;
	}
	return 0;
}
bool revise(csp *c, int Xi, int Xj)
{
	bool revised=false;
	vector<int>::iterator it;
	for(it=c->domain[Xi].begin(); it!=c->domain[Xi].end();it++)
	{
		vector<int>::iterator t;
		bool flag = 0;
		for(t=c->domain[Xj].begin(); t!=c->domain[Xj].end();t++)
		{
			if(*it!=*t)
			{
				flag = 1;
				break;
			}
		}
		if(!flag)
		{
			c->domain[Xi].erase(remove(c->domain[Xi].begin(),c->domain[Xi].end(),*it),c->domain[Xi].end());
			revised = true;
		}
	}
	return revised;
}

bool ac_3(csp *c)
{
	int i,j;
	int n = c->no_nodes;
	pair<int,int> arc;
	queue<pair<int,int> > queue;
	for(i=0;i<n;i++)
	{
		arc.first = i;
		vector<int>::iterator it;
		for(it=c->adjacent[i].begin();it!=c->adjacent[i].end();it++)
		{
			arc.second = *it;
			queue.push(arc);
		}
	}
	while(!queue.empty())
	{
		arc = queue.front();
		int x = arc.first;
		int y = arc.second;
		queue.pop();
		vector<int>::iterator it;
		if(revise(c,x,y))
		{
			if(c->domain[x].size()==0)
				return false;
			for(it=c->adjacent[x].begin();it!=c->adjacent[x].end();it++)
			{
				if(*it!=y)
				{
					pair<int,int> e;
					e.first = *it;
					e.second = x;
					queue.push(e);
				}
			}
		}
	}
	return true;
	
}