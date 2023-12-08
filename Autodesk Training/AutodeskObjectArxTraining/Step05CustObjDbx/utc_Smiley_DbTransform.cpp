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



//
// Step 4
// We are implementing 'getGripPoints' function to create the array of 
// grip points for smiley object and are implementing 'moveGripPointsAt' 
// function to stretch and to move the face, the mouth and eyes of 
// smiley object using a grip points. To control the size of smiley at 
// changes of its elements, we have implemented the 'ensureRadius' functions.
//
//Acad::ErrorStatus utc_Smiley::subGetGripPoints(AcGePoint3dArray& gripPoints) const
//{
//    assertReadEnabled();
//    //indices
//    // Grip points to face
//    AcGePoint3d cen(center());
//    AcGeVector3d xoff(radius(), 0, 0),
//        yoff(0, radius(), 0);
//    gripPoints.append(cen);			// 0
//    gripPoints.append(cen + xoff);		// 1
//    gripPoints.append(cen + yoff);		// 2
//    gripPoints.append(cen - xoff);		// 3
//    gripPoints.append(cen - yoff);		// 4
//    // Grip points to mouth
//    gripPoints.append(mouthLeft());		// 5
//    gripPoints.append(mouthRight());		// 6
//    gripPoints.append(mouthBottom());		// 7
//    gripPoints.append(AcGeLineSeg3d(mouthLeft(), mouthRight()).midPoint());  // 8
//    // Grip points to eye
//    xoff.x = yoff.y = m_eyesize;
//    // Left eye
//    cen = leftEyeCenter();
//    gripPoints.append(cen);			    // 9
//    gripPoints.append(cen + xoff);		// 10
//    gripPoints.append(cen + yoff);		// 11
//    gripPoints.append(cen - xoff);		// 12
//    gripPoints.append(cen - yoff);		// 13
//    // Left eye
//    cen = rightEyeCenter();
//    gripPoints.append(cen);			    // 14
//    gripPoints.append(cen + xoff);		// 15
//    gripPoints.append(cen + yoff);		// 16
//    gripPoints.append(cen - xoff);		// 17
//    gripPoints.append(cen - yoff);		// 18
//
//    return eOk;
//}

//Acad::ErrorStatus utc_Smiley::subMoveGripPointsAt(const AcGePoint3dArray& gripPoints,
//    const AcDbIntArray& indices)
//{
//    assertWriteEnabled();
//    int idx, count = indices.length();
//    AcGePoint3d idxpoint;
//
//    for (int i = 0; i < count; i++)		// a few grip points can be selected concurrently
//    {
//        idx = indices[i];
//        idxpoint = gripPoints[idx];
//
//        if (idx == 0)						// Move the smiley center
//        {
//            setCenter(idxpoint);
//        }
//        else if (idx >= 1 && idx <= 4)		// Stretch the smiley radius
//        {
//            scaleRadius(idxpoint.distanceTo(center()));
//        }
//        else if (idx == 5)					// Stretch the left edge of mouth
//        {
//            setMouth(idxpoint, mouthBottom(), mouthRight());
//            ensureRadiusMouth();
//        }
//        else if (idx == 6)					// Stretch the right edge of mouth
//        {
//            setMouth(mouthLeft(), mouthBottom(), idxpoint);
//            ensureRadiusMouth();
//        }
//        else if (idx == 7)					// Stretch the bottom edge of mouth
//        {
//            setMouth(mouthLeft(), idxpoint, mouthRight());
//            ensureRadiusMouth();
//        }
//        else if (idx == 8)					// Move the mouth
//        {
//            moveMouthToPoint(idxpoint);
//            ensureRadiusMouth();
//        }
//        else if (idx == 9 || idx == 14)		// Move the center of eyes 
//        {
//            setEyesApart((idxpoint.x - center().x) * 2);					// Apart >= 2*eyeSize
//
//            if (eyesApart() < 2 * eyeSize()) setEyesApart(2 * eyeSize());
//
//            setEyesHeight(idxpoint.y - center().y);						// Height >= eyeSize
//
//            if (eyesHeight() < eyeSize()) setEyesHeight(eyeSize());
//
//            ensureRadiusEyes();
//        }
//        else if ((idx >= 10 && idx <= 13) || (idx >= 15 && idx <= 18))	// Stretch the radius of eyes 
//        {
//            setEyeSize(idxpoint.distanceTo((idx < 14) ? leftEyeCenter() : rightEyeCenter()));
//
//            if (2 * eyeSize() > eyesApart()) setEyeSize(eyesApart() / 2);
//            ensureRadiusEyes();
//        };
//    }
//    return eOk;
//}
//



