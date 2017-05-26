#include <iostream>
using namespace std;

int countOne(const int N)
{	
	static int counter {0};
	
	if (N == 0)
		return counter;
	else{
		counter += N % 2;
		
		countOne(static_cast<int>(N/2));
	}
}
int main()
{
	int N {};
	
	cin >> N;
	
	cout<<countOne(N);
	return 0;
}