
#include <chrono>
#include <iostream>






#define TIME( callable, iterations ) \
	{\
		std::chrono::time_point<std::chrono::system_clock> start, end;\
		start = std::chrono::system_clock::now();\
		for (size_t i = 0; i < (iterations); ++i) {\
			callable();\
		}\
		end = std::chrono::system_clock::now();\
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();\
		std::cout << "TIMED '" << #callable << "' with " << iterations << " iterations: " << elapsed << " mus" << std::endl;\
	}


