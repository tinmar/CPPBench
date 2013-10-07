//
//  main.cpp
//  CPPBench
//
//  Created by Martin Jachimowicz on 06/10/2013.
//  Copyright (c) 2013 Martin Jachimowicz. All rights reserved.
//

#include <stdio.h>

#include "timer.hpp"
#include "call_bench.hpp"

static const size_t DEFAULT_NUM_ITERATIONS = 1000000000;

int main(int argc, const char** argv) {
	
	int result = 1;
	
	size_t numIterations = DEFAULT_NUM_ITERATIONS;
	do {
		if (argc > 2) {
			std::cout << "usage: CPPBench [num_iterations]" << std::endl;
			break;
		}
		
		if (2 == argc) {
			const char* arg = argv[1];
			numIterations = std::stoull(arg);
			if (0 == numIterations) {
				std::cout << "Got argument parsing error: " << arg << std::endl;
				break;
			}
		}
		
		call_bench::call_bench(numIterations);
		result = 0;
		
	} while (false);
		
	return result;
}