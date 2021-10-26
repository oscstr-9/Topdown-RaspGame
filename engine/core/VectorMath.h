#pragma once
#include <math.h>
#include <iostream>
//#include <iomanip>

struct VectorMath2
{
	union {
		struct
		{
			float x;
			float y;
		};
		float coords[2];
	};

	VectorMath2(float xIn, float yIn);
	VectorMath2();
	float& operator[](int index);
	float operator[](int index)const;
	VectorMath2 operator+(VectorMath2 vectorA);
	VectorMath2 operator-(VectorMath2 vectorA);
	VectorMath2 operator*(float multiplier);
	bool operator== (VectorMath2 vectorA);
	bool operator< (VectorMath2 vectorA);
	bool operator> (VectorMath2 vectorA);
	float Length();
	void Normalize();
	VectorMath2 NormalizeNew();
	float DotProduct(VectorMath2 vectorA);
	VectorMath2 CrossProduct(VectorMath2 vectorA);
	void PrintVector();
};

// vector constructor for all values
inline VectorMath2::VectorMath2(float xIn, float yIn)
{
	x = xIn;
	y = yIn;
}

// empty vector constructor
inline VectorMath2::VectorMath2()
{
	x = 0;
	y = 0;
}

// [] operator overload
inline float& VectorMath2::operator[](int index) {
	return coords[index];
}

// [] operator overload
inline float VectorMath2::operator[](int index)const {
	return coords[index];
}

// + operator overload
inline VectorMath2 VectorMath2::operator+(VectorMath2 vectorA) {
	VectorMath2 temp;
	for (int i = 0; i < 2; i++)
	{
		temp[i] = coords[i] + vectorA[i];
	}
	return temp;
}

// - operator overload
inline VectorMath2 VectorMath2::operator-(VectorMath2 vectorA) {
	VectorMath2 temp;
	for (int i = 0; i < 2; i++)
	{
		temp[i] = coords[i] - vectorA[i];
	}
	return temp;
}

// * operator overload
inline VectorMath2 VectorMath2::operator*(float multiplier) {
	VectorMath2 temp;
	for (int i = 0; i < 2; i++) {
		temp[i] = coords[i] * multiplier;
	}
	return temp;
}

inline bool VectorMath2::operator==(const VectorMath2 vectorA) {
        if(vectorA.x == x && vectorA.y == y)
            return true;

        return false;
}

inline bool VectorMath2::operator<(const VectorMath2 vectorA) {
        if(x < vectorA.x) return true;
        if(x > vectorA.x) return false;
        //x == coord.x
        if(y < vectorA.y) return true;
        if(y > vectorA.y) return false;

        return false;
}

inline bool VectorMath2::operator>(const VectorMath2 vectorA) {
        if(x > vectorA.x) return true;
        if(x < vectorA.x) return false;
        //x == coord.x
        if(y > vectorA.y) return true;
        if(y < vectorA.y) return false;

        return false;
}

// calculates and returns the length of a vector
inline float VectorMath2::Length() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

// normalizes a vector
inline void VectorMath2::Normalize() {
	if (Length() == 0) { return; }
	*this = *this * (1.0f / Length());
}

inline VectorMath2 VectorMath2::NormalizeNew() {
	if (Length() == 0) { return *this; }
	*this = *this * (1.0f / Length());
	return *this;
}

// calculates the dot product between a vector and agument vector
inline float VectorMath2::DotProduct(VectorMath2 vectorA) {
	float temp = 0;
	for (int i = 0; i < 2; i++)
	{
		temp += coords[i] * vectorA[i];
	}
	return temp;
}

// calculates the cross product between a vector and agument vector
inline VectorMath2 VectorMath2::CrossProduct(VectorMath2 vectorA) {
	VectorMath2 temp;
	//x*y
	temp[2] = (coords[0] * vectorA[1]) - (coords[1] * vectorA[0]);
	//y*z
	temp[0] = (coords[1] * vectorA[2]) - (coords[2] * vectorA[1]);
	return temp;
}

