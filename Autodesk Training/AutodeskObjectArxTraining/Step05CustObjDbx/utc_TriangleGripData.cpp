#include "StdAfx.h"
#include "utc_TriangleGripData.h"
#include "dbMultiModesGrip.h"
#include "utc_Smiley.h"


ACRX_CONS_DEFINE_MEMBERS(utc_TriangleGripData, AcDbMultiModesGripPE, 1);

AcDbMultiModesGripPE::GripMode utc_TriangleGripData::_currentGripMode;
AcDbObjectId utc_TriangleGripData::_lastModifiedEntId = AcDbObjectId::kNull;

utc_TriangleGripData::utc_TriangleGripData()
{
	// Default grip mode
	_currentGripMode.Mode = 0;
	_currentGripMode.DisplayString = AcString(L"Spring");
}

utc_TriangleGripData::~utc_TriangleGripData()
{
}

// Returns the possible grip modes
bool utc_TriangleGripData::getGripModes(AcDbEntity* pThis, AcDbGripData* pGripData, AcArray<GripMode>& modes, unsigned int& curMode) const
{
	GripMode gripMode1;
	gripMode1.Mode = 0;
	gripMode1.DisplayString = AcString(L"Spring");
	gripMode1.ActionType = GripActionType::kCommand;
	gripMode1.CommandString = AcString(L"ModeSwitchCmd ");

	modes.append(gripMode1);

	GripMode gripMode2;
	gripMode2.Mode = 1;
	gripMode2.DisplayString = AcString(L"Winter");
	gripMode2.ActionType = GripActionType::kCommand;
	gripMode2.CommandString = AcString(L"ModeSwitchCmd ");

	modes.append(gripMode2);

	curMode = 0;

	return true;
}

// Gets the current mode identifier.
unsigned int utc_TriangleGripData::mode(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return _currentGripMode.Mode;
}

// Return the current mode.
AcDbMultiModesGripPE::GripMode utc_TriangleGripData::modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return _currentGripMode;
}

// Sets the current mode.
bool utc_TriangleGripData::setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode)
{
	_currentGripMode.Mode = newMode;

	AcDbObjectId entId = pThis->id();
	utc_Smiley* pSmile = utc_Smiley::cast(pThis);

	switch (newMode)
	{
	case 0:
		acutPrintf(ACRX_T("\nSpring season, growing leaves !"));

		_currentGripMode.DisplayString = AcString(L"Spring");
		//pTree->setSeason(AcString(L"Spring"));
		// For graphics update
		//_lastModifiedEntId = pTree->id();

		break;

	case 1:
		acutPrintf(ACRX_T("\nWinter season, shedding leaves !"));

		_currentGripMode.DisplayString = AcString(L"Happy");
		pSmile->setEmo(Emo::kHappy);
		// For graphics update
		_lastModifiedEntId = pSmile->id();

		break;
	}
	return true;
}

// Gets the grip type of a given grip.
AcDbMultiModesGripPE::GripType utc_TriangleGripData::gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return AcDbMultiModesGripPE::GripType::kPrimary;
}

// To retrieve the objectId of the tree entity for graphics update
AcDbObjectId utc_TriangleGripData::getLastModifiedEntId()
{
	return _lastModifiedEntId;
}

// resets current mode to default 
void utc_TriangleGripData::reset(AcDbEntity* pThis)
{
	_currentGripMode.Mode = 0;
	_currentGripMode.DisplayString = AcString(L"Spring");
}