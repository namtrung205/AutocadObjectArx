#pragma once



#ifdef STEP06CUSTENTDBX_MODULE
#define DLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define DLLIMPEXP
#endif

#include "dbMultiModesGrip.h"

class DLLIMPEXP AdskContainerEntityMultiModesGripPE : public AcDbMultiModesGripPE
{
private:
	static AcDbMultiModesGripPE::GripMode _currentGripMode;

public:
	ACRX_DECLARE_MEMBERS(AdskContainerEntityMultiModesGripPE);

	AdskContainerEntityMultiModesGripPE();
	~AdskContainerEntityMultiModesGripPE();

	static AcDbObjectId getLastModifiedEntId();
	static Adesk::UInt32 getVertexNumberToAdd();

	virtual bool getGripModes(AcDbEntity* pThis, AcDbGripData* pGripData, AcArray<GripMode>& modes, unsigned int& curMode) const;
	virtual unsigned int mode(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual AcDbMultiModesGripPE::GripMode modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual bool setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode);
	virtual AcDbMultiModesGripPE::GripType gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const;
	virtual void reset(AcDbEntity* pThis);
};

#ifdef STEP06CUSTENTDBX_MODULE
ACDB_REGISTER_OBJECT_ENTRY_AUTO(AdskContainerEntityMultiModesGripPE)
#endif
