#pragma once
#include "dbgrip.h"

#include "dbMultiModesGrip.h"

class utc_TriangleGripData : public AcDbMultiModesGripPE
{

private:
	static AcDbMultiModesGripPE::GripMode _currentGripMode;
	static AcDbObjectId _lastModifiedEntId;

public:
	ACRX_DECLARE_MEMBERS(utc_TriangleGripData);

	utc_TriangleGripData();
	~utc_TriangleGripData();
	static AcDbObjectId getLastModifiedEntId();

	virtual bool getGripModes(AcDbEntity* pThis, AcDbGripData* pGripData, AcArray<GripMode>& modes, unsigned int& curMode) const;
	virtual unsigned int mode(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual AcDbMultiModesGripPE::GripMode modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual bool setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode);
	virtual AcDbMultiModesGripPE::GripType gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual void reset(AcDbEntity* pThis);
};
