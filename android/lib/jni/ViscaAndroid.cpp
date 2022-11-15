#include <jni.h>
#include "Visca.hpp"

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeInit(JNIEnv *, jobject){

}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeRelease(JNIEnv *, jobject){

}


JNIEXPORT void JNICALL Java_studio_stream_Visca_nativePanTilt(JNIEnv *, jobject){
    Visca *visca = new Visca("192.168.1.45", 45678);
    visca->panTilt(10, 10);
}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativePresetSet(JNIEnv *, jobject){

}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativePresetCall(JNIEnv *, jobject){

}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeZoom(JNIEnv *, jobject){

}

jint JNI_OnLoad(JavaVM *vm, void *reserved){
    return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif