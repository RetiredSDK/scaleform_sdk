/**************************************************************************

Filename    :   Render_Matrix4x4.cpp
Content     :   
Created     :   Jan 2011
Authors     :   Bart Muzzin

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render/Render_Matrix4x4.h"
#include "Kernel/SF_SIMD.h"

namespace Scaleform { namespace Render {

#ifdef SF_ENABLE_SIMD

template<> void Matrix4F::MultiplyMatrix(const Matrix4F &m1, const Matrix4F &m2)
{
    using namespace SIMD;

    Vector4f m10 = IS::LoadAligned(m1.M[0]);
    Vector4f m11 = IS::LoadAligned(m1.M[1]);
    Vector4f m12 = IS::LoadAligned(m1.M[2]);
    Vector4f m13 = IS::LoadAligned(m1.M[3]);

    Vector4f m20 = IS::LoadAligned(m2.M[0]);
    Vector4f m21 = IS::LoadAligned(m2.M[1]);
    Vector4f m22 = IS::LoadAligned(m2.M[2]);
    Vector4f m23 = IS::LoadAligned(m2.M[3]);

    Vector4f r0 = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1 = IS::Multiply   ( IS::Splat<0>(m11), m20 );
    Vector4f r2 = IS::Multiply   ( IS::Splat<0>(m12), m20 );
    Vector4f r3 = IS::Multiply   ( IS::Splat<0>(m13), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<1>(m12), m21, r2 );
    r3 =          IS::MultiplyAdd( IS::Splat<1>(m13), m21, r3 );

    r0 =          IS::MultiplyAdd( IS::Splat<2>(m10), m22, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<2>(m11), m22, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<2>(m12), m22, r2 );
    r3 =          IS::MultiplyAdd( IS::Splat<2>(m13), m22, r3 );

    r0 =          IS::MultiplyAdd( IS::Splat<3>(m10), m23, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<3>(m11), m23, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<3>(m12), m23, r2 );
    r3 =          IS::MultiplyAdd( IS::Splat<3>(m13), m23, r3 );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], r2);
    IS::StoreAligned(M[3], r3);
}

//specialize for 3x4 * 4x4
template<> void Matrix4F::MultiplyMatrix(const Matrix3F &m1, const Matrix4F &m2)
{
    using namespace SIMD;

    Vector4f m10 = IS::LoadAligned(m1.M[0]);
    Vector4f m11 = IS::LoadAligned(m1.M[1]);
    Vector4f m12 = IS::LoadAligned(m1.M[2]);

    Vector4f m20 = IS::LoadAligned(m2.M[0]);
    Vector4f m21 = IS::LoadAligned(m2.M[1]);
    Vector4f m22 = IS::LoadAligned(m2.M[2]);
    Vector4f m23 = IS::LoadAligned(m2.M[3]);

    Vector4f r0 = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1 = IS::Multiply   ( IS::Splat<0>(m11), m20 );
    Vector4f r2 = IS::Multiply   ( IS::Splat<0>(m12), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<1>(m12), m21, r2 );

    r0 =          IS::MultiplyAdd( IS::Splat<2>(m10), m22, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<2>(m11), m22, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<2>(m12), m22, r2 );

    r0 =          IS::MultiplyAdd( IS::Splat<3>(m10), m23, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<3>(m11), m23, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<3>(m12), m23, r2 );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], r2);
    IS::StoreAligned(M[3], m23);
}

// specialize for 4x4 * 3x4
template<> void Matrix4F::MultiplyMatrix(const Matrix4F &m1, const Matrix3F &m2)
{
    using namespace SIMD;

    Vector4f c0001 = IS::Constant<0,0,0,0xFFFFFFFF>();

    Vector4f m10   = IS::LoadAligned(m1.M[0]);
    Vector4f m11   = IS::LoadAligned(m1.M[1]);
    Vector4f m12   = IS::LoadAligned(m1.M[2]);
    Vector4f m13   = IS::LoadAligned(m1.M[3]);

    Vector4f m20   = IS::LoadAligned(m2.M[0]);
    Vector4f m21   = IS::LoadAligned(m2.M[1]);
    Vector4f m22   = IS::LoadAligned(m2.M[2]);

    Vector4f r0    = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1    = IS::Multiply   ( IS::Splat<0>(m11), m20 );
    Vector4f r2    = IS::Multiply   ( IS::Splat<0>(m12), m20 );
    Vector4f r3    = IS::Multiply   ( IS::Splat<0>(m13), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<1>(m12), m21, r2 );
    r3 =          IS::MultiplyAdd( IS::Splat<1>(m13), m21, r3 );

    r0 =          IS::MultiplyAdd( IS::Splat<2>(m10), m22, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<2>(m11), m22, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<2>(m12), m22, r2 );
    r3 =          IS::MultiplyAdd( IS::Splat<2>(m13), m22, r3 );

    r0 =          IS::Add( r0, IS::And( m10, c0001 ) );
    r1 =          IS::Add( r1, IS::And( m11, c0001 ) );
    r2 =          IS::Add( r2, IS::And( m12, c0001 ) );
    r3 =          IS::Add( r3, IS::And( m13, c0001 ) );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], r2);
    IS::StoreAligned(M[3], r3);
}

//specialize for 2x4 * 4x4
template<> void Matrix4F::MultiplyMatrix(const Matrix2F &m1, const Matrix4F &m2)
{
    using namespace SIMD;

    Vector4f m10 = IS::LoadAligned(m1.M[0]);
    Vector4f m11 = IS::LoadAligned(m1.M[1]);

    Vector4f m20 = IS::LoadAligned(m2.M[0]);
    Vector4f m21 = IS::LoadAligned(m2.M[1]);
    Vector4f m22 = IS::LoadAligned(m2.M[2]);
    Vector4f m23 = IS::LoadAligned(m2.M[3]);

    Vector4f r0 = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1 = IS::Multiply   ( IS::Splat<0>(m11), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );

    r0 =          IS::MultiplyAdd( IS::Splat<2>(m10), m22, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<2>(m11), m22, r1 );

    r0 =          IS::MultiplyAdd( IS::Splat<3>(m10), m23, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<3>(m11), m23, r1 );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], m22);
    IS::StoreAligned(M[3], m23);
}

// specialize for 4x4 * 2x4
template<> void Matrix4F::MultiplyMatrix(const Matrix4F &m1, const Matrix2F &m2)
{
    using namespace SIMD;

    Vector4f c0011 = IS::Constant<0,0,0xFFFFFFFF,0xFFFFFFFF>();

    Vector4f m10   = IS::LoadAligned(m1.M[0]);
    Vector4f m11   = IS::LoadAligned(m1.M[1]);
    Vector4f m12   = IS::LoadAligned(m1.M[2]);
    Vector4f m13   = IS::LoadAligned(m1.M[3]);

    Vector4f m20   = IS::LoadAligned(m2.M[0]);
    Vector4f m21   = IS::LoadAligned(m2.M[1]);

    Vector4f r0    = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1    = IS::Multiply   ( IS::Splat<0>(m11), m20 );
    Vector4f r2    = IS::Multiply   ( IS::Splat<0>(m12), m20 );
    Vector4f r3    = IS::Multiply   ( IS::Splat<0>(m13), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<1>(m12), m21, r2 );
    r3 =          IS::MultiplyAdd( IS::Splat<1>(m13), m21, r3 );

    r0 =          IS::Add( r0, IS::And( m10, c0011 ) );
    r1 =          IS::Add( r1, IS::And( m11, c0011 ) );
    r2 =          IS::Add( r2, IS::And( m12, c0011 ) );
    r3 =          IS::Add( r3, IS::And( m13, c0011 ) );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], r2);
    IS::StoreAligned(M[3], r3);
}

template<> void Matrix4F::EncloseTransformHomogeneous(RectF *pr, const RectF& r) const
{
    using namespace SIMD;

    Vector4f c0000 = IS::Constant<0,0,0,0>();

    Vector4f r0 = IS::LoadAligned(&r.x1);
    Vector4f m0 = IS::LoadAligned(M[0]);
    Vector4f m1 = IS::LoadAligned(M[1]);
    Vector4f m2 = IS::LoadAligned(M[2]);
    Vector4f m3 = IS::LoadAligned(M[3]);

    Vector4f t0  = IS::Shuffle<3,3,3,3>( m0, m1);
    Vector4f t1  = IS::Shuffle<3,3,3,3>( m2, m3);
    Vector4f mc3 = IS::Shuffle<0,2,0,2>( t0, t1 );

    // Make the corners of the rectangle.
    Vector4f tl = IS::Shuffle<0, 1, 0, 0>(r0, c0000);
    Vector4f tr = IS::Shuffle<2, 1, 0, 0>(r0, c0000);
    Vector4f br = IS::Shuffle<2, 3, 0, 0>(r0, c0000);
    Vector4f bl = IS::Shuffle<0, 3, 0, 0>(r0, c0000);

    Vector4f x,y,z,w;
    Vector4f p0,p1,p2,p3;

    // Transform each corner by the matrix, divide the result by W.
    x = IS::Dot3( tl, m0 );
    y = IS::Dot3( tl, m1 );
    z = IS::Dot3( tl, m2 );
    w = IS::Dot3( tl, m3 );
    w = IS::Add( w, IS::Splat<3>(mc3));
    p0 = IS::UnpackLo( x, y );
    p0 = IS::Shuffle<0,1,0,0>( p0, z);
    p0 = IS::Add(p0, mc3);
    p0 = IS::Divide( p0, w );

    x = IS::Dot3( tr, m0 );
    y = IS::Dot3( tr, m1 );
    z = IS::Dot3( tr, m2 );
    w = IS::Dot3( tr, m3 );
    w = IS::Add( w, IS::Splat<3>(mc3));
    p1 = IS::UnpackLo( x, y );
    p1 = IS::Shuffle<0,1,0,0>( p1, z);
    p1 = IS::Add(p1, mc3);
    p1 = IS::Divide( p1, w );

    x = IS::Dot3( br, m0 );
    y = IS::Dot3( br, m1 );
    z = IS::Dot3( br, m2 );
    w = IS::Dot3( br, m3 );
    w = IS::Add( w, IS::Splat<3>(mc3));
    p2 = IS::UnpackLo( x, y );
    p2 = IS::Shuffle<0,1,0,0>( p2, z);
    p2 = IS::Add(p2, mc3);
    p2 = IS::Divide( p2, w );

    x = IS::Dot3( bl, m0 );
    y = IS::Dot3( bl, m1 );
    z = IS::Dot3( bl, m2 );
    w = IS::Dot3( bl, m3 );
    w = IS::Add( w, IS::Splat<3>(mc3));
    p3 = IS::UnpackLo( x, y );
    p3 = IS::Shuffle<0,1,0,0>( p3, z);
    p3 = IS::Add(p3, mc3);
    p3 = IS::Divide( p3, w );

    // Find the maxima and minima of the bounds.
    Vector4f min, max;
    min = IS::Min(p0, p1);
    min = IS::Min(min, p2);
    min = IS::Min(min, p3);
    max = IS::Max(p0, p1);
    max = IS::Max(max, p2);
    max = IS::Max(max, p3);

    Vector4f result;
    result = IS::Shuffle<0,1,0,1>(min,max);
    IS::StoreAligned( (float*)pr, result );
}

template<> void Matrix4F::TransformHomogeneousAndScaleCorners(const RectF& bounds, float sx, float sy, float* dest) const
{
    using namespace SIMD;

    SF_SIMD_ALIGN(float sxsy_scalar[4]);
    sxsy_scalar[0] = sx;
    sxsy_scalar[1] = sy;
    Vector4f sxsy = IS::LoadAligned(sxsy_scalar);
    sxsy = IS::Shuffle<0,1,0,1>(sxsy, sxsy);

    // Assume IEEE754.
    Vector4f c0000 = IS::Constant<0,0,0,0>();
    Vector4f c1N1N = IS::Constant<0x3F800000,0xBF800000,0x3F800000,0xBF800000>();
    Vector4f c1111 = IS::Constant<0x3F800000,0x3F800000,0x3F800000,0x3F800000>();
    Vector4f cHALF = IS::Constant<0x3F000000,0x3F000000,0x3F000000,0x3F000000>();

    Vector4f r0 = IS::LoadAligned(&bounds.x1);
    Vector4f m0 = IS::LoadAligned(M[0]);
    Vector4f m1 = IS::LoadAligned(M[1]);
    Vector4f m2 = IS::LoadAligned(M[2]);
    Vector4f m3 = IS::LoadAligned(M[3]);

    Vector4f t0  = IS::Shuffle<3,3,3,3>( m0, m1);
    Vector4f t1  = IS::Shuffle<3,3,3,3>( m2, m3);
    Vector4f mc3 = IS::Shuffle<0,2,0,2>( t0, t1 );

    // Make three corners of the rectangle.
    Vector4f tl = IS::Shuffle<0, 1, 0, 0>(r0, c0000);
    Vector4f tr = IS::Shuffle<2, 1, 0, 0>(r0, c0000);
    Vector4f br = IS::Shuffle<2, 3, 0, 0>(r0, c0000);

    Vector4f x,y,z,w;
    Vector4f p0,p1,p2;

    Vector4f mc3_4 = IS::Splat<3>(mc3);
    // Transform each corner by the matrix, divide the result by W.
    x = IS::Dot3( tl, m0 );
    y = IS::Dot3( tl, m1 );
    z = IS::Dot3( tl, m2 );
    w = IS::Dot3( tl, m3 );
    w = IS::Add( w, mc3_4 );
    p0 = IS::UnpackLo( x, y );
    p0 = IS::Shuffle<0,1,0,0>( p0, z);
    p0 = IS::Add(p0, mc3);
    p0 = IS::Divide( p0, w );

    x = IS::Dot3( tr, m0 );
    y = IS::Dot3( tr, m1 );
    z = IS::Dot3( tr, m2 );
    w = IS::Dot3( tr, m3 );
    w = IS::Add( w, mc3_4);
    p1 = IS::UnpackLo( x, y );
    p1 = IS::Shuffle<0,1,0,0>( p1, z);
    p1 = IS::Add(p1, mc3);
    p1 = IS::Divide( p1, w );

    x = IS::Dot3( br, m0 );
    y = IS::Dot3( br, m1 );
    z = IS::Dot3( br, m2 );
    w = IS::Dot3( br, m3 );
    w = IS::Add( w, mc3_4);
    p2 = IS::UnpackLo( x, y );
    p2 = IS::Shuffle<0,1,0,0>( p2, z);
    p2 = IS::Add(p2, mc3);
    p2 = IS::Divide( p2, w );

    Vector4f sxsy_2 = IS::Multiply( sxsy, cHALF);
    Vector4f out0 = IS::Multiply( IS::Add( IS::Multiply(IS::Shuffle<0,1,0,1>(p0,p1), c1N1N), c1111), sxsy_2 );
    Vector4f out1 = IS::Multiply( IS::Add( IS::Multiply(p2, c1N1N), c1111), sxsy_2 );

    IS::StoreAligned(dest, out0);
    IS::StoreAligned(dest+4, out1);
}

#endif // SF_ENABLE_SIMD


}} // Scaleform::Render
