#include "stdafx.h"
#include "tchar.h"
#include "aced.h"
#include <rxregsvc.h>

#include "ArxCommands.h"


void initApp()
{
    // register a command with the AutoCAD command mechanism
    acedRegCmds->addCommand(_T("HELLOWORLD_COMMANDS"),
        _T("Hello"),
        _T("Bonjour"),
        ACRX_CMD_TRANSPARENT,
        helloWorld);
}

void unloadApp()
{
    acedRegCmds->removeGroup(_T("HELLOWORLD_COMMANDS"));

}

void helloWorld()
{
    acutPrintf(_T("\nHello World!"));
}


