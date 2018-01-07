#include "Quaternion.h"
#include <iostream>
#include "..\Debug\DL_Assert.h"
Quaternion::Quaternion(float aRotationX, float aRotationY, float aRotationZ, float aRotationAmount, bool aNormalize) 
	: myRotation(aRotationX, aRotationY, aRotationZ), myRotationAmount(aRotationAmount)
{
	if (aNormalize == true)
	{
		Normalize();
	}
}

Quaternion::Quaternion(const Vector3f &aRotation, float aRotationAmount /*= 1.0f*/, bool aNormalize)
	:Quaternion(aRotation.x, aRotation.y, aRotation.z, aRotationAmount, aNormalize)
{

}

Quaternion::Quaternion(const Vector4f & aRotationAndAmount /*= Vector4f(0.0f, 0.0f, 0.0f, 1.0f)*/, bool aNormalize)
	:Quaternion(aRotationAndAmount.x, aRotationAndAmount.y, aRotationAndAmount.z, aRotationAndAmount.w, aNormalize)
{

}

Quaternion::Quaternion(Matrix44f pm)
{
	float wsqrdminus1 = pm.m11 + pm.m22 + pm.m33;
	float xsqrdminus1 = pm.m11 - pm.m22 - pm.m33;
	float ysqrdminus1 = pm.m22 - pm.m11 - pm.m33;
	float zsqrdminus1 = pm.m33 - pm.m11 - pm.m22;
	int biggestindex = 0;
	float biggest = wsqrdminus1;
	if (xsqrdminus1 > biggest) {
		biggest = xsqrdminus1;
		biggestindex = 1;
	}
	if (ysqrdminus1 > biggest) {
		biggest = ysqrdminus1;
		biggestindex = 2;
	}
	if (zsqrdminus1 > biggest) {
		biggest = zsqrdminus1;
		biggestindex = 3;
	}
	float biggestval = sqrtf(biggest + 1.0f)*.5f;
	float mult = .25f / biggestval;
	switch (biggestindex) {
	case 0:
		myRotationAmount = biggestval;
		myRotation.x = (pm.m23 - pm.m32) * mult;
		myRotation.y = (pm.m31 - pm.m13) * mult;
		myRotation.z = (pm.m12 - pm.m21) * mult;
		break;
	case 1:
		myRotation.x = biggestval;
		myRotationAmount = (pm.m23 - pm.m32) * mult;
		myRotation.y = (pm.m12 + pm.m21) * mult;
		myRotation.z = (pm.m31 + pm.m13) * mult;
		break;
	case 2:
		myRotation.y = biggestval;
		myRotationAmount = (pm.m31 - pm.m13) * mult;
		myRotation.x = (pm.m12 + pm.m21) * mult;
		myRotation.z = (pm.m23 + pm.m32) * mult;
		break;
	case 3:
		myRotation.z = biggestval;
		myRotationAmount = (pm.m13 - pm.m21) * mult;
		myRotation.x = (pm.m31 + pm.m13) * mult;
		myRotation.y = (pm.m23 + pm.m32) * mult;
		break;
	};
}

Quaternion Quaternion::LookRotation(const Vector3f& aForward, const Vector3f& aUp)
{
	const Vector3f forward = aForward.GetNormalized();
	const Vector3f right = Vector3f::Cross(aUp, forward).GetNormalized();
	const Vector3f up = Vector3f::Cross(forward, right);
	const float m00 = right.x;
	const float m01 = right.y;
	const float m02 = right.z;
	const float m10 = up.x;
	const float m11 = up.y;
	const float m12 = up.z;
	const float m20 = forward.x;
	const float m21 = forward.y;
	const float m22 = forward.z;

	float num8 = m00 + m11 + m22;
	Quaternion quaternion;
	if (num8 > 0.f)
	{
		float num = sqrtf(num8 + 1.f);
		quaternion.myRotationAmount = num * 0.5f;
		num = 0.5f / num;
		quaternion.myRotation.x = (m12 - m21) * num;
		quaternion.myRotation.y = (m20 - m02) * num;
		quaternion.myRotation.z = (m01 - m10) * num;
		return quaternion;
	}
	if (m00 >= m11 && m00 >= m22)
	{
		const float num7 = sqrtf(1.f + m00 - m11 - m22);
		const float num4 = 0.5f / num7;
		quaternion.myRotation.x = 0.5f * num7;
		quaternion.myRotation.y = (m01 + m10) * num4;
		quaternion.myRotation.z = (m02 + m20) * num4;
		quaternion.myRotationAmount = (m12 - m21) * num4;
		return quaternion;
	}
	if (m11 > m22)
	{
		const float num6 = sqrtf(1.f + m11 - m00 - m22);
		const float num3 = 0.5f / num6;
		quaternion.myRotation.x = (m10 + m01) * num3;
		quaternion.myRotation.y = 0.5f * num6;
		quaternion.myRotation.z = (m21 + m12) * num3;
		quaternion.myRotationAmount = (m20 - m02) * num3;
		return quaternion;
	}
	auto num5 = sqrtf(1.f + m22 - m00 - m11);
	auto num2 = 0.5f / num5;
	quaternion.myRotation.x = (m20 + m02) * num2;
	quaternion.myRotation.y = (m21 + m12) * num2;
	quaternion.myRotation.z = 0.5f * num5;
	quaternion.myRotationAmount = (m01 - m10) * num2;
	return quaternion;

}

