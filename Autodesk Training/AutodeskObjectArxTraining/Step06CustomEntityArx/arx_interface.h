#pragma once
#include <dbmain.h>
#include <cstring>
#include <string>
#include <afxcoll.h>
#include "aced.h"

class __declspec(dllexport) ArxInterface
{
public:
	ArxInterface();
	~ArxInterface();

	//Simple data type as a parameter
	void PrintString(CString s);
	void DrawCircle(double rad);
	void DrawLine();
	void PlaceSmiley();
	void PlaceSmiley(double faceSize, double eyeSize);

	//return
	AcGeMatrix3d MoveUp(AcGeMatrix3d inputMat, double dis);
};