Acad::ErrorStatus utc_Smiley::subGetGripPoints(AcGePoint3dArray& gripPoints, AcDbIntArray& osnapModes, AcDbIntArray& geomIds) const
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
) const 
{
    assertReadEnabled();

    //----- This method is never called unless you return eNotImplemented 
    //----- from the new getGripPoints() method below (which is the default implementation)
    return (AcDbEntity::subGetGripPoints(grips, curViewUnitSize, gripSize, curViewDir, bitflags));
}

Acad::ErrorStatus utc_Smiley::subMoveGripPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset)
{
    assertWriteEnabled();
    int idx, count = indices.length();
    AcGePoint3d idxpoint;
    AcGePoint3d oldquad, newquad;

    for (int i = 0; i < count; i++)		// a few grip points can be selected concurrently
    {
        idx = indices[i];

        switch (idx)
        {
        case 0:
        {
            setCenter(center() + offset);
        } break;

        case 1:
        {
            oldquad = center() + AcGeVector3d(radius(), 0, 0);
            newquad = oldquad + offset;
            scaleRadius(newquad.distanceTo(center()));
        } break;

        case 2:
        {
            oldquad = center() + AcGeVector3d(0, radius(), 0);
            newquad = oldquad + offset;
            scaleRadius(newquad.distanceTo(center()));
        } break;

        case 3:
        {
            oldquad = center() - AcGeVector3d(radius(), 0, 0);
            newquad = oldquad + offset;
            scaleRadius(newquad.distanceTo(center()));
        } break;

        case 4:
        {
            oldquad = center() - AcGeVector3d(0, radius(), 0);
            newquad = oldquad + offset;
            scaleRadius(newquad.distanceTo(center()));
        } break;
        case 5:
        {
            setMouth(mouthLeft() + offset, mouthBottom(), mouthRight());
            ensureRadiusMouth();
        } break;

        case 6:
        {
            setMouth(mouthLeft(), mouthBottom(), mouthRight() + offset);
            ensureRadiusMouth();
        } break;

        case 7:
        {
            setMouth(mouthLeft(), mouthBottom() + offset, mouthRight());
            ensureRadiusMouth();
        } break;

        case 8:
        {
            setMouth(mouthLeft() + offset, mouthBottom() + offset, mouthRight() + offset);
            ensureRadiusMouth();
        } break;

        case 9:
        case 14:
        {
            AcGePoint3d eyecen;

            if (idx == 9)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            if (m_eyesheight + offset.x < 0)
                setEyesHeight(0);
            else
                setEyesHeight(m_eyesheight + offset.y);

            if (eyecen.x < center().x) // left eye
            {
                if (m_eyesapart - (offset.x * 2) < m_eyesize * 2)
                    setEyesApart(m_eyesize * 2);
                else
                    setEyesApart(m_eyesapart - (offset.x * 2));
            }
            else // right eye
            {
                if (m_eyesapart + (offset.x * 2) < m_eyesize * 2)
                    setEyesApart(m_eyesize * 2);
                else
                    setEyesApart(m_eyesapart + (offset.x * 2));
            }

            ensureRadiusEyes();
        } break;

        case 10:
        case 15:
        {
            AcGePoint3d eyecen;

            if (idx == 10)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            oldquad = eyecen + AcGeVector3d(m_eyesize, 0, 0);
            newquad = oldquad + offset;

            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                setEyeSize(m_eyesapart / 2);
            else
                setEyeSize(newquad.distanceTo(eyecen));

            ensureRadiusEyes();
        } break;

        case 11:
        case 16:
        {
            AcGePoint3d eyecen;

            if (idx == 11)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
            newquad = oldquad + offset;

            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                setEyeSize(m_eyesapart / 2);
            else
                setEyeSize(newquad.distanceTo(eyecen));

            ensureRadiusEyes();
        } break;

        case 12:
        case 17:
        {
            AcGePoint3d eyecen;

            if (idx == 12)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
            newquad = oldquad + offset;

            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                setEyeSize(m_eyesapart / 2);
            else
                setEyeSize(newquad.distanceTo(eyecen));

            ensureRadiusEyes();
        } break;

        case 13:
        case 18:
        {
            AcGePoint3d eyecen;

            if (idx == 18)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            oldquad = eyecen - AcGeVector3d(0, m_eyesize, 0);
            newquad = oldquad + offset;

            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                setEyeSize(m_eyesapart / 2);
            else
                setEyeSize(newquad.distanceTo(eyecen));

            ensureRadiusEyes();
        } break;
        }
    }

    return eOk;
}

Acad::ErrorStatus utc_Smiley::subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData, const AcGeVector3d& offset, const int bitflags)
{
    return AcDbEntity::subMoveGripPointsAt(gripAppData, offset, bitflags);
}







