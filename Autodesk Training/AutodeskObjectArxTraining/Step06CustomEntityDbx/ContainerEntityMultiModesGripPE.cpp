#include "StdAfx.h"
#include "dbMultiModesGrip.h"
#include "ContainerEntityMultiModesGripPE.h"

#include "ContainerEntity.h"
#include "PolylineVertexAddJig.h"

ACRX_CONS_DEFINE_MEMBERS(AdskContainerEntityMultiModesGripPE, AcDbMultiModesGripPE, 1);

AcDbMultiModesGripPE::GripMode AdskContainerEntityMultiModesGripPE::_currentGripMode;

AdskContainerEntityMultiModesGripPE::AdskContainerEntityMultiModesGripPE()
{
	// Default grip mode
	_currentGripMode.Mode = 0;
	_currentGripMode.DisplayString = AcString(_T("Stretch Vertex"));
}

AdskContainerEntityMultiModesGripPE::~AdskContainerEntityMultiModesGripPE()
{
}

// Returns the possible grip modes
bool AdskContainerEntityMultiModesGripPE::getGripModes(AcDbEntity* pThis, AcDbGripData* pGripData, AcArray<GripMode>& modes, unsigned int& curMode) const
{
	// "Stretch Vertex" mode
	GripMode gripMode1;
	gripMode1.Mode = 0;
	gripMode1.DisplayString = AcString(_T("Stretch Vertex"));
	gripMode1.ActionType = AcDbMultiModesGripPE::kDragOn;

	modes.append(gripMode1);

	// "Add Vertex" mode
	GripMode gripMode2;
	gripMode2.Mode = 1;
	gripMode2.DisplayString = AcString(_T("Add Vertex"));
	gripMode2.ActionType = AcDbMultiModesGripPE::kImmediate;

	modes.append(gripMode2);

	// "Remove Vertex" mode to be available only if there are 
	// more than 2 vertices in the polyline.
	AdskContainerEntity* pContEnt = AdskContainerEntity::cast(pThis);
	if (pContEnt->m_pPolyline != NULL)
	{
		if (pContEnt->m_pPolyline->numVerts() > 2)
		{
			GripMode gripMode3;
			gripMode3.Mode = 2;
			gripMode3.DisplayString = AcString(_T("Remove Vertex"));
			gripMode3.ActionType = AcDbMultiModesGripPE::kImmediate;

			modes.append(gripMode3);
		}
	}

	// "Stretch Vertex" is the current mode
	curMode = 0;

	return true;
}

// Gets the current mode identifier.
unsigned int AdskContainerEntityMultiModesGripPE::mode(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return _currentGripMode.Mode;
}

// Return the current mode.
AcDbMultiModesGripPE::GripMode AdskContainerEntityMultiModesGripPE::modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return _currentGripMode;
}

// Sets the current mode.
bool AdskContainerEntityMultiModesGripPE::setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode)
{
	bool retStatus = true;

	_currentGripMode.Mode = newMode;

	AcDbObjectId entId = pThis->id();
	AdskContainerEntity* pContEnt = AdskContainerEntity::cast(pThis);
	pContEnt->m_pCurrentGripMode = newMode;

	switch (newMode)
	{
	case 0:
	{
		_currentGripMode.DisplayString = AcString(_T("Stretch Vertex"));
		break;
	}

	case 1:
	{
		_currentGripMode.DisplayString = AcString(_T("Add Vertex"));

		// Create a temporary copy of the embedded Polyline for jigging purposes
		AcDbPolyline* pPolyTemp = AcDbPolyline::cast(pContEnt->m_pPolyline->clone());

		MyGripAppData* pMyGripAppData = static_cast<MyGripAppData*>(pGripData->appData());
		if (pMyGripAppData != NULL)
		{
			PolyLineVertexAddJig* pPolyAddVertedJig = new PolyLineVertexAddJig(pPolyTemp, pMyGripAppData->m_GripNumber);
			AcEdJig::DragStatus status = pPolyAddVertedJig->doIt();
			if (status != AcEdJig::kCancel)
			{
				pContEnt->m_iVertexNumber = pMyGripAppData->m_GripNumber;
				pContEnt->m_NewVertexCoord = pPolyAddVertedJig->AddedVertex();
			}
			else
				retStatus = false; // Cancel setting the GripMode as the Jig was canceled 

			delete pPolyAddVertedJig;
		}

		break;
	}

	case 2:
	{
		_currentGripMode.DisplayString = AcString(_T("Remove Vertex"));

		MyGripAppData* pMyGripAppData = static_cast<MyGripAppData*>(pGripData->appData());
		if (pMyGripAppData != NULL)
		{
			pContEnt->m_iVertexNumber = pMyGripAppData->m_GripNumber;
		}
		break;
	}
	}

	return retStatus;
}

// Gets the grip type of a given grip.
AcDbMultiModesGripPE::GripType AdskContainerEntityMultiModesGripPE::gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const
{
	return AcDbMultiModesGripPE::kPrimary;
}

// resets current mode to default 
void AdskContainerEntityMultiModesGripPE::reset(AcDbEntity* pThis)
{
	_currentGripMode.Mode = 0;
	_currentGripMode.DisplayString = AcString(_T("Stretch Vertex"));
}