//
// Created by peakchao on 19-3-20.
//
#include <jni.h>
#include <stdlib.h>
#include <memory.h>
#include "../jni/ndk_peakchao_com_androidndk_EncryptionAndDecryptUtil.h"

const char *DES_KEY = "12345678912345678912345678912345";

//把java的字符串转换成c的字符串,使用反射
char *Jstring2CStr(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    //1:先找到字节码文件
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    //2:通过字节码文件找到方法ID
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    //3:通过方法id，调用方法
    jbyteArray barr = (jbyteArray) (*env)->CallObjectMethod(env, jstr, mid,
                                                            strencode); // String .getByte("GB2312");
    //4:得到数据的长度
    jsize alen = (*env)->GetArrayLength(env, barr);
    //5：得到数据的首地址
    jbyte *ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    //6:得到C语言的字符串
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);         //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);  //
    return rtn;
}

/*
 * Class:     ndk_peakchao_com_androidndk_EncryptionAndDecryptUtil
 * Method:    Encryption
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ndk_peakchao_com_androidndk_EncryptionAndDecryptUtil_Encryption
        (JNIEnv *env, jclass jclass1, jstring jstr) {
    if (jstr == NULL) {
        return NULL;
    }
    jstring key;
    jstring result;
    jclass AESencrypt;
    jmethodID mid;

    // 1、从classpath路径下搜索ClassMethod这个类，并返回该类的Class对象
    AESencrypt = (*env)->FindClass(env, "ndk/peakchao/com/androidndk/EncryptionAndDecryptUtil");
    if (NULL == AESencrypt) {
        return NULL;
    }
    // 2、从clazz类中查找callStaticMethod方法
    mid = (*env)->GetStaticMethodID(env, AESencrypt, "encrypt",
                                    "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (NULL == mid) {
        (*env)->DeleteLocalRef(env, AESencrypt);
        return NULL;
    }


    key = (*env)->NewStringUTF(env, DES_KEY);
    // 3、调用clazz类的callStaticMethod静态方法
    result = (*env)->CallStaticObjectMethod(env, AESencrypt, mid, key, jstr);
    // 删除局部引用
    (*env)->DeleteLocalRef(env, AESencrypt);
    (*env)->DeleteLocalRef(env, key);

    /****************************************************************************************************/
    //1:将java的字符串转化为c语言
    char *cstr = Jstring2CStr(env, result);
    int i = 0;
    //2:给C语言字符加1
    for (i = 0; i < strlen(cstr); i++) {
        int num = 0;
        if (i % 2 == 0) {
            num = 1;
        } else {
            num = 2;
        }
        *(cstr + i) += num;
    }
    //3:将c语言字符串转化为java字符串
    jstring str = (*env)->NewStringUTF(env, cstr);
    /****************************************************************************************************/

    return str;
}

/*
 * Class:     ndk_peakchao_com_androidndk_EncryptionAndDecryptUtil
 * Method:    Decrypt
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ndk_peakchao_com_androidndk_EncryptionAndDecryptUtil_Decrypt
        (JNIEnv *env, jclass jclass1, jstring jstr) {
    if (jstr == NULL) {
        return NULL;
    }
    jstring key;
    jstring result;
    jclass AESencrypt;
    jmethodID mid;

    AESencrypt = (*env)->FindClass(env, "ndk/peakchao/com/androidndk/EncryptionAndDecryptUtil");
    if (NULL == AESencrypt) {
        return NULL;
    }
    mid = (*env)->GetStaticMethodID(env, AESencrypt, "decrypt",
                                    "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    if (NULL == mid) {
        (*env)->DeleteLocalRef(env, AESencrypt);
        return NULL;
    }
    key = (*env)->NewStringUTF(env, DES_KEY);

    /****************************************************************************************************/
    //1:将java的字符串转化为c语言
    char *cstr = Jstring2CStr(env, jstr);
    int i = 0;
    //2:给C语言字符加1
    for (i = 0; i < strlen(cstr); i++) {
        int num = 0;
        if (i % 2 == 0) {
            num = 1;
        } else {
            num = 2;
        }
        *(cstr + i) -= num;
    }
    //3:将c语言字符串转化为java字符串
    jstring str = (*env)->NewStringUTF(env, cstr);
    /****************************************************************************************************/

    result = (*env)->CallStaticObjectMethod(env, AESencrypt, mid, key,
                                            str);
    (*env)->DeleteLocalRef(env, AESencrypt);
    (*env)->DeleteLocalRef(env, key);

    return result;

}

