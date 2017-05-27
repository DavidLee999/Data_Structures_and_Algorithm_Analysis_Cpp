#include <iostream>
#include <initializer_list>
using namespace std;

int main()
{
	initializer_list<int> a {1,2,3,4};
	
	cout << a.size();
	return 0;
}