#pragma once
// StdAfx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__25E8220E_9ECE_40F8_9AFE_E1C46A54EFFE__INCLUDED_)
#define AFX_STDAFX_H__25E8220E_9ECE_40F8_9AFE_E1C46A54EFFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			//- Exclude rarely-used stuff from Windows headers
#endif

#pragma warning(disable: 4786)

#ifdef _DEBUG
#undef _DEBUG
#define _DEBUG_THIS_ONLY
#endif

#define WINVER         0x0501  // XP OR GREATER       
#define _WIN32_WINNT   0x0501  // XP OR GREATER
#define _WIN32_IE      0x0600  // IE 6 OR GREATER  

#include <afxwin.h>				//- MFC core and standard components
#include <afxext.h>				//- MFC extensions
#include <afxcmn.h>
#include <afxdialogex.h>

#include <vcclr.h>
#include <gcroot.h>
#using <mscorlib.dll>
#using <System.dll>
#include <math.h>
#include <vector>
#include <limits>
#include <sqltypes.h>
using namespace std;
#include "arxHeaders.h"
#include "dbxHeaders.h"
#include "mgdinterop.h"
//#include "resource.h"
//#include "Tool_Tips.h"
// RX Includes

#include "AcExtensionModule.h"

typedef AcArray<AcGeMatrix3d, AcArrayObjectCopyReallocator<AcGeMatrix3d> > AcGeMatrix3dArray; // AN ARRAY OF AcGeMatrix3d
typedef AcArray<AcGeBoundedPlane, AcArrayObjectCopyReallocator<AcGeBoundedPlane> > AcGeBoundedPlaneArray; // AN ARRAY OF AcGeBoundedPlane
typedef std::vector<AcGePoint3dArray> POINT_MULTIARRAY;

#define DLLIMPEXP __declspec(dllexport)
#include <tchar.h>

#endif // !defined(AFX_STDAFX_H__25E8220E_9ECE_40F8_9AFE_E1C46A54EFFE__INCLUDED)
