#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <chrono>

// to use the following 2 macros, you need to declare
// std::chrono::high_resolution_clock::time_point startTime
// before using
#define PROFILE_DECLR std::chrono::high_resolution_clock::time_point gProfileStartTime; \
                      std::chrono::high_resolution_clock::time_point gProfileEndTime;
#define PROFILE_START gProfileStartTime = std::chrono::high_resolution_clock::now();
#define PROFILE_END gProfileEndTime = std::chrono::high_resolution_clock::now();
#define PROFILE_PRINT std::cout << " execution elapsed " << std::chrono::duration_cast<std::chrono::microseconds>(gProfileEndTime - gProfileStartTime).count() << " ms" << std::endl;
#define PROFILE_RESET gProfileStartTime = 0; gProfileEndTime = 0;

// print all elements value inside container
// separated by a space, at the end it also prints newline
#define PRINTARRAY(v) for (int i=0,size=v.size(); i<size; ++i) { \
                            if (i < size-1) std::cout << v[i] << " "; else std::cout << v[i];} std::cout << std::endl;

#endif /* UTIL_H_ */
