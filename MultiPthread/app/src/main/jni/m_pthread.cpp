#include "m_pthread.h"
//
// Created by pierce on 19-3-7.
//
#include <android/log.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,##__VA_ARGS__);

JavaVM *javaVM;
jobject uuid_class_global_ref;
jmethodID uuid_get_mid;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *r) {
    LOGI("s%", "JNI_OnLoad");
    javaVM = vm;
    return JNI_VERSION_1_4;

}

void *pt_fun(void *args) {
    int i = 0;

    for (i = 0; i < 5; ++i) {

        JNIEnv *env;

        javaVM->AttachCurrentThread(&env, NULL);
        jstring uuid_str = (jstring) env->CallStaticObjectMethod(
                static_cast<jclass>(uuid_class_global_ref), uuid_get_mid);
        const char *arr = env->GetStringUTFChars(uuid_str, NULL);
        LOGI("%s", arr);
        if (i == 4)
            goto end;
        sleep(1);
    }
    end:
    javaVM->DetachCurrentThread();
    pthread_exit((void *) "0");
}

JNIEXPORT void JNICALL Java_com_pierce_multipthread_PThread_init
        (JNIEnv *env, jobject jobj) {
    jclass uuid_class = env->FindClass("com/pierce/multipthread/UUIDUtils");
    uuid_class_global_ref = env->NewGlobalRef(uuid_class);
    uuid_get_mid = env->GetStaticMethodID(static_cast<jclass>(uuid_class_global_ref), "get",
                                          "()Ljava/lang/String;");

}

/*
 * Class:     com_pierce_multipthread_PThread
 * Method:    pthread
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_pierce_multipthread_PThread_pthread
        (JNIEnv *env, jobject jobj) {
    pthread_t pt;
    pthread_create(&pt, NULL, pt_fun, (void *) "NO1");

}

/*
 * Class:     com_pierce_multipthread_PThread
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_pierce_multipthread_PThread_destroy
        (JNIEnv *env, jobject jobj) {
    env->DeleteGlobalRef(uuid_class_global_ref);
}
