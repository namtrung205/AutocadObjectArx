// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- utc_Smiley.cpp : Implementation of utc_Smiley
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "utc_Smiley.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 utc_Smiley::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	utc_Smiley, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, UTC_SMILEY,
UTCSTEP05CUSTOBJDBXAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
utc_Smiley::utc_Smiley () : AcDbEntity () 
{


}

utc_Smiley::~utc_Smiley () 
{


}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus utc_Smiley::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (utc_Smiley::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus utc_Smiley::dwgInFields (AcDbDwgFiler *pFiler) 
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
	if(pFiler->readPoint3d(&center) == Acad::ErrorStatus::eOk)
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
	Adesk::UInt32 backColor = 0;
	if ((es = pFiler->readUInt32(&backColor)) != Acad::eOk)
		return (es);
	m_backcolor.setCOLORREF(backColor);

	recordGraphicsModified();
	return eOk;
}

//- Dxf Filing protocol
Acad::ErrorStatus utc_Smiley::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("utc_Smiley")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (kDxfInt32, utc_Smiley::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus utc_Smiley::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEntity::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("utc_Smiley")) )
		return (pFiler->filerStatus ()) ;
	//----- Object version number needs to be read first
	struct resbuf rb ;
	pFiler->readItem (&rb) ;
	if ( rb.restype != AcDb::kDxfInt32 ) {
		pFiler->pushBackItem () ;
		pFiler->setError (Acad::eInvalidDxfCode, _RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32) ;
		return (pFiler->filerStatus ()) ;
	}
	Adesk::UInt32 version =(Adesk::UInt32)rb.resval.rlong ;
	if ( version > utc_Smiley::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < utc_Smiley::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while ( es == Acad::eOk && (es =pFiler->readResBuf (&rb)) == Acad::eOk ) {
		switch ( rb.restype ) {
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
				pFiler->pushBackItem () ;
				es =Acad::eEndOfFile ;
				break ;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if ( es != Acad::eEndOfFile )
		return (Acad::eInvalidResBuf) ;

	return (pFiler->filerStatus ()) ;
}



//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean utc_Smiley::subWorldDraw (AcGiWorldDraw *mode) 
{
	assertReadEnabled () ;
	return (AcDbEntity::subWorldDraw (mode)) ;
}


Adesk::UInt32 utc_Smiley::subSetAttributes (AcGiDrawableTraits *traits) 
{
	assertReadEnabled () ;
	return (AcDbEntity::subSetAttributes (traits)) ;
}
