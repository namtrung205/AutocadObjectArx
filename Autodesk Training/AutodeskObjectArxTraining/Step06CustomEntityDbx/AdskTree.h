//-----------------------------------------------------------------------------
//----- AdskTree.h : Declaration of the AdskTree
//-----------------------------------------------------------------------------
#pragma once

#ifdef STEP06CUSTENTDBX_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
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
