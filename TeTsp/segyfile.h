#ifndef SEGYFILE_H
#define SEGYFILE_H

#include <QFile>

#define N 8192

// 卷头:3600字节
struct TapeHead{
    quint8 tReserved1[12]; // 保留:3201-3212
    quint16 tChannelNums; // 每个记录的数据道数:3213-3214
    quint8 tReserved2[2]; // 保留:3215-3216
    quint16 tSampleTime; // 采用间隔(us):3217-3218
    quint8 tReserved3[2]; // 保留:3219-3220
    quint16 tSampleNums; // 样点数/每道:3221-3222
    quint8 tReserved4[2]; // 保留:3223-3224
    quint16 tDataType; // 数据样值格式码1-浮点:3225-3226
    quint8 tReserved5[28]; // 保留:3227-3254
    quint16 tUnitMeter; // 记录系统:1-米，2-英尺:3255-3256
    quint8 tReserved6[344]; // 保留:3257-3600
    QStringList tText; // 卷头文本 40行*80: 1-3200
};

// 道头与数据
struct SegyChannel{
    quint8 cReserved1[8]; // 保留:1-8
    quint32 cFldr; // 原始野外记录号:9-12
    quint8 cReserved2[16]; // 保留:13-28
    quint16 cTrid; /* 道识别码:29-30
                      1 = seismic data
                      2 = dead
                      3 = dummy
                      4 = time break
                      5 = uphole
                      6 = sweep
                      7 = timing
                      8 = water break
                      9---, N = optional use (N = 32,767) */

    quint8 cReserved3[84]; // 保留:31-114
    quint16 cSampleNums; // 本道的采样点数:115-116
    quint16 cSampleTime; // 本道的采样间隔:117-118
    quint8 cReserved4[122];	// 保留:119-240
    quint32 data[N]; // 数据段区
};
struct SegyChannelRead{
    quint8 cReserved1[8]; // 保留:1-8
    quint32 cFldr; // 原始野外记录号:9-12
    quint8 cReserved2[16]; // 保留:13-28
    quint16 cTrid; /* 道识别码:29-30
                      1 = seismic data
                      2 = dead
                      3 = dummy
                      4 = time break
                      5 = uphole
                      6 = sweep
                      7 = timing
                      8 = water break
                      9---, N = optional use (N = 32,767) */

    quint8 cReserved3[84]; // 保留:31-114
    quint16 cSampleNums; // 本道的采样点数:115-116
    quint16 cSampleTime; // 本道的采样间隔:117-118
    quint8 cReserved4[122];	// 保留:119-240
    float data[N]; // 数据段区
};


class Seg2File;

class SegyFile : public QFile
{
public:
    SegyFile(const QString &name, QObject *parent = 0);

    bool readAll();
    bool writeAll();
    bool setAll(const Seg2File &seg2file);

    struct TapeHead tapehead;
    QList<struct SegyChannel> channels;
    QList<struct SegyChannelRead> channels_read;
};

#endif // SEGYFILE_H