//==================================================================================================//

Acad::ErrorStatus utc_Smiley::subGetGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath,
    AcArray<Adesk::GsMarker>& gsMarkers) const
{
    assertReadEnabled();

    gsMarkers.removeAll();

    if (subPath.objectIds().length() == 0)
        return eNotApplicable;

    gsMarkers.append(subPath.subentId().index());

    return eOk;
}



Acad::ErrorStatus utc_Smiley::subGetSubentPathsAtGsMarker(AcDb::SubentType type,
    Adesk::GsMarker gsMark,
    const AcGePoint3d& pickPoint,
    const AcGeMatrix3d& viewXform,
    int& numPaths,
    AcDbFullSubentPath*& subentPaths,
    int numInserts = 0,
    AcDbObjectId* entAndInsertStack = nullptr) const
{
    assertReadEnabled();

    AcDbFullSubentPath pPaths;
    pPaths.subentId().setIndex(gsMark);
    pPaths.subentId().setType(AcDb::kClassSubentType);
    pPaths.objectIds().append(this->objectId());

    subentPaths = NULL;

    subentPaths = new AcDbFullSubentPath[1];
    subentPaths[0] = pPaths;

    numPaths = 1;

    return eOk;
}



//==================================================================================================//

Acad::ErrorStatus utc_Smiley::subGetSubentClassId(const AcDbFullSubentPath& path,
    CLSID* clsId) const
{
    assertReadEnabled();

    AcDbEntity* pEnt = subSubentPtr(path);

    if (pEnt != NULL)
    {
        pEnt->getClassID(clsId);
        return eOk;
    }

    return eInvalidInput;
}



//==================================================================================================//

Acad::ErrorStatus utc_Smiley::subGetSubentPathGeomExtents(const AcDbFullSubentPath& path,
    AcDbExtents& extents) const
{
    assertReadEnabled();

    AcDbEntity* pEnt = subSubentPtr(path);

    if (pEnt != NULL)
    {
        pEnt->getGeomExtents(extents);
        return eOk;
    }

    return eInvalidInput;
}

//==================================================================================================//

AcDbEntity* utc_Smiley::subSubentPtr(const AcDbFullSubentPath& id) const
{
    assertReadEnabled();

    Adesk::GsMarker iMark = id.subentId().index();

    if (iMark == kFaceMark)
    {
        AcDbCircle* pCircle = new AcDbCircle();
        pCircle->setCenter(center());
        pCircle->setNormal(m_normal);
        pCircle->setRadius(radius());
        return pCircle;
    }
    else if (iMark == kLeftEyeMark || iMark == kRightEyeMark)
    {
        AcGePoint3d  ptEyeCenter;

        if (iMark == kLeftEyeMark)
            ptEyeCenter = leftEyeCenter();
        else
            ptEyeCenter = rightEyeCenter();

        AcDbCircle* pCircle = new AcDbCircle();
        pCircle->setCenter(ptEyeCenter);
        pCircle->setNormal(m_normal);
        pCircle->setRadius(m_eyesize);
        return pCircle;
    }
    else if (iMark == kMouthMark)
    {
        AcGePoint3d smilecen(mouthCenter());
        AcGePoint3d startpt(mouthLeft());
        AcGePoint3d endpt(mouthRight());
        AcGeVector3d normvec(1, 0, 0);
        AcGeVector3d startvec = startpt - smilecen;
        AcGeVector3d endvec = endpt - smilecen;
        double startang = 2 * kPi - startvec.angleTo(normvec);
        double endang = 2 * kPi - endvec.angleTo(normvec);
        AcDbPolyline* pLine = new AcDbPolyline();

        AcGeVector3d vrCenterStart = startpt - smilecen;
        AcGeVector3d vrCenterEnd = endpt - smilecen;
        vrCenterStart /= vrCenterStart.length();
        vrCenterEnd /= vrCenterEnd.length();
        AcGeVector3d vrBase = vrCenterStart + vrCenterEnd;
        vrBase /= vrBase.length();

        if (startang - endang > kPi)
            vrBase *= -1;

        AcGePoint3d ptBulge = smilecen + vrBase * smilecen.distanceTo(endpt);
        AcGeLineSeg3d segStartEnd(startpt, endpt);

        double dBulge = segStartEnd.midPoint().distanceTo(ptBulge) / segStartEnd.midPoint().distanceTo(startpt);
        pLine->addVertexAt(0, AcGePoint2d(startpt.x, startpt.y), dBulge);
        pLine->addVertexAt(1, AcGePoint2d(endpt.x, endpt.y), 0);
        pLine->setClosed(true);
        return pLine;
    }

    return NULL;
}

