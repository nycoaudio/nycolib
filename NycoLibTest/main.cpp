#include "AudioStream.h"
#include <memory>
#include <iostream>
#include <vector>

using namespace nyco;


int main() {
	double dBuffer[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

	AudioStream<double> doubleStream ((double*)dBuffer, sizeof(dBuffer) / sizeof(dBuffer[0]), ownership::NO_OWNERSHIP);
	AudioStream<double> doubleStream2 ((double*)dBuffer, sizeof(dBuffer) / sizeof(dBuffer[0]), ownership::COPY);
	//AudioStream<double> doubleStream3 ((double*)dBuffer, sizeof(dBuffer) / sizeof(dBuffer[0]), ownership::TAKE, std::default_delete<double[]>{});

	std::cout << doubleStream << std::endl;

	for (int i = 0; i < doubleStream.size(); ++i) {
		std::cout << doubleStream[i] << std::endl;
	}

	for (int i = 0; i < doubleStream.size(); ++i) {
		doubleStream[i] = doubleStream[i] * 2;
	}

	auto newStream = +doubleStream;

	for (int i = 0; i < newStream.size(); ++i) {
		std::cout << newStream[i] << std::endl;
	}

	return 0;
}
