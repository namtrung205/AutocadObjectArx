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
		// Add your code for command AsdkStep04._ADDENTRY here
		//  When this command invoked at the first time
		//  it creates two objects: an AcDbDictionary object in the named
		//  objects dictionary (NOD) and an empty AcDbXrecord object to represent
		//  an individual entry. The XRecord will be replaced in a later lab by a
		//  custom object AsdkEmployeeDetails.
		//  Later invokations of the command just adds new XRecords to this
		//  dictionary.
		//  Storing these entries in the NOD will enable us to query all
		//  employees in the db quickly without iterating through all
		//  AcDbBlockTableRecords in the database.

		// Prompt the use for the an id
		TCHAR strID[133];
		if (acedGetString(0, _T("Enter employee name: "), strID) != RTNORM)
			return;

		// Get the named object dictionary
		AcDbDictionary* pNOD;
		if (acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary(pNOD, AcDb::kForRead) != Acad::eOk)
		{
			acutPrintf(_T("\nUnable to open the NOD! Aborting..."));
			return;
		}

		// See if our dictionary is already there
		AcDbObjectId idO;
		AcDbDictionary* pEmployeeDict = NULL;
		if (pNOD->getAt(_T("ASDK_EMPLOYEE_DICTIONARY"), idO) == Acad::eKeyNotFound) {
			// Create it if not
			if (pNOD->upgradeOpen() != Acad::eOk) {
				acutPrintf(_T("\nCannot open NOD for Write!"));
				pNOD->close();
				return;
			}
			pEmployeeDict = new AcDbDictionary;
			// Add it to the NOD
			if (pNOD->setAt(_T("ASDK_EMPLOYEE_DICTIONARY"), pEmployeeDict, idO) != Acad::eOk) {
				// We are really unlucky
				acutPrintf(_T("\nCannot add our dictionary in the AutoCAD NOD!"));
				// Clean-up memory and abort
				delete pEmployeeDict;
				pNOD->close();
				return;
			}
		}
		else {
			// Get it for write if it is already there
			AcDbObject* pO;
			if (acdbOpenAcDbObject(pO, idO, AcDb::kForWrite) != Acad::eOk) {
				acutPrintf(_T("\nCannot open the object for write."));
				pNOD->close();
				return;
			}
			// Check if someone has else has created an entry with our name
			// that is not a dictionary. This should never happen as long as
			// I use the registered developer RDS prefix.
			if ((pEmployeeDict = AcDbDictionary::cast(pO)) == NULL) {
				acutPrintf(_T("\nEntry found in the NOD, but it is not a dictionary."));
				pO->close();
				pNOD->close();
				return;
			}
		}
		pNOD->close();
		// Check if a record with this key is already there
		if (pEmployeeDict->getAt(strID, idO) == Acad::eOk) {
			acutPrintf(_T("\nThis employee is already registered."));
			pEmployeeDict->close();
			return;
		}
		// Let's add the new record. Append an empty xrecord.
		AcDbXrecord* pEmployeeEntry = new AcDbXrecord;
		if (pEmployeeDict->setAt(strID, pEmployeeEntry, idO) != Acad::eOk) {
			acutPrintf(_T("\nFailed to add the new employee in the dictionary."));
			delete pEmployeeEntry;
			pEmployeeDict->close();
			return;
		}
		pEmployeeEntry->close();
		pEmployeeDict->close();
	}


	static void utcMyGroup_LISTENTRIES(void)
	{
		// Add your code for command AsdkStep04._LISTENTRIES here
		// Get the named object dictionary
		AcDbDictionary* pNOD;
		if (acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary(pNOD, AcDb::kForRead) != Acad::eOk) {
			acutPrintf(_T("\nUnable to open the NOD! Aborting..."));
			return;
		}
		// See if our dictionary is already there
		AcDbObjectId idO;
		AcDbObject* pO;
		if (pNOD->getAt(_T("ASDK_EMPLOYEE_DICTIONARY"), idO) != Acad::eOk) {
			acutPrintf(_T("\nNo dictionary, no entry to remove..."));
			pNOD->close();
			return;
		}
		// Get employee dictionary for read
		if (acdbOpenAcDbObject(pO, idO, AcDb::kForRead) != Acad::eOk) {
			acutPrintf(_T("\nCannot open the object for write."));
			pNOD->close();
			return;
		}
		// Check if someone has else has created an entry with our name
		// that is not a dictionary. This should never happen as long as
		// I use the registered developer RDS prefix.
		AcDbDictionary* pEmployeeDict;
		if ((pEmployeeDict = AcDbDictionary::cast(pO)) == NULL) {
			acutPrintf(_T("\nEntry found in the NOD, but it is not a dictionary."));
			pO->close();
			pNOD->close();
			return;
		}
		pNOD->close();

		AcDbDictionaryIterator* pIter;
		if ((pIter = pEmployeeDict->newIterator()) != NULL) {
			for (; !pIter->done(); pIter->next()) {
				// Print name
				acutPrintf(_T("*Employee: %s\n"), pIter->name());
			}
			delete pIter;
		}

		pEmployeeDict->close();
	}

	static void utcMyGroup_REMOVEENTRY(void)
	{
		// Add your code for command AsdkStep04._REMOVEENTRY here
		// Prompt the user for the an employee name
		TCHAR strID[133];
		if (acedGetString(0, _T("Enter employee name: "), strID) != RTNORM)
			return;
		// Get the named object dictionary
		AcDbDictionary* pNOD;
		if (acdbHostApplicationServices()->workingDatabase()->getNamedObjectsDictionary(pNOD, AcDb::kForRead) != Acad::eOk) {
			acutPrintf(_T("\nUnable to open the NOD! Aborting..."));
			return;
		}
		// See if our dictionary is already there
		AcDbObjectId idO;
		AcDbObject* pO;
		if (pNOD->getAt(_T("ASDK_EMPLOYEE_DICTIONARY"), idO) != Acad::eOk) {
			acutPrintf(_T("\nNo dictionary, no entry to remove..."));
			pNOD->close();
			return;
		}
		// Get employee dictionary for read
		if (acdbOpenAcDbObject(pO, idO, AcDb::kForRead) != Acad::eOk) {
			acutPrintf(_T("\nCannot open the object for write."));
			pNOD->close();
			return;
		}
		// Check if someone has else has created an entry with our name
		// that is not a dictionary. This should never happen as long as
		// I use the registered developer RDS prefix.
		AcDbDictionary* pEmployeeDict;
		if ((pEmployeeDict = AcDbDictionary::cast(pO)) == NULL) {
			acutPrintf(_T("\nEntry found in the NOD, but it is not a dictionary."));
			pO->close();
			pNOD->close();
			return;
		}
		pNOD->close();
		// Check if a record with this key is there
		if (pEmployeeDict->getAt(strID, idO) != Acad::eOk) {
			acutPrintf(_T("\nEntry not found."));
			pEmployeeDict->close();
			return;
		}
		pEmployeeDict->close();
		// Get it for write 
		if (acdbOpenAcDbObject(pO, idO, AcDb::kForWrite) != Acad::eOk) {
			acutPrintf(_T("\nEntry cannot be opened for write."));
			return;
		}
		// And erase it
		pO->erase();
		pO->close();
	}



};


//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep04XrecordNODApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep04XrecordNODApp, utcMyGroup, _ADDENTRY, _ADDENTRY, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep04XrecordNODApp, utcMyGroup, _LISTENTRIES, _LISTENTRIES, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep04XrecordNODApp, utcMyGroup, _REMOVEENTRY, _REMOVEENTRY, ACRX_CMD_MODAL, NULL)


