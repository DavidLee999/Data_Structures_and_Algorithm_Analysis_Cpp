#include <iostream>
#include <string.h>

using namespace std;

inline bool validate (int pos, int direction, int length)
{
	return ((pos + 1) + direction*length >= 0 && pos + direction*length <= 4);
}

void findWords(const char puzzle[4][4], const char* word)
{
	const int length = strlen(word);
	
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			if ( puzzle[row][col] == word[0])
			{
				for ( int row_i = -1; row_i <= 1; ++row_i)
				{
					if( validate(row, row_i, length) )
					{
						for ( int col_i = -1; col_i <= 1; ++col_i)
						{
							if ( validate(col, col_i, length) )
							{
								if ( row_i == 0 && col_i == 0) continue;
								
								int index = 0;
								for (; index < length; ++index)
								{
									if (puzzle[row+row_i*index][col+col_i*index] != word[index]) break;
								}
								if (index == length)
								{
									cout << "Word ";
									for (int i = 0; i < length; ++i) cout << word[i];
									cout << " is found in the location (" << row << "," << col <<" ). ";
									cout << "Direction (" << row_i << ", " << col_i << "). " << endl;
									return;
								}
								
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	const int ROW = 4;
	const int COL = 4;
	
	char puzzle[ROW][COL] {{'t', 'h', 'i', 's'},
                             {'w', 'a', 't', 's'}, 
							 {'o', 'a', 'h', 'g'}, 
							 {'f', 'g', 'd', 't'}};
							 
							 
	char words[ROW][COL+1] {"this", "two", "fat", "that"};
	
	for ( int i = 0; i < 4; ++i )
		findWords(puzzle, words[i]);
	
	/* for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout<<words[i][j]<<" ";
		}
		cout<<endl;
	} */
}