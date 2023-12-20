#include "StdAfx.h"
//-----------------------------------------------------------------------------
//- Template class that wraps GCHandle from mscorlib.dll
#include <gcroot.h>

//----------- ------------------------------------------------------------------
//- autodesk interop header, to aid converting between unmanaged ObjectARX and managed ObjectARX.NET
#include "mgdinterop.h"
#include "UtcSimpleArxWrapperInterface.h"

#include "core_rxmfcapi.h"


using namespace System::Collections::Specialized;
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
namespace sysGen = System::Collections::Generic;


using namespace Autodesk::AutoCAD::Runtime;
using namespace Autodesk::AutoCAD::GraphicsSystem;
using namespace Autodesk::AutoCAD::Geometry;
using namespace Autodesk::AutoCAD::DatabaseServices;

//extern "C"
//{
//	__declspec(dllexport) CString GetResourceFnc(const CString& key)
//	{
//		CString actKey = key;
//		if (key[0] == '0' || key[0] == '1' || key[0] == '2' || key[0] == '3' || key[0] == '4' ||
//			key[0] == '5' || key[0] == '6' || key[0] == '7' || key[0] == '8' || key[0] == '9')
//		{
//			actKey = _T("NB") + key;
//		}
//		if (key[0] == '#')
//		{
//			actKey = _T("PRT") + key.Right(key.GetLength() - 1);
//		}
//		String^ value = CADWorxEquipmentArxWrapper::CADWorxEquipmentWrapperInterface::ValueAtKey(gcnew String(actKey));
//		CString val = value;
//		return val;
//	}
//	__declspec(dllexport) void LoadLanguageFnc(const CString& file)
//	{
//		CADWorxEquipmentArxWrapper::CADWorxEquipmentWrapperInterface::LoadLanguage(gcnew String(file));
//	}
//}
//-----------------------------------------------------------------------------	
//VithepTowerArxWrapper
//VithepTowerArxWrapperInterface
UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::UtcSimpleArxWrapperInterface()
{
	m_Interface = new ArxInterface();
}

//-----------------------------------------------------------------------------
UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::UtcSimpleArxWrapperInterface(System::IntPtr unmanagedPointer, bool bAutoDelete)
{

}

void UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::PrintString(String^ s)
{
	if (m_Interface)
	{
		return m_Interface->PrintString(s);
	}
}


void UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::DrawCircle(double r)
{
	if (m_Interface)
	{
		return m_Interface->DrawCircle(r);
	}
}


Matrix3d UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::MoveUp(Matrix3d inputMat, double dis)
{
	if (m_Interface)
	{
		return ToMatrix3d(m_Interface->MoveUp(GETMATRIX3D(inputMat), dis));
	}
}

void UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::PlaceSmiley(double faceSize, double eyeSize)
{
	if (m_Interface)
	{
		return m_Interface->PlaceSmiley(faceSize, eyeSize);
	}
}

void UtcSimpleArxWrapper::UtcSimpleArxWrapperInterface::PlaceSmiley()
{
	if (m_Interface)
	{
		return m_Interface->PlaceSmiley();
	}
}

