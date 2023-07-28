// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("utc")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep3SymbolTablesApp : public AcRxArxApp {

public:
	CStep3SymbolTablesApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CStep3SymbolTablesApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CStep3SymbolTablesApp, utcMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void utcMyGroup_CREATE () 
	{
		// Put your command code here
		AcDbObjectId layerId;
		UTILS::createLayer(_T("USER"), layerId);
		UTILS::createBlockRecord(_T("EMPLOYEE"));
	}

	static void utcMyGroup_SETLAYER()
	{
		//iterate all BlockRef in ModelSpace

		//Check name exists
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		if(pDb!=NULL)
		{
			AcDbObjectId modelId;
			modelId = acdbSymUtil()->blockModelSpaceId(pDb);
			AcDbBlockTableRecord* pBlockTableRecordModel;

			acdbOpenAcDbObject((AcDbObject*&)pBlockTableRecordModel, modelId, AcDb::kForRead);

			if(pBlockTableRecordModel != NULL)
			{
				AcDbBlockTableRecordIterator* pIterator;
				pBlockTableRecordModel->newIterator(pIterator);

				for (pIterator->start(); !pIterator->done(); pIterator->step())
				{
					AcDbEntity* pEntity;
					pIterator->getEntity(pEntity, AcDb::kForRead);

					if (pEntity->isKindOf(AcDbBlockReference::desc()))
					{
						AcDbBlockReference* pBlkRef = AcDbBlockReference::cast(pEntity);
						AcDbBlockTableRecord* pBlkTblRec;
						acdbOpenAcDbObject((AcDbObject*&)pBlkTblRec, pBlkRef->blockTableRecord(), AcDb::kForRead);
						ACHAR* pName;
						pBlkTblRec->getName(pName);
						if (_tccmp(pName,_T("EMPLOYEE")) == 0)
						{
							pBlkRef->upgradeOpen();
							pBlkRef->setLayer(_T("USER"));
						}

						pBlkRef->close();
						pBlkTblRec->close();
						pBlockTableRecordModel->close();
					}
				}
			}
		}
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep3SymbolTablesApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep3SymbolTablesApp, utcMyGroup, _CREATE, _CREATE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep3SymbolTablesApp, utcMyGroup, _SETLAYER, _SETLAYER, ACRX_CMD_MODAL, NULL)