//==================================================================================================//

Acad::ErrorStatus utc_Smiley::subGetGripPointsAtSubentPath(
    const AcDbFullSubentPath& path,
    AcDbGripDataPtrArray& grips,
    const double curViewUnitSize,
    const int gripSize,
    const AcGeVector3d& curViewDir,
    const int bitflags) const
{
    assertReadEnabled();

    Adesk::GsMarker iMark = path.subentId().index();

    if (iMark == kFaceMark)
    {
        AcGePoint3d _center(center());
        AcGeVector3d xoff(radius(), 0, 0);
        AcGeVector3d yoff(0, radius(), 0);

        AcDbGripData* pGrip1 = new AcDbGripData();
        pGrip1->setAppData((void*)(FACE_CENTER_GRIP_PT));
        pGrip1->setGripPoint(_center);
        grips.append(pGrip1);

        AcDbGripData* pGrip2 = new AcDbGripData();
        pGrip2->setAppData((void*)(FACE_RIGHT_GRIP_PT));
        pGrip2->setGripPoint(_center + xoff);
        grips.append(pGrip2);

        AcDbGripData* pGrip3 = new AcDbGripData();
        pGrip3->setAppData((void*)(FACE_TOP_GRIP_PT));
        pGrip3->setGripPoint(_center + yoff);
        grips.append(pGrip3);

        AcDbGripData* pGrip4 = new AcDbGripData();
        pGrip4->setAppData((void*)(FACE_LEFT_GRIP_PT));
        pGrip4->setGripPoint(_center - xoff);
        grips.append(pGrip4);

        AcDbGripData* pGrip5 = new AcDbGripData();
        pGrip5->setAppData((void*)(FACE_BOTTOM_GRIP_PT));
        pGrip5->setGripPoint(_center - yoff);
        grips.append(pGrip5);
    }
    else if (iMark == kLeftEyeMark || iMark == kRightEyeMark)
    {
        AcGePoint3d eyecen;
        AcGeVector3d xoff(m_eyesize, 0, 0);
        AcGeVector3d yoff(0, m_eyesize, 0);

        if (iMark == kLeftEyeMark)
            eyecen = leftEyeCenter();
        else
            eyecen = rightEyeCenter();

        AcDbGripData* pGrip1 = new AcDbGripData();
        pGrip1->setAppData((void*)(EYE_CENTER_GRIP_PT));
        pGrip1->setGripPoint(eyecen);
        grips.append(pGrip1);

        AcDbGripData* pGrip2 = new AcDbGripData();
        pGrip2->setAppData((void*)(EYE_RIGHT_GRIP_PT));
        pGrip2->setGripPoint(eyecen + xoff);
        grips.append(pGrip2);

        AcDbGripData* pGrip3 = new AcDbGripData();
        pGrip3->setAppData((void*)(EYE_TOP_GRIP_PT));
        pGrip3->setGripPoint(eyecen + yoff);
        grips.append(pGrip3);

        AcDbGripData* pGrip4 = new AcDbGripData();
        pGrip4->setAppData((void*)(EYE_LEFT_GRIP_PT));
        pGrip4->setGripPoint(eyecen - xoff);
        grips.append(pGrip4);

        AcDbGripData* pGrip5 = new AcDbGripData();
        pGrip5->setAppData((void*)(EYE_BOTTOM_GRIP_PT));
        pGrip5->setGripPoint(eyecen - yoff);
        grips.append(pGrip5);
    }
    else if (iMark == kMouthMark)
    {
        AcGeLineSeg3d chord(mouthLeft(), mouthRight());

        AcDbGripData* pGrip1 = new AcDbGripData();
        pGrip1->setAppData((void*)(MOUTH_LEFT_GRIP_PT));
        pGrip1->setGripPoint(mouthLeft());
        grips.append(pGrip1);

        AcDbGripData* pGrip2 = new AcDbGripData();
        pGrip2->setAppData((void*)(MOUTH_RIGHT_GRIP_PT));
        pGrip2->setGripPoint(mouthRight());
        grips.append(pGrip2);

        AcDbGripData* pGrip3 = new AcDbGripData();
        pGrip3->setAppData((void*)(MOUTH_MID_GRIP_PT));
        pGrip3->setGripPoint(chord.midPoint());
        grips.append(pGrip3);

        AcDbGripData* pGrip4 = new AcDbGripData();
        pGrip4->setAppData((void*)(MOUTH_BOTTOM_GRIP_PT));
        pGrip4->setGripPoint(mouthBottom());
        grips.append(pGrip4);
    }

    return eOk;
}


//==================================================================================================//

