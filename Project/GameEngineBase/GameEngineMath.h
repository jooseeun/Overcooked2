#pragma once
#include <math.h>
#include <Windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <string>
#include <math.h>
#include <cmath>

#include <DirectXCollision.h>
#include "GameEngineDebug.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")


// 설명 :
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float DEG;
	static const float DegreeToRadian;
	static const float RadianToDegree;

	static float Lerp(float p1, float p2, float Time)
	{
		return (1.0f - Time) * p1 + Time * p2;
	}

	// 보통 누적된 시간을 Time
	static float LerpLimit(float p1, float p2, float Time)
	{
		if (1.0f <= Time)
		{
			Time = 1.0f;
		}

		return Lerp(p1, p2, Time);
	}

private:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;


};

class float4x4;
class float4
{
public:
	// Dir
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;
	static const float4 FORWARD;
	static const float4 BACK;
	static const float4 ZERO;
	static const float4 ONE;

	// Color
	static const float4 YELLOW;
	static const float4 MAGENTA;
	static const float4 CYAN;
	static const float4 BLUE;
	static const float4 RED;
	static const float4 GREEN;
	static const float4 WHITE;
	static const float4 BLACK;

public:
	// 외적을 쓸수 있는곳
	// 마우스 클릭시 회전방향 알아낼때.
	static float4 Cross3D(const float4& _Left, const float4& _Right)
	{
		return DirectX::XMVector3Cross(_Left.DirectVector, _Right.DirectVector);
	}

	static float4 QuaternionToEulerAngles(float4 q)
	{
		float4 angles;

		double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
		double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
		angles.x = static_cast<float>(std::atan2(sinr_cosp, cosr_cosp));

		double sinp = 2 * (q.w * q.y - q.z * q.x);
		if (std::abs(sinp) >= 1)
			angles.y = static_cast<float>(std::copysign(GameEngineMath::PI / 2, sinp));
		else
			angles.y = static_cast<float>(std::asin(sinp));

		double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
		double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
		angles.z = static_cast<float>(std::atan2(siny_cosp, cosy_cosp));

		return angles;
	}

	static float4 Select(const float4& _Left, const float4& _Right, const float4& _Control)
	{
		float4 Return;

		if (_Control.x != 0.0f)
		{
			Return.x = _Right.x;
		}
		else {
			Return.x = _Left.x;
		}

		if (_Control.y != 0.0f)
		{
			Return.y = _Right.y;
		}
		else {
			Return.y = _Left.y;
		}

		if (_Control.z != 0.0f)
		{
			Return.z = _Right.z;
		}
		else {
			Return.z = _Left.z;
		}

		if (_Control.w != 0.0f)
		{
			Return.w = _Right.w;
		}
		else {
			Return.w = _Left.w;
		}

		//Return.Arr1DInt[0] = (_Left.Arr1DInt[0] & ~_Control.Arr1DInt[0]) | (_Right.Arr1DInt[0] & _Control.Arr1DInt[0]);
		//Return.Arr1DInt[1] = (_Left.Arr1DInt[1] & ~_Control.Arr1DInt[1]) | (_Right.Arr1DInt[1] & _Control.Arr1DInt[1]);
		//Return.Arr1DInt[2] = (_Left.Arr1DInt[2] & ~_Control.Arr1DInt[2]) | (_Right.Arr1DInt[2] & _Control.Arr1DInt[2]);
		//Return.Arr1DInt[3] = (_Left.Arr1DInt[3] & ~_Control.Arr1DInt[3]) | (_Right.Arr1DInt[3] & _Control.Arr1DInt[3]);
		return Return;
	}

	static float4 Normalize3DReturn(const float4& _Value)
	{
		float4 Return = _Value;
		Return.Normalize3D();
		return Return;
	}

	static float4 ABS3DReturn(const float4& _Postion)
	{
		return _Postion.ABS3DReturn();
	}

