LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := mpthread
LOCAL_CFLAGS   +=  -O3 -frtti -fexceptions
LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)
LOCAL_SRC_FILES := m_pthread.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/src/main/jni
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)