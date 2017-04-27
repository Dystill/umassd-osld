#ifndef OSLD_GLOBAL_H
#define OSLD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OSLD_LIBRARY)
#  define OSLDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OSLDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OSLD_GLOBAL_H
