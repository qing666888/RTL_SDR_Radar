#ifndef POOLOBJECT_GLOBAL_H
#define POOLOBJECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(POOLOBJECT_LIBRARY)
#  define POOLOBJECTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define POOLOBJECTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // POOLOBJECT_GLOBAL_H