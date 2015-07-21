//#include "serialthread.h"
//#include "fileutils.h"
//#include <QSerialPort>
//#include <QSerialPortInfo>
//#include <frame.h>
//#include <QDebug>
//#include <QByteArray>

//class FileUtils;
//QSerialPort *SerialThread::serialport = new  QSerialPort;

//SerialThread::SerialThread()
//{
//    if(serialport == NULL){
//        serialport = new QSerialPort;
//    }

//    if(serialport->isOpen()){
//        //停止读取数据
////        readTimer.stop();
//        serialport->close();
//    }
//    else
//    {
//        //设置设备号
//        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//        {
//            serialport->setPortName(info.portName());
//        }
//        serialport->open(QIODevice::ReadWrite);
//        serialport->setBaudRate(9600);
//        //设置数据位
//        serialport->setDataBits((QSerialPort::DataBits)(8));
//        //设置停止位
//        serialport->setStopBits((QSerialPort::StopBits)(1));
//        //校验
//        serialport->setParity((QSerialPort::Parity)(0));//23333333
////        readTimer.start(200);//每隔2ms
////        connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
//        //连接设备
//    }
//}

////析够函数
//SerialThread::~SerialThread()
//{
//    delete this;
//}

//// 发送帧数据
//void SerialThread::sendFrame(char sendBytes[]){
//    serialport->write(sendBytes);
//}

//// 初始化帧
//void SerialThread::sendStartFrame(){
//    int function_mode = FileUtils::project_id;
//    char send[2];
//    switch(function_mode){
//    // Led
//    case 0:
//        send[0]={0x01};
//        send[1]={0xff};
//        break;
//    // Timer
//    case 1:
//        send[0]={0x02};
//        send[1]={0xff};
//        break;
//    //Temperature
//    case 2:
//        send[0]={0x07};
//        send[1]={0xff};
//        break;
//    //Temperature and Humidity
//    case 3:
//        send[0]={0x06};
//        send[1]={0xff};
//        break;
//    // Shake
//    case 4:
//        send[0]={0x05};
//        send[1]={0xff};
//        break;
//    // RFID
//    case 5:
//        send[0]={0x14};
//        send[1]={0xff};
//        break;
//    // Port Communication
//    case 6:
//        send[0]={0x04};
//        send[1]={0xff};
//        break;
//    // Motor
//    case 7:
//        send[0]={0x11};
//        send[1]={0xff};
//        break;
//    // Light
//    case 8:
//        send[0]={0x08};
//        send[1]={0xff};
//        break;
//    // LCD
//    case 9:
//        send[0]={0x13};
//        send[1]={0xff};
//        break;
//    // Interrupt
//    case 10:
//        send[0]={0x03};
//        send[1]={0xff};
//        break;
//    // Infarred
//    case 11:
//        send[0]={0x09};
//        send[1]={0xff};
//        break;
//    // Button
//    case 12:
//        send[0]={0x12};
//        send[1]={0xff};
//        break;
//    // Audio
//    case 13:
//        send[0]={0x10};
//        send[1]={0xff};
//        break;
//    // Comprehensive
//    case 14:
//        send[0]={0x15};
//        send[1]={0xff};
//        break;
//    }
//    serialport->write(send);
//}



//void SerialThread::run(){
//    while(true){
//        QByteArray data;
//        data = this->serialport->readAll();//接受数据
//        char send[2];
//        qDebug()<<data.toHex();
//        int function_mode = FileUtils::project_id;
//        switch(function_mode){
//        // Led
//        case 0:
//            // 判断帧是否正确
//            if(!isFrame(data,0x01,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Timer
//        case 1:
//            // 判断帧是否正确
//            if(!isFrame(data,0x02,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        //Temperature
//        case 2:
//            // 判断帧是否正确
//            if(!isFrame(data,0x07,4)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        //Temperature and Humidity
//        case 3:
//            // 判断帧是否正确
//            if(!isFrame(data,0x06,4)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数

//            break;
//        // Shake
//        case 4:
//            // 判断帧是否正确
//            if(!isFrame(data,0x05,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // RFID
//        case 5:
//            // 判断帧是否正确
//            if(!isFrame(data,0x14)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Port Communication
//        case 6:
//            // 判断帧是否正确
//            if(!isFrame(data,0x04)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数

//            break;
//        // Motor
//        case 7:
//            // 判断帧是否正确
//            if(!isFrame(data,0x11,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Light
//        case 8:
//            // 判断帧是否正确
//            if(!isFrame(data,0x08,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // LCD
//        case 9:
//            // 判断帧是否正确
//            if(!isFrame(data,0x13,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Interrupt
//        case 10:
//            // 判断帧是否正确
//            if(!isFrame(data,0x03,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Infarred
//        case 11:
//            // 判断帧是否正确
//            if(!isFrame(data,0x09,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Button
//        case 12:
//            // 判断帧是否正确
//            if(!isFrame(data,0x12,3)){
//                return;
//            }
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Audio
//        case 13:
//            // 判断帧是否正确
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        // Comprehensive
//        case 14:
//            // 判断帧是否正确
//            if(data.isEmpty()){
//               return;
//            }
//            // 这里要增加相应的槽函数
//            break;
//        }



////        order=(unsigned char)data.at(1);
////        qDebug()<<order + 0x30;
////        if(order == 0){
////            addPeople();
////        }else if(order == 1){
////            removePeople();
//        }

//}
