#pragma once
#include "acgi.h"
#include "DemoGLTF/MrGltfExporter.h"

class UtcGiWorldGeometry: public AcGiWorldGeometry
{

private:
	MrGltfExporter* m_pGltfExporter;


public:
	UtcGiWorldGeometry(MrGltfExporter* pGltfExporter)
	{
		m_pGltfExporter = pGltfExporter;
	}

	~UtcGiWorldGeometry()
	{

	}

public:
	void SetGltfExporter(MrGltfExporter* pGltfExporter)
	{
		m_pGltfExporter = pGltfExporter;
	}



public:
	// Inherited via AcGiWorldGeometry
	virtual void getModelToWorldTransform(AcGeMatrix3d&) const override;
	virtual void getWorldToModelTransform(AcGeMatrix3d&) const override;
	virtual Adesk::Boolean pushModelTransform(const AcGeVector3d& vNormal) override;
	virtual Adesk::Boolean pushModelTransform(const AcGeMatrix3d& xMat) override;
	virtual Adesk::Boolean popModelTransform() override;
	virtual AcGeMatrix3d pushPositionTransform(AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset) override;
	virtual AcGeMatrix3d pushPositionTransform(AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset) override;
	virtual AcGeMatrix3d pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents) override;
	virtual AcGeMatrix3d pushScaleTransform(AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents) override;
	virtual AcGeMatrix3d pushOrientationTransform(AcGiOrientationTransformBehavior behavior) override;
	virtual Adesk::Boolean circle(const AcGePoint3d& center, const double radius, const AcGeVector3d& normal) const override;
	virtual Adesk::Boolean circle(const AcGePoint3d&, const AcGePoint3d&, const AcGePoint3d&) const override;
	virtual Adesk::Boolean circularArc(const AcGePoint3d& center, const double radius, const AcGeVector3d& normal, const AcGeVector3d& startVector, const double sweepAngle, const AcGiArcType arcType) const override;
	virtual Adesk::Boolean circularArc(const AcGePoint3d& start, const AcGePoint3d& point, const AcGePoint3d& end, const AcGiArcType arcType ) const override;
	virtual Adesk::Boolean polyline(const Adesk::UInt32 nbPoints, const AcGePoint3d* pVertexList, const AcGeVector3d* pNormal, Adesk::LongPtr lBaseSubEntMarker) const override;
	virtual Adesk::Boolean polyline(const AcGiPolyline& polylineObj) const override;
	virtual Adesk::Boolean polyPolyline(Adesk::UInt32 nbPolylines, const AcGiPolyline* pPolylines) const override;
	virtual Adesk::Boolean polygon(const Adesk::UInt32 nbPoints, const AcGePoint3d* pVertexList) const override;
	virtual Adesk::Boolean polyPolygon(const Adesk::UInt32 numPolygonIndices, const Adesk::UInt32* numPolygonPositions, const AcGePoint3d* polygonPositions, const Adesk::UInt32* numPolygonPoints, const AcGePoint3d* polygonPoints, const AcCmEntityColor* outlineColors, const AcGiLineType* outlineTypes, const AcCmEntityColor* fillColors, const AcCmTransparency* fillOpacities) const override;
	virtual Adesk::Boolean mesh(const Adesk::UInt32 rows, const Adesk::UInt32 columns, const AcGePoint3d* pVertexList, const AcGiEdgeData* pEdgeData , const AcGiFaceData* pFaceData, const AcGiVertexData* pVertexData, const bool bAutoGenerateNormals) const override;
	virtual Adesk::Boolean shell(const Adesk::UInt32 nbVertex, const AcGePoint3d* pVertexList, const Adesk::UInt32 faceListSize, const Adesk::Int32* pFaceList, const AcGiEdgeData* pEdgeData, const AcGiFaceData* pFaceData, const AcGiVertexData* pVertexData, const resbuf* pResBuf, const bool bAutoGenerateNormals) const override;
	virtual Adesk::Boolean text(const AcGePoint3d& position, const AcGeVector3d& normal, const AcGeVector3d& direction, const double height, const double width, const double oblique, const ACHAR* pMsg) const override;
	virtual Adesk::Boolean text(const AcGePoint3d& position, const AcGeVector3d& normal, const AcGeVector3d& direction, const ACHAR* pMsg, const Adesk::Int32 length, const Adesk::Boolean raw, const AcGiTextStyle& pTextStyle) const override;
	virtual Adesk::Boolean xline(const AcGePoint3d&, const AcGePoint3d&) const override;
	virtual Adesk::Boolean ray(const AcGePoint3d&, const AcGePoint3d&) const override;
	virtual Adesk::Boolean pline(const AcDbPolyline& lwBuf, Adesk::UInt32 fromIndex, Adesk::UInt32 numSegs) const override;
	virtual Adesk::Boolean draw(AcGiDrawable*) const override;
	virtual Adesk::Boolean image(const AcGiImageBGRA32& imageSource, const AcGePoint3d& position, const AcGeVector3d& u, const AcGeVector3d& v, TransparencyMode transparencyMode) const override;
	virtual Adesk::Boolean rowOfDots(int count, const AcGePoint3d& start, const AcGeVector3d& step) const override;
	virtual Adesk::Boolean ellipticalArc(const AcGePoint3d& center, const AcGeVector3d& normal, double majorAxisLength, double minorAxisLength, double startDegreeInRads, double endDegreeInRads, double tiltDegreeInRads, AcGiArcType arcType) const override;
	virtual Adesk::Boolean pushClipBoundary(AcGiClipBoundary* pBoundary) override;
	virtual void popClipBoundary() override;
	virtual Adesk::Boolean edge(const AcArray<AcGeCurve2d*>& edges) const override;
	virtual void setExtents(AcGePoint3d* pNewExtents) const override;
};

