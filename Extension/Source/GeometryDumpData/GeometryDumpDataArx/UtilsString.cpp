#include "UtilsString.h"

void Utils::String::PointToString(const AcGePoint3d& point, AcString& resultString)
{
		// Format the string using AcString::format or swprintf
		resultString.format(L"X: %.2f, Y: %.2f, Z: %.2f", point.x, point.y, point.z);
}