Acad::ErrorStatus utc_Smiley::subMoveGripPointsAtSubentPaths(
    const AcDbFullSubentPathArray& paths,
    const AcDbVoidPtrArray& gripAppData,
    const AcGeVector3d& offset,
    const int bitflags)
{
    assertWriteEnabled();

    AcGePoint3d oldquad, newquad;

    for (unsigned int i = 0; i < gripAppData.length(); i++)
    {
         Adesk::GsMarker iMark = paths[i].subentId().index();

        int idx =   (int)gripAppData.at(i);

        if (iMark == kFaceMark)
        {
            switch (idx)
            {
            case FACE_CENTER_GRIP_PT:
            {
                setCenter(center() + offset);
            } break;

            case FACE_RIGHT_GRIP_PT:
            {
                oldquad = center() + AcGeVector3d(radius(), 0, 0);
                newquad = oldquad + offset;
                scaleRadius(newquad.distanceTo(center()));
            } break;

            case FACE_TOP_GRIP_PT:
            {
                oldquad = center() + AcGeVector3d(0, radius(), 0);
                newquad = oldquad + offset;
                scaleRadius(newquad.distanceTo(center()));
            } break;

            case FACE_LEFT_GRIP_PT:
            {
                oldquad = center() - AcGeVector3d(radius(), 0, 0);
                newquad = oldquad + offset;
                scaleRadius(newquad.distanceTo(center()));
            } break;

            case FACE_BOTTOM_GRIP_PT:
            {
                oldquad = center() - AcGeVector3d(0, radius(), 0);
                newquad = oldquad + offset;
                scaleRadius(newquad.distanceTo(center()));
            } break;
            }
        }
        else if (iMark == kLeftEyeMark || iMark == kRightEyeMark)
        {
            AcGePoint3d eyecen;
            AcGeVector3d xoff(m_eyesize, 0, 0);
            AcGeVector3d yoff(0, m_eyesize, 0);

            if (iMark == kLeftEyeMark)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            switch (idx)
            {
            case EYE_CENTER_GRIP_PT:
            {
                if (m_eyesheight + offset.x < 0)
                    setEyesHeight(0);
                else
                    setEyesHeight(m_eyesheight + offset.y);

                if (eyecen.x < center().x) // left eye
                {
                    if (m_eyesapart - (offset.x * 2) < m_eyesize * 2)
                        setEyesApart(m_eyesize * 2);
                    else
                        setEyesApart(m_eyesapart - (offset.x * 2));
                }
                else // right eye
                {
                    if (m_eyesapart + (offset.x * 2) < m_eyesize * 2)
                        setEyesApart(m_eyesize * 2);
                    else
                        setEyesApart(m_eyesapart + (offset.x * 2));
                }

                ensureRadiusEyes();
            } break;

            case EYE_RIGHT_GRIP_PT:
            {
                oldquad = eyecen + AcGeVector3d(m_eyesize, 0, 0);
                newquad = oldquad + offset;

                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                    setEyeSize(m_eyesapart / 2);
                else
                    setEyeSize(newquad.distanceTo(eyecen));

                ensureRadiusEyes();
            } break;

            case EYE_TOP_GRIP_PT:
            {
                oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
                newquad = oldquad + offset;

                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                    setEyeSize(m_eyesapart / 2);
                else
                    setEyeSize(newquad.distanceTo(eyecen));

                ensureRadiusEyes();
            } break;

            case EYE_LEFT_GRIP_PT:
            {
                oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
                newquad = oldquad + offset;

                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                    setEyeSize(m_eyesapart / 2);
                else
                    setEyeSize(newquad.distanceTo(eyecen));

                ensureRadiusEyes();
            } break;

            case EYE_BOTTOM_GRIP_PT:
            {
                oldquad = eyecen - AcGeVector3d(0, m_eyesize, 0);
                newquad = oldquad + offset;

                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
                    setEyeSize(m_eyesapart / 2);
                else
                    setEyeSize(newquad.distanceTo(eyecen));

                ensureRadiusEyes();
            } break;
            }
        }
        else if (iMark == kMouthMark)
        {
            switch (idx)
            {
            case MOUTH_LEFT_GRIP_PT:
            {
                setMouth(mouthLeft() + offset, mouthBottom(), mouthRight());
                ensureRadiusMouth();
            } break;

            case MOUTH_RIGHT_GRIP_PT:
            {
                setMouth(mouthLeft(), mouthBottom(), mouthRight() + offset);
                ensureRadiusMouth();
            } break;

            case MOUTH_MID_GRIP_PT:
            {
                setMouth(mouthLeft() + offset, mouthBottom() + offset, mouthRight() + offset);
                ensureRadiusMouth();
            } break;

            case MOUTH_BOTTOM_GRIP_PT:
            {
                setMouth(mouthLeft(), mouthBottom() + offset, mouthRight());
                ensureRadiusMouth();
            } break;
            }
        }
    }
    return eOk;
}

