//-----------------------------------------------------------------------------
//----- AdskTree.h : Declaration of the AdskTree
//-----------------------------------------------------------------------------
#pragma once

#ifdef STEP06CUSTENTDBX_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP
#endif

//-----------------------------------------------------------------------------
#include "dbmain.h"

//-----------------------------------------------------------------------------
class DLLIMPEXP AdskTree : public AcDbEntity
{

public:
	ACRX_DECLARE_MEMBERS(AdskTree);

protected:
	static Adesk::UInt32 kCurrentVersionNumber;

private:
	AcGePoint3d _basePoint;
	AcString _season;

	void BuildSubTree(AcGeLineSeg3d* pMainBranch, int level, AcGiWorldDraw* mode, Adesk::Boolean flower = Adesk::kFalse);

public:
	AdskTree();
	virtual ~AdskTree();

	// Sets the season status
	void setSeason(AcString season);

	// Sets the insertion point
	void setBasePoint(AcGePoint3d basePoint);

	//----- AcDbObject protocols
	//- Dwg Filing protocol
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);

	//----- AcDbEntity protocols
	//- Graphics protocol
protected:
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

	//- Grip points protocol
	virtual Acad::ErrorStatus subGetGripPoints(AcDbGripDataPtrArray& grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d& curViewDir, const int bitflags) const;
	virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData, const AcGeVector3d& offset, const int bitflags);
};

#ifdef STEP06CUSTENTDBX_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(AdskTree)
#endif
