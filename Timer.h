#pragma once
#include <iostream>
#include <chrono>

struct Timer {
	std::chrono::high_resolution_clock::time_point start;

	//start timer
	void startTimer() {
		start = std::chrono::high_resolution_clock::now();
	}

	//end timer
	void endTimer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << elapsed.count() * 1000 << "ms" << "\n";
	}
};