//==================================================================================================//

//Acad::ErrorStatus utc_Smiley::subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
//    const AcGeVector3d& offset, const int bitflags)
//{
//
//    assertWriteEnabled();
//    int idx, count = gripAppData.length();
//    AcGePoint3d idxpoint;
//    AcGePoint3d oldquad, newquad;
//
//    for (int i = 0; i < count; i++)		// a few grip points can be selected concurrently
//    {
//
//
//        AcDbGripData* gripdata = static_cast<AcDbGripData*> (gripAppData.at(i));
//
//        switch (idx)
//        {
//            case 0:
//            {
//                setCenter(center() + offset);
//            } break;
//
//            case 1:
//            {
//                oldquad = center() + AcGeVector3d(radius(), 0, 0);
//                newquad = oldquad + offset;
//                scaleRadius(newquad.distanceTo(center()));
//            } break;
//
//            case 2:
//            {
//                oldquad = center() + AcGeVector3d(0, radius(), 0);
//                newquad = oldquad + offset;
//                scaleRadius(newquad.distanceTo(center()));
//            } break;
//
//            case 3:
//            {
//                oldquad = center() - AcGeVector3d(radius(), 0, 0);
//                newquad = oldquad + offset;
//                scaleRadius(newquad.distanceTo(center()));
//            } break;
//
//            case 4:
//            {
//                oldquad = center() - AcGeVector3d(0, radius(), 0);
//                newquad = oldquad + offset;
//                scaleRadius(newquad.distanceTo(center()));
//            } break;
//            case 5:
//            {
//                setMouth(mouthLeft() + offset, mouthBottom(), mouthRight());
//                ensureRadiusMouth();
//            } break;
//
//            case 6:
//            {
//                setMouth(mouthLeft(), mouthBottom(), mouthRight() + offset);
//                ensureRadiusMouth();
//            } break;
//
//            case 7:
//            {
//                setMouth(mouthLeft(), mouthBottom() + offset, mouthRight());
//                ensureRadiusMouth();
//            } break;
//
//            case 8:
//            {
//                setMouth(mouthLeft() + offset, mouthBottom() + offset, mouthRight() + offset);
//                ensureRadiusMouth();
//            } break;
//
//            case 9:
//            case 14:
//            {
//                AcGePoint3d eyecen;
//
//                if (idx == 9)
//                    eyecen = leftEyeCenter();
//                else
//                    eyecen = rightEyeCenter();
//
//                if (m_eyesheight + offset.x < 0)
//                    setEyesHeight(0);
//                else
//                    setEyesHeight(m_eyesheight + offset.y);
//
//                if (eyecen.x < center().x) // left eye
//                {
//                    if (m_eyesapart - (offset.x * 2) < m_eyesize * 2)
//                        setEyesApart(m_eyesize * 2);
//                    else
//                        setEyesApart(m_eyesapart - (offset.x * 2));
//                }
//                else // right eye
//                {
//                    if (m_eyesapart + (offset.x * 2) < m_eyesize * 2)
//                        setEyesApart(m_eyesize * 2);
//                    else
//                        setEyesApart(m_eyesapart + (offset.x * 2));
//                }
//
//                ensureRadiusEyes();
//            } break;
//
//            case 10:
//            case 15:
//            {
//                AcGePoint3d eyecen;
//
//                if (idx == 10)
//                    eyecen = leftEyeCenter();
//                else
//                    eyecen = rightEyeCenter();
//
//                oldquad = eyecen + AcGeVector3d(m_eyesize, 0, 0);
//                newquad = oldquad + offset;
//
//                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                    setEyeSize(m_eyesapart / 2);
//                else
//                    setEyeSize(newquad.distanceTo(eyecen));
//
//                ensureRadiusEyes();
//            } break;
//
//            case 11:
//            case 16:
//            {
//                AcGePoint3d eyecen;
//
//                if (idx == 11)
//                    eyecen = leftEyeCenter();
//                else
//                    eyecen = rightEyeCenter();
//
//                oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
//                newquad = oldquad + offset;
//
//                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                    setEyeSize(m_eyesapart / 2);
//                else
//                    setEyeSize(newquad.distanceTo(eyecen));
//
//                ensureRadiusEyes();
//            } break;
//
//            case 12:
//            case 17:
//            {
//                AcGePoint3d eyecen;
//
//                if (idx == 12)
//                    eyecen = leftEyeCenter();
//                else
//                    eyecen = rightEyeCenter();
//
//                oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
//                newquad = oldquad + offset;
//
//                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                    setEyeSize(m_eyesapart / 2);
//                else
//                    setEyeSize(newquad.distanceTo(eyecen));
//
//                ensureRadiusEyes();
//            } break;
//
//            case 13:
//            case 18:
//            {
//                AcGePoint3d eyecen;
//
//                if (idx == 18)
//                    eyecen = leftEyeCenter();
//                else
//                    eyecen = rightEyeCenter();
//
//                oldquad = eyecen - AcGeVector3d(0, m_eyesize, 0);
//                newquad = oldquad + offset;
//
//                if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                    setEyeSize(m_eyesapart / 2);
//                else
//                    setEyeSize(newquad.distanceTo(eyecen));
//
//                ensureRadiusEyes();
//            } break;
//        }
//    }
//
//    return eOk;
//}
//

