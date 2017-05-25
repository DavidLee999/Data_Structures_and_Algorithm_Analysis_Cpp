#include <iostream>
#include <string>
using namespace std;

bool isSwap(const string str, const int begin, const int end)
{
	for ( int i = begin; i < end; ++i)
	{
		if (str[i] == str[end])
			return false;
	}
	
	return true;
}
void permute (const string str, int low, int high)
{
	string strCopy = str;
	
	if (low == high )
		cout << str << endl;
	
	for ( int i = low; i <= high; ++i)
	{
		if(isSwap(strCopy, low, i))
		{
			swap(strCopy[low], strCopy[i]);
			permute(strCopy, low + 1, high);
			swap(strCopy[low], strCopy[i]);
		}
	}
}

void permute ( const string str )
{
	permute( str, 0, str.size() - 1 );
}
int main()
{
	string str {};
	
	cin>>str;
	
	cout<<endl;

	permute(str);
}