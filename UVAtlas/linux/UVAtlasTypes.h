#pragma once

#if defined(WIN32)
	#define CDECL __cdecl
#elif defined(__LINUX__)
	#define CDECL __attribute__((__cdecl__))
#endif

#ifdef __LINUX__

#define _Use_decl_annotations_
#define _In_
#define _In_opt_
#define _In_z_
#define _In_reads_(size)
#define _In_reads_opt_(size)
#define _In_reads_bytes_(size)
#define _Out_
#define _Out_opt_
#define _Out_writes_(size)
#define _Out_writes_bytes_(size)
#define _Inout_
#define _Inout_opt_
#define _When_(expr, annotes)
#define _Printf_format_string_
#define _Analysis_assume_(expr)
#define __in_ecount(size)
#define __out_ecount(size)

#define XM_CONST constexpr
#define XM_CONSTEXPR constexpr

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
typedef long HRESULT;
#endif // !_HRESULT_DEFINED

//HRESULT Codes
#define E_OUTOFMEMORY                    ((HRESULT)0x8007000EL)
#define S_OK                             ((HRESULT)0L)
#define E_FAIL                           ((HRESULT)0x80004005L)
#define E_INVALIDARG                     ((HRESULT)0x80070057L)
#define E_UNEXPECTED                     ((HRESULT)0x8000FFFFL)
#define E_ABORT                          ((HRESULT)0x80004004L)

#define FAILED(hr) (((HRESULT)(hr)) < 0)

#define WINAPI __attribute__((stdcall))
#define STDMETHOD(method) virtual __attribute__((nothrow,stdcall)) HRESULT method
#define STDMETHODIMP HRESULT __attribute__((stdcall))
#define PURE = 0
#define UNREFERENCED_PARAMETER(P) (P)


typedef unsigned long DWORD;
typedef const char* LPCSTR;
typedef void* HANDLE;

//DirectXMath Port

#define XM_CALLCONV __attribute__((fastcall))

