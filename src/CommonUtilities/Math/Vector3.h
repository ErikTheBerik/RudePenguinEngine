#pragma once


// Forward declarations
//
template<typename TYPE>
class Vector4;
template<typename TYPE>
class Vector2;


//
// Vector3
//

template<typename TYPE>
class Vector3
{
public:		// Construction
            //
            Vector3( void ) = default;
            Vector3( const Vector3 &aVector3 ) = default;
            Vector3( const Vector4<TYPE> &aVector4 );
			// Initializes the vector with the data from a Vector2, setting z to 1 
			explicit Vector3(const Vector2<TYPE> &aVector2)
			{
				x = aVector2.x;
				y = aVector2.y;
				z = 1;
			}
            template<typename U> explicit Vector3( const Vector3<U> &aVector );
            Vector3( const TYPE anX, const TYPE aY, const TYPE aZ );

			Vector3(const TYPE anValue)
			{
				x = y = z = anValue;
			}

			Vector3(const Vector2<TYPE> &aVector2, const TYPE aZ)
			{
				x = aVector2.x;
				y = aVector2.y;
				z = aZ;
			}

			TYPE operator [](int aValue) const
			{
				if (aValue == 0)
				{
					return x;
				}
				if (aValue == 1)
				{
					return y;
				}
				return z;
			}


            // Arithmetic
            //
            friend Vector3 operator +( Vector3 aLeft, const Vector3 &aRight )
            {
				return aLeft += aRight;
            }


            friend Vector3 operator -( Vector3 aLeft, const Vector3 &aRight )
            {
				return aLeft -= aRight;
            }


            friend Vector3 operator *( Vector3 aLeft, const TYPE aRight )
            {
				return aLeft *= aRight;
            }


            friend Vector3 operator /( Vector3 aLeft, const TYPE aRight )
            {
				return aLeft /= aRight;
            }


            friend Vector3 operator -( Vector3 aRight )
            {
				return aRight * static_cast<TYPE>(-1);
            }

			friend Vector3 operator *(const Vector3 &aLeft, const Vector3 &aRight)
			{
				return Vector3(aLeft.x * aRight.x, aLeft.y * aRight.y, aLeft.z * aRight.z);
			}

            // Comparison
            //
            friend bool operator ==( const Vector3 &aLeft, const Vector3 &aRight )
            {
				if (aLeft.x == aRight.x &&
					aLeft.y == aRight.y &&
					aLeft.z == aRight.z)
				{
					return true;
				}
				else
				{
					return false;
				}
            }

			std::string ToString() const
			{
				std::string position = "X:" + std::to_string(x) + " Y:" + std::to_string(y) + " Z:" + std::to_string(z);
				return position;
			}

            friend bool operator !=( const Vector3 &aLeft, const Vector3 &aRight )
            {
				return !(aLeft == aRight);
            }


            // Assignment
            //
            Vector3 &operator =( const Vector3 &aRight ) = default;
            Vector3 &operator =( const Vector4<TYPE> &aRight );

            // Combined
            //
            Vector3 &operator +=( const Vector3 &aRight );
            Vector3 &operator -=( const Vector3 &aRight );
            Vector3 &operator *=( const TYPE aRight );
            Vector3 &operator /=( const TYPE aRight );

            // Info
            //
            TYPE Length( void ) const;
            TYPE Length2( void ) const;
            TYPE Dot( const Vector3 &aRight ) const;
			Vector3 Cross(const Vector3 &aRight) const;
            Vector3 GetNormalized( void ) const;
			static Vector3 ComponentMultiplication(const Vector3 & aLeft, const Vector3 & aRight);
			Vector3 GetDirectionTowards(const Vector3 &aOtherVector) const
			{
				return (aOtherVector - *this).GetNormalized();
			}
			static float GetAngleFromCross(const Vector3<TYPE> & aCrossProductFromNormalizedVectors)
			{
				//Look in linalg book for proof that this works. Page 67. Only works for cross product of two NORMALIZED vectors
				float crossLength = aCrossProductFromNormalizedVectors.Length();
				//Clamp for float problems
				if (crossLength > 1.f)
				{
					crossLength = 1.f;
				}
				else if (crossLength < 0.f)
				{
					crossLength = 0.f;
				}
				return asin(crossLength);
			}

			static Vector3 Lerp(const Vector3<TYPE> & aLeft, const Vector3<TYPE> & aRight, float anAmount)
			{
				if (anAmount >= 1.0f)
				{
					return aRight;
				}
				if (anAmount <= 0.0f)
				{
					return aLeft;
				}

				return Vector3<TYPE>(aLeft.x + (aRight.x - aLeft.x) * anAmount, aLeft.y + (aRight.y - aLeft.y) * anAmount, aLeft.z + (aRight.z - aLeft.z) * anAmount);
			}

