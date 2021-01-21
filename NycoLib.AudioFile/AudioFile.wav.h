#pragma once

#include <cstdint>
#include "AudioFile.h"

namespace nyco {
	struct RIFFChunk {
		char chunkID[4];
		uint32_t chunkSize;
		char format[4];
	};

	struct FormatChunk {
		char chunkID[4];
		uint32_t chunkSize;
		uint16_t audioFormat;
		uint16_t numChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t blockAlign;
		uint16_t bitsPerSample;
		uint16_t extraParametersSize;

		// extra parameters
	};

	struct DataChunk
	{
		char chunkID[4];
		uint32_t chunkSize;

		// data[chunkSize]
	};

	template <>
	class AudioFile<AudioFormat::WAV> {

	};
}
