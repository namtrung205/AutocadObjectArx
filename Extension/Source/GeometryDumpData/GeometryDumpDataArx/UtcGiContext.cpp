#include "UtcGiContext.h"

Adesk::Boolean UtcGiContext::isPsOut() const
{
    return Adesk::Boolean();
}

Adesk::Boolean UtcGiContext::isPlotGeneration() const
{
    return Adesk::Boolean();
}

AcDbDatabase* UtcGiContext::database() const
{
    return nullptr;
}

bool UtcGiContext::isBoundaryClipping() const
{
    return false;
}
