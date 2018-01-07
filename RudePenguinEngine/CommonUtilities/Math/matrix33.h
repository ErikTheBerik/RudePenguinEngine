#pragma once
#include "vector.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <array>
#include <iostream>

// Forward declarations
//
template<typename TYPE>
class Matrix44;

template<typename TYPE>
class Matrix33
{
public:     // Constants to avoid using magic numbers
            //
            static const unsigned int   NumRows = 3,
                                        NumColumns = 3,
                                        NumElements = NumRows * NumColumns;

            // Initializes the matrix to the identity matrix
            //
			Matrix33(void)
			{
				(*this) = Identity;
			}

            // Initializes the matrix with the data from anOther
            //
			Matrix33(const Matrix33 &anOther)
			{
				(*this) = anOther;
			}

            // Initializes the matrix with the 3x3-part from anOther
            //
			Matrix33(const Matrix44<TYPE> &anOther)
			{
				m11 = anOther.m11;
				m12 = anOther.m12;
				m13 = anOther.m13;
				m21 = anOther.m21;
				m22 = anOther.m22;
				m23 = anOther.m23;
				m31 = anOther.m31;
				m32 = anOther.m32;
				m33 = anOther.m33;
			}

            // Initializes the matrix with the static_cast'ed data from anOther which uses another base type
            //
            template<typename U>
            Matrix33( const Matrix33<U> &anOther )
			{
				m11 = static_cast<TYPE>(anOther.m11);
				m12 = static_cast<TYPE>(anOther.m12);
				m13 = static_cast<TYPE>(anOther.m13);
				m21 = static_cast<TYPE>(anOther.m21);
				m22 = static_cast<TYPE>(anOther.m22);
				m23 = static_cast<TYPE>(anOther.m23);
				m31 = static_cast<TYPE>(anOther.m31);
				m32 = static_cast<TYPE>(anOther.m32);
				m33 = static_cast<TYPE>(anOther.m33);
			}

            // Initializes the matrix with the data from an array
            //
            // Explanation:
            // This allows the syntax: Matrix33 identity({1, 0, 0, 0, 1, 0, 0, 0, 1});
            //
			Matrix33(const TYPE(&anArray)[NumElements])
			{
				m11 = anArray[0];
				m12 = anArray[1];
				m13 = anArray[2];
				m21 = anArray[3];
				m22 = anArray[4];
				m23 = anArray[5];
				m31 = anArray[6];
				m32 = anArray[7];
				m33 = anArray[8];
			}

            // Initializes the matrix with plain values
            //
            Matrix33(
                const TYPE a11, const TYPE a12, const TYPE a13,
                const TYPE a21, const TYPE a22, const TYPE a23,
                const TYPE a31, const TYPE a32, const TYPE a33 )
			{
				m11 = a11;
				m12 = a12;
				m13 = a13;
				m21 = a21;
				m22 = a22;
				m23 = a23;
				m31 = a31;
				m32 = a32;
				m33 = a33;
			}

            // Adds and assigns the values of aRight to this matrix
            //
            Matrix33 &operator +=( const Matrix33 &aRight )
			{
				(*this) = (*this) + aRight;
				return (*this);
			}

            // Subtract and assigns the values of aRight to this matrix
            //
            Matrix33 &operator -=( const Matrix33 &aRight )
			{
				(*this) = (*this) - aRight;
				return (*this);
			}

            // Multiplies this matrix with aRight
            //
            Matrix33 &operator *=( const Matrix33 &aRight )
			{
				(*this) = (*this) * aRight;
				return (*this);
			}

            // Sets the values of this matrix to those of aRight
            //
			Matrix33 &operator =(const Matrix33 &aRight)
			{
				m11 = aRight.m11;
				m12 = aRight.m12;
				m13 = aRight.m13;
				m21 = aRight.m21;
				m22 = aRight.m22;
				m23 = aRight.m23;
				m31 = aRight.m31;
				m32 = aRight.m32;
				m33 = aRight.m33;

				return (*this);
			}

            // Transposes the matrix and returns *this
            //
            Matrix33 &Transpose( void )
			{
				Matrix33<TYPE> temp;
				temp = (*this);
				m11 = temp.m11;
				m12 = temp.m21;
				m13 = temp.m31;
				m21 = temp.m12;
				m22 = temp.m22;
				m23 = temp.m32;
				m31 = temp.m13;
				m32 = temp.m23;
				m33 = temp.m33;

				return (*this);
			}

			static TYPE Get2x2Determinant(const TYPE a11, const TYPE a12, const TYPE a21, const TYPE a22)
			{
				return a11 * a22 - a21 * a12;
			}