//==================================================================================================//

//Acad::ErrorStatus utc_Smiley::subMoveGripPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset)
//{
//    assertWriteEnabled();
//    int idx, count = indices.length();
//    AcGePoint3d idxpoint;
//    AcGePoint3d oldquad, newquad;
//
//    for (int i = 0; i < count; i++)		// a few grip points can be selected concurrently
//    {
//        idx = indices[i];
//
//        switch (idx)
//        {
//        case 0:
//        {
//            setCenter(center() + offset);
//        } break;
//
//        case 1:
//        {
//            oldquad = center() + AcGeVector3d(radius(), 0, 0);
//            newquad = oldquad + offset;
//            scaleRadius(newquad.distanceTo(center()));
//        } break;
//
//        case 2:
//        {
//            oldquad = center() + AcGeVector3d(0, radius(), 0);
//            newquad = oldquad + offset;
//            scaleRadius(newquad.distanceTo(center()));
//        } break;
//
//        case 3:
//        {
//            oldquad = center() - AcGeVector3d(radius(), 0, 0);
//            newquad = oldquad + offset;
//            scaleRadius(newquad.distanceTo(center()));
//        } break;
//
//        case 4:
//        {
//            oldquad = center() - AcGeVector3d(0, radius(), 0);
//            newquad = oldquad + offset;
//            scaleRadius(newquad.distanceTo(center()));
//        } break;
//        case 5:
//        {
//            setMouth(mouthLeft() + offset, mouthBottom(), mouthRight());
//            ensureRadiusMouth();
//        } break;
//
//        case 6:
//        {
//            setMouth(mouthLeft(), mouthBottom(), mouthRight() + offset);
//            ensureRadiusMouth();
//        } break;
//
//        case 7:
//        {
//            setMouth(mouthLeft(), mouthBottom() + offset, mouthRight());
//            ensureRadiusMouth();
//        } break;
//
//        case 8:
//        {
//            setMouth(mouthLeft() + offset, mouthBottom() + offset, mouthRight() + offset);
//            ensureRadiusMouth();
//        } break;
//
//        case 9:
//        case 14:
//        {
//            AcGePoint3d eyecen;
//
//            if (idx == 9)
//                eyecen = leftEyeCenter();
//            else
//                eyecen = rightEyeCenter();
//
//            if (m_eyesheight + offset.x < 0)
//                setEyesHeight(0);
//            else
//                setEyesHeight(m_eyesheight + offset.y);
//
//            if (eyecen.x < center().x) // left eye
//            {
//                if (m_eyesapart - (offset.x * 2) < m_eyesize * 2)
//                    setEyesApart(m_eyesize * 2);
//                else
//                    setEyesApart(m_eyesapart - (offset.x * 2));
//            }
//            else // right eye
//            {
//                if (m_eyesapart + (offset.x * 2) < m_eyesize * 2)
//                    setEyesApart(m_eyesize * 2);
//                else
//                    setEyesApart(m_eyesapart + (offset.x * 2));
//            }
//
//            ensureRadiusEyes();
//        } break;
//
//        case 10:
//        case 15:
//        {
//            AcGePoint3d eyecen;
//
//            if (idx == 10)
//                eyecen = leftEyeCenter();
//            else
//                eyecen = rightEyeCenter();
//
//            oldquad = eyecen + AcGeVector3d(m_eyesize, 0, 0);
//            newquad = oldquad + offset;
//
//            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                setEyeSize(m_eyesapart / 2);
//            else
//                setEyeSize(newquad.distanceTo(eyecen));
//
//            ensureRadiusEyes();
//        } break;
//
//        case 11:
//        case 16:
//        {
//            AcGePoint3d eyecen;
//
//            if (idx == 11)
//                eyecen = leftEyeCenter();
//            else
//                eyecen = rightEyeCenter();
//
//            oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
//            newquad = oldquad + offset;
//
//            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                setEyeSize(m_eyesapart / 2);
//            else
//                setEyeSize(newquad.distanceTo(eyecen));
//
//            ensureRadiusEyes();
//        } break;
//
//        case 12:
//        case 17:
//        {
//            AcGePoint3d eyecen;
//
//            if (idx == 12)
//                eyecen = leftEyeCenter();
//            else
//                eyecen = rightEyeCenter();
//
//            oldquad = eyecen - AcGeVector3d(m_eyesize, 0, 0);
//            newquad = oldquad + offset;
//
//            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                setEyeSize(m_eyesapart / 2);
//            else
//                setEyeSize(newquad.distanceTo(eyecen));
//
//            ensureRadiusEyes();
//        } break;
//
//        case 13:
//        case 18:
//        {
//            AcGePoint3d eyecen;
//
//            if (idx == 18)
//                eyecen = leftEyeCenter();
//            else
//                eyecen = rightEyeCenter();
//
//            oldquad = eyecen - AcGeVector3d(0, m_eyesize, 0);
//            newquad = oldquad + offset;
//
//            if (newquad.distanceTo(eyecen) > m_eyesapart / 2)
//                setEyeSize(m_eyesapart / 2);
//            else
//                setEyeSize(newquad.distanceTo(eyecen));
//
//            ensureRadiusEyes();
//        } break;
//        }
//    }
//
//    return eOk;
//}

