#pragma once

template<typename TYPE>
class Vector2
{
public:		// Construction
			//
	Vector2(void);
	Vector2(const Vector2 &aVector2) = default;
	template<typename U> explicit Vector2(const Vector2<U> &aVector2);
	Vector2(const TYPE anX, const TYPE aY);

	// Arithmetic
	//
	friend Vector2 operator +(Vector2 aLeft, const Vector2 &aRight)
	{
		return aLeft += aRight;
	}


	friend Vector2 operator -(Vector2 aLeft, const Vector2 &aRight)
	{
		//@TODO: Fugure out how we can test this
		return aLeft -= aRight;
	}


	friend Vector2 operator *(Vector2 aLeft, const TYPE aRight)
	{
		return aLeft *= aRight;
	}


	friend Vector2 operator /(Vector2 aLeft, const TYPE aRight)
	{
		return aLeft /= aRight;
	}


	friend Vector2 operator -(Vector2 aRight)
	{
		return aRight * static_cast<TYPE>(-1);
	}

	// Comparison
	//
	friend bool operator ==(const Vector2 &aLeft, const Vector2 &aRight)
	{
		if (aLeft.x == aRight.x &&
			aLeft.y == aRight.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	friend bool operator !=(const Vector2 &aLeft, const Vector2 &aRight)
	{
		return !(aLeft == aRight);
	}

	// Assignment
	//
	Vector2 &operator =(const Vector2 &aRight) = default; 

	// Compound assignment
	//
	Vector2 &operator +=(const Vector2 &aRight);
	Vector2 &operator -=(const Vector2 &aRight);
	Vector2 &operator *=(const TYPE aRight);
	Vector2 &operator /=(const TYPE aRight);

	// Info
	//
	TYPE Length(void) const;
	TYPE Length2(void) const;
	TYPE Dot(const Vector2<TYPE> &aRight) const;
	Vector2 GetNormalized(void) const;
	TYPE Manhattan(const Vector2<TYPE> &aRight) const;

	// Manipulation
	//
	Vector2 &Normalize(void);

	union
	{
		TYPE    x,
			u;
	};

	union
	{
		TYPE    y,
			v;
	};

	static TYPE Dot(const Vector2 &aFirstVector, const Vector2 &aSecondVector);
	static Vector2<TYPE> Project(const Vector2<TYPE> &aFirst, const Vector2<TYPE> &aSecond);
	static Vector2 Normalize(Vector2 aVector);
	static TYPE Manhattan(const Vector2<TYPE> &aLeft, const Vector2<TYPE> &aRight);

	static const Vector2	Zero,
		UnitX,
		UnitY,
		One,
		Up,
		Down,
		Right,
		Left,
		Half;
};

using Vector2c = Vector2<char>;
using Vector2i = Vector2<int>;
using Vector2ui = Vector2<unsigned int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

using Point2c = Vector2<char>;
using Point2i = Vector2<int>;
using Point2ui = Vector2<unsigned int>;
using Point2f = Vector2<float>;
using Point2d = Vector2<double>;

template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Zero(0, 0);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::UnitX(1, 0);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::UnitY(0, 1);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::One(1, 1);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Up(0, 1);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Down(0, -1);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Right(1, 0);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Left(-1, 0);
template<typename TYPE> const Vector2<TYPE> Vector2<TYPE>::Half(static_cast<TYPE>(0.5), static_cast<TYPE>(0.5));

#include "Vector2.inl"
