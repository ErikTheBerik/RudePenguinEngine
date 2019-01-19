#pragma once
#include <math.h>

template<typename TYPE>
Vector2<TYPE>::Vector2(void)
{
	x = static_cast<TYPE>(0);
	y = static_cast<TYPE>(0);
}

//template<typename TYPE>
//Vector2<TYPE>::Vector2(const Vector2 &aVector2)
//{
//	x = aVector2.x;
//	y = aVector2.y;
//}

template<typename TYPE>
template<typename U>
Vector2<TYPE>::Vector2(const Vector2<U> &aVector2)
{
	x = static_cast<TYPE>(aVector2.x);
	y = static_cast<TYPE>(aVector2.y);
}

template<typename TYPE>
Vector2<TYPE>::Vector2(const TYPE aX, const TYPE aY)
{
	x = aX;
	y = aY;
}

//template<typename TYPE>
//Vector2<TYPE>& Vector2<TYPE>::operator=(const Vector2 &aRight)
//{
//	x = aRight.x;
//	y = aRight.y;
//	return (*this);
//}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator+=(const Vector2 &aRight)
{
	x += aRight.x;
	y += aRight.y;
	return (*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator-=(const Vector2 &aRight)
{
	x -= aRight.x;
	y -= aRight.y;
	return (*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator*=( const TYPE aRight )
{
	x *= aRight;
	y *= aRight;
	return (*this);
}


template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator/=(const TYPE aRight)
{
	x /= aRight;
	y /= aRight;
	return (*this);
}

template<typename TYPE>
TYPE Vector2<TYPE>::Length() const
{
	return static_cast<TYPE>(sqrt(Length2()));
}

template<typename TYPE>
TYPE Vector2<TYPE>::Length2() const
{
	return x*x + y*y;
}

template<typename TYPE>
TYPE Vector2<TYPE>::Dot(const Vector2 &aRight) const
{
	return ((x * aRight.x) + (y * aRight.y));
}

template<typename TYPE>
TYPE Vector2<TYPE>::Dot(const Vector2 &aLeft, const Vector2 &aRight)
{
	return ((aLeft.x * aRight.x) + (aLeft.y * aRight.y));
}

template<typename TYPE>
Vector2<TYPE> Vector2<TYPE>::GetNormalized(void) const
{
	return Normalize(*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::Normalize(void)
{
	if (Length2() == 0)
	{
		y = 0;
		x = 0;
	}
	return (*this) /= Length();
}

template<typename TYPE>
Vector2<TYPE> Vector2<TYPE>::Normalize(Vector2 aVector)
{
	if (aVector.Length2() == 0)
	{
		return Vector2<TYPE>::Zero;
	}
	return aVector /= aVector.Length();
}

template<typename TYPE>
Vector2<TYPE> Vector2<TYPE>::Project(const Vector2<TYPE> &aFirst, const Vector2<TYPE> &aSecond)
{
	Vector2<TYPE> proj;
	const TYPE dot = Vector2<TYPE>::Dot(aFirst, aSecond);
	const TYPE length2 = aSecond.Length2();
	proj = aSecond * (dot / length2);

	return proj;
}

template<typename TYPE>
TYPE Vector2<TYPE>::Manhattan(const Vector2 &aDestinationPoint) const
{
	return abs(aDestinationPoint.x - x) + abs(aDestinationPoint.y - y);
}

template<typename TYPE>
TYPE Vector2<TYPE>::Manhattan(const Vector2 &anOriginPoint, const Vector2 &aDestinationPoint)
{
	return abs(aDestinationPoint.x - anOriginPoint.x) + abs(aDestinationPoint.y - anOriginPoint.y);
}