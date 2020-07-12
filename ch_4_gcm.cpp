# include <iostream>
# include <random>
# include <algorithm>
# include <functional>
# include <cassert>

// Representing line segments by 
// their length, which is an int 
// so we can meaningfully define 
// their GCD.
using line_segment = int; 

// Implementing the Euclidean continued 
// subtraction algorithm. Subtract the shorter 
// length from the longer, until both lengths 
// become equal. That value is the measure that 
// measures both of them. 
line_segment gcm0 ( line_segment a, line_segment b){
	while ( a != b ) {
		if ( b < a ) a = a - b; 
		else b = b - a;
	} // end while
	return a; 
}

// Making this more efficient for the case when 
// one length is much longer than the other. 
// Simply get the maximum number of times that
// the shorter fits into the longer, and subtract
// as before. This is analagous to  `b = aq + r`, 
// the more well known version of the algorithm. 
line_segment gcm0_long ( line_segment a, line_segment b) {
	line_segment q;
	while (a != b) {
		// Checking if the remainder of the 
		// previous operation has zeroed out 
		// either length. These correspond to the
		// remainders of the Euclidean algo, 
		// so we return the quotient i.e. the other 
		// number. 
		if ( a==0 ) return b; 
		if ( b==0 ) return a; 
		
		if ( a > b ) {
			// q is how many times `b` goes into `a`
			// i.e. we remove `q*b` from `a` safely.	
			q = a / b; 
			a = a - b*q;  
		} else {// b > a 
			// same case, but `a` goes into `b` now.
			q = b / a;
			b = b - a*q; 
		}
	} // end while
	return a; 
}	

// making our original algorithm faster. 
line_segment gcm1 ( line_segment a, line_segment b){
	
	// using a lambda to create our segment remainder calculator(s).
	// Note that the a and b inside the lambda are not captured 
	// from outer scope, and are local definitions. 
	auto segment_remainder_basic = [](line_segment a, line_segment b){
		while ( a > b ) a = a - b; 
		return a; 
	};

	// Making use of the recursive remainder lemma (Lemma 4.1)
	// to define a faster remainder calculator. Need to explicitly 
	// specify type and capture itself to recurse. 
	using segrem_fast_type = std::function<line_segment(line_segment, line_segment)>; 
	segrem_fast_type segment_remainder_fast = 
			[&segment_remainder_fast](line_segment a, line_segment b){
		if ( a <= b) return a; 
		if ( a - b <= b ) return a - b; 
		a = segment_remainder_fast(a, b+b); 
		if ( a <= b) return a; 
		return a - b; 
	};

	// Run the main thing with an easily changed 
	// segment remainder calculator. 
	while ( a != b ) {
		a = segment_remainder_fast(a,b); 
		std::swap (a,b); 
	} // end while
	return a; 
}



// Main code driver, using randomly generated
// integers to test each GCM algorithm against 
// previously verified ones, say GCM0.
int main(){
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(1,200); // guaranteed unbiased

	for ( int i = 1; i <= 20; i++) {
		auto a = uni(rng), b = uni(rng); 
		auto result = gcm_norecurse(a,b); 

		std::cout << "GCD(" << a << "," << b << ") = " 
			<< result << ": " << gcm0(a,b) << std::endl; 
	}
	return 0; 

}
