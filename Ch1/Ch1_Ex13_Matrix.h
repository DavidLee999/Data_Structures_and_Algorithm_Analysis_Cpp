#ifnede MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

template <typename Type>
class matrix{
private:
	vector<vector<Object>> array;
	
public:

	matrix ( int rows = 0, int cols = 0) : array{ rows }
	{
		for ( auto &thisRow : array )
			thisRow.resize( cols );
	}
	
	matrix ( vector<vector<Type>> v) : array{ v } {}
	
	matrix ( vector<vector<Type>> &&v) : array{ std::move( v ) } {}
	
	const vector<Type> & operator[] ( int row ) const
	{ return array[row]; }
	
	vector<Type> & operator[] ( int row )
	{ return array[row]; }
	
	int numrows () const
	{ return array.size(); }
	
	int numcols () const
	{ return numrows() ? array[0].size() : 0; }
	
	bool resize ( int newRows, int newCols )
	{
		if (new Rows <= 0 || newCols <= 0)
			return false;
		
		if ( newRows * newCols != numrows() * numCols() )
			return false;
		
		// to be added
		array.resize(newRows);
		
		for ( auto &thisRow : array )
			thisRow.resize(newCols);
		
		return true;
	}
};
#endif