void Quaternion::RotateTowardsPoint(const Vector3f & aCurrentPosition, const Vector3f & aTargetPosition)
{
	bool angleIsPositive = false;
	const Vector3f CurrentDirection = GetForward().GetNormalized();
	const float sign = GetRight().GetNormalized().Dot(aTargetPosition - aCurrentPosition); //Sign is positive to the right, negative to the left
	Vector3f rotAxis;

	if (sign > 0.0001f) // right
	{
		rotAxis = Vector3f::Cross(CurrentDirection, aTargetPosition - aCurrentPosition);
		angleIsPositive = true;
	}
	else if (sign < 0.0001f) //left
	{
		rotAxis = Vector3f::Cross(aTargetPosition - aCurrentPosition, CurrentDirection);
		angleIsPositive = false;
	}
	else //on track or point is precisely behind us
	{
		return;
	}

	// if this is true, then we are on the opposite course :[ (or right course, but we handled that before we called the function)
	if (isnan(rotAxis.z) == true || isnan(rotAxis.y) == true || isnan(rotAxis.x) == true || rotAxis == Vector3f::Zero)
	{
		return;
	}

	float angle = Vector3f::GetAngleFromCross(rotAxis);

	if (isnan(angle) == true || angle == 0.f)
	{
		return;
	}
	  
	if (angleIsPositive == false)
	{
		angle *= -1.f;
	}

	RotateAlongAxis(rotAxis, angle);
}

void Quaternion::Normalize()
{
	float magnitude = sqrtf(myRotation.x * myRotation.x + myRotation.y * myRotation.y + myRotation.z * myRotation.z + myRotationAmount * myRotationAmount);

	myRotation.x /= magnitude;
	myRotation.y /= magnitude;
	myRotation.z /= magnitude;
	myRotationAmount /= magnitude;
}
//
//Quaternion Quaternion::CreateFromVectorsYlf(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp)
//{
//	Vector3f newForward = (aEndPosition - aStartPosition);
//
//	//stolen from Nicos Look at and modified by Ylf
//
//	Vector3f newRight = (Vector3f::Cross(aUp.GetNormalized(), newForward)).GetNormalized();
//	Vector3f newUp = (Vector3f::Cross(newForward, newRight.GetNormalized())).GetNormalized();
//	newForward.Normalize();
//
//	float yAxisOffsetInZAxis = Vector3f(0.f, 0.f, 1.f).Dot(newUp);
//	float yAxisOffsetInXAxis = Vector3f(1.f, 0.f, 0.f).Dot(newUp);
//
//	float xAxisOffsetInYAxis = Vector3f(0.f, 1.f, 0.f).Dot(newRight);
//	float xAxisOffsetInZAxis = Vector3f(0.f, 0.f, 1.f).Dot(newRight);
//
//	float zAxisOffsetInXAxis = Vector3f(1.f, 0.f, 0.f).Dot(newForward);
//	float zAxisOffsetInYAxis = Vector3f(0.f, 1.f, 0.f).Dot(newForward);
//
//	float offsetXAxisRot = Vector3f::GetAngleBetween(Vector3f(1.f, 0.f, 0.f), newRight);
//	float offsetYAxisRot = Vector3f::GetAngleBetween(Vector3f(0.f, 1.f, 0.f), newUp);
//	float offsetZAxisRot = Vector3f::GetAngleBetween(Vector3f(0.f, 0.f, 1.f), newForward);
//
//	Quaternion quaternion;
//	//Rotate around y
//
//
//	//quaternion.RotateAroundLocalY(offsetXAxisRot);
//	return quaternion;
//	//----
//
//	//Vector3f newForward = Vector3f::Normalize(aEndPosition - aStartPosition);
//
//
//	//Quaternion quaternion;
//	//quaternion.Rotate();
//	//return quaternion;
//}



