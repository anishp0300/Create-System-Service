#define LOG_TAG "SigmaService"

#include <nativehelper/JNIHelp.h>
#include "android_runtime/AndroidRuntime.h"
#include "core_jni_helpers.h"
#include "jni.h"

#include <utils/Log.h>
#include <utils/misc.h>
#include <hardware/hardware.h>
#include <stdio.h>
#include <string>
#include <stdint.h>
#include <hardware/sigmaservice.h>

namespace android {

sigmaservice_device_t* sigmaservice_dev;

static jint init_native(JNIEnv* env, jobject clazz) {
    int err;
    hw_module_t* module;
    sigmaservice_device_t* dev = 0;
    err = hw_get_module(SIGMASERVICE_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
    if (err == 0) { 
       if (module->methods->open(module,"",((hw_device_t**)&dev)) !=0)
           return 0;
    }
    return (jint)(size_t)dev;
}

static int retStringNative(JNIEnv *env, jobject clazz, int ptr, jbyteArray buffer){
    sigmaservice_device_t* dev = (sigmaservice_device_t*)(intptr_t)ptr;
    jbyte* real_byte_array;
    int num;

    real_byte_array = env->GetByteArrayElements(buffer, NULL);
 
    if (dev == NULL) {
        return 0;
    }

    num = dev-> retString((char*) real_byte_array, env->GetArrayLength(buffer));
    env->ReleaseByteArrayElements(buffer, real_byte_array, 0);

    return num;
}

static int write_native(JNIEnv *env, jobject clazz, int ptr, jbyteArray buffer) {
    sigmaservice_device_t* dev = (sigmaservice_device_t*)(intptr_t)ptr;
    jbyte* real_byte_array;
    int num;
 
    real_byte_array = env->GetByteArrayElements(buffer, NULL);
    if (dev == NULL) {
        return 0;
    }
    num = dev-> give((char*)real_byte_array, env->GetArrayLength(buffer));
    env->ReleaseByteArrayElements(buffer, real_byte_array, 0);
    return num;
}


static JNINativeMethod method_table[] = {
    { "init_native", "()I", (void*)init_native },
    { "retStringNative", "(I)V", (void*)retStringNative },
    { "write_native", "(I[B)I", (void*)write_native },
};

int register_android_server_audio_SigmaService(JNIEnv* env) {
    return jniRegisterNativeMethods(env, "com/android/server/audio/SigmaService", method_table, NELEM(method_table));
};



};
