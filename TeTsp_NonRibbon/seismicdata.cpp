#include "seismicdata.h"
#include "segyfile.h"

#include <QMessageBox>

SeismicData::SeismicData(QObject *parent, SegyFile *segyfile) : QObject(parent)
{
    if(segyfile){
        setData(segyfile);
    }
}
void SeismicData::setData(SegyFile *segyfile)
{
    int NN=segyfile->tapehead.tSampleNums;
    if(NN>8192) NN = 8192;

    m_dt = segyfile->tapehead.tSampleTime;
    for(int i=0; i<segyfile->tapehead.tChannelNums;i++){
        for(int j=0; j<NN;j++){
            m_Data[j][i] = segyfile->channels_read.at(i).data[j];
        }
    }
}
