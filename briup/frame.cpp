
#include "frame.h"

/**
 * @brief isCommand 判断固定协议帧长度的返回协议帧
 * @param data
 * @param header
 * @param length
 * @return
 */
bool isFrame(QByteArray data,unsigned char header,int length){
    if(data==NULL){
        return false;
    }
    if(data.isEmpty()){          //
        return false;
    }
    if(data.length()!=length||data.at(0)!=header||data.at(data.length()-1)!=-1){
        return false;
    }
    return true;
}

/**
 *
 * @brief isCommand 判断不固定协议帧长度的返回协议帧
 * @param data
 * @param header
 * @return
 */
bool isFrame(QByteArray data, unsigned char header){\
    if(data==NULL){
        return false;
    }
    if(data.isEmpty()){          //
        return false;
    }
    if(data.length()==0||data.at(0)!=header||data.at(data.length()-1)!=-1){
        return false;
    }
    return true;
}

