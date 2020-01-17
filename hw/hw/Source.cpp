#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <numeric>

////////////////////////////////////////////////////////////////////////////
//     !! HOMEWORK !!
// use the C++ <algorithms> as extensively as you can for these problems!

// you may not modify this
struct Pube
{
	int num;
	std::string str;
	bool operator<( const Pube& rhs ) const
	{
		return num < rhs.num;
	}
	operator int() const
	{
		return num;
	}
}; 

// write your remove_erase_if template function here!
template<class T, class unaryPredicate>
void remove_erase_if( T& con,unaryPredicate pred )
{
	const auto new_end = std::remove_if( std::begin( con ),std::end( con ),pred );
	con.erase( new_end,std::end( con ) );
}

// write your custom insertion operator here!
std::ostream& operator<<( std::ostream& out,const Pube& rhs ) //that's must 'const'
{
	return out << "(" << rhs.num << ',' << rhs.str << ")";
}

int main()
{
	// materiel (do not modify!)
	const std::vector<Pube> numbers = { 
		{ 0,"zero" },
		{ 9,"nine" },
		{ 7,"seven" },
		{ 2,"two" },
		{ 8,"eight" },
		{ 3,"three" },
		{ 4,"four" },
		{ 1,"one" },
		{ 6,"six" },
		{ 5,"five" }
	};
	const std::vector<Pube> memes = {
		{ 3,"dat boi" },
		{ 1,"yaaaas" },
		{ 3,"soviet russia" },
		{ 1,"damn daniel" },
		{ 1,"hipster ariel" },
		{ 3,"harambe" },
		{ 2,"doge" },
		{ 3,"cash me outside" },
		{ 2,"henlo" },
		{ 3,"kappa" }
	};
	const std::string nambies = "eight one six eight three three eight five four two nine six nine";
	const std::string numpies = { 6, 6, 5, 0, 6, 1, 8, 6 };
	// Problem 1:
	// create a vector that contains 4 copies of each of the elements of memes
	// sort it first by number descending (score from 3 to 1) and then name ascending
	// output sorted meme list w/ score and name using custom insertion operator
	std::cout << "<< Sort Memes >>" << std::endl;
	{
		// code goes here
		//copy 4x, the reason is to force std::sort to use quick sort, and quick sort just care to one order(urutan)
		std::vector<Pube> copyMemes( memes.size() * 4 );
		auto a = copyMemes.begin();
		for( size_t i = 0; i < 4; i++,a += memes.size() )
		{
			std::copy( memes.begin(),memes.end(),a );
		}
		//minor
		std::sort( copyMemes.begin(),copyMemes.end(),
		[] ( const Pube& lhs,const Pube& rhs ) -> bool //maybe it must be 'const' too
		{
			return lhs.str < rhs.str;//ascending by name
		} );
		//major
		std::stable_sort( copyMemes.begin(),copyMemes.end(),
		[] ( const Pube& lhs,const Pube& rhs ) -> bool //maybe it must be 'const' too
		{
			return lhs.num > rhs.num;//descending by score
		} );
		//print to console
		std::copy( copyMemes.begin(),copyMemes.end(),std::ostream_iterator<Pube>( std::cout,"\n" ) );
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 2:
	// output nambies as string of digits without spaces
	// (can be done in single statement!)
	std::cout << "<< Number Words to Digits >>" << std::endl;
	{
		// code goes here
		std::string stringCopy;
		std::string buff;
		std::stringstream ss( nambies );
		while( ss.good() )//it's mean that ss is good
		{
			std::getline( ss,buff,' ' );
			for( const auto& i : numbers )
			{
				if( buff == i.str )
				{
					stringCopy.push_back( i.num + '0' );
					break;
				}
			}
		}
		std::cout << stringCopy << std::endl;
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 3:
	// output numpies as a string of words separated by spaces
	// don't use std::find_if or other searches
	std::cout << "<< Digits to Number Words >>" << std::endl;
	{
		auto sorted = numbers;
		std::sort( sorted.begin(),sorted.end() );
		std::transform( numpies.begin(),numpies.end(),std::ostream_iterator<std::string>( std::cout,", " ),
		[&sorted]( int x )
		{
			return sorted[x].str;
		} );
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 4:
	// find the product of all numbers in nambies
	// and output of course
	std::cout << "<< Product >>" << std::endl;
	{
		// code goes here
		std::vector<int> vec;
		std::string buff;
		std::stringstream ss( nambies );
		while( ss.good() )//it's mean that ss is good
		{
			std::getline( ss,buff,' ' );
			for( const auto& i : numbers )
			{
				if( buff == i.str )
				{
					vec.push_back( i.num );
					break;
				}
			}
		}
		//std::multiplies<std::string> that's gonna be error, because it's not make sense multiplies word
		std::cout << std::accumulate( vec.begin(),vec.end(),1,std::multiplies<int>{} ) << std::endl;
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 5:
	// find sums of corresponding nums in numbers and memes
	// output as comma separated list
	std::cout << "<< Parallel Sum >>" << std::endl;
	{
		// code goes here
		std::transform( numbers.begin(),numbers.end(),memes.begin(),std::ostream_iterator<int>( std::cout,", " ),
						std::plus<int>() );
		std::cout << std::endl;
	}
	std::cout << "============================================" << std::endl << std::endl;

	// Problem 6:
	// write a template function (not here, above int main())
	// that will remove elements from vector based on unary predicate
	// the following code should not be modified
	std::cout << "<< Top Memes >>" << std::endl;
	{
		// copy to get non-const vector
		auto maymays = memes;
		// remove all memes with score below 3
		remove_erase_if( maymays,[]( const Pube& p ) { return p.num < 3; } );
		// output results
		std::copy( maymays.begin(),maymays.end(),std::ostream_iterator<Pube>( std::cout,"\n" ) );
	}
	std::cout << "============================================" << std::endl << std::endl;

	std::cin.get();
	return 0;
}