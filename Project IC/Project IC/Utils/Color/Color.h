#pragma once
#include "../Math/Math.h"

using byte = unsigned char;

struct Color_t { byte r = 0, g = 0, b = 0, a = 0; };

namespace Color
{
	inline float TOFLOAT(byte x) {
		return (static_cast<float>(x) / 255.0f);
	}

	inline Vec3 TOVEC3(const Color_t &x) {
		return Vec3(TOFLOAT(x.r), TOFLOAT(x.g), TOFLOAT(x.b));
	}
}