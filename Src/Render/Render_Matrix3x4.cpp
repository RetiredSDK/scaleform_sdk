/**************************************************************************

Filename    :   Render_Matrix3x4.cpp
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
template<> void Matrix3F::MultiplyMatrix(const Matrix3F &m1, const Matrix3F &m2)
{
    using namespace SIMD;

    Vector4f m10 = IS::LoadAligned(m1.M[0]);
    Vector4f m11 = IS::LoadAligned(m1.M[1]);
    Vector4f m12 = IS::LoadAligned(m1.M[2]);

    Vector4f m20 = IS::LoadAligned(m2.M[0]);
    Vector4f m21 = IS::LoadAligned(m2.M[1]);
    Vector4f m22 = IS::LoadAligned(m2.M[2]);

    Vector4f r0 = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1 = IS::Multiply   ( IS::Splat<0>(m11), m20 );
    Vector4f r2 = IS::Multiply   ( IS::Splat<0>(m12), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<1>(m12), m21, r2 );

    r0 =          IS::MultiplyAdd( IS::Splat<2>(m10), m22, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<2>(m11), m22, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<2>(m12), m22, r2 );

    Vector4f addMask = IS::Constant<0,0,0,0xFFFFFFFF>();
    r0 =          IS::Add( r0, IS::And( m10, addMask ) );
    r1 =          IS::Add( r1, IS::And( m11, addMask ) );
    r2 =          IS::Add( r2, IS::And( m12, addMask ) );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], r2);
}

template<> void Matrix3F::MultiplyMatrix(const Matrix3F&m1, const Matrix2F &m2)
{
    using namespace SIMD;

    Vector4f m10 = IS::LoadAligned(m1.M[0]);
    Vector4f m11 = IS::LoadAligned(m1.M[1]);
    Vector4f m12 = IS::LoadAligned(m1.M[2]);

    Vector4f m20 = IS::LoadAligned(m2.M[0]);
    Vector4f m21 = IS::LoadAligned(m2.M[1]);

    Vector4f r0 = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1 = IS::Multiply   ( IS::Splat<0>(m11), m20 );
    Vector4f r2 = IS::Multiply   ( IS::Splat<0>(m12), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );
    r2 =          IS::MultiplyAdd( IS::Splat<1>(m12), m21, r2 );

    Vector4f addMask = IS::Constant<0,0,0xFFFFFFFF,0xFFFFFFFF>();
    r0 =          IS::Add( r0, IS::And( m10, addMask ) );
    r1 =          IS::Add( r1, IS::And( m11, addMask ) );
    r2 =          IS::Add( r2, IS::And( m12, addMask ) );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], r2);
}

template<> void Matrix3F::MultiplyMatrix(const Matrix2F&m1, const Matrix3F &m2)
{
    using namespace SIMD;

    Vector4f m10 = IS::LoadAligned(m1.M[0]);
    Vector4f m11 = IS::LoadAligned(m1.M[1]);

    Vector4f m20 = IS::LoadAligned(m2.M[0]);
    Vector4f m21 = IS::LoadAligned(m2.M[1]);
    Vector4f m22 = IS::LoadAligned(m2.M[2]);

    Vector4f r0 = IS::Multiply   ( IS::Splat<0>(m10), m20 );
    Vector4f r1 = IS::Multiply   ( IS::Splat<0>(m11), m20 );

    r0 =          IS::MultiplyAdd( IS::Splat<1>(m10), m21, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<1>(m11), m21, r1 );

    r0 =          IS::MultiplyAdd( IS::Splat<2>(m10), m22, r0 );
    r1 =          IS::MultiplyAdd( IS::Splat<2>(m11), m22, r1 );

    Vector4f addMask = IS::Constant<0,0,0,0xFFFFFFFF>();
    r0 =          IS::Add( r0, IS::And( m10, addMask ) );
    r1 =          IS::Add( r1, IS::And( m11, addMask ) );

    IS::StoreAligned(M[0], r0);
    IS::StoreAligned(M[1], r1);
    IS::StoreAligned(M[2], m22);
}

#endif // SF_ENABLE_SIMD

}} // Scaleform::Render