void Quaternion::RotateAlongAxis(const Vector3f &aAxis, float aRotationAmount)
{
	/*
	local_rotation.x = axis.x * sinf(fAngle / 2)
	local_rotation.y = axis.y * sinf(fAngle / 2)
	local_rotation.z = axis.z * sinf(fAngle / 2)
	local_rotation.w = cosf(fAngle / 2)
	*/

	Quaternion localRotation;
	localRotation.myRotation.x = aAxis.x * sinf(aRotationAmount / 2.f);
	localRotation.myRotation.y = aAxis.y * sinf(aRotationAmount / 2.f);
	localRotation.myRotation.z = aAxis.z * sinf(aRotationAmount / 2.f);
	localRotation.myRotationAmount = cosf(aRotationAmount / 2.f);

	*this = localRotation * *this;
}

void Quaternion::RotateWorld(const Vector3f& aRotationAmount)
{
	RotateWorldX(aRotationAmount.x);
	RotateWorldY(aRotationAmount.y);
	RotateWorldZ(aRotationAmount.z);
}

void Quaternion::RotateWorldX(float aRotationAmount)
{
	RotateAlongAxis(Vector3f(1.0f, 0.0f, 0.0f), aRotationAmount);
}

void Quaternion::RotateWorldY(float aRotationAmount)
{
	RotateAlongAxis(Vector3f(0.0f, 1.0f, 0.0f), aRotationAmount);
}

void Quaternion::RotateWorldZ(float aRotationAmount)
{
	RotateAlongAxis(Vector3f(0.0f, 0.0f, 1.0f), aRotationAmount);
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3f &aAxis, const float anAngle)
{
	float halfAngle = anAngle * .5f;
	float s = sinf(halfAngle);
	Quaternion q;
	q.myRotation.x = aAxis.x * s;
	q.myRotation.y = aAxis.y * s;
	q.myRotation.z = aAxis.z * s;
	q.myRotationAmount = cosf(halfAngle);
	return q;
}

void Quaternion::RotateLocal(const Vector3f& aRotationAmount)
{
	RotateLocalX(aRotationAmount.x);
	RotateLocalY(aRotationAmount.y);
	RotateLocalZ(aRotationAmount.z);
}

void Quaternion::RotateLocalX(float aRotationAmount)
{
	RotateAlongAxis(GetRight(), aRotationAmount);
}

void Quaternion::RotateLocalY(float aRotationAmount)
{
	RotateAlongAxis(GetUp(), aRotationAmount);
}

void Quaternion::RotateLocalZ(float aRotationAmount)
{
	RotateAlongAxis(GetForward(), aRotationAmount);
}


Vector3f Quaternion::ToEuler()  const
{
	float sp = -2.0f * (myRotation.y * myRotation.z - myRotationAmount*myRotation.x);// Extract sinf(pitch)

	float pitch, roll, yaw;

	if (fabs(sp) > 0.9999f) {// Check for Gimbel lock, giving slight tolerance for numerical imprecision
		pitch = (3.141592f / 2.f) * sp;// Looking straight up or down
		yaw = atan2(-myRotation.x*myRotation.z + myRotationAmount*myRotation.y, 0.5f - myRotation.y*myRotation.y - myRotation.z*myRotation.z);// Compute heading, slam roll to zero
		roll = 0.0f;
	}
	else {// Compute angles.  We don't have to use the "safe" asin function because we already checked for range errors when checking for Gimbel lock
		pitch = asinf(sp);
		yaw = atan2(myRotation.x*myRotation.z + myRotationAmount * myRotation.y, 0.5f - myRotation.x*myRotation.x - myRotation.y*myRotation.y);
		roll = atan2(myRotation.x*myRotation.y + myRotationAmount*myRotation.z, 0.5f - myRotation.x*myRotation.x - myRotation.z*myRotation.z);
	}

	return Vector3f(pitch, roll, yaw);
}

//taken from http://nic-gamedev.blogspot.se/2011/11/quaternion-math-getting-local-axis.html
Vector3f Quaternion::GetRight() const
{
	return *this * Vector3f(1.0f, 0.0f, 0.0f);
}

Vector3f Quaternion::GetLeft() const
{
	return -GetRight();
}

