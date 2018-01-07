#pragma once
#include <string>


// Forward declarations
//
template<typename TYPE>
class Vector3;


template<typename TYPE>
class Vector4
{
public:		// Construction
            //
            Vector4( void );
            Vector4( const Vector4 &anOther ) = default;
            explicit Vector4( const Vector3<TYPE> &anOther );
            template<typename U> explicit Vector4( const Vector4<U> &anOther );
            Vector4( const TYPE anX, const TYPE anY, const TYPE aZ, const TYPE aW );
			Vector4(const Vector3<TYPE> &aVector3, const TYPE aW) 
			{
				x = aVector3.x;
				y = aVector3.y;
				z = aVector3.z;
				w = aW;
			}


            // Arithmetic
            //
            friend Vector4 operator +( Vector4 aLeft, const Vector4 &aRight )
            {
				return aLeft += aRight;
            }


            friend Vector4 operator -( Vector4 aLeft, const Vector4 &aRight )
            {
				return aLeft -= aRight;
            }

			Vector4 & Vector4::operator=(const Vector3<TYPE> &aRight)
			{
				x = aRight.x;
				y = aRight.y;
				z = aRight.z;
				w = 1;
				return *this;
			}

            friend Vector4 operator *( Vector4 aLeft, const TYPE aRight )
            {
				return aLeft *= aRight;
            }


            friend Vector4 operator /( Vector4 aLeft, const TYPE aRight )
            {
				return aLeft /= aRight;
            }


            friend Vector4 operator -( Vector4 aRight )
            {
				return aRight * static_cast<TYPE>(-1);
            }


            // Comparison
            //
            friend bool operator ==( const Vector4 &aLeft, const Vector4 &aRight )
            {
				if (aLeft.x == aRight.x &&
					aLeft.y == aRight.y &&
					aLeft.z == aRight.z &&
					aLeft.w == aRight.w)
				{
					return true;
				}
				else
				{
					return false;
				}
            }


            friend bool operator !=( const Vector4 &aLeft, const Vector4 &aRight )
            {
				return !(aLeft == aRight);
            }


            // Assignment
            //
            Vector4 &operator =( const Vector4 &aRight ) = default;
            //Vector4 &operator =( const Vector3<TYPE> &aRight );

            // Combined
            //
            Vector4 &operator +=( const Vector4 &aRight );
            Vector4 &operator -=( const Vector4 &aRight );
            Vector4 &operator *=( const TYPE aRight );
            Vector4 &operator /=( const TYPE aRight );

            // Info
            //
            TYPE Length( void ) const;
            TYPE Length2( void ) const;
            TYPE Dot( const Vector4 &aRight ) const;
            Vector4 GetNormalized( void ) const;
			TYPE Manhattan(const Vector4<TYPE> &aRight) const;

            // Manipulation
            //
            Vector4 &Normalize( void );

            union
            {
                TYPE    x,
                        r,
						h;
            };

            union
            {
                TYPE    y,
                        g,
						s;
            };

            union
            {
                TYPE    z,
                        b,
						v;
            };

            union
            {
                TYPE    w,
                        a;
            };

            static Vector4 Normalize( Vector4 aVector );
            static TYPE Dot( const Vector4 &aFirstVector, const Vector4 &aSecondVector );
			static TYPE Manhattan(const Vector4<TYPE> &aLeft, const Vector4<TYPE> &aRight);

            static const Vector4	Zero,
                                    UnitX,
                                    UnitY,
                                    UnitZ,
                                    UnitW,
                                    One,
									Half;

			std::string ToString() const
			{
				std::string position = "X:" + std::to_string(x) + " Y:" + std::to_string(y) + " Z:" + std::to_string(z);
				return position;
			}
};

template<typename TYPE>
Vector4<TYPE>::Vector4(const Vector3<TYPE> &anOther)
{
	x = anOther.x;
	y = anOther.y;
	z = anOther.z;
	w = 1.0f;
}

using Vector4c  = Vector4<char>;
using Vector4i  = Vector4<int>;
using Vector4ui = Vector4<unsigned int>;
using Vector4f  = Vector4<float>;
using Vector4d  = Vector4<double>;

using Point4c   = Vector4<char>;
using Point4i   = Vector4<int>;
using Point4ui  = Vector4<unsigned int>;
using Point4f   = Vector4<float>;
using Point4d   = Vector4<double>;

template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::Zero(  0, 0, 0, 0 );
template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitX( 1, 0, 0, 0 );
template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitY( 0, 1, 0, 0 );
template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitZ( 0, 0, 1, 0 );
template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::UnitW( 0, 0, 0, 1 );
template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::One(1, 1, 1, 1);
template<typename TYPE> const Vector4<TYPE> Vector4<TYPE>::Half(static_cast<TYPE>(0.5), static_cast<TYPE>(0.5), static_cast<TYPE>(0.5), static_cast<TYPE>(0.5));


#include "Vector4.inl"
