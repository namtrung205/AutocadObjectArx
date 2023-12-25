#include "stdafx.h"
#include "UtcGiWorldGeometry.h"
#include "UtilsString.h"

void UtcGiWorldGeometry::getModelToWorldTransform(AcGeMatrix3d& retMat) const
{
    retMat = AcGeMatrix3d();

}

void UtcGiWorldGeometry::getWorldToModelTransform(AcGeMatrix3d& retMat) const
{
    retMat = AcGeMatrix3d();
}

Adesk::Boolean UtcGiWorldGeometry::pushModelTransform(const AcGeVector3d& vNormal)
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::pushModelTransform(const AcGeMatrix3d& xMat)
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::popModelTransform()
{
    return Adesk::Boolean();
}

AcGeMatrix3d UtcGiWorldGeometry::pushPositionTransform(AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset)
{
    return AcGeMatrix3d();
}

AcGeMatrix3d UtcGiWorldGeometry::pushPositionTransform(AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset)
{
    return AcGeMatrix3d();
}

AcGeMatrix3d UtcGiWorldGeometry::pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents)
{
    return AcGeMatrix3d();
}

AcGeMatrix3d UtcGiWorldGeometry::pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents)
{
    return AcGeMatrix3d();
}

AcGeMatrix3d UtcGiWorldGeometry::pushOrientationTransform(AcGiOrientationTransformBehavior behavior)
{
    return AcGeMatrix3d();
}

Adesk::Boolean UtcGiWorldGeometry::circle(const AcGePoint3d& center, const double radius, const AcGeVector3d& normal) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::circle(const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::circularArc(const AcGePoint3d& center, const double radius, const AcGeVector3d& normal, const AcGeVector3d& startVector, const double sweepAngle, const AcGiArcType arcType = kAcGiArcSimple) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::circularArc(const AcGePoint3d& start, const AcGePoint3d& point, const AcGePoint3d& end, const AcGiArcType arcType = kAcGiArcSimple) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::polyline(const Adesk::UInt32 nbPoints, const AcGePoint3d* pVertexList, const AcGeVector3d* pNormal = NULL, Adesk::LongPtr lBaseSubEntMarker = -1) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::polyline(const AcGiPolyline& polylineObj) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::polyPolyline(Adesk::UInt32 nbPolylines, const AcGiPolyline* pPolylines) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::polygon(const Adesk::UInt32 nbPoints, const AcGePoint3d* pVertexList) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::polyPolygon(const Adesk::UInt32 numPolygonIndices, const Adesk::UInt32* numPolygonPositions, const AcGePoint3d* polygonPositions, const Adesk::UInt32* numPolygonPoints, const AcGePoint3d* polygonPoints, const AcCmEntityColor* outlineColors = NULL, const AcGiLineType* outlineTypes = NULL, const AcCmEntityColor* fillColors = NULL, const AcCmTransparency* fillOpacities = NULL) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::mesh(const Adesk::UInt32 rows, const Adesk::UInt32 columns, const AcGePoint3d* pVertexList, const AcGiEdgeData* pEdgeData = NULL, const AcGiFaceData* pFaceData = NULL, const AcGiVertexData* pVertexData = NULL, const bool bAutoGenerateNormals = true) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::shell(const Adesk::UInt32 nbVertex, const AcGePoint3d* pVertexList, const Adesk::UInt32 faceListSize, const Adesk::Int32* pFaceList, const AcGiEdgeData* pEdgeData = NULL, const AcGiFaceData* pFaceData = NULL, const AcGiVertexData* pVertexData = NULL, const resbuf* pResBuf = NULL, const bool bAutoGenerateNormals = true) const
{
    //float* point_data;

    acutPrintf(_T("Shell Invoke: \n"));

    for (unsigned int i = 0; i < nbVertex; ++i)
    {
        AcGePoint3d v = pVertexList[i];
        AcString pointString;

        Utils::String::PointToString(v, pointString);
        
        acutPrintf(pointString.constPtr());
        acutPrintf(_T("\n"));

    }

    std::string accessorIdIndices;
    std::string accessorIdPositions;

    m_pGltfExporter->CreateTriangleResources(accessorIdIndices, accessorIdPositions, nbVertex, pVertexList, faceListSize, pFaceList, pEdgeData, pFaceData, pVertexData, pResBuf, bAutoGenerateNormals);
    m_pGltfExporter->CreateTriangleEntities(accessorIdIndices, accessorIdPositions);





    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::text(const AcGePoint3d& position, const AcGeVector3d& normal, const AcGeVector3d& direction, const double height, const double width, const double oblique, const ACHAR* pMsg) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::text(const AcGePoint3d& position, const AcGeVector3d& normal, const AcGeVector3d& direction, const ACHAR* pMsg, const Adesk::Int32 length, const Adesk::Boolean raw, const AcGiTextStyle& pTextStyle) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::xline(const AcGePoint3d&, const AcGePoint3d&) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::ray(const AcGePoint3d&, const AcGePoint3d&) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::pline(const AcDbPolyline& lwBuf, Adesk::UInt32 fromIndex = 0, Adesk::UInt32 numSegs = 0) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::draw(AcGiDrawable*) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::image(const AcGiImageBGRA32& imageSource, const AcGePoint3d& position, const AcGeVector3d& u, const AcGeVector3d& v, TransparencyMode transparencyMode = kTransparency8Bit) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::rowOfDots(int count, const AcGePoint3d& start, const AcGeVector3d& step) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::ellipticalArc(const AcGePoint3d& center, const AcGeVector3d& normal, double majorAxisLength, double minorAxisLength, double startDegreeInRads, double endDegreeInRads, double tiltDegreeInRads, AcGiArcType arcType = kAcGiArcSimple) const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiWorldGeometry::pushClipBoundary(AcGiClipBoundary* pBoundary)
{
    return Adesk::Boolean();
}

void UtcGiWorldGeometry::popClipBoundary()
{
}

Adesk::Boolean UtcGiWorldGeometry::edge(const AcArray<AcGeCurve2d*>& edges) const
{
    return Adesk::Boolean();
}

void UtcGiWorldGeometry::setExtents(AcGePoint3d* pNewExtents) const
{
}
