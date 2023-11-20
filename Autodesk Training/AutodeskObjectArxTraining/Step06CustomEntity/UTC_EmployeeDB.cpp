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
//----- UTC_EmployeeDB.cpp : Implementation of UTC_EmployeeDB
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "UTC_EmployeeDB.h"



//-----------------------------------------------------------------------------
Adesk::UInt32 UTC_EmployeeDB::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	UTC_EmployeeDB, AcDbEllipse,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, UTC_EMPLOYEEDB,
UTCSTEP06CUSTOMENTITYDBXAPP
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------

UTC_EmployeeDB::UTC_EmployeeDB() : AcDbObject()
{
	// TODO: do your initialization. 
	m_firstName = m_lastName = NULL;
	m_ID = 0;
	m_cube = 1;
}


UTC_EmployeeDB::~UTC_EmployeeDB () 
{


}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus UTC_EmployeeDB::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	////----- Save parent class information first.
	//Acad::ErrorStatus es =AcDbEllipse::dwgOutFields (pFiler) ;
	//if ( es != Acad::eOk )
	//	return (es) ;
	////----- Object version number needs to be saved first
	//if ( (es =pFiler->writeUInt32 (UTC_EmployeeDB::kCurrentVersionNumber)) != Acad::eOk )
	//	return (es) ;
	////----- Output params
	////.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus UTC_EmployeeDB::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbEllipse::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > UTC_EmployeeDB::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < UTC_EmployeeDB::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	return (pFiler->filerStatus ()) ;
}

//- Dxf Filing protocol
Acad::ErrorStatus UTC_EmployeeDB::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =AcDbEllipse::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("UTC_EmployeeDB")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (kDxfInt32, UTC_EmployeeDB::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus UTC_EmployeeDB::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =AcDbEllipse::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("UTC_EmployeeDB")) )
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
	if ( version > UTC_EmployeeDB::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < UTC_EmployeeDB::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while ( es == Acad::eOk && (es =pFiler->readResBuf (&rb)) == Acad::eOk ) {
		switch ( rb.restype ) 
		{
			case AcDb::kDxfXCoord:
				break;
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
Adesk::Boolean UTC_EmployeeDB::subWorldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;
	return (AcDbEllipse::subWorldDraw (mode)) ;
}


Adesk::UInt32 UTC_EmployeeDB::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return (AcDbEllipse::subSetAttributes (traits)) ;
}



Acad::ErrorStatus UTC_EmployeeDB::firstName(TCHAR*& firstName)
{
	assertReadEnabled();
	firstName = _tcsdup(m_firstName);
	return Acad::eOk;

}

Acad::ErrorStatus UTC_EmployeeDB::setLastName(const TCHAR* lastName)
{
	return Acad::ErrorStatus();
}

Acad::ErrorStatus UTC_EmployeeDB::lastName(TCHAR*& lastName)
{
	return Acad::ErrorStatus();
}

Acad::ErrorStatus UTC_EmployeeDB::setID(const Adesk::Int32 ID)
{
	return Acad::ErrorStatus();
}

Acad::ErrorStatus UTC_EmployeeDB::iD(Adesk::Int32& ID)
{
	return Acad::ErrorStatus();
}

Acad::ErrorStatus UTC_EmployeeDB::setCube(const Adesk::Int32 cube)
{
	return Acad::ErrorStatus();
}

Acad::ErrorStatus UTC_EmployeeDB::cube(Adesk::Int32& cube)
{
	return Acad::ErrorStatus();
}

Acad::ErrorStatus UTC_EmployeeDB::setFirstName(const TCHAR* firstName)
{

	assertWriteEnabled();
	if (m_firstName)
		free(m_firstName);
	m_firstName = _tcsdup(firstName);
	return Acad::eOk;

}


