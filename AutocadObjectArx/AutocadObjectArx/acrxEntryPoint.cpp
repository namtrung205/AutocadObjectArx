#include "rxregsvc.h"
#include "acutads.h"
#include <tchar.h>

#include "DA_Reactor.h"
//Commands

#include "DummiesCustomCommands.h"


// Simple acrxEntryPoint code. Normally intialization and cleanup
// (such as registering and removing commands) should be done here.
//
extern "C" AcRx::AppRetCode

acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    static DA_Reactor* pEdReac = NULL;
    switch (msg) {
    case AcRx::kInitAppMsg:
        // Allow application to be unloaded
        // Without this statement, AutoCAD will
        // not allow the application to be unloaded
        // except on AutoCAD exit.
        //
        acrxUnlockApplication(appId);
        // Register application as MDI aware. 
        // Without this statement, AutoCAD will
        // switch to SDI mode when loading the
        // application.
        //

        acrxRegisterAppMDIAware(appId);

        initCustomCommnands();

        //reactor event

        if (!pEdReac)
            pEdReac = new DA_Reactor();
        acedEditor->addReactor(pEdReac);



        break;
    case AcRx::kUnloadAppMsg:
        break;
    }
    return AcRx::kRetOK;
}

