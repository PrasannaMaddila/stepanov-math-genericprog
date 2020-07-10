# include <iostream>
# include <random>
# include <cassert>
// basic multiply function 
int multiply_basic (int n, int a) {
	if (n==1) return a; 
	return multiply_basic(n-1, a) + a; 
}

int multiply_egypt (int n, int a) {
	if (n==1) return a; 
	int result = multiply_egypt( n >> 1, a+a ); 
	if ( n * 0x1 ) result = result + a; 
	return result;
}

int main() {

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(1,30); // guaranteed unbiased
	
	for (int i=1; i < 10; i++) {
		auto n = uni(rng); 
		auto a = uni(rng); 

		auto result = multiply_egypt(n,a); 
		std::cout << n << " x " << a << " = " << result << std::endl; 
		assert ( result == n*a & "Multiplication verified." ); 
	}
	std::cout << "End of program" << std::endl; 
	return 0; 
}
