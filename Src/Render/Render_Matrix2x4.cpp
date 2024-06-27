/**************************************************************************

Filename    :   Render_Matrix2x4.cpp
Content     :   SIMD optimized matrix operations.
Created     :   Dec 2010
Authors     :   Bart Muzzin

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render/Render_Matrix2x4.h"
#include "Render/Render_Types2D.h"
#include "Kernel/SF_SIMD.h"

namespace Scaleform { namespace Render {

#ifdef SF_ENABLE_SIMD

template<>
void Matrix2F::EncloseTransform(RectF *pr, const RectF& r) const
{
    using namespace Scaleform::SIMD;

    Vector4f rect   = IS::LoadAligned(&r.x1);    
    Vector4f m0     = IS::LoadAligned(M[0]);
    Vector4f m1     = IS::LoadAligned(M[1]);

    Vector4f y1y1x1x1 = IS::UnpackLo(rect, rect);
    Vector4f y2y2x2x2 = IS::UnpackHi(rect, rect);    
    Vector4f add_yyxx = IS::Shuffle<3, 3, 3, 3>(m0, m1);

    Vector4f m11_01_10_00 = IS::UnpackLo(m0, m1);

    Vector4f m11y1_m01y1_m10x1_m00x1 = IS::Multiply(y1y1x1x1, m11_01_10_00);
    Vector4f m11y2_m01y2_m10x2_m00x2 = IS::Multiply(y2y2x2x2, m11_01_10_00);

    Vector4f m10x2_m10x1_m00x2_m00x1 = IS::UnpackLo(m11y1_m01y1_m10x1_m00x1, m11y2_m01y2_m10x2_m00x2);
    Vector4f m11y2_m11y1_m01y2_m01y1 = IS::UnpackHi(m11y1_m01y1_m10x1_m00x1, m11y2_m01y2_m10x2_m00x2);
    Vector4f m10x1_m10x2_m00x1_m00x2 = IS::Shuffle<1,0,3,2>(m10x2_m10x1_m00x2_m00x1, m10x2_m10x1_m00x2_m00x1);

    Vector4f yAyBxAxB = IS::Add(m10x2_m10x1_m00x2_m00x1, m11y2_m11y1_m01y2_m01y1);
    Vector4f yCyDxCxD = IS::Add(m10x1_m10x2_m00x1_m00x2, m11y2_m11y1_m01y2_m01y1);

    Vector4f min0_yyxx = IS::Min(yAyBxAxB, yCyDxCxD);
    Vector4f max0_yyxx = IS::Max(yAyBxAxB, yCyDxCxD);

    Vector4f min_yyxx = IS::Min(min0_yyxx, IS::Shuffle<1,0,3,2>(min0_yyxx, min0_yyxx));
    Vector4f max_yyxx = IS::Max(max0_yyxx, IS::Shuffle<1,0,3,2>(max0_yyxx, max0_yyxx));

    Vector4f yxyx       = IS::Shuffle<0,2,0,2>(min_yyxx, max_yyxx);
    Vector4f add_yxyx   = IS::Shuffle<0,2,0,2>(add_yyxx, add_yyxx);
    Vector4f result     = IS::Add(yxyx, add_yxyx);

    IS::StoreAligned(&pr->x1, result);
}

template<>
void Matrix2F::SetToAppend( const Matrix2F& m0, const Matrix2F& m1 )
{
    using namespace Scaleform::SIMD;
    
    Vector4f c0001 = IS::Constant<0,0,0,0xFFFFFFFF>();
    Vector4f c1101 = IS::Constant<0xFFFFFFFF,0xFFFFFFFF,0,0xFFFFFFFF>();
    Vector4f m1v0  = IS::LoadAligned(m1.M[0]);
    Vector4f m1v1  = IS::LoadAligned(m1.M[1]);
    Vector4f m0v0  = IS::LoadAligned(m0.M[0]);
    Vector4f m0v1  = IS::LoadAligned(m0.M[1]);

    Vector4f res_v0 = IS::And( m1v0, c0001 );
    Vector4f res_v1 = IS::And( m1v1, c0001 );

    Vector4f t0 = IS::Multiply( m0v0, IS::Shuffle<0,0,0,0>(m1v0, m1v0));
    Vector4f t1 = IS::Multiply( m0v0, IS::Shuffle<0,0,0,0>(m1v1, m1v1));

    Vector4f t2 = IS::MultiplyAdd( m0v1, IS::Shuffle<1,1,1,1>(m1v0, m1v0), t0);
    Vector4f t3 = IS::MultiplyAdd( m0v1, IS::Shuffle<1,1,1,1>(m1v1, m1v1), t1);

    IS::StoreAligned(&M[0][0], IS::And( IS::Add(res_v0, t2), c1101) );
    IS::StoreAligned(&M[1][0], IS::And( IS::Add(res_v1, t3), c1101) );
}

template<> void Matrix2F::SetToAppend( const Matrix2F & m0, const Matrix2F & m1, const Matrix2F & m2 )
{
    using namespace SIMD;

    Vector4f c0001 = IS::Constant<0,0,0,0xFFFFFFFF>();
    Vector4f c1101 = IS::Constant<0xFFFFFFFF,0xFFFFFFFF,0,0xFFFFFFFF>();
    Vector4f m0v0  = IS::LoadAligned(m0.M[0]);
    Vector4f m0v1  = IS::LoadAligned(m0.M[1]);
    Vector4f m1v0  = IS::LoadAligned(m1.M[0]);
    Vector4f m1v1  = IS::LoadAligned(m1.M[1]);
    Vector4f m2v0  = IS::LoadAligned(m2.M[0]);
    Vector4f m2v1  = IS::LoadAligned(m2.M[1]);

    Vector4f res_v0 = IS::And( m2v0, c0001 );
    Vector4f res_v1 = IS::And( m2v1, c0001 );

    // First Prepend multiply: m1 * m2.
    Vector4f t0 = IS::Multiply( m1v0, IS::Shuffle<0,0,0,0>(m2v0, m2v0));
    Vector4f t1 = IS::Multiply( m1v0, IS::Shuffle<0,0,0,0>(m2v1, m2v1));

    Vector4f t2 = IS::MultiplyAdd( m1v1, IS::Shuffle<1,1,1,1>(m2v0, m2v0), t0);
    Vector4f t3 = IS::MultiplyAdd( m1v1, IS::Shuffle<1,1,1,1>(m2v1, m2v1), t1);

    Vector4f m12v0 = IS::Add(res_v0, t2);
    Vector4f m12v1 = IS::Add(res_v1, t3);

    // Second append multiply.
    res_v0 = IS::And( m12v0, c0001 );
    res_v1 = IS::And( m12v1, c0001 );

    t0 = IS::Multiply( m0v0, IS::Shuffle<0,0,0,0>(m12v0, m12v0));
    t1 = IS::Multiply( m0v0, IS::Shuffle<0,0,0,0>(m12v1, m12v1));

    t2 = IS::MultiplyAdd( m0v1, IS::Shuffle<1,1,1,1>(m12v0, m12v0), t0);
    t3 = IS::MultiplyAdd( m0v1, IS::Shuffle<1,1,1,1>(m12v1, m12v1), t1);

    IS::StoreAligned(&M[0][0], IS::And( IS::Add(res_v0, t2), c1101) );
    IS::StoreAligned(&M[1][0], IS::And( IS::Add(res_v1, t3), c1101) );
}

template<> 
Matrix2F& Matrix2F::Append( const Matrix2F & m )
{
    using namespace Scaleform::SIMD;

    Vector4f c0001 = IS::Constant<0,0,0,0xFFFFFFFF>();
    Vector4f c1101 = IS::Constant<0xFFFFFFFF,0xFFFFFFFF,0,0xFFFFFFFF>();
    Vector4f m1v0  = IS::LoadAligned(m.M[0]);
    Vector4f m1v1  = IS::LoadAligned(m.M[1]);
    Vector4f m0v0  = IS::LoadAligned(M[0]);
    Vector4f m0v1  = IS::LoadAligned(M[1]);

    Vector4f res_v0 = IS::And( m1v0, c0001 );
    Vector4f res_v1 = IS::And( m1v1, c0001 );

    Vector4f t0 = IS::Multiply( m0v0, IS::Shuffle<0,0,0,0>(m1v0, m1v0));
    Vector4f t1 = IS::Multiply( m0v0, IS::Shuffle<0,0,0,0>(m1v1, m1v1));

    Vector4f t2 = IS::MultiplyAdd( m0v1, IS::Shuffle<1,1,1,1>(m1v0, m1v0), t0);
    Vector4f t3 = IS::MultiplyAdd( m0v1, IS::Shuffle<1,1,1,1>(m1v1, m1v1), t1);

    IS::StoreAligned(&M[0][0], IS::And( IS::Add(res_v0, t2), c1101) );
    IS::StoreAligned(&M[1][0], IS::And( IS::Add(res_v1, t3), c1101) );
    return *this;
}

#endif // SF_ENABLE_SIMD

}}
