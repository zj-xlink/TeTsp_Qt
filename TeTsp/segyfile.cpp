#include "segyfile.h"
#include "seg2file.h"

SegyFile::SegyFile(const QString &name, QObject *parent)
    :QFile(name,parent),
      tapehead{}
{

}

bool SegyFile::writeAll()
{

    bool state = false;
    const char *pch;

    if(open(QIODevice::WriteOnly)){
        this->seek(0);

        // 写卷头文本
        for(int i=0; i<tapehead.tText.size(); i++){
            pch = tapehead.tText.at(i).toStdString().c_str();
            write(pch,80);
            seek(i*80-80);
        }
        // 写卷头二进制信息
        seek(3200);
        write((char*)&tapehead,400);

        // 写各道信息
        for(int i=0; i<channels.size(); i++){
            write((char*)&(channels.at(i)),sizeof(struct SegyChannel));
        }
        close();
        state = true;
    }

    return state;
}

bool SegyFile::readAll()
{
    channels_read.clear();

    bool state = false;
    char line[80];
    struct SegyChannelRead channel;

    if(open(QIODevice::ReadOnly)){
        this->seek(0);
        tapehead.tText.clear();
        // 读卷头文本
        for(int i=0; i<40; i++){
            read(line,80);
            tapehead.tText.append(QString(line));
        }
        // 读卷头二进制信息
        read((char*)&tapehead,400);

        // 读各道信息
        for(int i=0; i<tapehead.tChannelNums; i++){
            read((char*)&channel,sizeof(struct SegyChannelRead));
            channels_read.append(channel);
        }
        close();
        state =  true;
    }
    return state;
}
