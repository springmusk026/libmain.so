#include <jni.h>
#include <dlfcn.h>
#include <cstring>
#include <cstdlib>

static void* unityLibraryHandle = nullptr;

extern "C" {

typedef jint (*JNI_OnLoad_t)(JavaVM *vm, void *reserved);

JNIEXPORT jboolean JNICALL
load(JNIEnv *env, jobject activityObject, jstring path) {
    const char *libraryPath = env->GetStringUTFChars(path, nullptr);
    if (!libraryPath) {
        return JNI_FALSE; // Failed to obtain library path
    }

    char fullPath[1000];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", libraryPath, "libunity.so");

    unityLibraryHandle = dlopen(fullPath, RTLD_LAZY | RTLD_LOCAL);
    env->ReleaseStringUTFChars(path, libraryPath);

    if (!unityLibraryHandle) {
        return JNI_FALSE; // Failed to load Unity library
    }

    JNI_OnLoad_t jniOnLoad = reinterpret_cast<JNI_OnLoad_t>(dlsym(unityLibraryHandle, "JNI_OnLoad"));
    if (!jniOnLoad) {
        dlclose(unityLibraryHandle);
        unityLibraryHandle = nullptr;
        return JNI_FALSE; // JNI_OnLoad symbol not found
    }

    JavaVM *vm = nullptr;
    if (env->GetJavaVM(&vm) != JNI_OK) {
        dlclose(unityLibraryHandle);
        unityLibraryHandle = nullptr;
        return JNI_FALSE; // Failed to obtain Java VM
    }

    jint result = jniOnLoad(vm, nullptr);
    if (result < JNI_VERSION_1_6) {
        dlclose(unityLibraryHandle);
        unityLibraryHandle = nullptr;
        return JNI_FALSE; // JNI version mismatch
    }

    return JNI_TRUE; // Successfully loaded Unity library
}

JNIEXPORT jboolean JNICALL
unload(JNIEnv *env, jclass activityObject) {
    if (unityLibraryHandle) {
        dlclose(unityLibraryHandle);
        unityLibraryHandle = nullptr;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    if (vm->GetEnv(reinterpret_cast<void**>(&globalEnv), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // Failed to obtain JNIEnv
    }

    jclass clazz = globalEnv->FindClass("com/unity3d/player/NativeLoader");
    if (!clazz) {
        return JNI_ERR; // Class not found
    }

    static const JNINativeMethod methods[] = {
        {"load",   "(Ljava/lang/String;)Z", reinterpret_cast<void *>(load)},
        {"unload", "()Z",                   reinterpret_cast<void *>(unload)}
    };

    jint ret = globalEnv->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(JNINativeMethod));
    if (ret != JNI_OK) {
        return ret; // Failed to register natives
    }

    return JNI_VERSION_1_6; // Successful initialization
}

} // extern "C"
