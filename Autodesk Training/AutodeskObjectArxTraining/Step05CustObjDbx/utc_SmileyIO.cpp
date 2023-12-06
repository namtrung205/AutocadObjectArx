

#include "StdAfx.h"
#include "utc_Smiley.h"

//-----------------------------------------------------------------------------
//----- utc_SmileyIO.cpp : Implementation of utc_Smiley
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus utc_Smiley::dwgOutFields(AcDbDwgFiler* pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dwgOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(utc_Smiley::kCurrentVersionNumber)) != Acad::eOk)
		return (es);
	//----- Output params
	//.....

	pFiler->writePoint3d(center());
	pFiler->writeDouble(radius());
	pFiler->writeVector3d(normal());
	pFiler->writeDouble(eyesApart());
	pFiler->writeDouble(eyesHeight());
	pFiler->writeDouble(eyeSize());

#ifdef SMILEY_WITH_TEXT
	pFiler->writeString(m_TextField);
#endif

	pFiler->writePoint3d(mouthLeft());
	pFiler->writePoint3d(mouthBottom());
	pFiler->writePoint3d(mouthRight());
	pFiler->writeUInt32(faceColor().getCOLORREF());



	return (pFiler->filerStatus());
}

Acad::ErrorStatus utc_Smiley::dwgInFields(AcDbDwgFiler* pFiler)
{
	assertWriteEnabled();
	// Method of base class must be perfomed first
	Acad::ErrorStatus es = AcDbEntity::dwgInFields(pFiler);

	//----- Object version number needs to be read first
	Adesk::UInt32 version = 0;
	if ((es = pFiler->readUInt32(&version)) != Acad::eOk)
		return (es);
	if (version > utc_Smiley::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);

	// Read face data
	AcGePoint3d center;
	if (pFiler->readPoint3d(&center) == Acad::ErrorStatus::eOk)
	{
		setCenter(center);
	}

	double radius;
	if (pFiler->readDouble(&radius) == Acad::ErrorStatus::eOk)
	{
		setRadius(radius);
	}

	AcGeVector3d normal;
	if (pFiler->readVector3d(&normal) == Acad::ErrorStatus::eOk)
	{
		setNormal(normal);
	}


	// Read eyes data
	double eyesApart;
	if (pFiler->readDouble(&eyesApart) == Acad::ErrorStatus::eOk)
	{
		setEyesApart(eyesApart);
	}

	double eyesHeight;
	if (pFiler->readDouble(&eyesHeight) == Acad::ErrorStatus::eOk)
	{
		setEyesHeight(eyesHeight);
	}

	double eyesSize;
	if (pFiler->readDouble(&eyesSize) == Acad::ErrorStatus::eOk)
	{
		setEyeSize(eyesSize);
	}

	// Read text data
#ifdef SMILEY_WITH_TEXT
	AcString faceString;
	if (pFiler->readString(faceString) == Acad::ErrorStatus::eOk)
	{
		m_TextField = faceString;
	}
#endif

	// Read mouth data
	AcGePoint3d mouthLeftPt, mouthBottomPt, mouthRightPt;
	if ((es = pFiler->readPoint3d(&mouthLeftPt)) != Acad::ErrorStatus::eOk)
	{
		return es;
	}

	if ((es = pFiler->readPoint3d(&mouthBottomPt)) != Acad::ErrorStatus::eOk)
	{
		return es;
	}

	if ((es = pFiler->readPoint3d(&mouthRightPt)) != Acad::ErrorStatus::eOk)
	{
		return es;
	}

	setMouth(mouthLeftPt, mouthBottomPt, mouthRightPt);
	// Read color data
	Adesk::UInt32 faceColor = 16776960;
	if ((es = pFiler->readUInt32(&faceColor)) != Acad::eOk)
		return (es);
	m_facecolor.setCOLORREF(faceColor);

	recordGraphicsModified();
	return eOk;
}

//- Dxf Filing protocol
Acad::ErrorStatus utc_Smiley::dxfOutFields(AcDbDxfFiler* pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dxfOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	es = pFiler->writeItem(AcDb::kDxfSubclass, _RXST("utc_Smiley"));
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(kDxfInt32, utc_Smiley::kCurrentVersionNumber)) != Acad::eOk)
		return (es);
	//----- Output params
	//.....
	//Not Implemented Yet

	return (pFiler->filerStatus());
}

