#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;

class csp
{
    public:
        //void create_matrix(int n);
        //void create_list(int n);
        csp(int n);
        void print_assignment();
        void print_adjacency_matrix();
        void print_adjacent();
        vector<vector<int> > adjacency_matrix;
        vector<vector<int> > adjacent;
        int no_nodes;
        vector<int> assignment;
        vector<vector<int> > domain;

};
csp::csp(int n)
{
	no_nodes = n;
	vector<int> v(n,0);
	int i,j;
	for(i=0;i<n;i++)
	{
		adjacency_matrix.push_back(v);
	}
	int count=n;
	while(count--)
	{
		i = rand()%n;
		j = rand()%n;
		adjacency_matrix[i][j] = 1;
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
				adjacency_matrix[i][j] = 0;
			if(adjacency_matrix[i][j]==1)
				adjacency_matrix[j][i] = 1;
		}
	}
	for(i=0;i<n;i++)
	{
		vector<int> Row;
		for(j=0;j<n;j++)
		{
			if(i!=j && adjacency_matrix[i][j])
				Row.push_back(j);
		}
		adjacent.push_back(Row);
	}
	for(i=0;i<n;i++)
	{
		assignment.push_back(-1);
	}
	vector<int> d;
	d.push_back(0);
	d.push_back(1);
	d.push_back(2);
	for(i=0;i<n;i++)
	{
		domain.push_back(d);
	}
}
void csp::print_assignment()
{
	
	int i,n=no_nodes;
	for(i=0;i<n;i++)
	{
		//cout << assignment[i] << endl;
		
		if(assignment[i]==0)
		{
			cout << i << ": RED" << endl;
		}
		else if(assignment[i]==1)
		{
			cout << i << ": GREEN" << endl;
		}
		else if(assignment[i]==2)
		{
			cout << i << ": BLUE" << endl;
		}
		else
		{
			cout << i << ": ERROR" << endl;
		}
		
	}
}
void csp::print_adjacency_matrix()
{
	int i,j,n=no_nodes;
	for(i=0;i<n;i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << adjacency_matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void csp::print_adjacent()
{
	vector<vector<int> >::iterator row ;
	vector<int>::iterator col;
	for (row = adjacent.begin(); row != adjacent.end(); row++)
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
    		cout << *col << " ";
    	}
    	cout << endl;
	}
}