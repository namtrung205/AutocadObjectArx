#pragma once
#include "acgi.h"
#include "UtcGiSubEntityTraits.h"
#include <UtcGiWorldGeometry.h>
#include "UtcGiContext.h"
class UtcGiWorldDraw: public AcGiWorldDraw
{
private:
	UtcGiSubEntityTraits* m_pTraits;
	UtcGiWorldGeometry* m_pGeom;
	AcGiRegenType m_regenType;
	UtcGiContext* m_pContext;

	//Exporter
	MrGltfExporter* m_pGltfExporter;

public:
	UtcGiWorldDraw();

	UtcGiWorldDraw(MrGltfExporter* pGltfExporter);

	~UtcGiWorldDraw()
	{

	}

	// Inherited via AcGiWorldDraw
	virtual AcGiRegenType regenType() const override;
	virtual Adesk::Boolean regenAbort() const override;
	virtual AcGiSubEntityTraits& subEntityTraits() const override;
	virtual AcGiGeometry* rawGeometry() const override;
	virtual Adesk::Boolean isDragging() const override;
	virtual double deviation(const AcGiDeviationType, const AcGePoint3d&) const override;
	virtual Adesk::UInt32 numberOfIsolines() const override;
	virtual AcGiContext* context() override;
	virtual AcGiWorldGeometry& geometry() const override;


public:
	void SetGltfExporter(MrGltfExporter* pGltfExporter)
	{
		m_pGltfExporter = pGltfExporter;
		if(m_pGeom!=nullptr)
		{
			m_pGeom->SetGltfExporter(m_pGltfExporter);
		}
	}

};

