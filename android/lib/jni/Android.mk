LOCAL_PATH := $(call my-dir)
LIBVISCA_ROOT_REL := ../../..
LIBVISCA_ROOT_ABS := $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
  $(LIBVISCA_ROOT_REL)/src/exceptions/ViscaNetworkException.cpp \
  $(LIBVISCA_ROOT_REL)/src/exceptions/ViscaValueException.cpp \
  $(LIBVISCA_ROOT_REL)/src/Visca.cpp \
  $(LOCAL_PATH)/ViscaAndroid.cpp

LOCAL_C_INCLUDES += \
  $(LIBVISCA_ROOT_ABS)/src

LOCAL_EXPORT_C_INCLUDES := \
  $(LIBUSB_ROOT_ABS)/src

LOCAL_CPP_FEATURES += exceptions
LOCAL_LDLIBS := -llog -landroid

LOCAL_MODULE := visca

include $(BUILD_SHARED_LIBRARY)