			static Matrix33 GetInverseMatrix(const Matrix33 &aMatrix)
			{
				Matrix33 tempMatrix;

				tempMatrix.m11 = Get2x2Determinant(aMatrix.m22, aMatrix.m23, aMatrix.m32, aMatrix.m33);
				tempMatrix.m12 = Get2x2Determinant(aMatrix.m13, aMatrix.m12, aMatrix.m33, aMatrix.m32);
				tempMatrix.m13 = Get2x2Determinant(aMatrix.m12, aMatrix.m13, aMatrix.m22, aMatrix.m23);

				tempMatrix.m21 = Get2x2Determinant(aMatrix.m23, aMatrix.m21, aMatrix.m33, aMatrix.m31);
				tempMatrix.m22 = Get2x2Determinant(aMatrix.m11, aMatrix.m13, aMatrix.m31, aMatrix.m33);
				tempMatrix.m23 = Get2x2Determinant(aMatrix.m13, aMatrix.m11, aMatrix.m23, aMatrix.m21);

				tempMatrix.m31 = Get2x2Determinant(aMatrix.m21, aMatrix.m22, aMatrix.m31, aMatrix.m32);
				tempMatrix.m32 = Get2x2Determinant(aMatrix.m12, aMatrix.m11, aMatrix.m32, aMatrix.m31);
				tempMatrix.m33 = Get2x2Determinant(aMatrix.m11, aMatrix.m12, aMatrix.m21, aMatrix.m22);

				return tempMatrix;
			}

            // Creates a transformation matrix for rotating anAngle rad around the x-axis
            //
			static Matrix33 CreateRotateAroundX(const TYPE anAngle)
			{
				return Matrix33({
					1,0,0,
					0, static_cast<TYPE>(cos(anAngle)), static_cast<TYPE>(sin(anAngle)),
					0, static_cast<TYPE>(-sin(anAngle)), static_cast<TYPE>(cos(anAngle))
				});
			}

            // Creates a transformation matrix for rotating anAngle rad around the y-axis
            //
			static Matrix33 CreateRotateAroundY(const TYPE anAngle)
			{
				return Matrix33({
					static_cast<TYPE>(cos(anAngle)), 0, static_cast<TYPE>(-sin(anAngle)),
					0,1,0,
					static_cast<TYPE>(sin(anAngle)), 0, static_cast<TYPE>(cos(anAngle))
				});
			}

            // Creates a transformation matrix for rotating anAngle rad around the z-axis
            //
            static Matrix33 CreateRotateAroundZ( const TYPE anAngle )
			{
				return Matrix33({
					static_cast<TYPE>(cos(anAngle)), static_cast<TYPE>(sin(anAngle)), 0,
					static_cast<TYPE>(-sin(anAngle)), static_cast<TYPE>(cos(anAngle)), 0,
					0,0,1
				});
			}

            // Returns a transposed copy of aMatrix
            //
			static Matrix33 Transpose(Matrix33 aMatrix)
			{
				Matrix33<TYPE> temp = aMatrix;
				return temp.Transpose();
			}

			// Sets the position part of a 2D transformation matrix
			void SetPosition(const Vector2<TYPE> &aPosition)
			{
				m31 = aPosition.x;
				m32 = aPosition.y;
			}

			// Gets the position part of a 2D transformation matrix 
			Vector2<TYPE> GetPosition(void) const
			{
				return Vector2<TYPE>(m31, m32);
			}

			Vector3<TYPE> GetTranslation() const
			{
				Vector3<TYPE> temp;
				temp.x = m31;
				temp.y = m32;
				temp.z = m33;
				return temp;
			}

			void SetTranslation(Vector3<TYPE> &aTranslation)
			{
				m31 = aTranslation.x;
				m32 = aTranslation.y;
				m33 = aTranslation.z;
			}

			// Rotates the upper left 2x2 part of the matrix by anAngle rad around the z-axis 
			Matrix33 &Rotate2D(const TYPE anAngle)
			{
				Matrix33<TYPE> temp = (*this);
				SetPosition(Vector2<TYPE>(static_cast<TYPE>(0), static_cast<TYPE>(0)));
				(*this) *= CreateRotateAroundZ(anAngle);				
				SetPosition(temp.GetPosition());
				return (*this);
			}

			// Sets the upper left 2x2 part of the matrix to the rotation of anAngle rad. Will 
			// create the same values for the rotation-part as the CreateRotateAroundZ but 
			// leaves the other values untouched. 
			Matrix33 &Set2DRotation(const TYPE anAngle)
			{
				m11 = static_cast<TYPE>(cos(anAngle));
				m12 = static_cast<TYPE>(sin(anAngle));
				m21 = static_cast<TYPE>(-sin(anAngle));
				m22 = static_cast<TYPE>(cos(anAngle));
				return (*this);
			}

            // The data of this matrix
            //
#pragma warning( disable : 4201 ) // NOTE: This works fine in VC2013 and GCC so I'm keeping it. //MAHAM
            union
            {
                struct
                {
					TYPE    m11, m12, m13,
						m21, m22, m23,
						m31, m32, m33;
                };

                std::array<TYPE, NumElements> myMatrix;
            };

            // Pre-created matrices
            //
            static const Matrix33   Identity,   // Identity matrix
                                    Zero;       // Matrix with all 0
};
#pragma warning( default : 4201 )

// Alias for Matrix33<float>. Add more if needed.
//
using Matrix33f = Matrix33<float>;

