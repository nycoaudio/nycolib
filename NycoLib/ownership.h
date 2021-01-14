#pragma once

#include <type_traits>


namespace nyco {
	template <typename T>
	struct empty_delete
	{
		empty_delete() /* noexcept */
		{
		}

		template <typename U>
		empty_delete(const empty_delete<U>&,
			typename std::enable_if<
			std::is_convertible<U*, T*>::value
			>::type* = nullptr) /* noexcept */
		{
		}

		void operator()(T* const) const /* noexcept */
		{
			// do nothing
		}
	};

	namespace ownership {
		struct take_ownership {};

		struct no_ownership {};

		struct copy {};

		template <typename T>
		struct is_ownership_struct : std::false_type {};

		template <>
		struct is_ownership_struct<take_ownership> : std::true_type {};

		template <>
		struct is_ownership_struct<no_ownership> : std::true_type {};

		template <>
		struct is_ownership_struct<copy> : std::true_type {};

		static constexpr auto COPY = copy{};
		static constexpr auto TAKE = take_ownership{};
		static constexpr auto NO_OWNERSHIP = no_ownership{};
	}
}