Vector3f Quaternion::operator*(const Vector3f& aRight) const
{
	//shamelessly stolen from http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
	Vector3f quaternionAsVector(myRotation.x, myRotation.y, myRotation.z);
	float scalar = myRotationAmount;

	Vector3f firstTest = quaternionAsVector * 2.0f * Vector3f::Dot(quaternionAsVector, aRight);
	Vector3f secondTest = aRight * (scalar*scalar - Vector3f::Dot(quaternionAsVector, quaternionAsVector));
	Vector3f thirdTest = Vector3f::Cross(quaternionAsVector, aRight) * scalar * 2.0f;

	return Vector3f(
		firstTest
		+ secondTest
		+ thirdTest);
}

Vector3f Quaternion::GetUp() const
{
	return *this * Vector3f(0.0f, 1.0f, 0.0f);
}

Vector3f Quaternion::GetDown() const
{
	return -GetUp();
}

Vector3f Quaternion::GetForward() const
{
	return *this * Vector3f(0.0f, 0.0f, 1.0f);
}

Vector3f Quaternion::GetBackward() const
{
	return -GetForward();
}

//	Roll = Z Rotation
float Quaternion::GetRoll() const
{
	return ToEuler().y;
	//return atan2f(2 * myRotation.y * myRotationAmount - 2 * myRotation.x * myRotation.z, 1 - 2 * myRotation.y * myRotation.y - 2 * myRotation.z * myRotation.z);
}

//	Pitch = X Rotation
float Quaternion::GetPitch() const
{
	return ToEuler().x;
	//return atan2f(2 * myRotation.x * myRotationAmount - 2 * myRotation.y * myRotation.z, 1 - 2 * myRotation.x * myRotation.x - 2 * myRotation.z * myRotation.z);
}

//	Yaw = Y Rotation
float Quaternion::GetYaw() const
{
	return ToEuler().z;
	/*
	float testVal = -2 * (myRotation.x * myRotation.z - myRotationAmount * myRotation.y); //asin(-2.0*(q.x*q.z - q.w*q.y));
	if (testVal > 1.0f)
	{
		testVal -= 2.f;
	}
	else if (testVal < -1.0f)
	{
		testVal += 2.f;
	}
	float returnValue = asinf(testVal);

	assert(!isnan(returnValue));
	return returnValue;*/
}

Quaternion Quaternion::LookAt(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp)
{
  	Vector3f forwardVector = Vector3f::Normalize(aEndPosition - aStartPosition);

	float dot = Vector3f::Dot(Vector3f(0.0f, 0.0f, 1.0f), forwardVector);

	if (std::abs(dot - (-1.0f)) < 0.000001f)
	{
		return Quaternion(aUp, 3.1415926535897932f);
	}
	if (std::abs(dot - (1.0f)) < 0.000001f)
	{
		return Quaternion();
	}

	float rotAngle = (float)std::acosf(dot);
	Vector3f rotAxis = Vector3f::Cross(Vector3f(0.0f, 0.0f, 1.0f), forwardVector);
	rotAxis = Vector3f::Normalize(rotAxis);

	Quaternion quaternion;
	quaternion.RotateAlongAxis(rotAxis, rotAngle);
	return CreateFromAxisAngle(rotAxis, rotAngle);
}

bool Quaternion::operator==(const Quaternion& aRight) const
{
	return aRight.myRotation == myRotation && aRight.myRotationAmount == myRotationAmount;
}

bool Quaternion::operator!=(const Quaternion& aRight) const
{
	return !(aRight == *this);
}

Quaternion Quaternion::operator*(const Quaternion& aRight) const
{
	/*
	(Q1 * Q2).x = (w1*x2 + x1*w2 + y1*z2 - z1*y2)
	(Q1 * Q2).y = (w1*y2 - x1*z2 + y1*w2 + z1*x2)
	(Q1 * Q2).z = (w1*z2 + x1*y2 - y1*x2 + z1*w2)
	(Q1 * Q2).w = (w1*w2 - x1*x2 - y1*y2 - z1*z2)
	*/

	Quaternion returnValue;
	returnValue.myRotation.x = myRotationAmount * aRight.myRotation.x + myRotation.x * aRight.myRotationAmount + myRotation.y * aRight.myRotation.z - myRotation.z * aRight.myRotation.y;

	returnValue.myRotation.y = myRotationAmount * aRight.myRotation.y - myRotation.x * aRight.myRotation.z + myRotation.y * aRight.myRotationAmount + myRotation.z * aRight.myRotation.x;

	returnValue.myRotation.z = myRotationAmount * aRight.myRotation.z + myRotation.x * aRight.myRotation.y - myRotation.y * aRight.myRotation.x + myRotation.z * aRight.myRotationAmount;

	returnValue.myRotationAmount = myRotationAmount * aRight.myRotationAmount - myRotation.x * aRight.myRotation.x - myRotation.y * aRight.myRotation.y - myRotation.z * aRight.myRotation.z;

	return returnValue;
}

