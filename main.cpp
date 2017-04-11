#include "csp.hpp"
#include "csp_algorithms.hpp"
#include<ctime>
int main()
{
	csp c(10);
	//c.print_adjacency_matrix();
	//c.print_adjacent();
	int start = clock();
	//cout << ac_3(&c) << endl;
	//cout << backtracking_forward_checking(&c) << endl;
	//backtracking(&c);
	cout  << min_conflicts(&c) << endl;
	int end = clock();
	cout << float(end-start)/(CLOCKS_PER_SEC) << endl;
	//cout  << min_conflicts(&c,1000) << endl;
	//c.print_assignment();
} 