#pragma once
#include "matrix44.h"
#include "Vector3.h"
#include "Vector4.h"
//created using reference from http://www.cprogramming.com/tutorial/3d/quaternions.html

class Quaternion
{
public:
	Quaternion(float aRotationX = 0.0f, float aRotationY = 0.0f, float aRotationZ = 0.0f, float aRotationAmount = 1.0f, bool aNormalize = true);
	Quaternion(Matrix44f aMatrix);
	Quaternion(const Vector3f &aRotation, float aRotationAmount = 1.0f, bool aNormalize = true);
	Quaternion(const Vector4f & aRotationAndAmount, bool aNormalize = true);
	void Normalize();

	//dont breathe this
	//Quaternion CreateFromVectorsYlf(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp);


	void RotateAlongAxis(const Vector3f& aAxis, float aRotationAmount);
	void RotateWorld(const Vector3f& aRotationAmount);
	void RotateWorldX(float aRotationAmount);
	void RotateWorldY(float aRotationAmount);
	void RotateWorldZ(float aRotationAmount);

	static Quaternion CreateFromAxisAngle(const Vector3f &aAxis, const float anAngle);

	void RotateLocal(const Vector3f& aRotationAmount);
	void RotateLocalX(float aRotationAmount);
	void RotateLocalY(float aRotationAmount);
	void RotateLocalZ(float aRotationAmount);

	static Quaternion LookRotation(const Vector3f& aForward, const Vector3f& aUp = Vector3f(0.f,1.f,0.f));

	void RotateTowardsPoint(const Vector3f & aCurrentPosition, const Vector3f & aTargetPosition);
	Vector3f ToEuler() const;

	Vector3f GetRight() const;
	Vector3f GetLeft() const;
	Vector3f GetUp() const;
	Vector3f GetDown() const;
	Vector3f GetForward() const;
	Vector3f GetBackward() const;

	//Roll = X Rotation
	float GetRoll() const;

	//Pitch = Y Rotation
	float GetPitch() const;

	//Yaw = Z Rotation
	float GetYaw() const;

	static Quaternion LookAt(const Vector3f &aStartPosition, const Vector3f &aEndPosition, const Vector3f &aUp = Vector3f(0.0f, 1.0f, 0.0f));

	//note: (Q1*Q2) != (Q2*Q1)
	Quaternion operator *(const Quaternion& aRight) const;


	bool operator ==(const Quaternion& aRight) const;
	bool operator !=(const Quaternion& aRight) const;

	//note: (Q1*Q2) != (Q2*Q1)
	Quaternion& operator *=(const Quaternion& aRight);

	Quaternion operator / (const float aScale) const;
	Quaternion operator * (const float aScale) const;
	Quaternion operator + (const Quaternion& aRight) const;
	Quaternion operator - (const Quaternion& aRight) const;
	Vector3f operator * (const Vector3f &aRight) const;

	Quaternion& operator /= (const float aScale);
	Quaternion& operator *=(const float aScale);
	Quaternion& operator += (const Quaternion& aRight);
	Quaternion& operator -= (const Quaternion& aRight);

	//this assumes the quaternion is normalized
	Matrix44f GenerateMatrix() const;

	static Quaternion GetInverse(const Quaternion &aQuaternion);
	static float Dot(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion);
	static Quaternion Lerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress);
	static Quaternion Slerp(const Quaternion &aFirstQuaternion, const Quaternion &aSecondQuaternion, const float aProgress);

//private:
	Vector3f myRotation;
	float myRotationAmount;
};