//==================================================================================================//

Acad::ErrorStatus utc_Smiley::subTransformSubentPathsBy(const AcDbFullSubentPathArray& paths, const AcGeMatrix3d& xform)
{
    assertWriteEnabled();

    for (unsigned int i = 0; i < paths.length(); i++)
    {
        Adesk::GsMarker iMark = paths[i].subentId().index();

        if (iMark == kFaceMark)
        {
            transformBy(xform);
        }
        else if (iMark == kRightEyeMark || iMark == kLeftEyeMark)
        {
            AcGePoint3d eyecen;
            AcGeVector3d xoff(m_eyesize, 0, 0);
            AcGeVector3d yoff(0, m_eyesize, 0);

            if (iMark == kLeftEyeMark)
                eyecen = leftEyeCenter();
            else
                eyecen = rightEyeCenter();

            AcGePoint3d ptOldEyeCen = eyecen;

            AcGePoint3d iTopPt = eyecen;
            iTopPt.y += m_eyesize;
            AcGePoint3d iRightPt = eyecen;
            iRightPt.x += m_eyesize;

            eyecen.transformBy(xform);
            iTopPt.transformBy(xform);
            iRightPt.transformBy(xform);

            AcGeVector3d Offset = eyecen - ptOldEyeCen;
            double dMinD = iTopPt.distanceTo(eyecen) < iRightPt.distanceTo(eyecen) ? iTopPt.distanceTo(eyecen) : iRightPt.distanceTo(eyecen);

            if (m_eyesheight + Offset.y < 0)
                setEyesHeight(0);
            else
                setEyesHeight(m_eyesheight + Offset.y);

            if (eyecen.x < center().x) // left eye
            {
                if (m_eyesapart - (Offset.x * 2) < m_eyesize * 2)
                    setEyesApart(m_eyesize * 2);
                else
                    setEyesApart(m_eyesapart - (Offset.x * 2));
            }
            else // right eye
            {
                if (m_eyesapart + (Offset.x * 2) < m_eyesize * 2)
                    setEyesApart(m_eyesize * 2);
                else
                    setEyesApart(m_eyesapart + (Offset.x * 2));
            }

            ensureRadiusEyes();

            if (dMinD > m_eyesapart / 2)
                setEyeSize(m_eyesapart / 2);
            else
                setEyeSize(dMinD);

            ensureRadiusEyes();
        }
        else if (iMark == kMouthMark)
        {
            AcGePoint3d ptMouthLeft = mouthLeft();
            AcGePoint3d ptMouthRight = mouthRight();
            AcGePoint3d ptMouthBottom = mouthBottom();

            ptMouthLeft.transformBy(xform);
            ptMouthRight.transformBy(xform);
            ptMouthBottom.transformBy(xform);

            AcGeVector3d vrLeftOffset = ptMouthLeft - mouthLeft();
            AcGeVector3d vrRightOffset = ptMouthRight - mouthRight();
            AcGeVector3d vrBottomOffset = ptMouthBottom - mouthBottom();
            setMouth(mouthLeft() + vrLeftOffset, mouthBottom() + vrBottomOffset, mouthRight() + vrRightOffset);
            ensureRadiusMouth();
        }
    }

    return eOk;
}

