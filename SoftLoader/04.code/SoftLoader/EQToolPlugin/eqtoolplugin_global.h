#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EQTOOLPLUGIN_LIB)
#  define EQTOOLPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define EQTOOLPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define EQTOOLPLUGIN_EXPORT
#endif