	static float VectorXYtoDegree(const float4& _Postion, const float4& _Target)
	{
		return VectorXYtoRadian(_Postion, _Target) * GameEngineMath::RadianToDegree;
	}

	static float VectorXYtoRadian(const float4& _Postion, const float4& _Target)
	{
		float4 Dir = _Target - _Postion;
		Dir.Normalize3D();
		// cos(90) => 1.5
		// acos(1.5) => 90
		float Angle = acosf(Dir.x);

		if (_Postion.y > _Target.y)
		{
			Angle = GameEngineMath::PI2 - Angle;
		}

		return Angle;
	}

	static float4 DegreeToDirection2D(float _Degree)
	{
		return RadianToDirection2D(_Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RadianToDirection2D(float _Radian)
	{
		return { cosf(_Radian) , sinf(_Radian) };
	}

	static float4 VectorRotationToDegreeZAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianZAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianZAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		Rot.x = _Value.x * cosf(_Radian) - _Value.y * sinf(_Radian);
		Rot.y = _Value.x * sinf(_Radian) + _Value.y * cosf(_Radian);
		Rot.z = _Value.z;
		return Rot;
	}

	static float4 VectorRotationToDegreeYAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianYAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianYAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		Rot.x = _Value.x * cosf(_Radian) - _Value.z * sinf(_Radian);
		Rot.z = _Value.x * sinf(_Radian) + _Value.z * cosf(_Radian);
		Rot.y = _Value.y;
		return Rot;
	}


	static float4 VectorRotationToDegreeXAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianXAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	// [][] * cosf   -sinf
	// [][]   sinf   cosf

	static float4 VectorRotationToRadianXAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		Rot.z = _Value.z * cosf(_Radian) - _Value.y * sinf(_Radian);
		Rot.y = _Value.z * sinf(_Radian) + _Value.y * cosf(_Radian);
		Rot.x = _Value.x;
		return Rot;
	}

	static float4 Lerp(const float4& p1, const float4& p2, float Time)
	{
		return p1 * (1.0f - Time) + p2 * Time;
	}

	static float4 SLerpQuaternion(const float4& _Left, const float4& _Right, float _Ratio)
	{
		if (0.0f >= _Ratio)
		{
			_Ratio = 0.0f;
		}
		if (1.0f <= _Ratio)
		{
			_Ratio = 1.0f;
		}

		return DirectX::XMQuaternionSlerp(_Left.DirectVector, _Right.DirectVector, _Ratio);
	}

	// 보통 누적된 시간을 Time
	static float4 LerpLimit(const float4& p1, const float4& p2, float Time)
	{
		if (0.0f >= Time)
		{
			Time = 0.0f;
		}

		if (1.0f <= Time)
		{
			Time = 1.0f;
		}

		return Lerp(p1, p2, Time);
	}

	static float4 MatrixToQuaternion(const class float4x4& M);

	static float InvSqrt(float f)
	{
		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(f);
		X0 = _mm_rsqrt_ss(Y0);	// 1sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	}


	bool IsNearlyZero() const
	{
		return fabsf(x) <= 1.e-4f && fabsf(y) <= 1.e-4f && fabsf(z) <= 1.e-4f;
	}

	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		// DirectX::XMVector3Dot
		float fValue = _Left.x * _Right.x + _Left.y * _Right.y + _Left.z * _Right.z;
		return fValue;
	}

	static float4 GetDegree3D(const float4& _Left, const float4& _Right)
	{
		float4 v3 = _Right - _Left;
		if (v3.z > 0)
		{
			v3 *= -1;
		}

		float xAngle = atan2(v3.y, v3.z) * 180 / GameEngineMath::PI;
		float yAngle = atan2(v3.x, v3.z) * 180 / GameEngineMath::PI;
		float zAngle = atan2(v3.y, v3.x) * 180 / GameEngineMath::PI;

		float4 Result = { xAngle, yAngle, zAngle };
		return Result;
	}

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};

		struct
		{
			int IntValueX;
			int IntValueY;
			int IntValueZ;
			int IntValueW;
		};


		float Arr1D[4];

		int Arr1DInt[4];

		DirectX::XMFLOAT3 DirectFloat3;
		DirectX::XMFLOAT4 DirectFloat4;
		DirectX::XMVECTOR DirectVector;
	};

