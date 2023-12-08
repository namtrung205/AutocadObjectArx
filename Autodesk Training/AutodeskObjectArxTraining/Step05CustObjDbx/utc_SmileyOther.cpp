//Impelementation for react and transform utc_smiley
#include "StdAfx.h"
#include "utc_Smiley.h"


//-------------------------------------------------------------------------//
//Explode
Acad::ErrorStatus utc_Smiley::subExplode(AcDbVoidPtrArray& entitySet) const
{
    assertReadEnabled();

    AcDbCircle* pFace = new AcDbCircle();			        // Create circle for face
    pFace->setPropertiesFrom(this);
    pFace->setNormal(normal());
    pFace->setRadius(radius());
    pFace->setCenter(center());
    entitySet.append(pFace);

    AcDbCircle* pLeftEye = new AcDbCircle();		        // Create circle for left eye
    pLeftEye->setPropertiesFrom(this);
    pLeftEye->setNormal(normal());
    pLeftEye->setRadius(eyeSize());
    pLeftEye->setCenter(leftEyeCenter());
    entitySet.append(pLeftEye);

    AcDbCircle* pRightEye = new AcDbCircle();		        // Create circle for right eye
    pRightEye->setPropertiesFrom(this);
    pRightEye->setNormal(normal());
    pRightEye->setRadius(eyeSize());
    pRightEye->setCenter(rightEyeCenter());
    entitySet.append(pRightEye);

    AcDbLine* pLine = new AcDbLine();				        // Create arc chord for mouth
    pLine->setPropertiesFrom(this);
    pLine->setNormal(normal());
    pLine->setStartPoint(mouthLeft());
    pLine->setEndPoint(mouthRight());
    entitySet.append(pLine);



    AcGeVector3d normvec(1, 0, 0);							// Create arc for mouth 
    double dStartAngle = 2 * kPi - (mouthLeft() - mouthCenter()).angleTo(normvec),
        dEndAngle = 2 * kPi - (mouthRight() - mouthCenter()).angleTo(normvec);

    AcDbArc* pArc = new AcDbArc();
    pArc->setPropertiesFrom(this);
    pArc->setNormal(normal());
    pArc->setRadius(mouthRadius());
    pArc->setCenter(mouthCenter());
    pArc->setStartAngle(dStartAngle);
    pArc->setEndAngle(dEndAngle);
    entitySet.append(pArc);

    pFace->close();
    pLeftEye->close();
    pRightEye->close();
    pLine->close();
    pArc->close();

    return eOk;
}
