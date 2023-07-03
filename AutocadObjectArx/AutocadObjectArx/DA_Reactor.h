#pragma once
#include "aced.h"

class DA_Reactor: public AcEditorReactor
{
public:
	DA_Reactor();
	~DA_Reactor();


	void unknownCommand(const ACHAR* /*cmdStr*/, AcDbVoidPtrArray* /*al*/) override;
	void commandWillStart(const ACHAR* /*cmdStr*/) override;
	void commandEnded(const ACHAR* /*cmdStr*/) override;
	void commandCancelled(const ACHAR* /*cmdStr*/) override;
	void commandFailed(const ACHAR* /*cmdStr*/) override;

};

