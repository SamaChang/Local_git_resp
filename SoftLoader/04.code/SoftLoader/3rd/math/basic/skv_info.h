#include "skv_config.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef OS_ANDROID
    #include <jni.h>
    #include <android/log.h>

    #ifndef POST
    #define POST "appId=%s&userId=%s&macId=%s"
    #endif

    #ifndef LOG_TAG
    #define HTTP_ADRR "http://wx.yonsz.com:8080/licenseList/checked"
    #endif

    #ifndef LOG_TAG
    #define LOG_TAG "SKV_INFO"
    #endif

    #ifndef NULL
    #define NULL 0
    #endif

    #ifndef CERTIFICATE_NAME
    #define CERTIFICATE_NAME "/storage/sdcard0/certificate"
    #endif

    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
    #define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
	#define LOGE(...) \
		((void)__android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__))

	#define LOG(format, ...) \
	  do { \
		__android_log_print(ANDROID_LOG_WARN, LOG_TAG, \
							"LOG (%s: %s(): %d) " format "\n", \
							__FILE__, __func__, __LINE__, ##__VA_ARGS__); \
	  } while (0)

	#define ERROR(format, ...) \
	  do { \
		__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, \
							"ERROR (%s: %s(): %d) " format "\n", \
							__FILE__, __func__, __LINE__, ##__VA_ARGS__); \
		exit(-1); \
	  } while (0)

	#define CHECK(test) \
	  do { \
		if (!(test)) { \
		  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, \
							  "CHECK (%s: %s(): %d) %s \n", \
							  __FILE__, __func__, __LINE__, #test); \
		  exit(-1); \
		} \
	  } while (0)

#else
	#define LOG(format, ...) \
	  do { \
		fprintf(stderr, "LOG (%s: %s(): ,%d" format "\n", \
				__FILE__, __func__, __LINE__, ##__VA_ARGS__); \
	  } while (0)

	#define ERROR(format, ...) \
	  do { \
		  fprintf(stderr, "ERROR (%s: %s(): ,%d) " format "\n", \
				  __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
		exit(-1); \
	  } while (0)

	#define CHECK(test) \
	  do { \
		if (!(test)) { \
		  fprintf(stderr, "CHECK (%s: %s(): %d) %s \n", \
				  __FILE__, __func__, __LINE__, #test); \
		  exit(-1); \
		} \
	  } while (0)
#endif 