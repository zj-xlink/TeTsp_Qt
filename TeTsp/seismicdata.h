#ifndef SEISMICDATA_H
#define SEISMICDATA_H

#include <QObject>
#include "tetsp.h"

class SegyFile;

class SeismicData : public QObject
{
    Q_OBJECT
public:
    explicit SeismicData(QObject *parent = 0, SegyFile *segyfile=0);
    void setData(SegyFile *segyfile);

signals:

public slots:

public:
    double m_Data[SEGY_SIZE_N][SEGY_SIZE_M];
    double m_dt;
};

#endif // SEISMICDATA_H
