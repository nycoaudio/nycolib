#ifndef NYCOLIB_AUDIO_STREAM_H
#define NYCOLIB_AUDIO_STREAM_H

/*
	Module: AudioStream (.h)

	Author: Binyamin Cohen @ NycoAudio

	Description:
		AudioStream contains the AudioStream class that defines common methods for working
		with streams of any type.

*/


#include <memory>
#include <iostream>
#include <assert.h>

#include "ownership.h"


#pragma region nyco - AudioStream - Declarations

namespace nyco {
using byte = unsigned char;

// forward declaration of AudioStreamBase
template <typename T>
class AudioStreamBase;

#pragma region AudioStreamBase<BufferType> friend functions forward declarations

// forward declarations for the AudioStream friend operators where AudioStream is the right operand

// BufferType + AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are shifted up by the value of a.
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator+(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType - AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are shifted down by the value of a.
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator-(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType * AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are scaled by the value of a.
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator*(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType / AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are scaled inversly by the value of a
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator/(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType % AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are the remainder of a divided by that value
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator%(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType ^ AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are the result of a XOR with a
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator^(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType & AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are the result of a AND with a
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator&(BufferType const& a, AudioStreamBase<BufferType> const& b);

// BufferType | AudioStreamBase<BufferType>
/*
* return a copy of b, where all values in it's buffer are the result of a OR with a
*/
template <typename BufferType>
AudioStreamBase<BufferType> operator|(BufferType const& a, AudioStreamBase<BufferType> const& b);

/*
* outputs a string representation of the audio stream to s.
*/
template <typename BufferType>
std::ostream& operator<<(std::ostream& s, AudioStreamBase<BufferType> const& stream);

#pragma endregion

template <typename BufferType>
class AudioStreamBase {

#pragma region Constructors
public:

	/*
	* constructs a new AudioStream and taking ownership over data with the specified deleter
	* a common deleter d = std::default_delete<BufferType[]>()
	*/
	template <typename Deleter>
	explicit AudioStreamBase(BufferType* data, size_t length, ownership::take_ownership, Deleter d);

	/*
	* constructs a new AudioStream pointing to data
	*/
	explicit AudioStreamBase(BufferType* data, size_t length, ownership::no_ownership);

	/*
	* constructs a new AudioStream and copying the buffer from data
	*/
	explicit AudioStreamBase(BufferType* data, size_t length, ownership::copy);

	/*
	* constructs a new AudioStream that points to a shared memory location
	* this does not take ownership
	*/
	explicit AudioStreamBase(std::shared_ptr<BufferType> data, size_t length, ownership::no_ownership);

	// Copy Constructor
	AudioStreamBase(AudioStreamBase<BufferType> const& stream) = delete;

	// Move Constructor
	AudioStreamBase(AudioStreamBase<BufferType>&& stream) = default;

#pragma endregion

#pragma region Methods
public:

	/*
	* does in-place transformation of the stream by the given function
	* applies func over every elements and assigns the result where the element was in the buffer
	*/
	template <typename Function>
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType>, BufferType>)
		AudioStreamBase<BufferType>& transform(Function&& func);

	/*
	* does in-place transformation of the stream by the given function and the given stream
	* applies func over every elements and assigns the result where the element was in the buffer
	* both AudioStreams must be the same length, or other has a length of 1
	*/
	template <typename Function>
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType, BufferType>, BufferType>)
		AudioStreamBase<BufferType>& transform(Function&& func, AudioStreamBase<BufferType> const& other);

	/*
	* shifts all elements in the stream to the left
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& shiftLeft(IntegralT const o);

	/*
	* shifts all elements in the stream to the right
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& shiftRight(IntegralT const o);

	/*
	* shifts (rotates) all elements in the stream to the left
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& rotateLeft(IntegralT const o);

	/*
	* shifts (rotates) all elements in the stream to the right
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& rotateRight(IntegralT const o);

	/*
	* makes a copy of the original AudioStream and returns it;
	*/
	AudioStreamBase<BufferType> clone() const;

	/*
	* returns a pointer to the first element of this AudioStream
	*/
	BufferType* begin();

	/*
	* returns a const pointer to the first element of this AudioStream
	*/
	BufferType const* begin() const;

	/*
	* returns a pointer to the last element of this AudioStream
	*/
	BufferType* end();

	/*
	* returns a const pointer to the last element of this AudioStream
	*/
	BufferType const* end() const;

	/*
	* returns the length of this AudioStream
	*/
	size_t size();

#pragma endregion

#pragma region Static Methods
public:

	/*
	* creates a new AudioStream from two streams and a function the operates over two elements
	*
	* same as copying the a and transforming it with func and b
	*/
	template <typename Function>
	requires (std::is_same_v<std::invoke_result_t<Function, BufferType, BufferType>, BufferType>)
		static AudioStreamBase<BufferType> zipWith(AudioStreamBase<BufferType> const& a, AudioStreamBase<BufferType> const& b, Function&& func);

#pragma endregion

#pragma region Operator Overloading

#pragma region Binary Operators

#pragma region AudioStreamBase<BufferType> OP AudioStreamBase<BufferType>
public:

	// AudioStreamBase<BufferType> + AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise addition
	*/
	AudioStreamBase<BufferType> operator+(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> - AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise subtraction
	*/
	AudioStreamBase<BufferType> operator-(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> * AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise multiplication
	*/
	AudioStreamBase<BufferType> operator*(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> / AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise division
	*/
	AudioStreamBase<BufferType> operator/(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> % AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise modulous
	*/
	AudioStreamBase<BufferType> operator%(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> ^ AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise XOR
	*/
	AudioStreamBase<BufferType> operator^(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> & AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise AND
	*/
	AudioStreamBase<BufferType> operator&(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> | AudioStreamBase<BufferType>
	/*
	* returns a new AudioStream where all elements are a result of memeber-wise OR
	*/
	AudioStreamBase<BufferType> operator|(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> >> AudioStreamBase<BufferType>
	/*
	* concats two AudioStreams. this is inserted before o
	*/
	AudioStreamBase<BufferType> operator>>(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> << AudioStreamBase<BufferType>
	/*
	* concats two AudioStreams. this is appended to o
	*/
	AudioStreamBase<BufferType> operator<<(AudioStreamBase<BufferType> const& o) const;

	// AudioStreamBase<BufferType> += AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise addition
	*/
	AudioStreamBase<BufferType>& operator+=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> -= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise subtraction
	*/
	AudioStreamBase<BufferType>& operator-=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> *= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise multiplication
	*/
	AudioStreamBase<BufferType>& operator*=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> /= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise division
	*/
	AudioStreamBase<BufferType>& operator/=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> %= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise modulous
	*/
	AudioStreamBase<BufferType>& operator%=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> ^= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise XOR
	*/
	AudioStreamBase<BufferType>& operator^=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> &= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise AND
	*/
	AudioStreamBase<BufferType>& operator&=(AudioStreamBase<BufferType> const& o);

	// AudioStreamBase<BufferType> |= AudioStreamBase<BufferType>
	/*
	* does in-place transformation of this AudioStream where all members are the result of member-wise OR
	*/
	AudioStreamBase<BufferType>& operator|=(AudioStreamBase<BufferType> const& o);

#pragma endregion

#pragma region AudioStreamBase<BufferType> OP BufferType
public:

	// AudioStreamBase<BufferType> + BufferType
	/*
	* returns transformed version of this AudioStream where all members are shifted up by o
	*/
	AudioStreamBase<BufferType> operator+(BufferType const& o) const;

	// AudioStreamBase<BufferType> - BufferType
	/*
	* returns transformed version of this AudioStream where all members are shifted down by o
	*/
	AudioStreamBase<BufferType> operator-(BufferType const& o) const;

	// AudioStreamBase<BufferType> * BufferType
	/*
	* returns transformed version of this AudioStream where all members are scaled by o
	*/
	AudioStreamBase<BufferType> operator*(BufferType const& o) const;

	// AudioStreamBase<BufferType> / BufferType
	/*
	* returns transformed version of this AudioStream where all members are scaled inversly by o
	*/
	AudioStreamBase<BufferType> operator/(BufferType const& o) const;

	// AudioStreamBase<BufferType> % BufferType
	/*
	* returns transformed version of this AudioStream where all members are the remainder of the division by o
	*/
	AudioStreamBase<BufferType> operator%(BufferType const& o) const;

	// AudioStreamBase<BufferType> ^ BufferType
	/*
	* returns transformed version of this AudioStream where all members are the result of a XOR
	*/
	AudioStreamBase<BufferType> operator^(BufferType const& o) const;

	// AudioStreamBase<BufferType> & BufferType
	/*
	* returns transformed version of this AudioStream where all members are the result of a AND
	*/
	AudioStreamBase<BufferType> operator&(BufferType const& o) const;

	// AudioStreamBase<BufferType> | BufferType
	/*
	* returns transformed version of this AudioStream where all members are the result of a OR
	*/
	AudioStreamBase<BufferType> operator|(BufferType const& o) const;

	// AudioStreamBase<BufferType> += BufferType
	/*
	* does in-place transformation of this AudioStream where all members are shifted up by o
	*/
	AudioStreamBase<BufferType>& operator+=(BufferType const& o);

	// AudioStreamBase<BufferType> -= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are shifted down by o
	*/
	AudioStreamBase<BufferType>& operator-=(BufferType const& o);

	// AudioStreamBase<BufferType> *= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are scaled by o
	*/
	AudioStreamBase<BufferType>& operator*=(BufferType const& o);

	// AudioStreamBase<BufferType> /= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are scaled inversly by o
	*/
	AudioStreamBase<BufferType>& operator/=(BufferType const& o);

	// AudioStreamBase<BufferType> %= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are the remainder of the division by o
	*/
	AudioStreamBase<BufferType>& operator%=(BufferType const& o);

	// AudioStreamBase<BufferType> ^= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are the result of a XOR
	*/
	AudioStreamBase<BufferType>& operator^=(BufferType const& o);

	// AudioStreamBase<BufferType> &= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are the result of a AND
	*/
	AudioStreamBase<BufferType>& operator&=(BufferType const& o);

	// AudioStreamBase<BufferType> |= BufferType
	/*
	* does in-place transformation of this AudioStream where all members are the result of a OR
	*/
	AudioStreamBase<BufferType>& operator|=(BufferType const& o);

#pragma endregion

#pragma region BufferType OP AudioStreamBase<BufferType>
private:

	// BufferType + AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are shifted up by o
	*/
	friend AudioStreamBase<BufferType> operator+(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType - AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are negated and shifted up by o
	*/
	friend AudioStreamBase<BufferType> operator-(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType * AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are scaled by o
	*/
	friend AudioStreamBase<BufferType> operator*(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType / AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are inversed and scaled up by o
	*/
	friend AudioStreamBase<BufferType> operator/(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType % AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are the result of o mod member
	*/
	friend AudioStreamBase<BufferType> operator%(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType ^ AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are the result of a XOR
	*/
	friend AudioStreamBase<BufferType> operator^(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType & AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are the result of a AND
	*/
	friend AudioStreamBase<BufferType> operator&(BufferType const& a, AudioStreamBase<BufferType> const& b);

	// BufferType | AudioStreamBase<BufferType>
	/*
	* returns transformed version of this AudioStream where all members are the result of a OR
	*/
	friend AudioStreamBase<BufferType> operator|(BufferType const& a, AudioStreamBase<BufferType> const& b);

#pragma endregion

#pragma region AudioStreamBase<BufferType> shift by integral
public:

	// AudioStreamBase<BufferType> << integral
	/*
	* returns a copy of the AudioStream where all elements in the stream are shifted to the left
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType> operator<<(IntegralT const o) const;

	// AudioStreamBase<BufferType> >> integral
	/*
	* returns a copy of the AudioStream where all elements in the stream are shifted to the right
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType> operator>>(IntegralT const o) const;

	// AudioStreamBase<BufferType> <<= integral
	/*
	* shifts all elements in the stream to the left
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		AudioStreamBase<BufferType>& operator<<=(IntegralT const o);

	// AudioStreamBase<BufferType> >>= integral
	/*
	* shifts all elements in the stream to the right
	*/
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
	/*
	* returns a copy of this AudioStream
	*/
	AudioStreamBase<BufferType> operator+() const;

	// - AudioStreamBase<BufferType>
	/*
	* returns a negated copy of this AudioStream
	*/
	AudioStreamBase<BufferType> operator-() const;

	// ~ AudioStreamBase<BufferType>
	/*
	* returns a bitwise-not copy of this AudioStream
	*/
	AudioStreamBase<BufferType> operator~() const;

#pragma endregion

#pragma region Indexing Operators
public:

	// AudioStreamBase<BufferType>[integral]
	/*
	* returns the i-th element in this AudioStream
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		BufferType& operator[](IntegralT i);

	// AudioStreamBase<BufferType>[integral]
	/*
	* returns the i-th element in this AudioStream
	*/
	template <typename IntegralT>
	requires (std::is_integral_v<IntegralT>)
		BufferType const& operator[](IntegralT i) const;

	// AudioStreamBase<BufferType>[floating_point]
	/*
	* retuens the lement in the relative position in this AudioStream (where 0 <= x <= 1)
	* might be removed in the future
	*/
	template <typename FloatingT>
	requires (std::is_floating_point_v<FloatingT>)
		BufferType& operator[](FloatingT x);

	// AudioStreamBase<BufferType>[floating_point]
	/*
	* retuens the lement in the relative position in this AudioStream (where 0 <= x <= 1)
	* might be removed in the future
	*/
	template <typename FloatingT>
	requires (std::is_floating_point_v<FloatingT>)
		BufferType const& operator[](FloatingT x) const;

#pragma endregion

#pragma region ostream << Overload
private:

	// ostream& << AudioStreamBase<BufferType>
	/*
	* outputs a string representation of the audio stream to s.
	*/
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
	if (other.m_nLength == 1) {
		return transform([func](BufferType a) {
			return func(a, other[0]);
			});
	}
	assert(m_nLength == other.m_nLength);
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

#endif // !NYCOLIB_AUDIO_STREAM_H
