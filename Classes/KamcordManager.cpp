#include "KamcordManager.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

namespace platform {
	#define CLASS_NAME "jp/co/translimit/casual/videorec/KamcordManager"

    platform::KamcordManager::KamcordManager(){
    };

    platform::KamcordManager::~KamcordManager(){
    };

    KamcordManager* KamcordManager::getInstance()
    {
        static KamcordManager manager;
        return &manager;
    }

    void KamcordManager::setup(std::string key, std::string secret, std::string appName)
    {
    	cocos2d::JniMethodInfo t;
    	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setup", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {

    		// string生成
    		jstring jkey = t.env->NewStringUTF(key.c_str());
    		jstring jsecret = t.env->NewStringUTF(secret.c_str());
    		jstring jappName = t.env->NewStringUTF(appName.c_str());

    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jkey, jsecret, jappName);
    	    t.env->DeleteLocalRef(t.classID);
    	}
    }

    void KamcordManager::startRecording()
    {
    	cocos2d::JniMethodInfo t;
    	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "startRecording", "()V")) {
    		t.env->CallStaticVoidMethod(t.classID, t.methodID);
    	    t.env->DeleteLocalRef(t.classID);
    	}
    }

    void KamcordManager::stopRecording()
    {
    	cocos2d::JniMethodInfo t;
    	if (cocos2d::JniHelper::getStaticMethodInfo(t, CLASS_NAME, "stopRecording", "()V")) {
    		t.env->CallStaticVoidMethod(t.classID, t.methodID);
    	    t.env->DeleteLocalRef(t.classID);
    	}
    }

    void KamcordManager::pauseRecording()
    {
    }

    void KamcordManager::resumeRecording()
    {
    }

}
