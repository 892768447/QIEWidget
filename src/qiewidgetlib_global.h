#ifndef QIEWIDGETLIB_GLOBAL_H
#define QIEWIDGETLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QIEWIDGETLIB_LIBRARY)
#  define QIEWIDGETLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QIEWIDGETLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QIEWIDGETLIB_GLOBAL_H
