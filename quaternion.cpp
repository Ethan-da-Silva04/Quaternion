
#include <cmath>
template<typename T>
struct Quaternion {
	T re_part;
	T i_part;
	T j_part;
	T k_part;

	Quaternion<T>(T re_part = 0, T i_part = 0, T j_part = 0, T k_part = 0)
		: re_part(re_part), i_part(i_part), j_part(j_part), k_part(k_part) {}

	T magnitude_sq() const {
		T sum = 0;
		const T* ptr = (const T*) (this);
		for (size_t i = 0; i < 4; i++) {
			T value = *ptr++;
			sum += value * value;
		}
		return sum;
	}

	T magnitude() const {
		return std::sqrt(magnitude_sq());
	}

	void normalize() {
		*this = (*this) / magnitude();	
	}

	constexpr Quaternion<T> conjugate() {
		return Quaternion<T>(re_part, -i_part, -j_part, -k_part);
	}

	constexpr Quaternion<T> inverse() {
		return (1 / magnitude_sq()) * conjugate();
	}

	friend constexpr Quaternion<T> operator+(const Quaternion<T>& fst, const Quaternion<T> snd) {
		return Quaternion<T>(fst.re_part + snd.re_part, fst.i_part + snd.i_part, fst.j_part + snd.j_part, fst.k_part + snd.k_part);
	}

	friend constexpr Quaternion<T> operator-(const Quaternion<T>& fst) {
		return Quaternion<T>(-fst.re_part, -fst.i_part, -fst.j_part, -fst.k_part);
	}

	friend constexpr Quaternion<T> operator*(T x, const Quaternion<T>& q) {
		return Quaternion<T>(x * q.re_part, x * q.i_part, x * q.j_part, x * q.k_part);
	}

	friend constexpr Quaternion<T> operator/(T x, const Quaternion<T>& q) {
		return (1 / x) * q;
	}

	friend constexpr Quaternion<T> operator-(const Quaternion<T>& fst, const Quaternion<T>& snd) {
		return fst + (-snd);
	}

	friend constexpr Quaternion<T> operator*(const Quaternion<T>& fst, const Quaternion<T>& snd) {
		return Quaternion<T>(
			fst.re_part * snd.re_part - fst.i_part * snd.i_part - fst.j_part * snd.j_part - fst.k_part * snd.k_part,
			fst.re_part * snd.i_part + fst.i_part * snd.re_part + fst.j_part * snd.k_part - fst.k_part * snd.j_part,
			fst.re_part * snd.j_part - fst.i_part * snd.k_part + fst.j_part * snd.re_part + fst.k_part * snd.i_part,
			fst.re_part * snd.k_part + fst.i_part * snd.j_part - fst.j_part * snd.i_part + fst.k_part * snd.re_part
		);
	}
};
