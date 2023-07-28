// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
//----- D:\PRIVATE\GitHub\Autocad Object ARX\AutocadObjectArx\Autodesk Training\AutodeskObjectArxTraining\Step2ObjectArxWizard\UtcEditorReactor.cpp : Implementation of UTC
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "D:\PRIVATE\GitHub\Autocad Object ARX\AutocadObjectArx\Autodesk Training\AutodeskObjectArxTraining\Step2ObjectArxWizard\UtcEditorReactor.h"

//-----------------------------------------------------------------------------
UtcEditorReactor::UtcEditorReactor (const bool autoInitAndRelease) : AcEditorReactor(), mbAutoInitAndRelease(autoInitAndRelease) {
	if ( autoInitAndRelease ) {
		if ( acedEditor )
			acedEditor->addReactor (this) ;
		else
			mbAutoInitAndRelease =false ;
	}
}

//-----------------------------------------------------------------------------
UtcEditorReactor::~UtcEditorReactor () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void UtcEditorReactor::Attach () {
	Detach () ;
	if ( !mbAutoInitAndRelease ) {
		if ( acedEditor ) {
			acedEditor->addReactor (this) ;
			mbAutoInitAndRelease =true ;
		}
	}
}

void UtcEditorReactor::Detach () {
	if ( mbAutoInitAndRelease ) {
		if ( acedEditor ) {
			acedEditor->removeReactor (this) ;
			mbAutoInitAndRelease =false ;
		}
	}
}

AcEditor *UtcEditorReactor::Subject () const {
	return (acedEditor) ;
}

bool UtcEditorReactor::IsAttached () const {
	return (mbAutoInitAndRelease) ;
}
