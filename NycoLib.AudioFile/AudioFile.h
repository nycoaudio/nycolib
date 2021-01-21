#pragma once

#include <type_traits>
#include <fstream>


namespace nyco {
	enum class AudioFormat {
		WAV,
		MP3,
		OGG,
		AAC
	};

	struct AudioInformation {
	public:
		uint16_t channelCount;
		uint32_t sampleRate;
		uint16_t audioFormat;

	public:
		bool isPCM();
	};

	class AudioFileBase {
	public:
		// load file from disk
		AudioFileBase(char const* filePath, char const* mode);

		// get channel data as std::shared_ptr<AudioStream>

		// dump to file

		// get num channels

		// get sample rate

		// get bits per sample

	protected:
		std::fstream m_fsFileStream;
	};

	template <AudioFormat AudioFormat>
	class AudioFile : AudioFileBase {

	};
}
