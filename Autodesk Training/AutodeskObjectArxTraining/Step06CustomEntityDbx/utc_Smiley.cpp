
//-----------------------------------------------------------------------------
//----- utc_Smiley.cpp : Implementation of utc_Smiley
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "utc_Smiley.h"

#ifdef SMILEY_WITH_TEXT
const ACHAR utc_Smiley::mTextFieldValue[] = { _T("Text Sample") };
#endif

//-----------------------------------------------------------------------------
Adesk::UInt32 utc_Smiley::kCurrentVersionNumber =1 ;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	utc_Smiley, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, UTC_SMILEY,
UTCStep06CustEntDbxApp
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

//-----------------------------------------------------------------------------
utc_Smiley::utc_Smiley () : AcDbEntity () 
{
	m_normal.set(0, 0, 1);
	setCenter(AcGePoint3d(0, 0, 0));
	setRadius(1.0);
	m_eyesapart = 0.9;
	m_eyesheight = 0.4;
	m_eyesize = 0.15;

	AcGeVector3d vecstart(0.9 * sin(1.25 * kPi), 0.9 * cos(1.25 * kPi), 0),
		vecend(0.9 * cos(1.75 * kPi), 0.9 * sin(1.75 * kPi), 0),
		vecbottom(0, -1.0, 0);
	AcGePoint3d mouthcen(center());
	mouthcen.y += 0.4;

	setMouth(mouthcen + vecstart, mouthcen + vecbottom, mouthcen + vecend);

	m_facecolor.setRGB(255, 255, 0);
	m_eyescolor.setRGB(0, 0, 0);
	m_mouthcolor.setRGB(255, 0, 0);
	recordGraphicsModified();

#ifdef SMILEY_WITH_TEXT
	m_TextField = mTextFieldValue;
#endif

}

utc_Smiley::~utc_Smiley () 
{


}