namespace DirectX
{

XM_CONST float XM_PI = 3.141592654f;

struct __vector4
{
	union
	{
		float vector4_f32[4];
		uint32_t vector4_u32[4];
	};
};
//------------------------------------------------------------------------------
// Vector intrinsic: Four 32 bit floating point components aligned on a 16 byte
// boundary and mapped to hardware vector registers
typedef __vector4 XMVECTOR;
typedef const XMVECTOR& FXMVECTOR;

//------------------------------------------------------------------------------
// Conversion types for constants
__attribute__((align(16))) struct XMVECTORF32
{
    union
    {
        float f[4];
        XMVECTOR v;
    };

    inline operator XMVECTOR() const { return v; }
    inline operator const float*() const { return f; }
};

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

//------------------------------------------------------------------------------
// Initialize a vector with four floating point values
inline XMVECTOR XM_CALLCONV XMVectorSet
(
    float x, 
    float y, 
    float z, 
    float w
)
{
    XMVECTORF32 vResult = { { { x, y, z, w } } };
    return vResult.v;
}

//------------------------------------------------------------------------------
// Initialize a vector with a replicated floating point value
inline XMVECTOR XM_CALLCONV XMVectorReplicate
(
    float Value
)
{
    XMVECTORF32 vResult;
    vResult.f[0] = 
    vResult.f[1] = 
    vResult.f[2] = 
    vResult.f[3] = Value;
    return vResult.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMLoadFloat2
(
    const XMFLOAT2* pSource
)
{
    assert(pSource);
    XMVECTOR V;
    V.vector4_f32[0] = pSource->x;
    V.vector4_f32[1] = pSource->y;
    V.vector4_f32[2] = 0.f;
    V.vector4_f32[3] = 0.f;
    return V;
}

//------------------------------------------------------------------------------

inline void XM_CALLCONV XMStoreFloat2
(
    XMFLOAT2* pDestination, 
    FXMVECTOR  V
)
{
    assert(pDestination);
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMLoadFloat3
(
    const XMFLOAT3* pSource
)
{
    assert(pSource);
    XMVECTOR V;
    V.vector4_f32[0] = pSource->x;
    V.vector4_f32[1] = pSource->y;
    V.vector4_f32[2] = pSource->z;
    V.vector4_f32[3] = 0.f;
    return V;
}

//------------------------------------------------------------------------------

inline void XM_CALLCONV XMStoreFloat3
(
    XMFLOAT3* pDestination, 
    FXMVECTOR V
)
{
    assert(pDestination);
    pDestination->x = V.vector4_f32[0];
    pDestination->y = V.vector4_f32[1];
    pDestination->z = V.vector4_f32[2];
}

//------------------------------------------------------------------------------
// Return the X component in an FPU register. 
inline float XM_CALLCONV XMVectorGetX(FXMVECTOR V)
{
    return V.vector4_f32[0];
}

// Sets the Y component of a vector to a passed floating point value
inline XMVECTOR XM_CALLCONV XMVectorSetY(FXMVECTOR V, float y)
{
    XMVECTORF32 U = { { {
            V.vector4_f32[0],
            y,
            V.vector4_f32[2],
            V.vector4_f32[3]
        } } };
    return U.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorNegate
(
    FXMVECTOR V
)
{
    XMVECTORF32 Result = { { {
            -V.vector4_f32[0],
            -V.vector4_f32[1],
            -V.vector4_f32[2],
            -V.vector4_f32[3]
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorAdd
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
            V1.vector4_f32[0] + V2.vector4_f32[0],
            V1.vector4_f32[1] + V2.vector4_f32[1],
            V1.vector4_f32[2] + V2.vector4_f32[2],
            V1.vector4_f32[3] + V2.vector4_f32[3]
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorSubtract
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
            V1.vector4_f32[0] - V2.vector4_f32[0],
            V1.vector4_f32[1] - V2.vector4_f32[1],
            V1.vector4_f32[2] - V2.vector4_f32[2],
            V1.vector4_f32[3] - V2.vector4_f32[3]
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMultiply
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
            V1.vector4_f32[0] * V2.vector4_f32[0],
            V1.vector4_f32[1] * V2.vector4_f32[1],
            V1.vector4_f32[2] * V2.vector4_f32[2],
            V1.vector4_f32[3] * V2.vector4_f32[3]
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorDivide
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    XMVECTORF32 Result = { { {
            V1.vector4_f32[0] / V2.vector4_f32[0],
            V1.vector4_f32[1] / V2.vector4_f32[1],
            V1.vector4_f32[2] / V2.vector4_f32[2],
            V1.vector4_f32[3] / V2.vector4_f32[3]
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorScale
(
    FXMVECTOR V, 
    float    ScaleFactor
)
{
    XMVECTORF32 Result = { { {
            V.vector4_f32[0] * ScaleFactor,
            V.vector4_f32[1] * ScaleFactor,
            V.vector4_f32[2] * ScaleFactor,
            V.vector4_f32[3] * ScaleFactor
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorSqrt
(
    FXMVECTOR V
)
{
    XMVECTORF32 Result = { { {
            sqrtf(V.vector4_f32[0]),
            sqrtf(V.vector4_f32[1]),
            sqrtf(V.vector4_f32[2]),
            sqrtf(V.vector4_f32[3])
        } } };
    return Result.v;
}

//------------------------------------------------------------------------------

inline bool XM_CALLCONV XMVector3Equal
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    return (((V1.vector4_f32[0] == V2.vector4_f32[0]) && (V1.vector4_f32[1] == V2.vector4_f32[1]) && (V1.vector4_f32[2] == V2.vector4_f32[2])) != 0);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Dot
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    float fValue = V1.vector4_f32[0] * V2.vector4_f32[0] + V1.vector4_f32[1] * V2.vector4_f32[1] + V1.vector4_f32[2] * V2.vector4_f32[2];
    XMVECTORF32 vResult;
    vResult.f[0] = 
    vResult.f[1] = 
    vResult.f[2] = 
    vResult.f[3] = fValue;
    return vResult.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2Dot
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    XMVECTORF32 Result;
    Result.f[0] =
    Result.f[1] =
    Result.f[2] =
    Result.f[3] = V1.vector4_f32[0] * V2.vector4_f32[0] + V1.vector4_f32[1] * V2.vector4_f32[1];
    return Result.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Cross
(
    FXMVECTOR V1, 
    FXMVECTOR V2
)
{
    // [ V1.y*V2.z - V1.z*V2.y, V1.z*V2.x - V1.x*V2.z, V1.x*V2.y - V1.y*V2.x ]

    XMVECTORF32 vResult = { { {
            (V1.vector4_f32[1] * V2.vector4_f32[2]) - (V1.vector4_f32[2] * V2.vector4_f32[1]),
            (V1.vector4_f32[2] * V2.vector4_f32[0]) - (V1.vector4_f32[0] * V2.vector4_f32[2]),
            (V1.vector4_f32[0] * V2.vector4_f32[1]) - (V1.vector4_f32[1] * V2.vector4_f32[0]),
            0.0f
        } } };
    return vResult.v;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2LengthSq
(
    FXMVECTOR V
)
{
    return XMVector2Dot(V, V);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2Length
(
    FXMVECTOR V
)
{
    XMVECTOR Result;
    Result = XMVector2LengthSq(V);
    Result = XMVectorSqrt(Result);
    return Result;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3LengthSq
(
    FXMVECTOR V
)
{
    return XMVector3Dot(V, V);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Length
(
    FXMVECTOR V
)
{
    XMVECTOR Result;

    Result = XMVector3LengthSq(V);
    Result = XMVectorSqrt(Result);

    return Result;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Normalize
(
    FXMVECTOR V
)
{
    float fLength;
    XMVECTOR vResult;

    vResult = XMVector3Length( V );
    fLength = vResult.vector4_f32[0];

    // Prevent divide by zero
    if (fLength > 0) {
        fLength = 1.0f/fLength;
    }
    
    vResult.vector4_f32[0] = V.vector4_f32[0]*fLength;
    vResult.vector4_f32[1] = V.vector4_f32[1]*fLength;
    vResult.vector4_f32[2] = V.vector4_f32[2]*fLength;
    vResult.vector4_f32[3] = V.vector4_f32[3]*fLength;
    return vResult;
}

/****************************************************************************
 *
 * XMVECTOR operators
 *
 ****************************************************************************/

#ifndef _XM_NO_XMVECTOR_OVERLOADS_

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator+ (FXMVECTOR V)
{
    return V;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator- (FXMVECTOR V)
{
    return XMVectorNegate(V);
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator+=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorAdd(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator-=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorSubtract(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator*=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorMultiply(V1, V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& XM_CALLCONV operator/=
(
    XMVECTOR&       V1,
    FXMVECTOR       V2
)
{
    V1 = XMVectorDivide(V1,V2);
    return V1;
}

//------------------------------------------------------------------------------

inline XMVECTOR& operator*=
(
    XMVECTOR&   V,
    const float S
)
{
    V = XMVectorScale(V, S);
    return V;
}

//------------------------------------------------------------------------------

inline XMVECTOR& operator/=
(
    XMVECTOR&   V,
    const float S
)
{
    XMVECTOR vS = XMVectorReplicate( S );
    V = XMVectorDivide(V, vS);
    return V;
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator+
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorAdd(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator-
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorSubtract(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator*
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorMultiply(V1, V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator/
(
    FXMVECTOR V1,
    FXMVECTOR V2
)
{
    return XMVectorDivide(V1,V2);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator*
(
    FXMVECTOR      V,
    const float    S
)
{
    return XMVectorScale(V, S);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator/
(
    FXMVECTOR      V,
    const float    S
)
{
    XMVECTOR vS = XMVectorReplicate( S );
    return XMVectorDivide(V, vS);
}

//------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV operator*
(
    float           S,
    FXMVECTOR  	    V
)
{
    return XMVectorScale(V, S);
}

#endif /* !_XM_NO_XMVECTOR_OVERLOADS_ */

} /* namespace DirectX */


#endif //__LINUX__
