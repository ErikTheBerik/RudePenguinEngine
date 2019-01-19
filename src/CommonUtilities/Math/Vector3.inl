#pragma once
#include <math.h>

//template<typename TYPE>
//Vector3<TYPE>::Vector3(const Vector3 &aVector3)
//{
//	x = aVector3.x;
//	y = aVector3.y;
//	z = aVector3.z;
//}

template<typename TYPE>
template<typename U>
Vector3<TYPE>::Vector3(const Vector3<U> &aVector3)
{
	x = static_cast<TYPE>(aVector3.x);
	y = static_cast<TYPE>(aVector3.y);
	z = static_cast<TYPE>(aVector3.z);
}

template<typename TYPE>
Vector3<TYPE>::Vector3(const TYPE aX, const TYPE aY, const TYPE aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

//projects a point on a line
template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::GetProjection(const Vector3<TYPE> &aPoint, const Vector3<TYPE> &aStart, const Vector3<TYPE> &aEnd)
{
	Vector3<TYPE> vec = aPoint - aStart;
	Vector3<TYPE> diff = aEnd - aStart;
	float final = vec.Dot(diff) / diff.Dot(diff);
	diff *= final;
	return aStart + diff;
}

template<typename TYPE>
Vector3<TYPE>::Vector3(const Vector4<TYPE> &aVector4)
{
	x = aVector4.x;
	y = aVector4.y;
	z = aVector4.z;
}

// template<typename TYPE>
// Vector3<TYPE>& Vector3<TYPE>::operator=(const Vector3 &aRight)
// {
// 	x = aRight.x;
// 	y = aRight.y;
// 	z = aRight.z;
// 	return (*this);
// }

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator+=(const Vector3 &aRight)
{
	x += aRight.x;
	y += aRight.y;
	z += aRight.z;
	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator-=(const Vector3 &aRight)
{
	x -= aRight.x;
	y -= aRight.y;
	z -= aRight.z;
	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator*=(const TYPE aRight)
{
	x *= aRight;
	y *= aRight;
	z *= aRight;
	return (*this);
}


template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator/=(const TYPE aRight)
{
	x /= aRight;
	y /= aRight;
	z /= aRight;
	return (*this);
}

template<typename TYPE>
TYPE Vector3<TYPE>::Length() const
{
	if (*this == Vector3<TYPE>::Zero)
	{
		return 0;
	}
	return static_cast<TYPE>(sqrt(Length2()));
}

template<typename TYPE>
TYPE Vector3<TYPE>::Length2() const
{
	TYPE returnVal = x*x + y*y + z*z;
	return returnVal;
}

template<typename TYPE>
TYPE Vector3<TYPE>::Dot(const Vector3 &aRight) const
{
	return ((x * aRight.x) + (y * aRight.y) + (z * aRight.z));
}

template<typename TYPE>
TYPE Vector3<TYPE>::Dot(const Vector3 &aLeft, const Vector3 &aRight)
{
	return ((aLeft.x * aRight.x) + (aLeft.y * aRight.y) + (aLeft.z * aRight.z));
}

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::GetNormalized(void) const
{
	return Normalize(*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::Normalize(void)
{
	float aLength = Length2();
	if (aLength != 0.0f)
	{
		return (*this) /= Length();
	}

	return *this;
}

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::Normalize(Vector3 aVector)
{
	float aLength = aVector.Length();
	if (aLength != 0.0f)
	{
		return aVector /= aLength;
	}

	return aVector;
}

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::HalfVector(const Vector3<TYPE> &aLeft, const Vector3<TYPE> &aRight)
{
	return (aLeft + aRight).GetNormalized();
}


template<typename TYPE>
TYPE Vector3<TYPE>::Manhattan(const Vector3 &aDestinationPoint) const
{
	return abs(aDestinationPoint.x - x) + abs(aDestinationPoint.y - y) + abs(aDestinationPoint.z - z);
}

template<typename TYPE>
TYPE Vector3<TYPE>::Manhattan(const Vector3 &anOriginPoint, const Vector3 &aDestinationPoint)
{
	return abs(aDestinationPoint.x - anOriginPoint.x) + abs(aDestinationPoint.y - anOriginPoint.y) + abs(aDestinationPoint.z - anOriginPoint.z);
}

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::Cross(const Vector3 &aLeft, const Vector3 &aRight)
{
	Vector3<TYPE> tempVector;
	tempVector.x = aLeft.y * aRight.z - aLeft.z * aRight.y;
	tempVector.y = aLeft.z * aRight.x - aLeft.x * aRight.z;
	tempVector.z = aLeft.x * aRight.y - aLeft.y * aRight.x;

	return tempVector;
}

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::Cross(const Vector3 &aRight) const
{
	Vector3<TYPE> tempVector;
	tempVector.x = y * aRight.z - z * aRight.y;
	tempVector.y = z * aRight.x - x * aRight.z;
	tempVector.z = x * aRight.y - y * aRight.x;

	return tempVector;
}