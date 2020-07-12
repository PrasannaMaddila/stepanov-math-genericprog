# include <iostream>
# include <random>
# include <cassert>

// basic multiply function 
// standard naive multiplication.
int multiply_basic (int n, int a) {
	if (n==1) return a; 
	return multiply_basic(n-1, a) + a; 
}

// Commonly called the Russian Peasant algorithm,
// halves the first number while doubling the second.
// this works because every number has a base-2 rep-
// -resentation. 
int multiply_egypt (int n, int a) {
	if (n==1) return a; 
	int result = multiply_egypt( n >> 1, a+a ); 
	if ( n & 0x1 ) result = result + a; 
	return result;
}

// Accumulate-version of the egyptian multiply algo.
// Because recursion is expensive, we're going to 
// make this strictly tail-recursive. 
int multiply_acc_egypt ( int r, int n, int a) {
	// if ( n==1 ) return r + a;
        if ( n & 0x1 ) { 
		r += a;
		if ( n==1 ) return r; 
	}
	n = n >> 1;  // Bit-shift n to divide by 2
	a += a;      // Double a correspondingly. 
	return multiply_acc_egypt(r, n, a); 
}

// or just replace the recursion completely?
int multiply_acc_loop_egypt (int r, int n, int a) {
	// using an infinite loop to sub for
	// the recursion. 	
	// guaranteed to return because n 
	// eventually becomes 1. 
	while (true) {
		if ( n & 0x1 ) { 
			r += a;
			if ( n==1 ) return r; 
		}
		n = n >> 1;  // Bit-shift n to divide by 2
		a += a;      // Double a correspondingly. 
	}
}

// defining a helper function to work with the numbers 
// before blindly multiplying them; this ensures we don't 
// have to deal with the worst case of `2^n - 1`; 
int multiply_egypt_helper(int n, int a) {
	// working n until it is odd,
	// because the even case isn't handled
	// well by the `n-1`.
	while ( n & 0 ) {
		a += a; 
		n = n >> 1; 
	}
	
	// weeding out the trivial case. 
	if ( n==1 ) return a; 
	
	// now that no further benefits can be
	// obtained with n, multiply.
	return multiply_acc_loop_egypt(a, n-1, a); 
}


// code to randomly test the chosen multiply function. 
// uses a random generator to get pairs of numbers to test.
// currently set to the range (1,30).
int main() {

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(1,30); // guaranteed unbiased
	
	for (int i=1; i < 10; i++) {
		auto n = uni(rng); 
		auto a = uni(rng); 

		auto result = multiply_egypt_helper(n,a); 
		std::cout << n << " x " << a << " = " << result << std::endl; 
		assert ( result == n*a ); 
	}
	std::cout << "End of program" << std::endl; 
	return 0; 
}
