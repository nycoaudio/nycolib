#pragma once

#include <memory>
#include "ownership.h"
#include <iostream>
#include <assert.h>


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
		explicit AudioStreamBase(BufferType* data, size_t length, ownership::take_ownership, Deleter d);

		explicit AudioStreamBase(BufferType* data, size_t length, ownership::no_ownership);

		explicit AudioStreamBase(BufferType* data, size_t length, ownership::copy);

		//template <typename Deleter>
		//explicit AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::take_ownership, Deleter d);

		explicit AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::no_ownership);

		//explicit AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::copy);

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
		requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
			AudioStreamBase<BufferType>& transform(Function&& func, AudioStreamBase<BufferType> const& other);

		AudioStreamBase<BufferType> clone() const;

		size_t size();

#pragma endregion

#pragma region Static Methods
	public:

		template <typename Function>
		requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
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

	//template <>
	//class AudioStream<double> : public AudioStreamBase<double> {
	//public:
	//	using AudioStreamBase<double>::AudioStreamBase;
	//};

	//template <>
	//class AudioStream<byte> : public AudioStreamBase<byte> {
	//public:
	//	using AudioStreamBase<byte>::AudioStreamBase;

	//};

	//template <>
	//class AudioStream<short> : public AudioStreamBase<short> {
	//public:
	//	using AudioStreamBase<short>::AudioStreamBase;
	//};

	//template <>
	//class AudioStream<float> : public AudioStreamBase<float> {
	//public:
	//	using AudioStreamBase<float>::AudioStreamBase;
	//};
}

#pragma endregion

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
		assert(x < m_nLength && x >= 0);
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
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator-(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator*(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator/(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator%(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator^(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator&(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator|(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator>>(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator<<(AudioStreamBase<BufferType> const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator+=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator-=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator*=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator/=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator%=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator^=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator&=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator|=(AudioStreamBase<BufferType> const& o)
	{
		// TODO: insert return statement here
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - AudioStreamBase<BufferType> OP BufferType

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator+(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator-(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator*(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator/(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator%(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator^(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator&(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator|(BufferType const& o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator+=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator-=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator*=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator/=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator%=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator^=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator&=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

	template <typename BufferType>
	AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator|=(BufferType const& o)
	{
		// TODO: insert return statement here
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - BufferType OP AudioStreamBase<BufferType>

	template <typename BufferType>
	AudioStreamBase<BufferType> operator+(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator-(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator*(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator/(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator%(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator^(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator&(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> operator|(BufferType const& a, AudioStreamBase<BufferType> const& b)
	{
		return AudioStreamBase<BufferType>();
	}

#pragma endregion

#pragma region AudioStreamBase<BufferType> - OPs - Binary OPs - AudioStreamBase<BufferType> OP Integral

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator<<(IntegralT const o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType> AudioStreamBase<BufferType>::operator>>(IntegralT const o) const
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator<<=(IntegralT const o)
	{
		return AudioStreamBase<BufferType>();
	}

	template <typename BufferType>
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::operator>>=(IntegralT const o)
	{
		return AudioStreamBase<BufferType>();
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
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
		AudioStreamBase<BufferType>& AudioStreamBase<BufferType>::transform(Function&& func, AudioStreamBase<BufferType> const& other)
	{
		BufferType* ptr = m_pBuffer.get();
		for (int i = 0; i < m_nLength; ++i) {
			ptr[i] = func(ptr[i], other[i]);
		}
		return this;
	}

	template <typename BufferType>
	AudioStreamBase<BufferType> AudioStreamBase<BufferType>::clone() const
	{
		return AudioStreamBase<BufferType>(m_pBuffer.get(), m_nLength, ownership::COPY);
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
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
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