public:
	bool IsZero2D() const
	{
		return x == 0.0f && y == 0.0f;
	}

	UINT GetUIntColor() const
	{
		UINT Int;
		char* ColorPtr = reinterpret_cast<char*>(&Int);
		ColorPtr[0] = static_cast<int>(x * 255.0f); // 1.0f * 255.0f
		ColorPtr[1] = static_cast<int>(y * 255.0f);
		ColorPtr[2] = static_cast<int>(z * 255.0f);
		ColorPtr[3] = static_cast<int>(w * 255.0f);

		return Int;
	}

	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}


	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	POINT GetConvertWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	std::string ToString()
	{
		std::string Value;
		Value += "x : ";
		Value += std::to_string(x);
		Value += " y : ";
		Value += std::to_string(y);
		Value += " z : ";
		Value += std::to_string(z);
		return Value;
	}

	std::string ToDataString()
	{
		std::string Value;
		{
			std::string TmpS = std::to_string(x);
			TmpS = TmpS.substr(0, TmpS.find('.') + 3);
			Value += TmpS;
		}

		Value += ",";
		{
			std::string TmpS = std::to_string(y);
			TmpS = TmpS.substr(0, TmpS.find('.') + 3);
			Value += TmpS;
		}

		Value += ",";
		{
			std::string TmpS = std::to_string(z);
			TmpS = TmpS.substr(0, TmpS.find('.') + 3);
			Value += TmpS;
		}

		return Value;
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.5f, 1.0f };
	}

	float4 ABS3DReturn() const
	{
		return float4(fabsf(x), fabsf(y), fabsf(z));
	}

	float Length() const
	{
		// sqrtf 제곱근 구해줍니다.
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	void Normalize3D()
	{
		DirectVector = DirectX::XMVector3Normalize(DirectVector);
		return;
	}

	float4 Normalize3DReturn() const
	{
		float4 Return = *this;
		Return.Normalize3D();
		return Return;
	}

	void Range2D(float _Max)
	{
		Normalize3D();

		x *= _Max;
		y *= _Max;
		return;
	}

	operator DirectX::XMFLOAT4() const
	{
		return DirectFloat4;
	}

	operator DirectX::XMFLOAT3() const
	{
		return DirectFloat3;
	}

	float& operator[](int _Index)
	{
		return Arr1D[_Index];
	}


	float4 operator-(const float4& _Other) const
	{
		return { x - _Other.x, y - _Other.y, z - _Other.z, 1.0f };
	}

	float4 operator-() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4 operator+(const float4& _Other) const
	{
		return { x + _Other.x, y + _Other.y, z + _Other.z, 1.0f };
	}

	float4 operator*(const float _Value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, float4(_Value).DirectVector);
	}

	float4 operator*(const float4& _Value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, _Value.DirectVector);
	}

	float4 operator/(const float _Value) const
	{
		return DirectX::XMVectorDivide(DirectVector, float4(_Value).DirectVector);
	}

	float4& operator/=(const float _Value)
	{
		DirectVector = DirectX::XMVectorDivide(DirectVector, float4(_Value).DirectVector);

		return *this;
	}

	float4 operator/(const float4& _Value) const
	{
		return DirectX::XMVectorDivide(DirectVector, _Value.DirectVector);
	}

	float4& operator+=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

	float4& operator-=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;

		return *this;
	}

	float4& operator*=(const float _Other)
	{
		x *= _Other;
		y *= _Other;
		z *= _Other;

		return *this;
	}


	float4& operator*=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;

		return *this;
	}

	float4 DegreeRotationToQuaternionReturn() const
	{
		float4 Rot = *this;
		Rot *= GameEngineMath::DegreeToRadian;
		Rot.DirectVector = DirectX::XMQuaternionRotationRollPitchYawFromVector(Rot.DirectVector);
		return Rot;
	}

	bool CompareInt2D(const float4& _Value) const
	{
		return ix() == _Value.ix() && iy() == _Value.iy();
	}

	bool CompareInt3D(const float4& _Value) const
	{
		return ix() == _Value.ix() &&
			iy() == _Value.iy() &&
			iz() == _Value.iz();
	}

	bool CompareInt4D(const float4& _Value) const
	{
		return ix() == _Value.ix() &&
			iy() == _Value.iy() &&
			iz() == _Value.iz() &&
			iw() == _Value.iw();
	}


	float4 RotationToDegreeZ(float _Degree)
	{
		return RotationToRadianZAXis(_Degree * GameEngineMath::DegreeToRadian);
	}

	float4 RotationToRadianZAXis(float _Radian)
	{
		*this = VectorRotationToRadianZAxis(*this, _Radian);
		return *this;
	}

	POINT ToWinAPIPOINT() const
	{
		POINT NewPoint;
		NewPoint.x = ix();
		NewPoint.y = iy();
		return NewPoint;
	}

	void TransformCoord(const float4x4& _Value);

	float4 TransformCoordReturn(const float4x4& _Value);

	void TransformNormal(const float4x4& _Value);

	float4 TransformNormalReturn(const float4x4& _Value);


