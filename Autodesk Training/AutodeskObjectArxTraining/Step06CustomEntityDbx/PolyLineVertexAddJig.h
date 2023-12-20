#pragma once
#include "dbjig.h"

class PolyLineVertexAddJig : public AcEdJig
{
public:
	PolyLineVertexAddJig();
	~PolyLineVertexAddJig();
	PolyLineVertexAddJig(AcDbPolyline* pPoly, Adesk::UInt32 vertexToAdd);

	AcEdJig::DragStatus doIt();
	virtual DragStatus sampler();
	virtual Adesk::Boolean update();

	AcGePoint2d AddedVertex();

	virtual AcDbEntity* entity() const;

private:
	AcDbPolyline* m_pPoly;
	Adesk::UInt32 m_nVertexToAdd;

	AcGePoint3d vertexPointTemp;
	AcGePoint3d vertexPoint;

	Adesk::Boolean addNew;
};
