#include <math.h>
#define MIN(A,B) (((A) > (B)) ? (B) : (A))
#define MAX(A,B) (((A) > (B)) ? (A) : (B))
#define SAFE_DELETE(aPointer) if((aPointer) != (nullptr)){delete(aPointer); (aPointer)=(nullptr);} 
#define SWAP(A,B) auto C = A; A = B; B = C;
#define CLAMP(aValue, aMin, aMax) ((aValue) < (aMin) ? (aMin) : (aValue) > (aMax) ? (aMax) : (aValue))
#define ERASE(aVector, aIndex)  \
aVector[(aIndex)] = aVector[aVector.size() -1];\
aVector.resize(aVector.size() -1);
#define POWEROF(aBase, aExponent)\
for(int i = 1; i < (aExponent); i++)\
{\
	aBase =(aBase) * (aBase);\
}
#define SORT(aVector) \
	bool sorted = true;\
	int index = 1;\
while (sorted == true)\
{\
	sorted = false;\
	index++;\
	for (size_t i = 0; i < (aVector.size() + 1) - index; i++)\
	{\
		if(aVector[i] > aVector[i + 1])\
		{\
			auto temp = aVector[i];\
			aVector[i] = aVector[i + 1];\
			aVector[i + 1] = temp;\
			sorted = true;\
		}\
	}\
}\
	
#define DISTANCE2D(aX1, aY1, aX2, aY2) sqrt(((aX1 - aX2) * (aX1 - aX2)) + ((aY1 - aY2) * (aY1 - aY2)))
#define	DISTANCE3D(aX1, aY1, aZ1, aX2, aY2, aZ2) sqrt(((aX1 - aX2) * (aX1 - aX2)) + ((aY1 - aY2) * (aY1 - aY2)) + ((aZ1 - aZ2) * (aZ1 - aZ2)))

