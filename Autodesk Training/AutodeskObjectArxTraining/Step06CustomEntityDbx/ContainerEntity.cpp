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
//----- ontainerEntity.cpp : Implementation of ContainerEntity
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "ContainerEntity.h"


//-----------------------------------------------------------------------------
Adesk::UInt32 AdskContainerEntity::kCurrentVersionNumber = 1;

ACRX_NO_CONS_DEFINE_MEMBERS(MyGripAppData, AcDbObject);

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS(
	AdskContainerEntity, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
	AcDbProxyEntity::kNoOperation, ADSKMYPLINE,
	ADSKMULTIMODEGRIPSAMPLEAPP
	| Product Desc : A description for your object
	| Company : Your company name
	| WEB Address : Your company WEB site address
)

//-----------------------------------------------------------------------------
AdskContainerEntity::AdskContainerEntity() : AcDbEntity()
{
	m_pPolyline = NULL;
	m_pCurrentGripMode = 0;
	m_iVertexNumber = 0;
}

AdskContainerEntity::~AdskContainerEntity()
{
	if (m_pPolyline)
	{
		delete m_pPolyline;
		m_pPolyline = 0;
	}
}

Acad::ErrorStatus AdskContainerEntity::dwgInFields(AcDbDwgFiler * pFiler)
{
	assertWriteEnabled();

	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dwgInFields(pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number needs to be read first
	Adesk::UInt32 version = 0;
	if ((es = pFiler->readUInt32(&version)) != Acad::eOk)
		return (es);

	if (version > AdskContainerEntity::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);

	//----- Read params

	Adesk::UInt32 numVerts = 0;
	pFiler->readUInt32(&numVerts);

	AcGePoint3dArray points;
	for (int i = 0; i < numVerts; i++)
	{
		AcGePoint3d pt;
		pFiler->readPoint3d(&pt);
		points.append(pt);
	}

	if (m_pPolyline)
	{
		delete m_pPolyline;
		m_pPolyline = 0;
	}

	m_pPolyline = new AcDbPolyline(numVerts);
	m_pPolyline->setDatabaseDefaults();

	for (int i = 0; i < numVerts; i++)
	{
		AcGePoint3d pt(points[i]);
		m_pPolyline->addVertexAt(i, AcGePoint2d(pt.x, pt.y));
	}

	//Return
	return (pFiler->filerStatus());
}


Acad::ErrorStatus AdskContainerEntity::dwgOutFields(AcDbDwgFiler * pFiler) const
{
	assertReadEnabled();

	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dwgOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);

	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(AdskContainerEntity::kCurrentVersionNumber)) != Acad::eOk)
		return (es);

	//----- Output params
	if (m_pPolyline)
	{
		Adesk::UInt32 numVerts = m_pPolyline->numVerts();

		pFiler->writeUInt32(numVerts);

		for (int i = 0; i < numVerts; i++)
		{
			AcGePoint3d pt;
			m_pPolyline->getPointAt(i, pt);
			pFiler->writePoint3d(pt);
		}
	}

	// Return
	return (pFiler->filerStatus());
}

Adesk::Boolean AdskContainerEntity::subWorldDraw(AcGiWorldDraw * mode)
{
	assertReadEnabled();

	if (m_pPolyline)
		mode->geometry().pline(*m_pPolyline);

	return (AcDbEntity::subWorldDraw(mode));
}

Acad::ErrorStatus AdskContainerEntity::subGetGripPoints(AcDbGripDataPtrArray & grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d & curViewDir, const int bitflags) const
{
	assertReadEnabled();

	if (m_pPolyline)
	{
		Adesk::UInt32 numVerts = m_pPolyline->numVerts();
		for (int i = 0; i < numVerts; i++)
		{
			AcGePoint3d pt;
			m_pPolyline->getPointAt(i, pt);

			AcDbGripData* pGripData = new AcDbGripData();
			pGripData->setAppData(new MyGripAppData(i));
			pGripData->setGripPoint(pt);
			grips.append(pGripData);
		}
	}
	return Acad::eOk;
}

Acad::ErrorStatus AdskContainerEntity::subMoveGripPointsAt(const AcDbVoidPtrArray & gripAppData, const AcGeVector3d & offset, const int bitflags)
{
	assertWriteEnabled();

	if (m_pPolyline)
	{
		switch (m_pCurrentGripMode)
		{
		case 0: // Stretch 
		{
			for (int i = 0; i < gripAppData.length(); i++)
			{
				MyGripAppData* pMyGripAppData = static_cast<MyGripAppData*>(gripAppData.at(i));
				if (pMyGripAppData != NULL)
				{
					int num = pMyGripAppData->m_GripNumber;

					AcGePoint3d pt;
					m_pPolyline->getPointAt(num, pt);

					AcGeMatrix3d mat = AcGeMatrix3d::kIdentity;
					mat = mat.translation(offset);

					pt = pt.transformBy(mat);

					m_pPolyline->setPointAt(num, AcGePoint2d(pt.x, pt.y));
				}
			}
			break;
		}

		case 1: // Add Vertex
		{
			m_pPolyline->addVertexAt(m_iVertexNumber + 1, AcGePoint2d(m_NewVertexCoord.x, m_NewVertexCoord.y));

			m_pCurrentGripMode = 0; // Reset to default GripMode
			break;
		}

		case 2: // Remove Vertex
		{
			if (m_iVertexNumber < m_pPolyline->numVerts())
				m_pPolyline->removeVertexAt(m_iVertexNumber);

			m_pCurrentGripMode = 0; // Reset to default GripMode
			break;
		}
		}
	}
	return Acad::eOk;
}

Acad::ErrorStatus AdskContainerEntity::subTransformBy(const AcGeMatrix3d & xform)
{
	assertWriteEnabled();

	if (m_pPolyline)
		m_pPolyline->transformBy(xform);

	return (AcDbEntity::subTransformBy(xform));
}

