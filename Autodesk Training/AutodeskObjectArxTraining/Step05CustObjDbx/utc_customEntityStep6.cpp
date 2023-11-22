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
//----- utc_customEntityStep6.cpp : Implementation of utc_customEntityStep6
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "utc_customEntityStep6.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 utc_customEntityStep6::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	utc_customEntityStep6, AcDbEllipse,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, UTC_CUSTOMENTITYSTEP6,
UTCSTEP05CUSTOBJDBXAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
utc_customEntityStep6::utc_customEntityStep6 () : AcDbEllipse(AcGePoint3d(), AcGeVector3d(0, 0, 1), AcGeVector3d(1, 0, 0), 1)
{
	// TODO: do your initialization. 
	m_firstName = m_lastName = NULL;

}

utc_customEntityStep6::~utc_customEntityStep6 () {
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus utc_customEntityStep6::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEllipse::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (utc_customEntityStep6::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	Adesk::Int32 nId;
	if(iD(nId) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeInt32(nId);
	}

	Adesk::Int32 nCube;
	if (cube(nCube) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeInt32(nCube);
	}

	TCHAR* sFirstName;
	if (firstName(sFirstName) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeString(sFirstName);
	}

	TCHAR* sLastName;
	if (lastName(sLastName) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeString(sLastName);
	}

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus utc_customEntityStep6::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEllipse::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > utc_customEntityStep6::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < utc_customEntityStep6::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	//Need to write custom data
	Adesk::Int32 Id = 0;
	if ((es = pFiler->readInt32(&Id)) != Acad::eOk)
		return (es);
	setID(Id);

	Adesk::Int32 cube = 0;
	if ((es = pFiler->readInt32(&cube)) != Acad::eOk)
		return (es);
	setCube(cube);

	AcString firstName;
	if ((es = pFiler->readString(firstName)) != Acad::eOk)
		return (es);
	setFirstName(firstName);

	AcString lastName;
	if ((es = pFiler->readString(lastName)) != Acad::eOk)
		return (es);
	setLastName(lastName);

	return (pFiler->filerStatus ()) ;
}

//- Dxf Filing protocol
Acad::ErrorStatus utc_customEntityStep6::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEllipse::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("utc_customEntityStep6")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (kDxfInt32, utc_customEntityStep6::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....
	Adesk::Int32 nId;
	if (iD(nId) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeInt32(AcDb::kDxfInt32, nId);

	}

	Adesk::Int32 nCube;
	if (cube(nCube) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeInt32(AcDb::kDxfInt32, nCube);
	}

	TCHAR* sFirstName;
	if (firstName(sFirstName) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeString(AcDb::kDxfXTextString, sFirstName);
	}

	TCHAR* sLastName;
	if (lastName(sLastName) == Acad::ErrorStatus::eOk)
	{
		pFiler->writeString(AcDb::kDxfXTextString, sLastName);
	}

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus utc_customEntityStep6::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEllipse::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("utc_customEntityStep6")) )
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
	if ( version > utc_customEntityStep6::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < utc_customEntityStep6::kCurrentVersionNumber )
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
Adesk::Boolean utc_customEntityStep6::subWorldDraw (AcGiWorldDraw * pWd) {
	assertReadEnabled () ;

	pWd->subEntityTraits().setFillType(kAcGiFillAlways);
	AcGePoint3d m_points[3];
	m_points[0] = AcGePoint3d(0, 0, 0);
	m_points[1] = AcGePoint3d(1, 0, 0);
	m_points[2] = AcGePoint3d(1, 1, 0);
	pWd->geometry().polygon(3, m_points);
	pWd->subEntityTraits().setFillType(kAcGiFillNever);
	pWd->geometry().circle(m_points[0], m_points[1], m_points[2]);

	//Draw solid with yellow 
	pWd->subEntityTraits().setColor(2);
	AcDb3dSolid* pSolid = new AcDb3dSolid();

	pSolid->createBox(1, 1, 1);
	pSolid->worldDraw(pWd);
	
	delete(pSolid);
	pSolid = NULL;
	

	return (AcDbEllipse::subWorldDraw (pWd)) ;
}


Adesk::UInt32 utc_customEntityStep6::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (AcDbEllipse::subSetAttributes (traits)) ;
}



Acad::ErrorStatus utc_customEntityStep6::firstName(TCHAR*& firstName) const
{
	assertReadEnabled();
	firstName = _tcsdup(m_firstName);
	return Acad::eOk;

}

Acad::ErrorStatus utc_customEntityStep6::setFirstName(const TCHAR* firstName)
{

	assertWriteEnabled();
	if (m_firstName)
		free(m_firstName);
	m_firstName = _tcsdup(firstName);
	return Acad::eOk;

}



Acad::ErrorStatus utc_customEntityStep6::lastName(TCHAR*& lastName) const
{
	assertReadEnabled();
	lastName = _tcsdup(m_lastName);
	return Acad::eOk;

}

Acad::ErrorStatus utc_customEntityStep6::setLastName(const TCHAR* lastName)
{

	assertWriteEnabled();
	if (m_lastName)
		free(m_lastName);
	m_lastName = _tcsdup(lastName);
	return Acad::eOk;

}



Acad::ErrorStatus utc_customEntityStep6::cube(Adesk::Int32& cube)  const
{
	assertReadEnabled();
	cube = m_cube;
	return Acad::eOk;

}

Acad::ErrorStatus utc_customEntityStep6::setCube(const Adesk::Int32 cube)
{
	assertWriteEnabled();
	m_cube = cube;
	return Acad::eOk;

}



Acad::ErrorStatus utc_customEntityStep6::iD(Adesk::Int32& id)  const
{
	assertReadEnabled();
	id = m_ID;
	return Acad::eOk;

}

Acad::ErrorStatus utc_customEntityStep6::setID(const Adesk::Int32 id)
{
	assertWriteEnabled();
	m_ID = id;
	return Acad::eOk;

}

