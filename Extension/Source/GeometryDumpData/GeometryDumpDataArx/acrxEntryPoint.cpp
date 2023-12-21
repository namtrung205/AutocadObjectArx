#include "stdafx.h"
#include "tchar.h"
#include "aced.h"
#include <rxregsvc.h>


extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(pkt);
        acrxRegisterAppMDIAware(pkt);

        acutPrintf(_T("\nInitApp OK!\n"));

        break;
    case AcRx::kUnloadAppMsg:
        break;
    default:
        break;
    }

    return AcRx::kRetOK;
}