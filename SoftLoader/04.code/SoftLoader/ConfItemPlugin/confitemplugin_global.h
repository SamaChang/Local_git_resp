#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CONFITEMPLUGIN_LIB)
#  define CONFITEMPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define CONFITEMPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define CONFITEMPLUGIN_EXPORT
#endif
