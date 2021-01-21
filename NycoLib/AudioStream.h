#pragma once

#include <memory>
#include <iostream>
#include <assert.h>

#include "ownership.h"
#include "NycoMath.h"


#pragma region nyco - AudioStream - Declarations

namespace nyco {
	using byte = unsigned char;

	template <typename T>
	class AudioStreamBase;

#pragma region AudioStreamBase<BufferType> friend functions forward declarations

	// BufferType + AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator+(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType - AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator-(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType * AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator*(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType / AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator/(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType % AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator%(BufferType const& a, AudioStreamBase<BufferType> const& b);

	template <typename BufferType>
	// BufferType ^ AudioStreamBase<BufferType>
	AudioStreamBase<BufferType> operator^(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType & AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator&(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType | AudioStreamBase<BufferType>
	template <typename BufferType>
	AudioStreamBase<BufferType> operator|(BufferType const& a, AudioStreamBase<BufferType> const& b);

	template <typename BufferType>
	std::ostream& operator<<(std::ostream& s, AudioStreamBase<BufferType> const& stream);

#pragma endregion

	template <typename BufferType>
	class AudioStreamBase {

#pragma region Constructors
	public:

		template <typename Deleter>
		explicit AudioStreamBase(BufferType* data, size_t length, ownership::take_ownership, Deleter d = std::default_delete<BufferType[]>());

		explicit AudioStreamBase(BufferType* data, size_t length, ownership::no_ownership);

		explicit AudioStreamBase(BufferType* data, size_t length, ownership::copy);

		explicit AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::no_ownership);

		// Copy Constructor
		AudioStreamBase(AudioStreamBase<BufferType> const& stream) = delete;

		// Move Constructor
		AudioStreamBase(AudioStreamBase<BufferType>&& stream) = default;

#pragma endregion

#pragma region Methods
	public:

		// does in-place transformation of the stream by the given function
		template <typename Function>
		requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
			AudioStreamBase<BufferType>& transform(Function&& func);

		// does in-place transformation of the stream by the given function and the other stream
		// same as func(this, other); where func iterates over elements and calls this[i] = inner_func(this[i], other[i]);
		template <typename Function>
		requires (std::is_same_v<std::invoke_result_t<Function, BufferType, BufferType>, BufferType>)
			AudioStreamBase<BufferType>& transform(Function&& func, AudioStreamBase<BufferType> const& other);

		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType>& shiftLeft(IntegralT const o);

		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType>& shiftRight(IntegralT const o);

		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType>& rotateLeft(IntegralT const o);

		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType>& rotateRight(IntegralT const o);

		AudioStreamBase<BufferType> clone() const;

		BufferType* begin();

		BufferType const* begin() const;

		BufferType* end();

		BufferType const* end() const;

		size_t size();

#pragma endregion

#pragma region Static Methods
	public:

		template <typename Function>
		requires (std::is_same_v<std::invoke_result_t<Function, BufferType, BufferType>, BufferType>)
			static AudioStreamBase<BufferType> zipWith(AudioStreamBase<BufferType> const& a, AudioStreamBase<BufferType> const& b, Function&& func);

#pragma endregion

#pragma region Operator Overloading

#pragma region Binary Operators

#pragma region AudioStreamBase<BufferType> OP AudioStreamBase<BufferType>
	public:

		// AudioStreamBase<BufferType> + AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator+(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> - AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator-(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> * AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator*(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> / AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator/(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> % AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator%(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> ^ AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator^(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> & AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator&(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> | AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator|(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> >> AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator>>(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> << AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator<<(AudioStreamBase<BufferType> const& o) const;

		// AudioStreamBase<BufferType> += AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator+=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> -= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator-=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> *= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator*=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> /= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator/=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> %= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator%=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> ^= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator^=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> &= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator&=(AudioStreamBase<BufferType> const& o);

		// AudioStreamBase<BufferType> |= AudioStreamBase<BufferType>
		AudioStreamBase<BufferType>& operator|=(AudioStreamBase<BufferType> const& o);

#pragma endregion

#pragma region AudioStreamBase<BufferType> OP BufferType
	public:

		// AudioStreamBase<BufferType> + BufferType
		AudioStreamBase<BufferType> operator+(BufferType const& o) const;

		// AudioStreamBase<BufferType> - BufferType
		AudioStreamBase<BufferType> operator-(BufferType const& o) const;

		// AudioStreamBase<BufferType> * BufferType
		AudioStreamBase<BufferType> operator*(BufferType const& o) const;

		// AudioStreamBase<BufferType> / BufferType
		AudioStreamBase<BufferType> operator/(BufferType const& o) const;

		// AudioStreamBase<BufferType> % BufferType
		AudioStreamBase<BufferType> operator%(BufferType const& o) const;

		// AudioStreamBase<BufferType> ^ BufferType
		AudioStreamBase<BufferType> operator^(BufferType const& o) const;

		// AudioStreamBase<BufferType> & BufferType
		AudioStreamBase<BufferType> operator&(BufferType const& o) const;

		// AudioStreamBase<BufferType> | BufferType
		AudioStreamBase<BufferType> operator|(BufferType const& o) const;

		// AudioStreamBase<BufferType> += BufferType
		AudioStreamBase<BufferType>& operator+=(BufferType const& o);

		// AudioStreamBase<BufferType> -= BufferType
		AudioStreamBase<BufferType>& operator-=(BufferType const& o);

		// AudioStreamBase<BufferType> *= BufferType
		AudioStreamBase<BufferType>& operator*=(BufferType const& o);

		// AudioStreamBase<BufferType> /= BufferType
		AudioStreamBase<BufferType>& operator/=(BufferType const& o);

		// AudioStreamBase<BufferType> %= BufferType
		AudioStreamBase<BufferType>& operator%=(BufferType const& o);

		// AudioStreamBase<BufferType> ^= BufferType
		AudioStreamBase<BufferType>& operator^=(BufferType const& o);

		// AudioStreamBase<BufferType> &= BufferType
		AudioStreamBase<BufferType>& operator&=(BufferType const& o);

		// AudioStreamBase<BufferType> |= BufferType
		AudioStreamBase<BufferType>& operator|=(BufferType const& o);

#pragma endregion

#pragma region BufferType OP AudioStreamBase<BufferType>
	private:

		// BufferType + AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator+(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType - AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator-(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType * AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator*(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType / AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator/(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType % AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator%(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType ^ AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator^(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType & AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator&(BufferType const& a, AudioStreamBase<BufferType> const& b);

		// BufferType | AudioStreamBase<BufferType>
		friend AudioStreamBase<BufferType> operator|(BufferType const& a, AudioStreamBase<BufferType> const& b);

#pragma endregion

#pragma region AudioStreamBase<BufferType> shift by integral
	public:

		// AudioStreamBase<BufferType> << integral
		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType> operator<<(IntegralT const o) const;

		// AudioStreamBase<BufferType> >> integral
		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType> operator>>(IntegralT const o) const;

		// AudioStreamBase<BufferType> <<= integral
		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType>& operator<<=(IntegralT const o);

		// AudioStreamBase<BufferType> >>= integral
		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			AudioStreamBase<BufferType>& operator>>=(IntegralT const o);

#pragma endregion

		// Deleting the operator= so you can't assign stream by reference
		AudioStreamBase<BufferType>& operator=(AudioStreamBase<BufferType> const& rhs) = delete;

#pragma endregion

#pragma region Unary Operators
	public:

		// + AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator+() const;

		// - AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator-() const;

		// ~ AudioStreamBase<BufferType>
		AudioStreamBase<BufferType> operator~() const;

#pragma endregion

#pragma region Indexing Operators
	public:

		// AudioStreamBase<BufferType>[integral]
		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			BufferType& operator[](IntegralT x);

		// AudioStreamBase<BufferType>[integral]
		template <typename IntegralT>
		requires (std::is_integral_v<IntegralT>)
			BufferType const& operator[](IntegralT x) const;

		// AudioStreamBase<BufferType>[floating_point]
		template <typename FloatingT>
		requires (std::is_floating_point_v<FloatingT>)
			BufferType& operator[](FloatingT x);

		// AudioStreamBase<BufferType>[floating_point]
		template <typename FloatingT>
		requires (std::is_floating_point_v<FloatingT>)
			BufferType const& operator[](FloatingT x) const;

#pragma endregion

#pragma region ostream << Overload
	private:

		// ostream& << AudioStreamBase<BufferType>
		template <typename BufferType>
		friend std::ostream& operator<<(std::ostream& s, AudioStreamBase<BufferType> const& stream);

#pragma endregion

#pragma endregion

#pragma region Protected Members
	protected:

		std::shared_ptr<BufferType> m_pBuffer;

		size_t m_nLength;

#pragma endregion

	};

	template <typename T>
	class AudioStream : public AudioStreamBase<T> {
	public:
		using AudioStreamBase<T>::AudioStreamBase;
	};

	template <typename BufferType>
	using MultiChannelAudioStream = AudioStream<AudioStream<BufferType>>;
}

#pragma endregion

namespace std {
	// overloading this method since AudioStream % AudioStream uses std::fmod internally.
	template <typename BufferType>
	nyco::AudioStream<BufferType> fmod(nyco::AudioStream<BufferType> const& a, nyco::AudioStream<BufferType> const& b) {
		return a % b;
	}
}

#pragma region nyco - AudioStream - Definitions

namespace nyco {
#pragma region AudioStreamBase<BufferType>

#pragma region AudioStreamBase<BufferType> - OPs

#pragma region AudioStreamBase<BufferType> - OPs - Indexers

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		BufferType& AudioStreamBase<BufferType>::operator[](IntegralT x)
	{
		if (x < 0) {
			x += m_nLength;
		}
		assert(x < m_nLength&& x >= 0);
		return m_pBuffer.get()[x];
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		BufferType const& AudioStreamBase<BufferType>::operator[](IntegralT x) const
	{
		if (x < 0) {
			x += m_nLength;
		}
		assert(x < m_nLength&& x >= 0);
		return m_pBuffer.get()[x];
	}

	template <typename BufferType>
	template <typename FloatingT>
	requires (std::is_floating_point_v<FloatingT>)
		BufferType& AudioStreamBase<BufferType>::operator[](FloatingT x)
	{
		if (x < 0) {
			x += m_nLength;
		}
		assert(x < m_nLength&& x >= 0);
		return m_pBuffer.get()[x];
	}

	template <typename BufferType>
	template <typename FloatingT>
	requires (std::is_floating_point_v<FloatingT>)
		BufferType const& AudioStreamBase<BufferType>::operator[](FloatingT x) const
	{
		if (x < 0) {
			x += m_nLength;
		}
		assert(x < m_nLength&& x >= 0);
		return m_pBuffer.get()[x];
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Unary OPs

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator+() const
	{
		return this->clone();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator-() const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([](BufferType x) {
			return -x;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator~() const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([](BufferType x) {
			return ~x;
			});
		return stream;
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - AudioStreamBase<BufferType> OP AudioStreambase<BufferType>

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator+(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a + b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator-(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a - b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator*(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a * b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator/(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a / b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator%(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return std::fmod(a, b);
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator^(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a ^ b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator&(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a & b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator|(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>::zipWith(*this, o, [](BufferType a, BufferType b) {
			return a | b;
			});
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator>>(AudioStreamBase<BufferType> const& o) const
	{
		BufferType* buffer = new BufferType[m_nLength + o.m_nLength];
		std::memcpy(buffer, m_pBuffer.get(), m_nLength * sizeof(BufferType));
		std::memcpy(buffer + m_nLength, o.m_pBuffer.get(), o.m_nLength * sizeof(BufferType));
		return AudioStreamBase<BufferType>(buffer, m_nLength + o.m_nLength, ownership::TAKE, std::default_delete<BufferType[]>());
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator<<(AudioStreamBase<BufferType> const& o) const
	{
		return (*this) >> o;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator+=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a + b;
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator-=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a - b;
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator*=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a * b;
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator/=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a / b;
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator%=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return std::fmod(a, b);
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator^=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a ^ b;
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator&=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a & b;
			}, o);
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator|=(AudioStreamBase<BufferType> const& o)
	{
		transform([](BufferType a, BufferType b) {
			return a | b;
			}, o);
		return *this;
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - AudioStreamBase<BufferType> OP BufferType

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator+(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in + o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator-(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in - o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator*(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in * o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator/(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in / o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator%(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return std::fmod(in, o);
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator^(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in ^ o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator&(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in & o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator|(BufferType const& o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream.transform([o](BufferType in) {
			return in | o;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator+=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in + o;
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator-=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in - o;
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator*=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in * o;
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator/=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in / o;
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator%=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return std::fmod(in, o);
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator^=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in ^ o;
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator&=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in & o;
			});
		return *this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator|=(BufferType const& o)
	{
		transform([o](BufferType in) {
			return in | o;
			});
		return *this;
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - BufferType OP AudioStreamBase<BufferType>

	template <typename BufferType>
	AudioStreamBase<BufferType> operator+(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a + in;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator-(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a - in;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator*(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a * in;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator/(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a / in;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator%(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return std::fmod(a, in);
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator^(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a ^ in;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator&(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a & in;
			});
		return stream;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator|(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		AudioStreamBase<BufferType> stream = b.clone();
		stream.transform([a](BufferType in) {
			return a | in;
			});
		return stream;
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - AudioStreamBase<BufferType> OP Integral

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator<<(IntegralT const o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream <<= o;
		return stream;
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator>>(IntegralT const o) const
	{
		AudioStreamBase<BufferType> stream = this->clone();
		stream >>= o;
		return stream;
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator<<=(IntegralT const o)
	{
		IntegralT shift = o;
		if (shift >= m_nLength) {
			shift = std::fmod(shift, m_nLength);
		}
		if (shift == 0) {
			return *this;
		}
		if (shift < 0) {
			return (*this) >>= shift;
		}
		BufferType* ptr = m_pBuffer.get();
		for (int srcIndex = shift, dstIndex = 0; srcIndex < m_nLength; ++srcIndex, ++dstIndex) {
			ptr[dstIndex] = ptr[srcIndex];
		}
		BufferType defaultValue = BufferType{};
		for (int i = m_nLength - shift; i < m_nLength; ++i) {
			ptr[i] = defaultValue;
		}
		return *this;
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator>>=(IntegralT const o)
	{
		IntegralT shift = o;
		if (shift >= m_nLength) {
			shift = std::fmod(shift, m_nLength);
		}
		if (shift == 0) {
			return *this;
		}
		if (shift < 0) {
			return (*this) <<= shift;
		}
		BufferType* ptr = m_pBuffer.get();
		for (int srcIndex = m_nLength - shift - 1, dstIndex = m_nLength - 1; srcIndex >= 0; --srcIndex, --dstIndex) {
			ptr[dstIndex] = ptr[srcIndex];
		}
		BufferType defaultValue = BufferType{};
		for (int i = 0; i < shift; ++i) {
			ptr[i] = defaultValue;
		}
		return *this;
	}

#pragma endregion

#pragma endregion

	template <typename BufferType>
	std::ostream& operator<<(std::ostream& s, AudioStreamBase<BufferType> const& stream)
	{
		return s << "AudioStream(" << stream.m_nLength << " Samples [" << stream.m_nLength * sizeof(BufferType) << " Bytes] @ 0x" << stream.m_pBuffer.get() << ")";
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - Constructors

#pragma region AudioStreamBase<BufferType> - Constructors - By Pointer

	template <typename BufferType>
	template <typename Deleter>
	AudioStreamBase<BufferType>::AudioStreamBase(BufferType* data, size_t length, ownership::take_ownership, Deleter d)
		: m_pBuffer{ data, d }
		, m_nLength{ length }
	{
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>::AudioStreamBase(BufferType* data, size_t length, ownership::no_ownership)
		: m_pBuffer{ data, empty_delete<BufferType>() }
		, m_nLength{ length }
	{
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>::AudioStreamBase(BufferType* data, size_t length, ownership::copy)
		: m_pBuffer{ nullptr }
		, m_nLength{ length }
	{
		BufferType* newData = new BufferType[m_nLength];
		std::memcpy(newData, data, m_nLength * sizeof(BufferType));
		m_pBuffer = std::shared_ptr<BufferType>(newData, std::default_delete<BufferType[]>());
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - Constructors - By Shared Pointer

	//template <typename BufferType>
	//template <typename Deleter>
	//AudioStreamBase<BufferType>::AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::take_ownership, Deleter d)
	//{
	//}

	template <typename BufferType>
	AudioStreamBase<BufferType>::AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::no_ownership)
		: m_pBuffer{ data }
		, m_nLength{ length }
	{
	}

	//template <typename BufferType>
	//AudioStreamBase<BufferType>::AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::copy)
	//{
	//}

#pragma endregion

#pragma endregion

#pragma region AudioStreamBase<BufferType> - Methods

	template <typename BufferType>
	template <typename Function>
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::transform(Function&& func)
	{
		BufferType* ptr = m_pBuffer.get();
		for (int i = 0; i < m_nLength; ++i) {
			ptr[i] = func(ptr[i]);
		}
		return *this;
	}

	template <typename BufferType>
	template <typename Function>
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType, BufferType>, BufferType>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::transform(Function&& func, AudioStreamBase<BufferType> const& other)
	{
		BufferType* ptr = m_pBuffer.get();
		for (int i = 0; i < m_nLength; ++i) {
			ptr[i] = func(ptr[i], other[i]);
		}
		return *this;
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::shiftLeft(IntegralT const o) {
		return (*this) <<= o;
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::shiftRight(IntegralT const o) {
		return (*this) >>= o;
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::rotateLeft(IntegralT const o) {
		AudioStreamBase<BufferType> copy = this->clone();
		return ((*this) <<= o) += (copy >>= (m_nLength - o));
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::rotateRight(IntegralT const o) {
		AudioStreamBase<BufferType> copy = this->clone();
		return ((*this) >>= o) += (copy <<= (m_nLength - o));
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::clone() const
	{
		return AudioStreamBase<BufferType>(m_pBuffer.get(), m_nLength, ownership::COPY);
	}

	template <typename BufferType>
	BufferType* AudioStreamBase<BufferType>::begin() {
		return m_pBuffer.get();
	}

	template <typename BufferType>
	BufferType const* AudioStreamBase<BufferType>::begin() const {
		return m_pBuffer.get();
	}

	template <typename BufferType>
	BufferType* AudioStreamBase<BufferType>::end() {
		return m_pBuffer.get() + m_nLength;
	}

	template <typename BufferType>
	BufferType const* AudioStreamBase<BufferType>::end() const {
		return m_pBuffer.get() + m_nLength;
	}

	template <typename BufferType>
	size_t AudioStreamBase<BufferType>::size()
	{
		return m_nLength;
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - Static Methods

	template <typename BufferType>
	template <typename Function>
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType, BufferType>, BufferType>)
		AudioStreamBase<BufferType> AudioStreamBase<BufferType>::zipWith(AudioStreamBase<BufferType> const& a, AudioStreamBase<BufferType> const& b, Function&& func)
	{
		AudioStreamBase<BufferType> stream = a.clone();
		stream.transform(func, b);
		return stream;
	}

#pragma endregion

#pragma endregion
}

#pragma endregion
