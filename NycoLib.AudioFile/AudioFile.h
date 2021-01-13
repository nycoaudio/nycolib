#pragma once

#include <type_traits>
#include <fstream>


namespace nyco {
	enum class AudioFormats {
		WAV,
		MP3,
		OGG,
		AAC
	};

	class AudioFileBasic {
	public:
		// load file from disk
		AudioFileBasic(char const *filePath, char const *mode);

		// get channel data as std::shared_ptr<AudioStream>

		// dump to file

		// get num channels

		// get sample rate

		// get bits per sample

	protected:
		std::fstream m_fsFileStream;
	};

	template <AudioFormats AudioFormat>
	class AudioFile : AudioFileBasic {

	};
}
