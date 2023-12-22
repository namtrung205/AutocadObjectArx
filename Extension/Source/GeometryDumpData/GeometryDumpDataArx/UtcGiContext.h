#pragma once
#include "acgi.h"

class UtcGiContext : public AcGiContext
{
public:
	UtcGiContext()
	{

	}

	~UtcGiContext()
	{

	}

	// Inherited via AcGiContext
	virtual Adesk::Boolean isPsOut() const override;
	virtual Adesk::Boolean isPlotGeneration() const override;
	virtual AcDbDatabase* database() const override;
	virtual bool isBoundaryClipping() const override;
};

