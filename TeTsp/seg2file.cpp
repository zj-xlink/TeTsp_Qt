#include <QIODevice>

#include "seg2file.h"

Seg2File::Seg2File(const QString &name, QObject *parent)
    :QFile(name,parent),
      spot{}
{

}

bool Seg2File::readAll()
{
    channels.clear();

    bool state = false;
    quint8 num;
    quint8 ch;
    quint32 point;
    QString str;
    struct Seg2Channel channel;

    if(open(QIODevice::ReadOnly)){
        // 读取炮头二进制文件
        read((char*)&spot,32);
        // 读取各道头位置
        for(int i=0; i<spot.sChannelSize; i++){
            read((char*)&point,sizeof(point));
            spot.sChannelPoints.append(point);
        }
        // 读取炮头文本文件
        while(this->pos() < spot.sChannelPoints.at(0)){
            read((char*)&num,1);
            for(int i=1;i<num;i++){
                read((char*)&ch,1);
                if(ch != 0)
                    str += ch;
            }
            spot.sSpotString.append(str);
            str.clear();
        }

        //  读取各道信息
        for(int i=0; i<spot.sChannelSize; i++){
            // 读取道头二进制信息
            this->seek(spot.sChannelPoints.at(i)); // 定位到道头i
            read((char*)&channel,32);

            // 读取道头文本文件
            while(this->pos() < spot.sChannelPoints.at(i)+channel.cHeadSize){
                read((char*)&num,1);
                for(int i=1;i<num;i++){
                    read((char*)&ch,1);
                    if(ch != 0)
                        str += ch;
                }
                channel.cChannelString.append(str);
                str.clear();
            }

            // 读取道数据
            read((char*)&(channel.cChannelData),channel.cDataSize);

            channels.append(channel);
        }
        close();
        state = true;
    }
    return state;
}

double Seg2File::getSampleInterval()
{
    double si=0, temp=0;
    int index;

    QStringList list = channels.at(0).cChannelString;
    foreach(QString str, list){
        index = str.indexOf(QString("SAMPLE_INTERVAL"));
        temp = str.mid(index+15).toDouble();

        if(temp>0) si = temp;
    }
    return si;
}


