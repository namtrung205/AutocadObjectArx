#pragma once
#include "acgi.h"
class UtcGiSubEntityTraits : public AcGiSubEntityTraits
{

public:
	UtcGiSubEntityTraits()
	{

	}
	~UtcGiSubEntityTraits()
	{

	}

	// Inherited via AcGiSubEntityTraits
	virtual void setColor(const Adesk::UInt16 color) override;
	virtual void setTrueColor(const AcCmEntityColor& color) override;
	virtual void setLayer(const AcDbObjectId layerId) override;
	virtual void setLineType(const AcDbObjectId linetypeId) override;
	virtual void setSelectionMarker(const Adesk::LongPtr markerId) override;
	virtual void setFillType(const AcGiFillType) override;
	virtual void setLineWeight(const AcDb::LineWeight lw) override;
	virtual void setLineTypeScale(double dScale) override;
	virtual void setThickness(double dThickness) override;
	virtual Adesk::UInt16 color(void) const override;
	virtual AcCmEntityColor trueColor(void) const override;
	virtual AcDbObjectId layerId(void) const override;
	virtual AcDbObjectId lineTypeId(void) const override;
	virtual AcGiFillType fillType(void) const override;
	virtual AcDb::LineWeight lineWeight(void) const override;
	virtual double lineTypeScale(void) const override;
	virtual double thickness(void) const override;
};

