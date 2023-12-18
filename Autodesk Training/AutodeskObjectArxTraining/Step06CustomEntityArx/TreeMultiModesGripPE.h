#pragma once

#include "dbMultiModesGrip.h"


class AdskTreeMultiModesGripPE : public AcDbMultiModesGripPE
{
private:
	static AcDbMultiModesGripPE::GripMode _currentGripMode;
	static AcDbObjectId _lastModifiedEntId;

public:
	ACRX_DECLARE_MEMBERS(AdskTreeMultiModesGripPE);

	AdskTreeMultiModesGripPE();
	~AdskTreeMultiModesGripPE();
	static AcDbObjectId getLastModifiedEntId();

	virtual bool getGripModes(AcDbEntity* pThis, AcDbGripData* pGripData, AcArray<GripMode>& modes, unsigned int& curMode) const;
	virtual unsigned int mode(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual AcDbMultiModesGripPE::GripMode modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual bool setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode);
	virtual AcDbMultiModesGripPE::GripType gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual void reset(AcDbEntity* pThis);
};
