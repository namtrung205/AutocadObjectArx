//Impelementation for react and transform utc_smiley
#include "StdAfx.h"
#include "utc_Smiley.h"



//validate radius
void utc_Smiley::ensureRadiusMouth()
{
	double d;
	AcGePoint3d cen(center());
	if ((d = cen.distanceTo(mouthLeft())) > radius() / 1.1) setRadius(1.1 * d);
	if ((d = cen.distanceTo(mouthRight())) > radius() / 1.1) setRadius(1.1 * d);
	if ((d = cen.distanceTo(mouthBottom())) > radius() / 1.1) setRadius(1.1 * d);
}

void utc_Smiley::ensureRadiusEyes()
{
	double d = center().distanceTo(leftEyeCenter()) + eyeSize();
	if (d > radius() / 1.1) setRadius(1.1 * d);
}