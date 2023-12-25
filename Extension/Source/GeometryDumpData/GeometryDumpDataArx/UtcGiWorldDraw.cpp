
#include "stdafx.h"
#include "UtcGiWorldDraw.h"


UtcGiWorldDraw::UtcGiWorldDraw()
{
    m_pTraits = new UtcGiSubEntityTraits();
    m_pGeom = new UtcGiWorldGeometry(m_pGltfExporter);
    m_pContext = new UtcGiContext();
}

UtcGiWorldDraw::UtcGiWorldDraw(MrGltfExporter* pGltfExporter)
{
    m_pGltfExporter = pGltfExporter;

    m_pTraits = new UtcGiSubEntityTraits();
    m_pGeom = new UtcGiWorldGeometry(m_pGltfExporter);
    m_pContext = new UtcGiContext();
}

AcGiRegenType UtcGiWorldDraw::regenType() const
{
    return AcGiRegenType::kAcGiShadedDisplay;
}

Adesk::Boolean UtcGiWorldDraw::regenAbort() const
{
    return Adesk::Boolean();
}

AcGiSubEntityTraits& UtcGiWorldDraw::subEntityTraits() const
{
    // TODO: insert return statement here
    return *m_pTraits;

}

AcGiGeometry* UtcGiWorldDraw::rawGeometry() const
{
    return nullptr;
}

Adesk::Boolean UtcGiWorldDraw::isDragging() const
{
    return Adesk::Boolean();
}

double UtcGiWorldDraw::deviation(const AcGiDeviationType, const AcGePoint3d&) const
{
    return 0.05;
}

Adesk::UInt32 UtcGiWorldDraw::numberOfIsolines() const
{
    return Adesk::UInt32();
}

AcGiContext* UtcGiWorldDraw::context()
{
    return m_pContext;
}

AcGiWorldGeometry& UtcGiWorldDraw::geometry() const
{
    // TODO: insert return statement here
    return *m_pGeom;
}
