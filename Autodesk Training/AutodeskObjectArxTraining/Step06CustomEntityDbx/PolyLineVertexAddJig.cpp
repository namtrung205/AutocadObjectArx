#include "StdAfx.h"
#include "PolyLineVertexAddJig.h"

PolyLineVertexAddJig::PolyLineVertexAddJig() :AcEdJig()
{
	m_pPoly = NULL;
	vertexPointTemp = AcGePoint3d::kOrigin;
	vertexPoint = AcGePoint3d::kOrigin;
	addNew = Adesk::kTrue;
}

PolyLineVertexAddJig::PolyLineVertexAddJig(AcDbPolyline* pPoly, Adesk::UInt32 vertexToAdd)
{
	m_pPoly = pPoly;
	m_nVertexToAdd = vertexToAdd;
	vertexPointTemp = AcGePoint3d::kOrigin;
	vertexPoint = AcGePoint3d::kOrigin;
	addNew = Adesk::kTrue;
}

PolyLineVertexAddJig::~PolyLineVertexAddJig()
{
	if (m_pPoly)
	{
		delete m_pPoly;
		m_pPoly = NULL;
	}
}

AcEdJig::DragStatus PolyLineVertexAddJig::doIt()
{
	AcEdJig::DragStatus stat = AcEdJig::kCancel;

	if (m_pPoly)
	{
		setDispPrompt(ACRX_T("\n Select vertex point : "));
		stat = drag();
	}

	return stat;
}

AcEdJig::DragStatus PolyLineVertexAddJig::sampler()
{
	DragStatus stat;
	setUserInputControls((UserInputControls)
		(AcEdJig::kAccept3dCoordinates
			| AcEdJig::kNoNegativeResponseAccepted
			| AcEdJig::kNoZeroResponseAccepted));

	stat = acquirePoint(vertexPoint);
	if (vertexPointTemp != vertexPoint)
		vertexPointTemp = vertexPoint;
	else if (stat == AcEdJig::kNormal)
		return AcEdJig::kNoChange;

	return stat;
}

Adesk::Boolean PolyLineVertexAddJig::update()
{
	if (m_pPoly)
	{
		if (addNew)
		{
			m_pPoly->addVertexAt(m_nVertexToAdd + 1, AcGePoint2d(vertexPoint.x, vertexPoint.y));
		}
		else
		{
			if (m_nVertexToAdd < m_pPoly->numVerts())
				m_pPoly->setPointAt(m_nVertexToAdd + 1, AcGePoint2d(vertexPoint.x, vertexPoint.y));
		}
	}

	if (addNew)
		addNew = Adesk::kFalse;

	return Adesk::kTrue;
}

AcDbEntity* PolyLineVertexAddJig::entity() const
{
	return m_pPoly;
}

AcGePoint2d PolyLineVertexAddJig::AddedVertex()
{
	return AcGePoint2d(vertexPoint.x, vertexPoint.y);
}
