#include "DA_LayerCommands.h"

void CD_CreateNewLayer()
{
	AcDbLayerTable* pLayerTbl = NULL;
	// Get the current Database
	AcDbDatabase* pDB = acdbHostApplicationServices()->workingDatabase();

	// Get the LayerTable for write because we will create a new entry
	pDB->getSymbolTable(pLayerTbl, AcDb::kForWrite);

	// Check if the layer is already there
	if (!pLayerTbl->has(_T("MYLAYER"))) {

		// Instantiate a new object and set its properties
		AcDbLayerTableRecord* pLayerTblRcd = new AcDbLayerTableRecord;
		pLayerTblRcd->setName(_T("MYLAYER"));
		pLayerTblRcd->setIsFrozen(0); // layer set to THAWED
		pLayerTblRcd->setIsOff(0); // layer set to ON
		pLayerTblRcd->setIsLocked(0); // layer un-locked
		AcCmColor color;
		color.setColorIndex(7); // set layer color to white
		pLayerTblRcd->setColor(color);

		// Now, add the new layer to its container
		pLayerTbl->add(pLayerTblRcd);

		// Close the new layer (DON'T DELETE IT)
		pLayerTblRcd->close();

		// Close the container
		pLayerTbl->close();
	}
	else {
		// If our layer is already there, just close the container and continue
		pLayerTbl->close();
		acutPrintf(_T("\nMYLAYER already exists"));
	}

}