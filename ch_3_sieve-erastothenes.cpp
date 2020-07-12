# include <iostream>
# include <vector>
# include <cassert>

// Generic function to mark all values accessible 
// within `first` and `last` iterators which are
// `factor` away from each other as false i.e.
// false -> not prime.


template < class RandomAccessIterator >
void mark_sieve (RandomAccessIterator first, 
		RandomAccessIterator last, int factor) {
	// make sure we're not accessing a 
	// zero size container. 
	assert ( first != last ); 
	
	// mark the first element as false,
	*first = false; 

	// and every element `factor` away 
	// from it.
	while ( last - first > factor ) {
		first = first + factor; 
		*first = false; 
	}
} // end 

// code to sift through the range [0,N); this i 
// specified between the iterators `first` and `last`. 
template < typename RandomAccessIterator >
void sift_basic ( RandomAccessIterator first, int N) {
	 
	RandomAccessIterator last = first + N;	// defining `last` for convenience.
	std::fill (first, last, true); 		// Marking all values as true.
						// This is true because *first = 3 
						// and so on. 
	int index=1, index_square=3; 		// Similarly, first[3] = 2*3 + 3 = 9
						// which is the first square. 
	int factor = 3; 			// first factor by which we sieve things out. 

	// looping through until we get a prime 
	// whose square exceeds the last element in 
	// the container. 
	while (index_square < N){
		
		// if the `first[index] (= *(first+index))`
		// element is prime, sieve out all of its brethren.
		if ( first[index] )
			mark_sieve(first+index_square, last, factor); 
		
		index++;			// increment index to get 2*(i+1) + 1
						// as the value under the index.
	        index_square += factor;         // Use the formula: 
						// index_square = factor(i) + factor(i+1)
						// `factor` is currently factor(i)
		factor += 2;			// this gives factor -> factor(i+1).
		index_square += factor; 	// completing the formula.
	}// end while
}

int main(){
	std::vector<bool> vect(200); 
	
	std::cout << vect.size() << " is the size of vector.\n"; 
	
	// calling the sift on our list of vectors. 
	// note that the vector is essentially the range 
	// [first=3 : step=2 : last=(2*size+1)]
	sift_basic ( vect.begin(), vect.size() ); 

	// Every index corresponds to the `2*index+1` odd number!!
	// We disregard the presence of even numbers as we know 
	// already that they are not prime. Thus, vect[0] -> 3 etc. 
	for ( auto itr = vect.begin(); itr != vect.end(); ++itr){
		std::cout << 2*( itr - vect.begin() + 1 ) + 1<< "-> " << *itr << std::endl; 
	}
	std::cout << std::endl; 
	return 0; 
}
