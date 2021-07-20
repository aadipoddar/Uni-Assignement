#include <iostream>
#include <sstream>

class HashTable
{
public:
	struct Entry
	{
		std::string Data;
		std::string Status = "never used";
	};
	static const int Size = 26;
public:
	HashTable ( ) = default;

	void Add ( const std::string & entryString )
	{
		bool exists = Find ( entryString );
		if ( !exists )
		{
			int insertIndex = GetInsertIndex ( entryString );
			m_Entries [ insertIndex ].Data = entryString;
			m_Entries [ insertIndex ].Status = "occupied";
		}
	}
	
	void Delete ( const std::string & entryString )
	{
		int index;
		bool exists = Find ( entryString , &index );
		if ( exists )
		{
			m_Entries [ index ].Status = "tombstone";
		}

	}

	void Print ( ) const
	{
		bool first = true;
		for ( int i = 0; i < Size; i++ )
		{
			if ( m_Entries [ i ].Status == "occupied" )
			{
				if ( !first )
				{
					std::cout << ' ';
				}
				std::cout << m_Entries [ i ].Data;
				first = false;
			}
		}
		std::cout << std::endl;
	}
private:
	int GetIndex ( const std::string & entryString ) const
	{
		return entryString.back ( ) - 'a';
	}

	bool Find ( const std::string & entryString , int * outIndex = nullptr ) const
	{
		int index = GetIndex ( entryString );
		while ( true )
		{
			if ( m_Entries[index].Data == entryString )
			{
				if ( outIndex )
				{
					*outIndex = index;
				}
				return true;
			}

			if ( m_Entries[index].Status == "never used" )
			{
				return false;
			}

			index = ( index + 1 ) % Size;
		}
		
		return false;
	}

	int GetInsertIndex ( const std::string & entryString ) const
	{
		int index = GetIndex ( entryString );
		while ( true )
		{
			if ( m_Entries [ index ].Status == "never used" || m_Entries [ index ].Status == "tombstone" )
			{
				return index;
			}

			index = ( index + 1 ) % Size;
		}

		return -1;
	}
private:
	Entry m_Entries [ Size ];
};

int main ( )
{
	// Aapple Aorange Dapple Astrawberry
	// orange strawberry

	std::string input;
	getline ( std::cin , input );

	HashTable hashtable;

	std::stringstream ss ( input );
	while ( ss.good() )
	{
		std::string token; // Apple
		ss >> token;

		std::string entryString = token.substr ( 1 );
		if ( token [ 0 ] == 'A' )
		{
			hashtable.Add ( entryString );
 		}
		
		else if ( token [ 0 ] == 'D' )
		{
			hashtable.Delete ( entryString );
		}
	}

	hashtable.Print ( );

}