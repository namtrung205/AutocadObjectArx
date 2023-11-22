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
//----- utc_Smiley.h : Declaration of the utc_Smiley
//-----------------------------------------------------------------------------
#pragma once

#ifdef STEP05CUSTOBJDBX_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "dbmain.h"
#include "gearc3d.h"
#define SMILEY_WITH_TEXT

//-----------------------------------------------------------------------------
class DLLIMPEXP utc_Smiley : public AcDbEntity {

	// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------
//fields:
private:
	AcGeVector3d    m_normal;            // smiley normal vector
	AcGeCircArc3d   m_facecircle;        // smiley face
	AcGeCircArc3d   m_moutharc;          // smiley mouth arc (not written out)
	double          m_eyesapart;         // smiley eyes apart
	double          m_eyesheight;        // smiley eyes height
	double          m_eyesize;           // smiley eyes size
	AcCmEntityColor m_backcolor;

#ifdef SMILEY_WITH_TEXT
	static const ACHAR mTextFieldValue[];
	AcString m_TextField;
#endif

protected:
	void ensureRadiusMouth();
	void ensureRadiusEyes();

public:
	/** Description:
	Enumeration for Smiley GS mark type.
	*/
	enum gsMarkType
	{
		/** Description:
		No GS mark.
		*/
		kNone = 0,

		/** Description:
		GS mark of smiley face.
		*/
		kFaceMark = 1,

		/** Description:
		GS mark of left smiley eye.
		*/
		kLeftEyeMark = kFaceMark + 1,

		/** Description:
		GS mark of right smiley eye.
		*/
		kRightEyeMark = kLeftEyeMark + 1,

		/** Description:
		GS mark of smiley mouth.
		*/
		kMouthMark = kRightEyeMark + 1
	};

//----------------
//Public zone

public:
	ACRX_DECLARE_MEMBERS(utc_Smiley) ;


protected:
	static Adesk::UInt32 kCurrentVersionNumber ;

public:
	utc_Smiley () ;
	virtual ~utc_Smiley () ;

	//----- AcDbObject protocols
	//- Dwg Filing protocol
	virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const ;
	virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) ;

	//- Dxf Filing protocol
	virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler *pFiler) const ;
	virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler *pFiler) ;

	//----- AcDbEntity protocols
	//- Graphics protocol
protected:
	virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode) ;
	virtual Adesk::UInt32 subSetAttributes (AcGiDrawableTraits *traits) ;


public:

//
// Smiley property functions
//
	virtual AcCmEntityColor backColor()	const;		// smiley back color
	virtual void setBackColor(const AcCmEntityColor& color);

	virtual AcGeVector3d normal() const;			// smiley normal
	virtual void setNormal(const AcGeVector3d v);

	virtual AcGePoint3d center() const;				// smiley center
	virtual void setCenter(const AcGePoint3d c);

	virtual double radius() const;					// smiley radius
	virtual void setRadius(const double r);

	virtual double eyesApart() const;				// eyes apart
	virtual void setEyesApart(const double a);

	virtual double eyesHeight() const;				// eyes height
	virtual void setEyesHeight(const double h);

	virtual double eyeSize() const;					// eyes size
	virtual void setEyeSize(const double s);

	virtual AcGePoint3d leftEyeCenter() const;		// center of left eye
	virtual AcGePoint3d rightEyeCenter() const;		// center of right eye

	virtual double mouthRadius() const;				// radius of mouth arc
	virtual AcGePoint3d mouthCenter() const;		// center of mouth arc
	virtual AcGePoint3d mouthLeft() const;			// left point of mouth arc
	virtual AcGePoint3d mouthRight() const;			// right point of mouth arc
	virtual AcGePoint3d mouthBottom() const;		// bottom point of mouth arc
	// whole mouth
	virtual void setMouth(const AcGePoint3d& left, const AcGePoint3d& bottom, const AcGePoint3d& right);
	void moveMouthToPoint(const AcGePoint3d point);




} ;

#ifdef STEP05CUSTOBJDBX_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(utc_Smiley)
#endif

#define UTC_SMILEY_DBXSERVICE _T("UTC_SMILEY_DBXSERVICE")