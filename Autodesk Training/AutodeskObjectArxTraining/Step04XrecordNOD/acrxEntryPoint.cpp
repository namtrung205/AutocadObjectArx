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
#define szRDS _RXST("ADSK")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep04XrecordNODApp : public AcRxArxApp {

public:
	CStep04XrecordNODApp () : AcRxArxApp () {}

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
	
	static void utcMyGroup_ADDENTRY()
	{
		/*Prompt the user for an employee name(acedGetString()).
		- Get the Named Objects Dictionary from the current working database(AcDbDictionary, AcDbDatabase::getNamedObjectsDictionary()).
		- Check if the "ASDK_EMPLOYEE_DICTIONARY" is already in the NOD(AcDbDictionary::getAt()).
		- If the "ASDK_EMPLOYEE_DICTIONARY" base level is not in the NOD, then create a new
		- AcDbDictionary with key "ASDK_EMPLOYEE_DICTIONARY" and add it to the named objects 
		dictionary(new AcDbDictionary, AcDbDictionary::setAt()).
		- Check if the name of the employee is already in the "ASDK_EMPLOYEE_DICTIONARY" dictionary.
		- If the employee dictionary is not present, then create a new AcDbXrecordand add it to
		the "ASDK_EMPLOYEE_DICTIONARY" (AcDbDictionary::setAt()).
		- Don't forget to close the Named Objects Dictionary, the "ASDK_EMPLOYEE_DICTIONARY" and the Xrecord if created. 
		- Using AcDbXrecord requires the include file <dbxrecrd.h>.Though you don't have to include it, 
		as explained earlier in ObjectARX Headers. */

		//Get string from User
		TCHAR employeeName[256] = { 0 };
		acedGetString(NULL, _T("\nEnter application name: "), employeeName);
		
		AcDbDatabase* pDb = acdbHostApplicationServices()->workingDatabase();
		if (pDb != NULL)
		{

			AcDbDictionary* pDict;
			pDb->getNamedObjectsDictionary(pDict, AcDb::kForRead);

			if(pDict->has(_T("ASDK_EMPLOYEE_DICTIONARY")))
			{
				AcDbObject* entryObj;
				pDict->getAt(_T("ASDK_EMPLOYEE_DICTIONARY"), entryObj);
			}
			else
			{
				AcDbObject* newValue;
				AcDbObjectId retObjId;
				pDict->setAt(_T("ASDK_EMPLOYEE_DICTIONARY"), newValue, retObjId);

				pDict


			}
		}
	}
};


//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep04XrecordNODApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep04XrecordNODApp, utcMyGroup, _ADDENTRY, _ADDENTRY, ACRX_CMD_MODAL, NULL)


