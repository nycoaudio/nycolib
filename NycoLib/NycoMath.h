#pragma once

#include <cmath>


namespace nyco {
	template <typename BufferType>
	BufferType add(BufferType a, BufferType b) {
		return a + b;
	}

	template <typename BufferType>
	BufferType sub(BufferType a, BufferType b) {
		return a - b;
	}

	template <typename BufferType>
	BufferType mult(BufferType a, BufferType b) {
		return a * b;
	}

	template <typename BufferType>
	BufferType div(BufferType a, BufferType b) {
		return a / b;
	}

	template <typename BufferType>
	BufferType mod(BufferType a, BufferType b) {
		return std::fmod(a, b);
	}

	template <typename BufferType>
	BufferType bw_and(BufferType a, BufferType b) {
		return a & b;
	}

	template <typename BufferType>
	BufferType bw_xor(BufferType a, BufferType b) {
		return a ^ b;
	}

	template <typename BufferType>
	BufferType bw_or(BufferType a, BufferType b) {
		return a | b;
	}
}
