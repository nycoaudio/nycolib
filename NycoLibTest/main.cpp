#include "AudioStream.h"
#include <memory>
#include <iostream>
#include <vector>

#include "../NycoLib.AudioFile/AudioFile.h"

using namespace nyco;


int main() {

	double dBuffer[] = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

	AudioStream<double> doubleStream ((double*)dBuffer, sizeof(dBuffer) / sizeof(dBuffer[0]), ownership::NO_OWNERSHIP);
	AudioStream<double> doubleStream2 ((double*)dBuffer, sizeof(dBuffer) / sizeof(dBuffer[0]), ownership::COPY);

	std::cout << doubleStream << std::endl;

	doubleStream *= 2;

	for (int i = 0; i < doubleStream.size(); ++i) {
		std::cout << doubleStream[i] << std::endl;
	}

	auto newStream = +doubleStream;

	std::cout << newStream << std::endl;

	newStream.rotateRight(3);

	for (auto a : newStream) {
		std::cout << a << std::endl;
	}

	return 0;
}
