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
#include "utc_EmployeeDetails.h"


//-----------------------------------------------------------------------------
#define szRDS _RXST("utc")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CStep05CustObjArxApp : public AcRxArxApp {

public:
	CStep05CustObjArxApp () : AcRxArxApp () {}

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
	

	static void utcMyGroup_ADDDETAIL() {
		// Put your command code here

		// Add your code for command AsdkStep05._ADDDETAIL here
		// Prompt the user for the employee details
		ads_name ename;
		ads_point pt;
		// Get the data from the user
		if (acedEntSel(_T("Select employee: "), ename, pt) != RTNORM)
			return;
		// Do a quick check
		// a more comprehensive check could include 
		// whether we already have the detail object on this candidate
		AcDbObjectId idO;
		if (acdbGetObjectId(idO, ename) != Acad::eOk)
			return;
		AcDbObject* pO;
		if (acdbOpenAcDbObject(pO, idO, AcDb::kForWrite) != Acad::eOk)
			return;
		if (!pO->isKindOf(AcDbBlockReference::desc())) {
			acutPrintf(_T("\nThis is not a block reference."));
			pO->close();
			return;
		}
		// Get user input
		int id, cubeNumber;
		TCHAR strFirstName[133];
		TCHAR strLastName[133];
		if (acedGetInt(_T("Enter employee ID: "), &id) != RTNORM
			|| acedGetInt(_T("Enter cube number: "), &cubeNumber) != RTNORM
			|| acedGetString(0, _T("Enter employee first name: "), strFirstName) != RTNORM
			|| acedGetString(0, _T("Enter employee last name: "), strLastName) != RTNORM
			) {
			pO->close();
			return;
		}
		// Get the extension dictionary
		if ((idO = pO->extensionDictionary()) == AcDbObjectId::kNull) {
			if (pO->createExtensionDictionary() != Acad::eOk) {
				pO->close();
				acutPrintf(_T("\nFailed to create ext. dictionary."));
				return;
			}
			idO = pO->extensionDictionary();
		}
		// We do not need the block reference object anymore.
		pO->close();
		// Make sure you open erased extension dictionaries
		// you may need to unerase them
		AcDbDictionary* pExtDict;
		if (acdbOpenAcDbObject((AcDbObject*&)pExtDict, idO, AcDb::kForWrite, Adesk::kTrue) != Acad::eOk) {
			acutPrintf(_T("\nFailed to open ext. dictionary."));
			return;
		}
		// Unerase the ext. dictionary if it was erased
		if (pExtDict->isErased())
			pExtDict->erase(Adesk::kFalse);
		// See if our dictionary is already there
		AcDbDictionary* pEmployeeDict;
		if (pExtDict->getAt(_T("ASDK_EMPLOYEE_DICTIONARY"), idO) == Acad::eKeyNotFound) 
		{
			// Create it if not
			pEmployeeDict = new AcDbDictionary;
			Acad::ErrorStatus es;
			if ((es = pExtDict->setAt(_T("ASDK_EMPLOYEE_DICTIONARY"), pEmployeeDict, idO)) != Acad::eOk) {
				pExtDict->close();
				acutPrintf(_T("\nFailed to create the 'Employee' dictionary."));
				return;
			}
		}
		else 
		{
			// Open our dictionary for write if it is already there
			if (acdbOpenAcDbObject(pO, idO, AcDb::kForWrite) != Acad::eOk) {
				pExtDict->close();
				acutPrintf(_T("\nFailed to open the 'Employee' dictionary."));
				return;
			}
			// Check if someone has else has created an entry with our name
			// that is not a dictionary.
			if ((pEmployeeDict = AcDbDictionary::cast(pO)) == NULL) {
				pO->close();
				pExtDict->close();
				acutPrintf(_T("\nThe entry is not a dictionary"));
				return;
			}
		}
		// We do not need the ext. dictionary object anymore
		pExtDict->close();
		// Check if a record with this key is already there
		if (pEmployeeDict->getAt(_T("DETAILS"), idO) == Acad::eOk) {
			pEmployeeDict->close();
			acutPrintf(_T("\nDetails already assign to that 'Employee' object."));
			return;
		}
		// Create an EmployeeDetails object and set its fields
		utc_EmployeeDetails* pEmployeeDetails = new utc_EmployeeDetails;
		pEmployeeDetails->setID(id);
		pEmployeeDetails->setCube(cubeNumber);
		pEmployeeDetails->setFirstName(strFirstName);
		pEmployeeDetails->setLastName(strLastName);
		// Add it to the dictionary
		if (pEmployeeDict->setAt(_T("DETAILS"), pEmployeeDetails, idO) != Acad::eOk) {
			delete pEmployeeDetails;
			acutPrintf(_T("\nFailed to add details to that object."));
			pEmployeeDict->close();
			return;

		}
		// Done
		acutPrintf(_T("\nDetails successfully added!"));
		pEmployeeDict->close();
		pEmployeeDetails->close();
	}


	static void utcMyGroup_LISTDETAILS() 
	{
		// Put your command code here
		// Add your code for command here
		// Prompt the user for the employee details
		ads_name ename;
		ads_point pt;
		// Get the data from the user
		if (acedEntSel(_T("Select employee: "), ename, pt) != RTNORM)
			return;

		// Do a quick check
		// a more comprehensive check could include 
		// whether we already have the detail object on this candidate
		AcDbObjectId idO;
		if (acdbGetObjectId(idO, ename) != Acad::eOk)
			return;
		AcDbObject* pO;
		if (acdbOpenAcDbObject(pO, idO, AcDb::kForRead) != Acad::eOk)
			return;
		if (!pO->isKindOf(AcDbBlockReference::desc())) {
			acutPrintf(_T("\nThis is not a block reference."));
			pO->close();
			return;
		}
		idO.handle().print();

		ACHAR* pBuf = new ACHAR;
		size_t nBufLen = 0;

		if(idO.handle().getIntoAsciiBuffer(pBuf, nBufLen))
		{
			acutPrintf(pBuf);
		}

		// Get the extension dictionary
		if ((idO = pO->extensionDictionary()) != AcDbObjectId::kNull) 
		{
			idO = pO->extensionDictionary();
		}

		// We do not need the block reference object anymore.
		pO->close();
		// Make sure you open erased extension dictionaries
		// you may need to unerase them
		AcDbDictionary* pExtDict;
		if (acdbOpenAcDbObject((AcDbObject*&)pExtDict, idO, AcDb::kForRead, Adesk::kTrue) != Acad::eOk) {
			acutPrintf(_T("\nFailed to open ext. dictionary."));
			return;
		}
		// Unerase the ext. dictionary if it was erased
		if (pExtDict->isErased())
			pExtDict->erase(Adesk::kFalse);

		// See if our dictionary is already there
		AcDbDictionary* pEmployeeDict;
		if (pExtDict->getAt(_T("ASDK_EMPLOYEE_DICTIONARY"), idO) == Acad::eKeyNotFound)
		{
			pExtDict->close();
			acutPrintf(_T("\nHave no 'Employee' dictionary."));
			return;
		}
		else
		{
			// Open our dictionary for write if it is already there
			if (acdbOpenAcDbObject(pO, idO, AcDb::kForRead) != Acad::eOk) {
				pExtDict->close();
				acutPrintf(_T("\nFailed to open the 'Employee' dictionary."));
				return;
			}
			// Check if someone has else has created an entry with our name
			// that is not a dictionary.
			if ((pEmployeeDict = AcDbDictionary::cast(pO)) == NULL) {
				pO->close();
				pExtDict->close();
				acutPrintf(_T("\nThe entry is not a dictionary"));
				return;
			}
		}
		// We do not need the ext. dictionary object anymore
		pExtDict->close();



		// Check if a record with this key is already there
		if (pEmployeeDict->getAt(_T("DETAILS"), idO) == Acad::eOk) {


			if (acdbOpenAcDbObject(pO, idO, AcDb::kForRead) != Acad::eOk) {
				pEmployeeDict->close();
				acutPrintf(_T("\nFailed to open the 'Employee' dictionary."));
				return;
			}

			acutPrintf(pO->isA()->name());
			utc_EmployeeDetails* pEmployeeDetails = utc_EmployeeDetails::cast(pO);
			if(pEmployeeDetails!=NULL)
			{
				TCHAR* strLastName;
				pEmployeeDetails->lastName(strLastName);
				acutPrintf(_T("\n"));
				acutPrintf(strLastName);
			
			}

			pEmployeeDict->close();
			acutPrintf(_T("\nDetails already assign to that 'Employee' object."));
			return;
		}
		//// Create an EmployeeDetails object and set its fields
		//utc_EmployeeDetails* pEmployeeDetails = new utc_EmployeeDetails;
		//pEmployeeDetails->setID(id);
		//pEmployeeDetails->setCube(cubeNumber);
		//pEmployeeDetails->setFirstName(strFirstName);
		//pEmployeeDetails->setLastName(strLastName);
		//// Add it to the dictionary
		//if (pEmployeeDict->setAt(_T("DETAILS"), pEmployeeDetails, idO) != Acad::eOk) {
		//	delete pEmployeeDetails;
		//	acutPrintf(_T("\nFailed to add details to that object."));
		//	pEmployeeDict->close();
		//	return;

		//}
		// Done
		acutPrintf(_T("\nDetails successfully added!"));
		pEmployeeDict->close();
		//pEmployeeDetails->close();


	}


	static void utcMyGroup_REMOVEDETAIL() {
		// Put your command code here
	}



} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CStep05CustObjArxApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CStep05CustObjArxApp, utcMyGroup, _ADDDETAIL, _ADDDETAIL, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep05CustObjArxApp, utcMyGroup, _LISTDETAILS, _LISTDETAILS, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CStep05CustObjArxApp, utcMyGroup, _REMOVEDETAIL, _REMOVEDETAIL, ACRX_CMD_MODAL, NULL)


