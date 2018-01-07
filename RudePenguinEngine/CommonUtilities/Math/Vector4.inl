#pragma once
#include <math.h>

template<typename TYPE>
Vector4<TYPE>::Vector4(void)
{
	x = static_cast<TYPE>(0);
	y = static_cast<TYPE>(0);
	z = static_cast<TYPE>(0);
	w = static_cast<TYPE>(0);
}

//template<typename TYPE>
//Vector4<TYPE>::Vector4(const Vector4 &aVector4)
//{
//	x = aVector4.x;
//	y = aVector4.y;
//	z = aVector4.z;
//	w = aVector4.w;
//}

template<typename TYPE>
template<typename U>
Vector4<TYPE>::Vector4(const Vector4<U> &aVector4)
{
	x = static_cast<TYPE>(aVector4.x);
	y = static_cast<TYPE>(aVector4.y);
	z = static_cast<TYPE>(aVector4.z);
	w = static_cast<TYPE>(aVector4.w);
}

template<typename TYPE>
Vector4<TYPE>::Vector4(const TYPE aX, const TYPE aY, const TYPE aZ, const TYPE aW)
{
	x = aX;
	y = aY;
	z = aZ;
	w = aW;
}

//template<typename TYPE>
//Vector4<TYPE>& Vector4<TYPE>::operator=(const Vector4 &aRight)
//{
//	x = aRight.x;
//	y = aRight.y;
//	z = aRight.z;
//	w = aRight.w;
//	return (*this);
//}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator+=(const Vector4 &aRight)
{
	x += aRight.x;
	y += aRight.y;
	z += aRight.z;
	w += aRight.w;
	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator-=(const Vector4 &aRight)
{
	x -= aRight.x;
	y -= aRight.y;
	z -= aRight.z;
	w -= aRight.w;
	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator*=(const TYPE aRight)
{
	x *= aRight;
	y *= aRight;
	z *= aRight;
	w *= aRight;
	return (*this);
}


template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator/=(const TYPE aRight)
{
	x /= aRight;
	y /= aRight;
	z /= aRight;
	w /= aRight;
	return (*this);
}

template<typename TYPE>
TYPE Vector4<TYPE>::Length() const
{
	return static_cast<TYPE>(sqrt(x*x + y*y + z*z + w*w));
}

template<typename TYPE>
TYPE Vector4<TYPE>::Length2() const
{
	return pow(Length(), 2);
}

template<typename TYPE>
TYPE Vector4<TYPE>::Dot(const Vector4 &aRight) const
{
	return ((x * aRight.x) + (y * aRight.y) + (z * aRight.z) + (w * aRight.w));
}

template<typename TYPE>
TYPE Vector4<TYPE>::Dot(const Vector4 &aLeft, const Vector4 &aRight)
{
	return ((aLeft.x * aRight.x) + (aLeft.y * aRight.y) + (aLeft.z * aRight.z) + (aLeft.w * aRight.w));
}

template<typename TYPE>
Vector4<TYPE> Vector4<TYPE>::GetNormalized(void) const
{
	return Normalize(*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::Normalize(void)
{
	return (*this) /= Length();
}

template<typename TYPE>
Vector4<TYPE> Vector4<TYPE>::Normalize(Vector4 aVector)
{
	return aVector /= aVector.Length();
}

template<typename TYPE>
TYPE Vector4<TYPE>::Manhattan(const Vector4 &aDestinationPoint) const
{
	return abs(aDestinationPoint.x - x) + abs(aDestinationPoint.y - y) + abs(aDestinationPoint.z - z) + abs(aDestinationPoint.w - w);
}

template<typename TYPE>
TYPE Vector4<TYPE>::Manhattan(const Vector4 &anOriginPoint, const Vector4 &aDestinationPoint)
{
	return abs(aDestinationPoint.x - anOriginPoint.x) + abs(aDestinationPoint.y - anOriginPoint.y) + abs(aDestinationPoint.z - anOriginPoint.z) + abs(aDestinationPoint.w - anOriginPoint.w);
}