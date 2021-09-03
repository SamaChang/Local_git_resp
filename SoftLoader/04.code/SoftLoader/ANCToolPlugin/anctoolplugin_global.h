#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ANCTOOLPLUGIN_LIB)
#  define ANCTOOLPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define ANCTOOLPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define ANCTOOLPLUGIN_EXPORT
#endif
