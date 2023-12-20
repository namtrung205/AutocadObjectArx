#include "StdAfx.h"
#include "dbMultiModesGrip.h"
#include "TreeMultiModesGripPE.h"
#include "AdskTree.h"

ACRX_CONS_DEFINE_MEMBERS(AdskTreeMultiModesGripPE, AcDbMultiModesGripPE, 1);

AcDbMultiModesGripPE::GripMode AdskTreeMultiModesGripPE::_currentGripMode;
AcDbObjectId AdskTreeMultiModesGripPE::_lastModifiedEntId = AcDbObjectId::kNull;

AdskTreeMultiModesGripPE::AdskTreeMultiModesGripPE()
{
	// Default grip mode
	_currentGripMode.Mode = 0;
	_currentGripMode.DisplayString = AcString(_T("Spring"));
}

AdskTreeMultiModesGripPE::~AdskTreeMultiModesGripPE()
{
}

// Returns the possible grip modes
bool AdskTreeMultiModesGripPE::getGripModes(AcDbEntity* pThis, AcDbGripData* pGripData, AcArray<GripMode>& modes, unsigned int& curMode) const
{
	GripMode gripMode1;
	gripMode1.Mode = 0;
	gripMode1.DisplayString = AcString(_T("Spring"));
	gripMode1.ActionType = GripActionType::kCommand;
	gripMode1.CommandString = AcString(_T("ModeSwitchCmd "));

	modes.append(gripMode1);

	GripMode gripMode2;
	gripMode2.Mode = 1;
	gripMode2.DisplayString = AcString(_T("Winter"));
	gripMode2.ActionType = GripActionType::kCommand;
	gripMode2.CommandString = AcString(_T("ModeSwitchCmd "));

	modes.append(gripMode2);

	curMode = 0;

	return true;
}

// Gets the current mode identifier.
unsigned int AdskTreeMultiModesGripPE::mode(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return _currentGripMode.Mode;
}

// Return the current mode.
AcDbMultiModesGripPE::GripMode AdskTreeMultiModesGripPE::modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return _currentGripMode;
}

// Sets the current mode.
bool AdskTreeMultiModesGripPE::setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode)
{
	_currentGripMode.Mode = newMode;

	AcDbObjectId entId = pThis->id();
	AdskTree* pTree = AdskTree::cast(pThis);

	switch (newMode)
	{
	case 0:
		acutPrintf(ACRX_T("\nSpring season, growing leaves !"));

		_currentGripMode.DisplayString = AcString(_T("Spring"));
		pTree->setSeason(AcString(_T("Spring")));
		// For graphics update
		_lastModifiedEntId = pTree->id();

		break;

	case 1:
		acutPrintf(ACRX_T("\nWinter season, shedding leaves !"));

		_currentGripMode.DisplayString = AcString(_T("Winter"));
		pTree->setSeason(AcString(_T("Winter")));
		// For graphics update
		_lastModifiedEntId = pTree->id();

		break;
	}
	return true;
}

// Gets the grip type of a given grip.
AcDbMultiModesGripPE::GripType AdskTreeMultiModesGripPE::gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return AcDbMultiModesGripPE::GripType::kPrimary;
}

// To retrieve the objectId of the tree entity for graphics update
AcDbObjectId AdskTreeMultiModesGripPE::getLastModifiedEntId()
{
	return _lastModifiedEntId;
}

// resets current mode to default 
void AdskTreeMultiModesGripPE::reset(AcDbEntity* pThis)
{
	_currentGripMode.Mode = 0;
	_currentGripMode.DisplayString = AcString(_T("Spring"));
}