Quaternion& Quaternion::operator*=(const Quaternion& aRight)
{
	*this = *this * aRight;
	return *this;
}

Quaternion Quaternion::operator/(const float aScale) const
{
	return Quaternion(myRotation / aScale, myRotationAmount / aScale);
}

Quaternion Quaternion::operator*(const float aScale) const
{
	return Quaternion(myRotation * aScale, myRotationAmount * aScale, false);
}

Quaternion Quaternion::operator+(const Quaternion& aRight) const
{
	return Quaternion(myRotation + aRight.myRotation, myRotationAmount + aRight.myRotationAmount);
}

Quaternion Quaternion::operator-(const Quaternion& aRight) const
{
	return Quaternion(myRotation - aRight.myRotation, myRotationAmount - aRight.myRotationAmount);
}

Quaternion& Quaternion::operator*=(const float aScale)
{
	*this = *this * aScale;
	return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& aRight)
{
	*this = *this + aRight;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& aRight)
{
	*this = *this - aRight;
	return *this;
}

Quaternion& Quaternion::operator/=(const float aScale)
{
	*this = *this / aScale;
	return *this;
}

Matrix44f Quaternion::GenerateMatrix() const
{
	//Shamefully stolen from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	float X = myRotation.x;
	float Y = myRotation.y;
	float Z = myRotation.z;
	float W = myRotationAmount;
	float xx = X * X;
	float xy = X * Y;
	float xz = X * Z;
	float xw = X * W;
	float yy = Y * Y;
	float yz = Y * Z;
	float yw = Y * W;
	float zz = Z * Z;
	float zw = Z * W;

	Matrix44f returnValue;
	returnValue.m11 = 1 - 2 * (yy + zz);
	returnValue.m12 = 2 * (xy - zw);
	returnValue.m13 = 2 * (xz + yw);

	returnValue.m21 = 2 * (xy + zw);
	returnValue.m22 = 1 - 2 * (xx + zz);
	returnValue.m23 = 2 * (yz - xw);

	returnValue.m31 = 2 * (xz - yw);
	returnValue.m32 = 2 * (yz + xw);
	returnValue.m33 = 1 - 2 * (xx + yy);

	returnValue.m14 = returnValue.m24 = returnValue.m34 = returnValue.m41 = returnValue.m42 = returnValue.m43 = 0;
	returnValue.m44 = 1;

	returnValue.Transpose();
	return returnValue;
}

Quaternion Quaternion::GetInverse(const Quaternion &aQuaternion)
{
	Quaternion temp;
	temp.myRotationAmount = aQuaternion.myRotationAmount;
	temp.myRotation = aQuaternion.myRotation * -1;

	return temp;
}

float Quaternion::Dot(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion)
{
	return aFirstQuaternion.myRotation.Dot(aSecondQuaternion.myRotation) + aFirstQuaternion.myRotationAmount * aSecondQuaternion.myRotationAmount;
}

Quaternion Quaternion::Lerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress)
{
	return Quaternion(aFirstQuaternion * (1.f - aProgress) + aSecondQuaternion * aProgress);
}

Quaternion Quaternion::Slerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress)
{
	Quaternion first = aFirstQuaternion;
	Quaternion second = aSecondQuaternion;
	float angle = Quaternion::Dot(first, second);
	Quaternion quaternion;
	// make sure we use the short rotation
	if (angle < 0.0f)
	{
		first = first * -1.0f;
		angle *= -1.0f;
	}

	if (angle <= (1 - 0.05f)) // spherical interpolation
	{
		const float theta = acosf(angle);
		const float invsintheta = 1.0f / (sinf(theta));
		const float scale = sinf(theta * (1.0f - aProgress)) * invsintheta;
		const float invscale = sinf(theta * aProgress) * invsintheta;
		Quaternion firstMul = first * scale;
		Quaternion secondMul = second * invscale;
		Quaternion res = firstMul + secondMul;
		return res;
	}
	return Lerp(first, second, aProgress);

}
