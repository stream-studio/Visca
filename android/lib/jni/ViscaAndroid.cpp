#include <jni.h>
#include <android/log.h>
#include "Visca.hpp"

#ifdef __cplusplus
extern "C" {
#endif


#if __SIZEOF_POINTER__ == 8
# define GET_CUSTOM_DATA(env, thiz, fieldID) reinterpret_cast<Visca*>(env->GetLongField ( thiz, fieldID) )
# define SET_CUSTOM_DATA(env, thiz, fieldID, data) env->SetLongField (thiz, fieldID, (jlong)data)
#else
# define GET_CUSTOM_DATA(env, thiz, fieldID) reinterpret_cast<Visca*>((jint)(env)->GetLongField (thiz, fieldID))
# define SET_CUSTOM_DATA(env, thiz, fieldID, data) env->SetLongField (thiz, fieldID, (jlong)(jint)data)
#endif

static jfieldID pointer_field_id;

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeClassInit(JNIEnv *env, jclass clazz){
    pointer_field_id = env->GetFieldID (clazz, "pointer", "J");

    if (!pointer_field_id) {
        __android_log_print (ANDROID_LOG_ERROR, "studio", "The calling class does not implement all necessary interface methods");
    }
}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeInit(JNIEnv *env, jobject thiz){
    __android_log_print(ANDROID_LOG_INFO, "visca", "Visca Init");
    Visca *visca = new Visca("192.168.1.45", 45678);
    SET_CUSTOM_DATA(env, thiz, pointer_field_id, visca);
    

}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeRelease(JNIEnv *env, jobject thiz){
    Visca *visca = GET_CUSTOM_DATA(env, thiz, pointer_field_id);
    if (!visca){
        return;
    }
    delete visca;
}


JNIEXPORT void JNICALL Java_studio_stream_Visca_nativePanTilt(JNIEnv *env, jobject thiz){
    Visca *visca = GET_CUSTOM_DATA(env, thiz, pointer_field_id);
    if (!visca){
        return;
    }
    visca->panTilt(10, 10);
}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativePresetSet(JNIEnv *env, jobject thiz){
    Visca *visca = GET_CUSTOM_DATA(env, thiz, pointer_field_id);
    if (!visca){
        return;
    }
    visca->presetSet(1);
}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativePresetCall(JNIEnv *env, jobject thiz){
    Visca *visca = GET_CUSTOM_DATA(env, thiz, pointer_field_id);
    if (!visca){
        return;
    }
    visca->presetCall(1);
}

JNIEXPORT void JNICALL Java_studio_stream_Visca_nativeZoom(JNIEnv *env, jobject thiz){
    Visca *visca = GET_CUSTOM_DATA(env, thiz, pointer_field_id);
    if (!visca){
        return;
    }
    visca->zoom(10);
}

jint JNI_OnLoad(JavaVM *vm, void *reserved){
    return JNI_VERSION_1_6;
}

#ifdef __cplusplus
}
#endif