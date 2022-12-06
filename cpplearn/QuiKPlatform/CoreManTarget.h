#ifndef __COREMANTARGET_H__
#define __COREMANTARGET_H__

#include <QSharedPointer>
#include "CoreApp/CoreMan.h"

class CoreManTarget
{
public:
    CoreManTarget();
    ~CoreManTarget();

    void Init();

private:
    CoreMan *_coreMan;
};

#endif // __COREMANTARGET_H__