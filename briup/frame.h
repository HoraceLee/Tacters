#ifndef COMMAND_H
#define COMMAND_H

#include <QByteArray>

bool isFrame(QByteArray data,unsigned char haeder,int length);

bool isFrame(QByteArray data,unsigned char haeder);

#endif // COMMAND_H

