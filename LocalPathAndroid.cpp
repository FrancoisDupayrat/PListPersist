//
//  LocalPathAndroid.cpp
//  PListPersist
//
//  Created by François Dupayrat on 14/01/13.
//
//

#include "LocalPath"

CCString* getLocalPath(const char* name)
{
	JNIEnv* env = getJNIEnv();
	jclass classId = env->FindClass("com/plistpersist/localpath/LocalPath");
	jmethodID method = env->GetStaticMethodID(classId, "getLocalPath", "()Ljava/lang/String;");
	jstring directory = (jstring)env->CallStaticObjectMethod(classId, method);
	const char *nativeString = env->GetStringUTFChars(directory, 0);
    LOGD("Getting local path : %s, name : %s", nativeString, name);
	CCString* path = ScreateF("%s/%s", nativeString, name);
	env->ReleaseStringUTFChars(directory, nativeString);
	return path;
}