public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}
	float4(float _Value)
		: x(_Value), y(_Value), z(_Value), w(_Value)
	{

	}


	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	float4(const DirectX::XMVECTOR& _Vector)
		: DirectVector(_Vector)
	{

	}



};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	float4 CenterLeftTopPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterTop()) };
	}

	float4 CenterLeftBotPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterBot()) };
	}

	float4 CenterRightTopPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterTop()) };
	}

	float4 CenterRightBotPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterBot()) };
	}

	int CenterLeft() const
	{
		return Pos.ix() - Scale.hix();
	}

	int CenterRight() const
	{
		return Pos.ix() + Scale.hix();
	}

	int CenterTop() const
	{
		return Pos.iy() - Scale.hiy();
	}

	int CenterBot() const
	{
		return Pos.iy() + Scale.hiy();
	}

	bool OverLap(const GameEngineRect& _Other)
	{
		if (CenterBot() < _Other.CenterTop())
		{
			return false;
		}

		if (CenterTop() > _Other.CenterBot())
		{
			return false;
		}

		if (CenterRight() < _Other.CenterLeft())
		{
			return false;
		}

		if (CenterLeft() > _Other.CenterRight())
		{
			return false;
		}

		return true;
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{

	}
};

class float4x4
{
public:
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
		float4 ArrV[4];
		DirectX::XMMATRIX DirectMatrix;
	};

public:
	float4x4(const DirectX::XMMATRIX& _DirectMatrix)
		: DirectMatrix(_DirectMatrix)
	{
	}

	float4x4()
	{
		Identity();
	}