			static Vector3 Lerp(const Vector3<TYPE> & aLeft, const Vector3<TYPE> & aRight, const Vector3<TYPE> &anAmount)
			{
				return Vector3<TYPE>(aLeft.x + (aRight.x - aLeft.x) * anAmount.x, aLeft.y + (aRight.y - aLeft.y) * anAmount.y, aLeft.z + (aRight.z - aLeft.z) * anAmount.z);
			}

			static Vector3 Slerp(const Vector3<TYPE> & aFrom, const Vector3<TYPE> & aTo, float anAmount)
			{

				if (anAmount == 0) return aFrom;
				if (aFrom == aTo || anAmount == 1.0f) return aTo;

				if (aFrom.Length2() == 0 || aTo.Length2() == 0) return aTo;

				float theta = acos(Vector3f::Dot(aFrom, aTo) / (aFrom.Length() * aTo.Length()));
				//float thetaDegree = theta * RadianToDegree;

				if (theta == 0) return aTo;

				float sinTheta = sin(theta);
				return (aFrom * (sin((1 - anAmount) * theta) / sinTheta)) + (aTo * (sin(anAmount * theta) / sinTheta));
			}

			TYPE Manhattan(const Vector3<TYPE> &aRight) const;
			static Vector3 GetProjection(const Vector3 &aPoint, const Vector3 &aStart, const Vector3 &aEnd);

			//Returns the positive "clockwise" Angle From first to second vector. 
			static float GetAngleBetween(const Vector3<TYPE> & aFirstVector, const Vector3<TYPE> & aSecondVector)
			{
				//shamelessly stolen from ylf
				float sign =  aFirstVector.Dot(aSecondVector);

				//Look in linalg book for proof that this works. Page 67. Only works for cross product of two NORMALIZED vectors
				float crossLength = Vector3<TYPE>::Cross(aFirstVector.GetNormalized(), aSecondVector.GetNormalized()).Length();
				//Clamp for float problems

				if (crossLength > 1.f)
				{
					crossLength = 1.f;
				}
				else if (crossLength < 0.f)
				{
					crossLength = 0.f;
				}

				float angle = asin(crossLength);

				if (sign < 0.f) // angle is greater than 90, but cross angle doesn't distinct forward from backwards
				{
					angle = 3.1415926f - angle;
				}

				return angle;
			}

            // Manipulation
            //
            Vector3 &Normalize( void );

            union
            {
                TYPE    x,
                        u,
                        r,
						h;
            };

            union
            {
                TYPE    y,
                        v,
                        g,
						s;
            };

            union
            {
                TYPE    z,
                        w,
                        b,
						v;
            };

            static TYPE Dot( const Vector3 &aLeft, const Vector3 &aRight );
            static Vector3 Cross( const Vector3 &aLeft, const Vector3 &aRight );
            static Vector3 Normalize( Vector3 aVector );
			static Vector3 HalfVector(const Vector3 &aLeft, const Vector3 &aRight);
			static TYPE Manhattan(const Vector3<TYPE> &aLeft, const Vector3<TYPE> &aRight);

			static const Vector3	
				Zero,
				UnitX,
				UnitY,
				UnitZ,
				One,
				Forward,
				Backward,
				Left,
				Right,
				Up,
				Down,
				Max,
				Half;
};

template<typename TYPE>
Vector3<TYPE> Vector3<TYPE>::ComponentMultiplication(const Vector3<TYPE> & aLeft, const Vector3<TYPE> & aRight)
{
	return Vector3<TYPE>(aLeft.x * aRight.x, aLeft.y * aRight.y, aLeft.z * aRight.z);
}

using Vector3c  = Vector3<char>;
using Vector3i  = Vector3<int>;
using Vector3ui = Vector3<unsigned int>;
using Vector3f  = Vector3<float>;
using Vector3d  = Vector3<double>;

using Point3c   = Vector3<char>;
using Point3i   = Vector3<int>;
using Point3ui  = Vector3<unsigned int>;
using Point3f   = Vector3<float>;
using Point3d   = Vector3<double>;

template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Zero(  0, 0, 0 );
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitX( 1, 0, 0 );
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitY( 0, 1, 0 );
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitZ( 0, 0, 1 );
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::One(1, 1, 1);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Forward(0, 0, 1);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Backward(0, 0, -1);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Left(-1, 0, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Right(1, 0, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Up(0, 1, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Down(0, -1, 0);
template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Max(FLT_MAX, FLT_MAX, FLT_MAX);
template<typename TYPE> const Vector2<TYPE> Vector3<TYPE>::Half(static_cast<TYPE>(0.5), static_cast<TYPE>(0.5), static_cast<TYPE>(0.5));

#include "Vector3.inl"