// this function prints vector3s
inline void VectorMath2::PrintVector() {
	for (int i = 0; i < 2; i++)
	{
		std::cout << coords[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}

//--------------------------------------------------------------------------------------\\

struct VectorMath3
{
	union {
		struct
		{
			float x;
			float y;
			float z;
		};
		float coords[3];
	};

	VectorMath3(float xIn, float yIn, float zIn);
	VectorMath3(VectorMath2, float zIn);
	VectorMath3();
	float& operator[](int index);
	float operator[](int index)const;
	VectorMath3 operator+(VectorMath3 vectorA);
	VectorMath3 operator-(VectorMath3 vectorA);
	VectorMath3 operator*(float multiplier);
	float Length();
	void Normalize();
	VectorMath3 NormalizeNew();
	float DotProduct(VectorMath3 vectorA);
	VectorMath3 CrossProduct(VectorMath3 vectorA);
	void PrintVector();
};

// vector constructor for all values
inline VectorMath3::VectorMath3(float xIn, float yIn, float zIn)
{
	x = xIn;
	y = yIn;
	z = zIn;
}

inline VectorMath3::VectorMath3(VectorMath2 xyIn, float zIn){
	x = xyIn.x;
	y = xyIn.y;
	z = zIn;
}

// empty vector constructor
inline VectorMath3::VectorMath3()
{
	x = 0;
	y = 0;
	z = 0;
}

// [] operator overload
inline float& VectorMath3::operator[](int index) {
	return coords[index];
}

// [] operator overload
inline float VectorMath3::operator[](int index)const {
	return coords[index];
}

// + operator overload
inline VectorMath3 VectorMath3::operator+(VectorMath3 vectorA) {
	VectorMath3 temp;
	for (int i = 0; i < 3; i++)
	{
		temp[i] = coords[i] + vectorA[i];
	}
	return temp;
}

// - operator overload
inline VectorMath3 VectorMath3::operator-(VectorMath3 vectorA) {
	VectorMath3 temp;
	for (int i = 0; i < 3; i++)
	{
		temp[i] = coords[i] - vectorA[i];
	}
	return temp;
}

// * operator overload
inline VectorMath3 VectorMath3::operator*(float multiplier) {
	VectorMath3 temp;
	for (int i = 0; i < 3; i++) {
		temp[i] = coords[i] * multiplier;
	}
	return temp;
}

// calculates and returns the length of a vector
inline float VectorMath3::Length() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

// normalizes a vector
inline void VectorMath3::Normalize() {
	if (Length() == 0) {return;}
	*this = *this * (1.0f / Length());
}

inline VectorMath3 VectorMath3::NormalizeNew() {
	if (Length() == 0) {return *this;}
	*this = *this * (1.0f / Length());
	return *this;
}

// calculates the dot product between a vector and agument vector
inline float VectorMath3::DotProduct(VectorMath3 vectorA) {
	float temp = 0;
	for (int i = 0; i < 3; i++)
	{
		temp += coords[i] * vectorA[i];
	}
	return temp;
}

// calculates the cross product between a vector and agument vector
inline VectorMath3 VectorMath3::CrossProduct(VectorMath3 vectorA) {
	VectorMath3 temp;
	//x*y
	temp[2] = (coords[0] * vectorA[1]) - (coords[1] * vectorA[0]);
	//y*z
	temp[0] = (coords[1] * vectorA[2]) - (coords[2] * vectorA[1]);
	//x*z
	temp[1] = (coords[0] * vectorA[2]) - (coords[2] * vectorA[0]);
	return temp;
}

// this function prints vector3s
inline void VectorMath3::PrintVector() {
	for (int i = 0; i < 3; i++)
	{
		std::cout << coords[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}

//--------------------------------------------------------------------------------------\\

struct VectorMath4
{
	union {
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float coords[4];
	};

	VectorMath4(float xIn, float yIn, float zIn, float wIn);
	VectorMath4(float xIn, float yIn, float zIn);
	VectorMath4(float wIn);
	VectorMath4();
	VectorMath4(VectorMath3 vector, float W);
	float operator[](int index)const;
	float& operator[](int index);
	VectorMath4 operator+(VectorMath4 vectorA);
	VectorMath4 operator-(VectorMath4 vectorA);
	VectorMath4 operator*(float multiplier);
	float Length();
	void Normalize();
	VectorMath4 NormalizeNew();
	float DotProduct(VectorMath4 vectorA);
	VectorMath4 CrossProduct(VectorMath4 vectorA);
	void PrintVector();
};

inline VectorMath4::VectorMath4(float xIn, float yIn, float zIn, float wIn) {
	x = xIn;
	y = yIn;
	z = zIn;
	w = wIn;;
}

// constructor for // constructor for x, y, z
inline VectorMath4::VectorMath4(float xIn, float yIn, float zIn) {
	x = xIn;
	y = yIn;
	z = zIn;
	w = 0;
}

// constructor for empty vector with preset w
inline VectorMath4::VectorMath4(float wIn) {
	x = 0;
	y = 0;
	z = 0;
	w = wIn;
}

// constructor for empty vector
inline VectorMath4::VectorMath4() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

inline VectorMath4::VectorMath4(VectorMath3 vector, float W) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = W;
}

// [] operator overload
inline float& VectorMath4::operator[](int index) {
	return coords[index];
}

// [] operator overload
inline float VectorMath4::operator[](int index)const {
	return coords[index];
}

// + operator overload
inline VectorMath4 VectorMath4::operator+(VectorMath4 vectorA) {
	VectorMath4 temp;
	for (int i = 0; i < 4; i++)
	{
		temp[i] = coords[i] + vectorA[i];
	}
	return temp;
}

// - operator overload
inline VectorMath4 VectorMath4::operator-(VectorMath4 vectorA) {
	VectorMath4 temp;
	for (int i = 0; i < 4; i++)
	{
		temp[i] = coords[i] - vectorA[i];
	}
	return temp;
}

// * operator overload
inline VectorMath4 VectorMath4::operator*(float multiplier) {
	VectorMath4 temp;
	for (int i = 0; i < 4; i++) {
		temp[i] = coords[i] * multiplier;
	}
	return temp;
}

// calculates and returns the length of a vector
inline float VectorMath4::Length() {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
}

// normalizes a vector
inline void VectorMath4::Normalize() {
	if (Length() == 0) { return; }
	*this  = *this * (1.0f/Length());
}

inline VectorMath4 VectorMath4::NormalizeNew() {
	if (Length() == 0) { return *this; }
	*this = *this * (1.0f / Length());
	return *this;
}

// calculates the dot product between a vector and agument vector
inline float VectorMath4::DotProduct(VectorMath4 vectorA) {
	float temp = 0;
	for (int i = 0; i < 4; i++)
	{
		temp += coords[i] * vectorA[i];
	}
	return temp;
}

// calculates the cross product between a vector and agument vector
inline VectorMath4 VectorMath4::CrossProduct(VectorMath4 vectorA) {
	VectorMath4 temp;
	//x*y
	temp[2] = (coords[0] * vectorA[1]) - (coords[1] * vectorA[0]);
	//y*z
	temp[0] = (coords[1] * vectorA[2]) - (coords[2] * vectorA[1]);
	//x*z
	temp[1] = (coords[0] * vectorA[2]) - (coords[2] * vectorA[0]);
	//w
	temp[3] = 0;
	return temp;
}

// this function prints vector4s
inline void VectorMath4::PrintVector() {
	for (int i = 0; i < 4; i++)
	{
		std::cout << coords[i];
		std::cout << " ";
	}
	std::cout << std::endl;
}