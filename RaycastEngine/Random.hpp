#pragma once

namespace utilities {
	namespace rng {

		class Xorshift {
		public:
			//Stav RNG
			unsigned int x;
			const int fmask = (1 << 23) - 1;
			Xorshift(const unsigned int seed) { x = seed; }
			int next() {
				x ^= x >> 6;
				x ^= x << 17;
				x ^= x >> 9;
				return int(x);
			}

			template<typename T>
			T numberInRange(T low, T high) {
				union {
					float f;
					int i;
				} u;
				u.i = (next() & fmask) | 0x3f800000;
				return low + (u.f - 1.f) * (high - low);
			}
		};
	}
}