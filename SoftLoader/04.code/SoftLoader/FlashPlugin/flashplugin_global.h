#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FLASHPLUGIN_LIB)
#  define FLASHPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define FLASHPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define FLASHPLUGIN_EXPORT
#endif