Acad::ErrorStatus utc_Smiley::dxfInFields(AcDbDxfFiler* pFiler) {
	assertWriteEnabled();
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dxfInFields(pFiler);
	if (es != Acad::eOk || !pFiler->atSubclassData(_RXST("utc_Smiley")))
		return (pFiler->filerStatus());
	//----- Object version number needs to be read first
	struct resbuf rb;
	pFiler->readItem(&rb);
	if (rb.restype != AcDb::kDxfInt32) {
		pFiler->pushBackItem();
		pFiler->setError(Acad::eInvalidDxfCode, _RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32);
		return (pFiler->filerStatus());
	}
	Adesk::UInt32 version = (Adesk::UInt32)rb.resval.rlong;
	if (version > utc_Smiley::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < utc_Smiley::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while (es == Acad::eOk && (es = pFiler->readResBuf(&rb)) == Acad::eOk) {
		switch (rb.restype) {
			//----- Read params by looking at their DXF code (example below)
			//case AcDb::kDxfXCoord:
			//	if ( version == 1 )
			//		cen3d =asPnt3d (rb.resval.rpoint) ;
			//	else 
			//		cen2d =asPnt2d (rb.resval.rpoint) ;
			//	break ;
			//.....

		default:
			//----- An unrecognized group. Push it back so that the subclass can read it again.
			pFiler->pushBackItem();
			es = Acad::eEndOfFile;
			break;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if (es != Acad::eEndOfFile)
		return (Acad::eInvalidResBuf);

	//Not Implemented Yet

	return (pFiler->filerStatus());
}



//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean utc_Smiley::subWorldDraw(AcGiWorldDraw* wd)
{
	assertReadEnabled();

	AcGeVector3d offset(0, 0, 0);
	// If dragging, don't fill the smiley
	if (wd->isDragging()) {
		wd->subEntityTraits().setTrueColor(m_facecolor);  // Returns a 'True' true color.
		wd->subEntityTraits().setFillType(AcGiFillType::kAcGiFillNever);
	}
	else
	{
		wd->subEntityTraits().setTrueColor(m_facecolor);  // Returns a 'True' true color.
		wd->subEntityTraits().setFillType(AcGiFillType::kAcGiFillAlways);
	}


	// Drawing circle of face
	wd->subEntityTraits().setSelectionMarker(kFaceMark); // 1 == kFaceMark
	wd->geometry().circle(center(), radius(), m_normal);


	if (!wd->isDragging())
		wd->subEntityTraits().setTrueColor(m_eyescolor);		// Set the background true color.

	// Drawing circle of left eye
	wd->subEntityTraits().setSelectionMarker(kLeftEyeMark); // 2 == kLeftEyeMark
	wd->geometry().circle(leftEyeCenter(), m_eyesize, m_normal);

	// Drawing circle of right eye
	wd->subEntityTraits().setSelectionMarker(kRightEyeMark); // 3 == kRightEyeMark
	wd->geometry().circle(rightEyeCenter(), m_eyesize, m_normal);


	// Drawing arc of mouth
	if (!wd->isDragging())
		wd->subEntityTraits().setTrueColor(m_mouthcolor);		// Set the background true color.
	AcGePoint3d smilecen(mouthCenter() + offset),
		startpt(mouthLeft() + offset),
		endpt(mouthRight() + offset);
	AcGeVector3d startvec = startpt - smilecen,
		endvec = endpt - smilecen;
	double mouthangle = startvec.angleTo(endvec);
	// Give the eyes GS markers of 4.
	wd->subEntityTraits().setSelectionMarker(kMouthMark); // 4 == kMouthMark
	wd->geometry().circularArc(smilecen, mouthRadius(), m_normal, startvec, mouthangle, kAcGiArcChord);

	//Arc
	wd->subEntityTraits().setSelectionMarker(5);
	wd->subEntityTraits().setTrueColor(AcCmEntityColor(255, 0, 0));// Set the background true color.
	wd->geometry().text(smilecen + startvec, m_normal, -startvec, mouthRadius() / 2., mouthRadius() / 5., 0, m_TextField);



	return true;
}


Adesk::UInt32 utc_Smiley::subSetAttributes(AcGiDrawableTraits* traits)
{
	assertReadEnabled();
	return (AcDbEntity::subSetAttributes(traits));
}

