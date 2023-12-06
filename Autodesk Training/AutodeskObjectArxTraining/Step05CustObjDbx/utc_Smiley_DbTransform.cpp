//Impelementation for react and transform utc_smiley
#include "StdAfx.h"
#include "utc_Smiley.h"

#define FACE_CENTER_GRIP_PT 1
#define FACE_RIGHT_GRIP_PT  2
#define FACE_TOP_GRIP_PT	3
#define FACE_LEFT_GRIP_PT	4
#define FACE_BOTTOM_GRIP_PT	5

#define EYE_CENTER_GRIP_PT  1
#define EYE_RIGHT_GRIP_PT   2
#define EYE_TOP_GRIP_PT		3
#define EYE_LEFT_GRIP_PT	4
#define EYE_BOTTOM_GRIP_PT	5

#define MOUTH_LEFT_GRIP_PT		1
#define MOUTH_RIGHT_GRIP_PT		2
#define MOUTH_MID_GRIP_PT		3
#define MOUTH_BOTTOM_GRIP_PT	4

#define LINE_LEFT_GRIP_PT		1
#define LINE_RIGHT_GRIP_PT		2


//
// Step 3
// We are implementing 'transformBy' function to move, to scale and  
// to rotate the smiley object. To stretch and constrict of smiley, 
// we have implemented the 'scaleRadius' function. This function will
// being used in following steps.
//
Acad::ErrorStatus utc_Smiley::subTransformBy(const AcGeMatrix3d& xform)
{
    assertWriteEnabled();

    // Transform the center point and get the translation vector
    AcGePoint3d oldCenter(center()),
        newCenter(center());
    newCenter.transformBy(xform);
    AcGeVector3d transVec = newCenter - center();

    // Get the equivalent transformation
    AcGeMatrix3d newXform;
    newXform.setToTranslation(transVec);

    // Only translate the face and mouth - do not transform!
    m_facecircle.transformBy(newXform);
    m_moutharc.transformBy(newXform);

    // Get the point at a quadrant, transform it..
    AcGePoint3d oldXquad = center() + AcGeVector3d(radius(), 0, 0),
        newXquad(oldXquad);
    newXquad.transformBy(xform);

    // ... then scale the Smiley accordingly
    if (false == xform.isEqualTo(AcGeMatrix3d::kIdentity))
        scaleRadius(radius() * newCenter.distanceTo(newXquad) / oldCenter.distanceTo(oldXquad));

    xDataTransformBy(xform);

    return eOk;
}

void utc_Smiley::scaleRadius(const double r)     // stretch and constrict of smiley
{
    assertWriteEnabled();
    AcGePoint3d cen(center());
    double rad = radius(),
        factor = r / rad;
    setEyesApart(factor * eyesApart());
    setEyesHeight(factor * eyesHeight());
    setEyeSize(factor * eyeSize());
    setMouth(mouthLeft().scaleBy(factor, cen),
        mouthBottom().scaleBy(factor, cen),
        mouthRight().scaleBy(factor, cen));
    setRadius(r);
    recordGraphicsModified();
}


//
// Step 4
// We are implementing 'getGripPoints' function to create the array of 
// grip points for smiley object and are implementing 'moveGripPointsAt' 
// function to stretch and to move the face, the mouth and eyes of 
// smiley object using a grip points. To control the size of smiley at 
// changes of its elements, we have implemented the 'ensureRadius' functions.
//
Acad::ErrorStatus utc_Smiley::subGetGripPoints(AcGePoint3dArray& gripPoints) const
{
    assertReadEnabled();
    //indices
    // Grip points to face
    AcGePoint3d cen(center());
    AcGeVector3d xoff(radius(), 0, 0),
        yoff(0, radius(), 0);
    gripPoints.append(cen);			// 0
    gripPoints.append(cen + xoff);		// 1
    gripPoints.append(cen + yoff);		// 2
    gripPoints.append(cen - xoff);		// 3
    gripPoints.append(cen - yoff);		// 4
    // Grip points to mouth
    gripPoints.append(mouthLeft());		// 5
    gripPoints.append(mouthRight());		// 6
    gripPoints.append(mouthBottom());		// 7
    gripPoints.append(AcGeLineSeg3d(mouthLeft(), mouthRight()).midPoint());  // 8
    // Grip points to eye
    xoff.x = yoff.y = m_eyesize;
    // Left eye
    cen = leftEyeCenter();
    gripPoints.append(cen);			    // 9
    gripPoints.append(cen + xoff);		// 10
    gripPoints.append(cen + yoff);		// 11
    gripPoints.append(cen - xoff);		// 12
    gripPoints.append(cen - yoff);		// 13
    // Left eye
    cen = rightEyeCenter();
    gripPoints.append(cen);			    // 14
    gripPoints.append(cen + xoff);		// 15
    gripPoints.append(cen + yoff);		// 16
    gripPoints.append(cen - xoff);		// 17
    gripPoints.append(cen - yoff);		// 18

    return eOk;
}