public:
	void ZeroCheck()
	{
		for (size_t i = 0; i < 16; i++)
		{
			if (Arr1D[i] <= FLT_EPSILON)
			{
				Arr1D[i] = 0.0f;
			}
		}
	}

	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();

		//memset(Arr1D, 0, sizeof(float) * 16);
		//Arr2D[0][0] = 1.0f;
		//Arr2D[1][1] = 1.0f;
		//Arr2D[2][2] = 1.0f;
		//Arr2D[3][3] = 1.0f;
	}

	void Scale(const float4& _Value)
	{
		// Identity();

		DirectMatrix = DirectX::XMMatrixScaling(_Value.x, _Value.y, _Value.z);

		//Arr2D[0][0] = _Value.x;
		//Arr2D[1][1] = _Value.y;
		//Arr2D[2][2] = _Value.z;
		//Arr2D[3][3] = 1.0f;
	}

	void Position(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);

		// Identity();
		//Arr2D[3][0] = _Value.x;
		//Arr2D[3][1] = _Value.y;
		//Arr2D[3][2] = _Value.z;
		//Arr2D[3][3] = 1.0f;
	}

	void RotationXDegree(const float _Value)
	{
		RotationXRadian(_Value);
	}

	void RotationXRadian(const float _Value)
	{
		Arr2D[1][1] = cosf(_Value);
		Arr2D[1][2] = sinf(_Value);
		Arr2D[2][1] = -sinf(_Value);
		Arr2D[2][2] = cosf(_Value);
	}

	void RotYDegree(const float _Value)
	{
		RotationYRadian(_Value);
	}

	void RotationYRadian(const float _Value)
	{
		Arr2D[0][0] = cosf(_Value);
		Arr2D[0][2] = -sinf(_Value);
		Arr2D[2][0] = sinf(_Value);
		Arr2D[2][2] = cosf(_Value);
	}

	void RotationZDegree(const float _Value)
	{
		RotationZRadian(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationZRadian(const float _Value)
	{
		Arr2D[0][0] = cosf(_Value);
		Arr2D[0][1] = sinf(_Value);
		Arr2D[1][0] = -sinf(_Value);
		Arr2D[1][1] = cosf(_Value);
	}

	void RotationDegree(const float4& _Value)
	{
		RotationRadian(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationRadian(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Value.DirectVector);

		//float4x4 XRot;
		//float4x4 YRot;
		//float4x4 ZRot;
		//XRot.RotationXRadian(_Value.x);
		//YRot.RotationYRadian(_Value.y);
		//ZRot.RotationZRadian(_Value.z);

		//*this = XRot * YRot * ZRot;
	}

	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin, float _ZMax)
	{

		// 크기 자전 이동 뷰 투영 뷰포트 => 모니터에
		//                                마우스포지션은
		//                       * 마우스포지션은

		//             -1~1사이의 값이
		//            640
		Arr2D[0][0] = _Width / 2.0f;
		Arr2D[0][1] = 0.0f;
		Arr2D[0][2] = 0.0f;
		Arr2D[0][3] = 0.0f;

		Arr2D[1][0] = 0.0f;
		Arr2D[1][1] = -_Height / 2.0f;
		Arr2D[1][2] = 0.0f;
		Arr2D[1][3] = 0.0f;

		Arr2D[2][0] = 0.0f;
		Arr2D[2][1] = 0.0f;
		Arr2D[2][2] = 1.0f / 2.0f;
		Arr2D[2][3] = 0.0f;

		Arr2D[3][0] = _Width * 0.5f + _Left;
		Arr2D[3][1] = _Height * 0.5f + _Right;
		Arr2D[3][2] = 1.0f / 2.0f;
		Arr2D[3][3] = 1.0f;
	}

	// Fov to Degree
	void PerspectiveFovLH(float _FovDegree, float _Width, float _Height, float _Near, float _Far)
	{
		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovDegree * GameEngineMath::DegreeToRadian * 0.5f, _Width / _Height, _Near, _Far);

		//assert(NearZ > 0.f && FarZ > 0.f);
		//assert(!XMScalarNearEqual(FovAngleY, 0.0f, 0.00001f * 2.0f));
		//assert(!XMScalarNearEqual(AspectRatio, 0.0f, 0.00001f));
		//assert(!XMScalarNearEqual(FarZ, NearZ, 0.00001f));

		//float    SinFov;
		//float    CosFov;
		// XMScalarSinCos(&SinFov, &CosFov, 0.5f * FovAngleY);

		//               45                                 
		//float Tan = tanf(_FovDegree * GameEngineMath::DegreeToRadian * 0.5f);
		//float fRange = _Far / (_Far - _Near);
		//
		//Arr2D[0][0] = 1.0f / (Tan * (_Width / _Height)); // / z
		//Arr2D[0][1] = 0.0f;
		//Arr2D[0][2] = 0.0f;
		//Arr2D[0][3] = 0.0f;
		//
		//Arr2D[1][0] = 0.0f;
		//Arr2D[1][1] = 1.0f / Tan;
		//Arr2D[1][2] = 0.0f;
		//Arr2D[1][3] = 0.0f;
		//
		// 
		// 기존의 n = 0, f = 1 값이 아니라 반대로 되도록 되어있음
		//Arr2D[2][0] = 0.0f;
		//Arr2D[2][1] = 0.0f;
		//Arr2D[2][2] = -1 / (_Far - _Near);
		//Arr2D[2][3] = 1.0f;
		//
		//Arr2D[3][0] = 0.0f;
		//Arr2D[3][1] = 0.0f;
		//Arr2D[3][2] = fRange;
		//Arr2D[3][3] = 0.0f;
	}

	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		// DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);

	   //assert(!XMScalarNearEqual(ViewWidth, 0.0f, 0.00001f));
	   //assert(!XMScalarNearEqual(ViewHeight, 0.0f, 0.00001f));
	   //assert(!XMScalarNearEqual(FarZ, NearZ, 0.00001f));

		float fRange = 1.0f / (_Far - _Near);

		Arr2D[0][0] = 2.0f / _Width;
		Arr2D[0][1] = 0.0f;
		Arr2D[0][2] = 0.0f;
		Arr2D[0][3] = 0.0f;

		Arr2D[1][0] = 0.0f;
		Arr2D[1][1] = 2.0f / _Height;
		Arr2D[1][2] = 0.0f;
		Arr2D[1][3] = 0.0f;

		Arr2D[2][0] = 0.0f;
		Arr2D[2][1] = 0.0f;
		Arr2D[2][2] = fRange;
		Arr2D[2][3] = 0.0f;

		Arr2D[3][0] = 0.0f;
		Arr2D[3][1] = 0.0f;
		Arr2D[3][2] = -fRange * _Near;
		Arr2D[3][3] = 1.0f;
	}

	//               바라보고 있는 위치
	void LookAtLH(const float4& _EyePostion, const float4& _EyeFocus, const float4& _Up)
	{
		LookToLH(_EyePostion, (_EyeFocus - _EyePostion), _Up);
	}

	void LookToLH(const float4& _EyePostion, const float4& _EyeDir, const float4& _Up)
	{
		DirectMatrix = DirectX::XMMatrixLookToLH(_EyePostion.DirectVector, _EyeDir.DirectVector, _Up.DirectVector);
	}

	void Inverse()
	{
		DirectMatrix = DirectX::XMMatrixInverse(nullptr, DirectMatrix);
	}

	float4x4 InverseReturn()
	{
		DirectX::XMMATRIX Result = DirectX::XMMatrixInverse(nullptr, DirectMatrix);
		return Result;
	}

	void Transpose()
	{
		DirectMatrix = DirectX::XMMatrixTranspose(DirectMatrix);
	}

	static float4x4 Transformation(float4 _Scale, float4 _RotQ, float4 _Pos)
	{
		return DirectX::XMMatrixTransformation(float4::ZERO.DirectVector, float4::ZERO.DirectVector, _Scale.DirectVector, float4::ZERO.DirectVector, _RotQ.DirectVector, _Pos.DirectVector);
	}

	float4 ExtractScaling()
	{
		float4 ret = float4::ZERO;
		float Tolerance = 1.e-8f;

		const float SquareSum0 = (Arr2D[0][0] * Arr2D[0][0]) + (Arr2D[0][1] * Arr2D[0][1]) + (Arr2D[0][2] * Arr2D[0][2]);
		const float SquareSum1 = (Arr2D[1][0] * Arr2D[1][0]) + (Arr2D[1][1] * Arr2D[1][1]) + (Arr2D[1][2] * Arr2D[1][2]);
		const float SquareSum2 = (Arr2D[2][0] * Arr2D[2][0]) + (Arr2D[2][1] * Arr2D[2][1]) + (Arr2D[2][2] * Arr2D[2][2]);

		if (SquareSum0 > Tolerance)
		{
			float Scale0 = sqrtf(SquareSum0);
			ret.x = Scale0;
			float InvScale0 = 1.f / Scale0;
			Arr2D[0][0] *= InvScale0;
			Arr2D[0][1] *= InvScale0;
			Arr2D[0][2] *= InvScale0;
		}
		else
		{
			ret.x = 0;
		}

		if (SquareSum1 > Tolerance)
		{
			float Scale1 = sqrtf(SquareSum1);
			ret.y = Scale1;
			float InvScale1 = 1.f / Scale1;
			Arr2D[1][0] *= InvScale1;
			Arr2D[1][1] *= InvScale1;
			Arr2D[1][2] *= InvScale1;
		}
		else
		{
			ret.y = 0;
		}

		if (SquareSum2 > Tolerance)
		{
			float Scale2 = sqrtf(SquareSum2);
			ret.z = Scale2;
			float InvScale2 = 1.f / Scale2;
			Arr2D[2][0] *= InvScale2;
			Arr2D[2][1] *= InvScale2;
			Arr2D[2][2] *= InvScale2;
		}
		else
		{
			ret.z = 0;
		}

		return ret;
	}


	inline float Determinant() const
	{
		return	Arr2D[0][0] * (
			Arr2D[1][1] * (Arr2D[2][2] * Arr2D[3][3] - Arr2D[2][3] * Arr2D[3][2]) -
			Arr2D[2][1] * (Arr2D[1][2] * Arr2D[3][3] - Arr2D[1][3] * Arr2D[3][2]) +
			Arr2D[3][1] * (Arr2D[1][2] * Arr2D[2][3] - Arr2D[1][3] * Arr2D[2][2])
			) -
			Arr2D[1][0] * (
				Arr2D[0][1] * (Arr2D[2][2] * Arr2D[3][3] - Arr2D[2][3] * Arr2D[3][2]) -
				Arr2D[2][1] * (Arr2D[0][2] * Arr2D[3][3] - Arr2D[0][3] * Arr2D[3][2]) +
				Arr2D[3][1] * (Arr2D[0][2] * Arr2D[2][3] - Arr2D[0][3] * Arr2D[2][2])
				) +
			Arr2D[2][0] * (
				Arr2D[0][1] * (Arr2D[1][2] * Arr2D[3][3] - Arr2D[1][3] * Arr2D[3][2]) -
				Arr2D[1][1] * (Arr2D[0][2] * Arr2D[3][3] - Arr2D[0][3] * Arr2D[3][2]) +
				Arr2D[3][1] * (Arr2D[0][2] * Arr2D[1][3] - Arr2D[0][3] * Arr2D[1][2])
				) -
			Arr2D[3][0] * (
				Arr2D[0][1] * (Arr2D[1][2] * Arr2D[2][3] - Arr2D[1][3] * Arr2D[2][2]) -
				Arr2D[1][1] * (Arr2D[0][2] * Arr2D[2][3] - Arr2D[0][3] * Arr2D[2][2]) +
				Arr2D[2][1] * (Arr2D[0][2] * Arr2D[1][3] - Arr2D[0][3] * Arr2D[1][2])
				);
	}

	static float4x4 Affine(float4 _Scale, float4 _Rot, float4 _Pos)
	{
		// _Rot.DirectVector 쿼터니온 입니다.
		return DirectX::XMMatrixAffineTransformation(_Scale.DirectVector, float4::ZERO.DirectVector, _Rot.DirectVector, _Pos.DirectVector);
	}

public: // 연산자
	float4x4 operator*(const float4x4& _Value)
	{
		return DirectX::XMMatrixMultiply(DirectMatrix, _Value.DirectMatrix);
	}
};

float4 operator*(const float4& _Vector, const float4x4& _Value);
float4& operator*=(float4& _Vector, const float4x4& _Value);

