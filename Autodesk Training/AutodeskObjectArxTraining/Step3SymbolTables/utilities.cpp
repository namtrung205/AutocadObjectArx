#include "stdafx.h"
#include "utilities.h"


namespace UTILS
{
	Acad::ErrorStatus createLayer(const TCHAR* layerName, AcDbObjectId& layerId)
	{
		//Check name exists
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		if (pDb != NULL)
		{

			AcDbLayerTable* pDbLayerTable = NULL;
			pDb->getLayerTable(pDbLayerTable, AcDb::kForRead);
			if (pDbLayerTable != NULL)
			{
				AcDbObjectId recordId;
				if (pDbLayerTable->getAt(layerName, recordId, false) == eOk)
				{
					layerId = recordId;
					return Acad::eOk;
				}
				else //Create new layer
				{

					pDbLayerTable->upgradeOpen();
					AcDbLayerTableRecord* pLayerTblRec = new AcDbLayerTableRecord();
					pLayerTblRec->setName(layerName);
					if (pDbLayerTable->add(recordId, pLayerTblRec) == Acad::eOk)
					{
						layerId = recordId;
					}
					pLayerTblRec->close();
				}

			}
			pDbLayerTable->close();
		}

		return Acad::eOk;
	}

	Acad::ErrorStatus createBlockRecord(const TCHAR* name)
	{
		//Check name exists
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		if (pDb != NULL)
		{
			AcDbBlockTable* pDbBlkTable = NULL;
			pDb->getBlockTable(pDbBlkTable, AcDb::kForRead);
			if (pDbBlkTable != NULL)
			{
				AcDbObjectId recordId;
				if (pDbBlkTable->getAt(name, recordId, false) == eOk)
				{
					return Acad::eOk;
				}
				else //Create new layer
				{
					pDbBlkTable->upgradeOpen();
					AcDbBlockTableRecord* pBlkTblRec = new AcDbBlockTableRecord();
					pBlkTblRec->setName(name);


					AcDbCircle* head = new AcDbCircle(AcGePoint3d(0, 0, 0), AcGeVector3d(0, 0, 1), 1);
					head->setColorIndex(2); //yellow

					AcDbCircle* leftEye = new AcDbCircle(AcGePoint3d(0.5, 0.35, 0), AcGeVector3d(0, 0, 1), 0.15);
					leftEye->setColorIndex(3); //Blue

					AcDbCircle* rightEye = new AcDbCircle(AcGePoint3d(-0.5, 0.35, 0), AcGeVector3d(0, 0, 1), 0.15);
					rightEye->setColorIndex(3); //Blue

					AcDbArc* mouth = new AcDbArc(AcGePoint3d(0, 0.3, 0), 1, 3.96, 5.43);
					mouth->setColorIndex(1); //Blue


					pBlkTblRec->appendAcDbEntity(head);
					pBlkTblRec->appendAcDbEntity(leftEye);
					pBlkTblRec->appendAcDbEntity(rightEye);
					pBlkTblRec->appendAcDbEntity(mouth);


					if (pDbBlkTable->add(recordId, pBlkTblRec) != Acad::eOk)
					{
						return pDbBlkTable->add(recordId, pBlkTblRec);
					}
					pBlkTblRec->close();
				}
			}
			pDbBlkTable->close();
		}
		return Acad::eOk;
	}
}


