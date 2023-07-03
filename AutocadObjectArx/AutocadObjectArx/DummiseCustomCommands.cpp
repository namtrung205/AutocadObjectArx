#include "DummiesCustomCommands.h"

void initCustomCommnands()
{
    // Register your command
    acedRegCmds->addCommand(_T("D_CREATENEWLAYER"), _T("D_CREATENEWLAYER"), _T("D_CREATENEWLAYER"), ACRX_CMD_MODAL, CD_CreateNewLayer);
}

