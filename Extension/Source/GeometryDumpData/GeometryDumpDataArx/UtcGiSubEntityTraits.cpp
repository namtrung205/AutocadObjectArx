#include "UtcGiSubEntityTraits.h"

void UtcGiSubEntityTraits::setColor(const Adesk::UInt16 color)
{

}

void UtcGiSubEntityTraits::setTrueColor(const AcCmEntityColor& color)
{
}

void UtcGiSubEntityTraits::setLayer(const AcDbObjectId layerId)
{
}

void UtcGiSubEntityTraits::setLineType(const AcDbObjectId linetypeId)
{
}

void UtcGiSubEntityTraits::setSelectionMarker(const Adesk::LongPtr markerId)
{
}

void UtcGiSubEntityTraits::setFillType(const AcGiFillType)
{
}

void UtcGiSubEntityTraits::setLineWeight(const AcDb::LineWeight lw)
{
}

void UtcGiSubEntityTraits::setLineTypeScale(double dScale = 1.0)
{
}

void UtcGiSubEntityTraits::setThickness(double dThickness)
{
}

Adesk::UInt16 UtcGiSubEntityTraits::color(void) const
{
	return Adesk::UInt16();
}

AcCmEntityColor UtcGiSubEntityTraits::trueColor(void) const
{
	return AcCmEntityColor();
}

AcDbObjectId UtcGiSubEntityTraits::layerId(void) const
{
	return AcDbObjectId();
}

AcDbObjectId UtcGiSubEntityTraits::lineTypeId(void) const
{
	return AcDbObjectId();
}

AcGiFillType UtcGiSubEntityTraits::fillType(void) const
{
	return AcGiFillType();
}

AcDb::LineWeight UtcGiSubEntityTraits::lineWeight(void) const
{
	return AcDb::LineWeight();
}

double UtcGiSubEntityTraits::lineTypeScale(void) const
{
	return 0.0;
}

double UtcGiSubEntityTraits::thickness(void) const
{
	return 0.0;
}