template<typename TYPE> 
const Matrix33<TYPE> Matrix33<TYPE>::Identity = Matrix33(
{
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
});

template<typename TYPE> 
const Matrix33<TYPE> Matrix33<TYPE>::Zero = Matrix33(
{
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
});

// Returns a new vector which is the product of the vector aLeft and the matrix 
// aRight. Make sure you convert aLeft to a Vector3 and set it's .z-value to 1
// 
template<typename TYPE>
Vector2<TYPE> operator *(Vector2<TYPE> aLeft, const Matrix33<TYPE> &aRight)
{
	Vector3<TYPE> temp3(aLeft);
	temp3 = temp3 * aRight;
	return Vector2<TYPE>(temp3.x, temp3.y);
}

// Returns a new matrix which is the sum of aLeft and aRight
//
template<typename TYPE>
Matrix33<TYPE> operator +( Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight )
{
	Matrix33<TYPE> temp = aLeft;
	temp.m11 += aRight.m11;
	temp.m12 += aRight.m12;
	temp.m13 += aRight.m13;
	temp.m21 += aRight.m21;
	temp.m22 += aRight.m22;
	temp.m23 += aRight.m23;
	temp.m31 += aRight.m31;
	temp.m32 += aRight.m32;
	temp.m33 += aRight.m33;
	return temp;
}


// Returns a new matrix wich is the difference of aLeft and aRight
//
template<typename TYPE>
Matrix33<TYPE> operator -( Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight )
{
	Matrix33<TYPE> temp = aLeft;
	temp.m11 -= aRight.m11;
	temp.m12 -= aRight.m12;
	temp.m13 -= aRight.m13;
	temp.m21 -= aRight.m21;
	temp.m22 -= aRight.m22;
	temp.m23 -= aRight.m23;
	temp.m31 -= aRight.m31;
	temp.m32 -= aRight.m32;
	temp.m33 -= aRight.m33;
	return temp;
}


// Returns a new matrix which is the product of aLeft and aRight
//
template<typename TYPE>
Matrix33<TYPE> operator *( Matrix33<TYPE> aLeft, const Matrix33<TYPE> &aRight )
{
	Matrix33<TYPE> temp = aLeft;
	temp.m11 = (aLeft.m11 * aRight.m11) + (aLeft.m12 * aRight.m21) + (aLeft.m13 * aRight.m31);
	temp.m12 = (aLeft.m11 * aRight.m12) + (aLeft.m12 * aRight.m22) + (aLeft.m13 * aRight.m32);
	temp.m13 = (aLeft.m11 * aRight.m13) + (aLeft.m12 * aRight.m23) + (aLeft.m13 * aRight.m33);

	temp.m21 = (aLeft.m21 * aRight.m11) + (aLeft.m22 * aRight.m21) + (aLeft.m23 * aRight.m31);
	temp.m22 = (aLeft.m21 * aRight.m12) + (aLeft.m22 * aRight.m22) + (aLeft.m23 * aRight.m32);
	temp.m23 = (aLeft.m21 * aRight.m13) + (aLeft.m22 * aRight.m23) + (aLeft.m23 * aRight.m33);

	temp.m31 = (aLeft.m31 * aRight.m11) + (aLeft.m32 * aRight.m21) + (aLeft.m33 * aRight.m31);
	temp.m32 = (aLeft.m31 * aRight.m12) + (aLeft.m32 * aRight.m22) + (aLeft.m33 * aRight.m32);
	temp.m33 = (aLeft.m31 * aRight.m13) + (aLeft.m32 * aRight.m23) + (aLeft.m33 * aRight.m33);

	return temp;
}


// Returns a new matrix which is the product of the vector aLeft and the matrix aRight
//
template<typename TYPE>
Vector3<TYPE> operator *( Vector3<TYPE> aLeft, const Matrix33<TYPE> &aRight )
{
	Vector3<TYPE> retVector;
	retVector.x = (aLeft.x * aRight.m11) + (aLeft.y * aRight.m21) + (aLeft.z * aRight.m31);
	retVector.y = (aLeft.x * aRight.m12) + (aLeft.y * aRight.m22) + (aLeft.z * aRight.m32);
	retVector.z = (aLeft.x * aRight.m13) + (aLeft.y * aRight.m23) + (aLeft.z * aRight.m33);
	return retVector;
}


// Compares aLeft and aRight componentwise
//
template<typename TYPE>
bool operator ==(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
{
	return
		aLeft.m11 == aRight.m11 &&
		aLeft.m12 == aRight.m12 &&
		aLeft.m13 == aRight.m13 &&
		aLeft.m21 == aRight.m21 &&
		aLeft.m22 == aRight.m22 &&
		aLeft.m23 == aRight.m23 &&
		aLeft.m31 == aRight.m31 &&
		aLeft.m32 == aRight.m32 &&
		aLeft.m33 == aRight.m33;
}


// Returns the negated result of aLeft == aRight
//
template<typename TYPE>
bool operator !=(const Matrix33<TYPE> &aLeft, const Matrix33<TYPE> &aRight)
{
	return !(aLeft == aRight);
}
