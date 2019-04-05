#pragma once

#if defined(WIN32)
	#define CDECL __cdecl
#elif defined(__LINUX__)
	#define CDECL __attribute__((__cdecl__))
#endif

#ifdef __LINUX__

#define _In_
#define _In_opt_
#define _In_reads_(size)
#define _In_reads_opt_(size)
#define _In_reads_bytes_(size)
#define _Out_
#define _Out_opt_
#define _Inout_
#define _Inout_opt_
#define _When_(expr, annotes)


#define XM_CONST constexpr
#define XM_CONSTEXPR constexpr

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef long HRESULT;
#endif // !_HRESULT_DEFINED

namespace DirectX
{
//------------------------------------------------------------------------------
// 2D Vector; 32 bit floating point components
struct XMFLOAT2
{
    float x;
    float y;

    XMFLOAT2() = default;

    XMFLOAT2(const XMFLOAT2&) = default;
    XMFLOAT2& operator=(const XMFLOAT2&) = default;

    XMFLOAT2(XMFLOAT2&&) = default;
    XMFLOAT2& operator=(XMFLOAT2&&) = default;

    XM_CONSTEXPR XMFLOAT2(float _x, float _y) : x(_x), y(_y) {}
    explicit XMFLOAT2(_In_reads_(2) const float* pArray) : x(pArray[0]), y(pArray[1]) {}
};

//------------------------------------------------------------------------------
// 3D Vector; 32 bit floating point components
struct XMFLOAT3
{
    float x;
    float y;
    float z;

    XMFLOAT3() = default;

    XMFLOAT3(const XMFLOAT3&) = default;
    XMFLOAT3& operator=(const XMFLOAT3&) = default;

    XMFLOAT3(XMFLOAT3&&) = default;
    XMFLOAT3& operator=(XMFLOAT3&&) = default;

    XM_CONSTEXPR XMFLOAT3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    explicit XMFLOAT3(_In_reads_(3) const float* pArray) : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}
};
} /* namespace DirectX */


#endif //__LINUX__
