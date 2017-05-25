// created by Penghua Li
// DS&AA C++ Ch1 Ex1

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
void bubbleSort(T* arr, size_t N)
{
	for (size_t i = 0; i < N - 1; ++i)
	{
		for (size_t j = 0; j < N - i - 1; ++j)
		{
			if ( arr[j] > arr[j+1] )
				swap(arr[j+1], arr[j]);
		}
	}
}


int main()
{
	size_t N {};
	
	cin >> N;
	
	int* arr = new int[N];
	
	size_t k = N / 2;
	
	srand(time(0));
	
	for ( size_t i = 0; i < N; i++)
	{
		arr[i] = rand();
	}
	
	clock_t begin = clock();
	
	bubbleSort(arr, N);
	
	clock_t end = clock();
	
	clock_t spentTime = end - begin;
	
	cout << N << " values." << "\t";
	
	cout << k << "th largest value is " << arr[k] << "\t";
	
	cout <<"spending time " << spentTime << " nsce" << endl;
	
	delete[] arr;
	
	return 0;
}
