#include "CoreManTarget.h"

CoreManTarget::CoreManTarget()
{
    _coreMan = new CoreMan();
}

CoreManTarget::~CoreManTarget()
{
    _coreMan->uninit();
}

void CoreManTarget::Init()
{
    _coreMan->init();
}
