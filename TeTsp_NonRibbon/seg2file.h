#ifndef SEG2FILE_H
#define SEG2FILE_H

#include <QFile>

#define N 8192

// 炮头
struct SpotHead{
    quint16 sId; // 炮头标识:0-1
    quint16 sFxg; // 版本号:2-3
    quint16 sPointSize; // 道头指针尺寸:4-5
    quint16 sChannelSize; // 文件中的道数:6-7
    quint8 sAscii; // 串结束符尺寸:8
    quint8 sAscii1; // 第一个串结束符:9
    quint8 sAscii2; // 第二个串结束符:10
    quint8 sLineend; // 换行符尺寸:11
    quint8 sLineend1; // 第一个换行符:12
    quint8 sLineend2;  // 第二个换行符:13
    quint8 sResreved[18]; // 保留:14-31
    QList<quint32> sChannelPoints; // 道指针
    QStringList sSpotString; // 炮头文本信息
};

// 道信息
struct Seg2Channel{
    quint16 cId; // 道头标志:0-1
    quint16 cHeadSize; // 道头尺寸:2-3
    quint32 cDataSize; // 数据段长度(样点数x4):4-7
    quint32 cSampleNums; // 样点数/道:8-11
    quint8 cDataType; // 数据段格式码
    quint8 cReserved[19]; // 保留:13-31
    QStringList cChannelString; // 道头文本信息
    qint32 cChannelData[N]; // 道数据
};


class Seg2File : public QFile
{
public:
    Seg2File(const QString &name, QObject *parent=0);

    bool readAll();
    double getSampleInterval();

    struct SpotHead spot; // 炮头
    QList<struct Seg2Channel> channels; // 道头

};

#endif // SEG2FILE_H
