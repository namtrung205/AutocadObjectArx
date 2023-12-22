#include "stdafx.h"
#include "tchar.h"
#include "aced.h"
#include <rxregsvc.h>

#include "UtcGiWorldDraw.h"



#include "DemoGLTF/CreateTriangleMesh.h"






//-----------------------------------------------------------------------------
#define szRDS _RXST("UTC")
//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class GeometryDumpDataApp : public AcRxArxApp {

public:
	GeometryDumpDataApp() : AcRxArxApp() {}

	virtual AcRx::AppRetCode On_kInitAppMsg(void* pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kInitAppMsg(pkt);

		// TODO: Add your initialization code here

		return (retCode);
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg(void* pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode = AcRxArxApp::On_kUnloadAppMsg(pkt);

		// TODO: Unload dependencies here

		return (retCode);
	}

	virtual void RegisterServerComponents() {
	}


	static void utcCommandGroup_DUMPDATA(void) 
	{
		acutPrintf(_T("\nBegin Dump Data...!\n"));
		//Iterator all entity in Model Space
        IterateEntities();


		//
	}

    static void IterateEntities()
    {
        AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();

        if (pDb == nullptr)
        {
            acutPrintf(_T("\nCannot access the current database."));
            return;
        }

        AcDbBlockTable* pBlockTable;
        if (acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead) != Acad::eOk)
        {
            acutPrintf(_T("\nCannot access the block table."));
            return;
        }

        AcDbBlockTableRecord* pModelSpace;
        if (pBlockTable->getAt(ACDB_MODEL_SPACE, pModelSpace, AcDb::kForRead) != Acad::eOk)
        {
            acutPrintf(_T("\nCannot access the Model Space."));
            pBlockTable->close();
            return;
        }

        pBlockTable->close();

        AcDbEntity* pEntity;
        AcDbBlockTableRecordIterator* pIterator;
        if (pModelSpace->newIterator(pIterator) != Acad::eOk)
        {
            acutPrintf(_T("\nCannot create iterator."));
            pModelSpace->close();
            return;
        }

        for (; !pIterator->done(); pIterator->step())
        {
            if (pIterator->getEntity(pEntity, AcDb::kForRead) == Acad::eOk)
            {
                // Process the entity (pEntity) here.
                acutPrintf(_T("\nCurrent Type: "));
                acutPrintf(pEntity->isA()->name());

                ACHAR handleAsString[17];
                pEntity->objectId().handle().getIntoAsciiBuffer(handleAsString);
                acutPrintf(handleAsString);
                acutPrintf(_T("\n"));



                UtcGiWorldDraw* wd = new UtcGiWorldDraw();
                pEntity->worldDraw(wd);




                pEntity->close();
            }
        }

        delete pIterator;
        pModelSpace->close();

        fs::path path = "D:\\abc.glb";
        Demo::SerializeTriangle(path);

    }

};

//-----------------------------------------------------------------------------

IMPLEMENT_ARX_ENTRYPOINT(GeometryDumpDataApp)

ACED_ARXCOMMAND_ENTRY_AUTO(GeometryDumpDataApp, utcCommandGroup, _DUMPDATA, DUMPDATA, ACRX_CMD_TRANSPARENT, NULL)