Acad::ErrorStatus utc_Smiley::subGetGripPoints(
    AcDbGripDataPtrArray& grips, const double curViewUnitSize, const int gripSize,
    const AcGeVector3d& curViewDir, const int bitflags
) const {
    assertReadEnabled();

    //indices
    // Grip points to face

    AcGePoint3d cen(center());
    AcGeVector3d xoff(radius(), 0, 0),
        yoff(0, radius(), 0);

    AcDbGripData* gripData_1 = new AcDbGripData();
    gripData_1->setGripPoint(cen);
    grips.append(gripData_1);

    //gripPoints.append(cen);			    // 0
    //gripPoints.append(cen + xoff);		// 1
    //gripPoints.append(cen + yoff);		// 2
    //gripPoints.append(cen - xoff);		// 3
    //gripPoints.append(cen - yoff);		// 4
    //// Grip points to mouth
    //gripPoints.append(mouthLeft());		// 5
    //gripPoints.append(mouthRight());		// 6
    //gripPoints.append(mouthBottom());		// 7
    //gripPoints.append(AcGeLineSeg3d(mouthLeft(), mouthRight()).midPoint());  // 8
    //// Grip points to eye
    //xoff.x = yoff.y = m_eyesize;
    //// Left eye
    //cen = leftEyeCenter();
    //gripPoints.append(cen);			    // 9
    //gripPoints.append(cen + xoff);		// 10
    //gripPoints.append(cen + yoff);		// 11
    //gripPoints.append(cen - xoff);		// 12
    //gripPoints.append(cen - yoff);		// 13
    //// Left eye
    //cen = rightEyeCenter();
    //gripPoints.append(cen);			    // 14
    //gripPoints.append(cen + xoff);		// 15
    //gripPoints.append(cen + yoff);		// 16
    //gripPoints.append(cen - xoff);		// 17
    //gripPoints.append(cen - yoff);		// 18


    return eOk;
}


//
// Step 5
// We are implementing 'getOsnapPoints' function to create the array of 
// snap points for smiley object. Snap points are being used for joining of
// smiley object with other objects at drawing. At testing, appropriate snap
// mode must be ON.
//
Acad::ErrorStatus utc_Smiley::subGetOsnapPoints(AcDb::OsnapMode osnapMode,
    Adesk::GsMarker   /*gsSelectionMark*/,
    const AcGePoint3d& /*pickPoint*/,
    const AcGePoint3d& /*lastPoint*/,
    const AcGeMatrix3d& /*xfm*/,
    const AcGeMatrix3d& /*ucs*/,
    AcGePoint3dArray& snapPoints) const
{
    assertReadEnabled();
    switch (osnapMode)
    {
    case AcDb::kOsModeCen:
        snapPoints.append(center());			// Osnap center to the face's center
        snapPoints.append(leftEyeCenter());
        snapPoints.append(rightEyeCenter());
        return eOk;

    case AcDb::kOsModeQuad:						// Osnap quad to the face's quad points
    case AcDb::kOsModeNear:
    { AcGeVector3d xoff(radius(), 0, 0), yoff(0, radius(), 0);
    AcGePoint3d cen(center());
    snapPoints.append(cen + xoff);
    snapPoints.append(cen + yoff);
    snapPoints.append(cen - xoff);
    snapPoints.append(cen - yoff);
    }
    return eOk;

    case AcDb::kOsModeMid:
    case AcDb::kOsModeEnd:
    case AcDb::kOsModeNode:
    case AcDb::kOsModeIns:
    case AcDb::kOsModePerp:
    case AcDb::kOsModeTan:
    default: break;
    }
    return eInvalidInput;
}

