#ifndef LIBQPUASM_UINTX_H
#define LIBQPUASM_UINTX_H

#include <limits>
#include <cstdint>
#include <cassert>

namespace qpuasm
{
	namespace detail
	{
		template<typename T, uint64_t s>
		struct uint_most_T
		{
		private:
			static_assert((uint64_t)std::numeric_limits<T>::max() >= ((uint64_t)1 << s) - 1,
				"Error: Base type is not large enough to hold an integer of desired size.");
			
			static constexpr T mask = (T)(((uint64_t)1 << s) - 1);
			
			T val;

		public:
			typedef T type;
			static constexpr uint64_t bits = s;

			uint_most_T() = default;
			template<typename U>
			uint_most_T(const U& v) :
				val(static_cast<T>(val) & mask)
			{
				// Shouldn't be created with a value that is
				// to large to be held
				assert((val & ~mask) == 0);
			}

			template<typename U = T>
			operator U() const
			{
				return static_cast<T>(val);
			}
			template<typename U>
			uint_most_T& operator=(const U& v)
			{
				val = static_cast<T>(v) & mask;

				// Shouldn't be created with a value that is
				// to large to be held
				assert((val & ~mask) == 0);
				return *this;
			}
		};

		template<uint64_t s, bool c1, bool c2, bool c3>
		struct type_selector;

		template<uint64_t s>
		struct type_selector<s, false, false, false>
		{
			typedef uint64_t type;
		};
		template<uint64_t s>
		struct type_selector<s, false, false, true>
		{
			typedef uint32_t type;
		};
		template<uint64_t s>
		struct type_selector<s, false, true, true>
		{
			typedef uint16_t type;
		};
		template<uint64_t s>
		struct type_selector<s, true, true, true>
		{
			typedef uint8_t type;
		};
	}

	template<uint64_t s>
	using uint = detail::uint_most_T<typename detail::type_selector<s, (s <= 8), (s <= 16), (s <= 32)>::type, s>;
}

#endif
