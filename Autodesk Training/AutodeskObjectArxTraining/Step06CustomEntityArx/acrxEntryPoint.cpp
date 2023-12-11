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
#include "utc_customEntityStep6.h"
#include "utc_Smiley.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("utc")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep06CustEntArxApp : public AcRxArxApp {

public:
	CStep06CustEntArxApp () : AcRxArxApp () {}

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

	virtual void RegisterServerComponents () 
	{
	}
	
	static void utcMyGroup_CREATEEMPLOYEE() 
	{
		// Put your command code here
		//Get Point
		ads_point pt;
		ads_point pt_res;

		acedGetPoint(pt,_T("Select point..."), pt_res);

		asPnt3d(pt_res);
		utc_customEntityStep6* cusEnt6 = new utc_customEntityStep6;
		cusEnt6->setID(3);
		cusEnt6->setCube(3);
		cusEnt6->setFirstName(_T("fName"));
		cusEnt6->setLastName(_T("lName"));

		//Add entity to model space
		{
			//Check name exists
			AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
			if (pDb != NULL)
			{
				AcDbObjectId modelId;
				modelId = acdbSymUtil()->blockModelSpaceId(pDb);
				AcDbBlockTableRecord* pBlockTableRecordModel;

				acdbOpenAcDbObject((AcDbObject*&)pBlockTableRecordModel, modelId, AcDb::kForRead);

				if (pBlockTableRecordModel != NULL)
				{
					pBlockTableRecordModel->upgradeOpen();
					pBlockTableRecordModel->appendAcDbEntity(cusEnt6);
					pBlockTableRecordModel->close();
				}
			}

		}
	
		cusEnt6->close();
	}

	static void utcMyGroup_CREATESMILEY()
	{
		// Put your command code here
		//Get Point
		ads_point pt_res;

		acedGetPoint(NULL, _T("Select point..."), pt_res);
		AcGePoint3d cenPt = asPnt3d(pt_res);

		utc_Smiley* pSmile = new utc_Smiley();
		pSmile->setCenter(cenPt);


		//Add entity to model space
		{
			//Check name exists
			AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
			if (pDb != NULL)
			{
				AcDbObjectId modelId;
				modelId = acdbSymUtil()->blockModelSpaceId(pDb);
				AcDbBlockTableRecord* pBlockTableRecordModel;

				acdbOpenAcDbObject((AcDbObject*&)pBlockTableRecordModel, modelId, AcDb::kForRead);

				if (pBlockTableRecordModel != NULL)
				{
					pBlockTableRecordModel->upgradeOpen();
					pBlockTableRecordModel->appendAcDbEntity(pSmile);
					pBlockTableRecordModel->close();
				}
			}

		}
		pSmile->close();
	}

} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep06CustEntArxApp)


ACED_ARXCOMMAND_ENTRY_AUTO(CStep06CustEntArxApp, utcMyGroup, _CREATEEMPLOYEE, _CREATEEMPLOYEE, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep06CustEntArxApp, utcMyGroup, _CREATESMILEY, _CREATESMILEY, ACRX_CMD_MODAL, NULL)


