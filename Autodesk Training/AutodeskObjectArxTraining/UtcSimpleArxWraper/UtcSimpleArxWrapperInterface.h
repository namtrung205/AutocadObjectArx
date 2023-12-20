#pragma once
#include "arx_interface.h"
//-----------------------------------------------------------------------------
using namespace System;
using namespace System::Collections::Specialized;
using namespace System::Collections::Generic;
using namespace System;
using namespace System::Reflection;
#if (BCAD)
using namespace Teigha::Geometry;
using namespace Teigha::DatabaseServices;
#else
using namespace Autodesk::AutoCAD::Geometry;
using namespace Autodesk::AutoCAD::DatabaseServices;
#endif

namespace UtcSimpleArxWrapper {

	[Autodesk::AutoCAD::Runtime::Wrapper("ArxInterface")]

	public ref class UtcSimpleArxWrapperInterface
	{
	public:
		//- Constructor
		UtcSimpleArxWrapperInterface();

	internal:
		UtcSimpleArxWrapperInterface(System::IntPtr unmanagedPointer, bool bAutoDelete);

	public:

		void PrintString(String^ s);
		void DrawCircle(double r);
		Matrix3d MoveUp(Matrix3d inputMat, double distance);
		void PlaceSmiley();
		void PlaceSmiley(double faceSize, double eyeSize);

	private:
		ArxInterface* m_Interface;
	};
}
