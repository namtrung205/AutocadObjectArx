//-----------------------------------------------------------------------------
//----- AdskTree.cpp : Implementation of AdskTree
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AdskTree.h"

//-----------------------------------------------------------------------------
Adesk::UInt32 AdskTree::kCurrentVersionNumber = 1;

//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS(
	AdskTree, AcDbEntity,
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent,
	AcDbProxyEntity::kNoOperation, ADSKTREE,
	ADSKMULTIMODEGRIPSIMPLESAMPLEAPP
	| Product Desc : A description for your object
	| Company : Your company name
	| WEB Address : Your company WEB site address
)

//-----------------------------------------------------------------------------
AdskTree::AdskTree() : AcDbEntity()
{
	_basePoint = AcGePoint3d::kOrigin;
	_season = AcString(_T("Spring"));
}

AdskTree::~AdskTree()
{
}

//-----------------------------------------------------------------------------
//----- AcDbObject protocols
//- Dwg Filing protocol
Acad::ErrorStatus AdskTree::dwgOutFields(AcDbDwgFiler * pFiler) const {
	assertReadEnabled();
	//----- Save parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dwgOutFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be saved first
	if ((es = pFiler->writeUInt32(AdskTree::kCurrentVersionNumber)) != Acad::eOk)
		return (es);

	//----- Output params
	pFiler->writePoint3d(_basePoint);

	return (pFiler->filerStatus());
}

Acad::ErrorStatus AdskTree::dwgInFields(AcDbDwgFiler * pFiler) {
	assertWriteEnabled();
	//----- Read parent class information first.
	Acad::ErrorStatus es = AcDbEntity::dwgInFields(pFiler);
	if (es != Acad::eOk)
		return (es);
	//----- Object version number needs to be read first
	Adesk::UInt32 version = 0;
	if ((es = pFiler->readUInt32(&version)) != Acad::eOk)
		return (es);
	if (version > AdskTree::kCurrentVersionNumber)
		return (Acad::eMakeMeProxy);

	//----- Read params
	pFiler->readPoint3d(&_basePoint);

	return (pFiler->filerStatus());
}


//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean AdskTree::subWorldDraw(AcGiWorldDraw * mode)
{
	assertReadEnabled();

	AcGeLineSeg3d mainBranch(_basePoint, AcGePoint3d(_basePoint.x, _basePoint.y + 10.0, _basePoint.z));
	AcDbLine* pLine1 = new AcDbLine(mainBranch.startPoint(), mainBranch.endPoint());
	mode->geometry().draw(pLine1);
	delete pLine1;

	int level = 0;
	BuildSubTree(&mainBranch, level, mode);

	return (AcDbEntity::subWorldDraw(mode));
}

void AdskTree::setBasePoint(AcGePoint3d basePoint)
{
	_basePoint = basePoint;
}

void AdskTree::setSeason(AcString season)
{
	_season = season;
}

void AdskTree::BuildSubTree(AcGeLineSeg3d * pMainBranch, int level, AcGiWorldDraw * mode, Adesk::Boolean flower)
{
	if (mode->isDragging() && level >= 2)
		return; // Light weight for dragging

	if (level >= 3)
	{
		if (_season == AcString(_T("Spring")))
		{
			AcDbCircle* pLeaf = new AcDbCircle(pMainBranch->endPoint(), AcGeVector3d::kZAxis, pMainBranch->length() * 0.2);
			if (flower)
				pLeaf->setColorIndex(1);
			else
				pLeaf->setColorIndex(2);
			mode->geometry().draw(pLeaf);
			delete pLeaf;
		}
		return;
	}

	int subLevel = level + 1;
	AcGePoint3d sp = AcGePoint3d::kOrigin;
	AcGePoint3d ep = AcGePoint3d::kOrigin;
	AcGeInterval intrvl;
	pMainBranch->getInterval(intrvl, sp, ep);
	double len = pMainBranch->length();

	AcGePoint3dArray pts;
	pMainBranch->getSamplePoints(5, pts);

	const double PI = 3.1415926535897932385;
	int cnt = 1;
	if (level == 0)
		cnt = 2;
	for (; cnt < 5; cnt++)
	{
		AcGeVector3d dir = pMainBranch->direction().normalize();
		AcGePoint3d refPt1 = pts[cnt];

		if (cnt == 4)
		{
			AcGePoint3d refPt2 = refPt1 + (len * 0.5) * dir;

			AcGeLineSeg3d branch1(refPt1, refPt2);
			AcDbLine* pBranchLine1 = new AcDbLine(refPt1, refPt2);
			mode->geometry().draw(pBranchLine1);
			delete pBranchLine1;
			BuildSubTree(&branch1, subLevel, mode, Adesk::kTrue);
		}
		else
		{
			AcGePoint3d refPt2 = refPt1 + (len * 0.5) * dir.transformBy(AcGeMatrix3d::rotation(PI * 0.25, AcGeVector3d::kZAxis, refPt1));

			AcGeLineSeg3d branch1(refPt1, refPt2);
			AcDbLine* pBranchLine1 = new AcDbLine(refPt1, refPt2);
			mode->geometry().draw(pBranchLine1);
			delete pBranchLine1;
			BuildSubTree(&branch1, subLevel, mode);

			dir = pMainBranch->direction().normalize();
			refPt2 = refPt1 + (len * 0.5) * dir.transformBy(AcGeMatrix3d::rotation(-PI * 0.25, AcGeVector3d::kZAxis, refPt1));
			AcGeLineSeg3d branch2(refPt1, refPt2);
			AcDbLine* pBranchLine2 = new AcDbLine(refPt1, refPt2);
			mode->geometry().draw(pBranchLine2);
			delete pBranchLine2;
			BuildSubTree(&branch2, subLevel, mode);
		}
	}
}

Acad::ErrorStatus AdskTree::subGetGripPoints(AcDbGripDataPtrArray & grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d & curViewDir, const int bitflags) const
{
	assertReadEnabled();

	AcDbGripData* pGripData = new AcDbGripData();
	pGripData->setGripPoint(_basePoint);
	grips.append(pGripData);

	return Acad::eOk;
}

Acad::ErrorStatus AdskTree::subMoveGripPointsAt(
	const AcDbVoidPtrArray & gripAppData, const AcGeVector3d & offset,
	const int bitflags)
{
	assertWriteEnabled();

	_basePoint += offset;

	return Acad::eOk;
}

Acad::ErrorStatus AdskTree::subTransformBy(const AcGeMatrix3d & xform)
{
	assertWriteEnabled();
	_basePoint.transformBy(xform);
	return (AcDbEntity::subTransformBy(xform));
}

