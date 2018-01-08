#include "seg2stosegys.h"
#include "seg2file.h"
#include "segyfile.h"

Seg2sToSegys::Seg2sToSegys(QObject *parent) : QObject(parent)
{

}
void Seg2sToSegys::setSeg2FileNames(const QStringList &files)
{
    seg2fileNames.clear();
    foreach(QString str, files){
        seg2fileNames.append(str);
    }
}

void Seg2sToSegys::loadSeg2Files()
{
    clearSeg2Files();
    foreach(QString str, seg2fileNames){
        Seg2File *file = new Seg2File(str,this);
        file->readAll();
        seg2files.append(file);
    }
}

void Seg2sToSegys::saveAsSegys(const QString &fileName)
{
    clearSegyFiles();
////////////////////////////////////////////////////////////////
    //int bb[12]={0,1,2, 6,7,8, 3,4,5, 9,10,11};
    //int aa[24]={0,1,2,3,4,5,     13,15,16,19,      10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    //int cc[4]={90,95,95,110};
    //double ttt[8192];

    QString segyfile = seg2fileNames.at(0);
    int index = segyfile.lastIndexOf(QString("/"));
    segyfile.remove(index,segyfile.size()-index);
    segyfile += "/TeTsp_%1_%2.sgy";

    int n = (seg2files.at(0))->spot.sChannelSize;
    int m = seg2files.size();
    for(int i=0; i<n; i++){
        QString temp = segyfile.arg(i/3+1).arg(char('X'+i%3));
        SegyFile *file = new SegyFile(temp,this);
        // 设置卷头信息
        file->tapehead.tChannelNums = m;
        file->tapehead.tSampleTime = (quint16)(seg2files.at(0)->getSampleInterval()*1e6);
        file->tapehead.tSampleNums = seg2files.at(0)->channels.at(0).cSampleNums;
        file->tapehead.tDataType = 1;
        file->tapehead.tUnitMeter = 1;
        file->tapehead.tText.append(QString("ZJ's Segy"));

        for(int j=0; j<m; j++){
            // 设置道信息
            struct SegyChannel channel = {};
            channel.cFldr = 1;
            channel.cTrid = 1;
            channel.cSampleNums = seg2files.at(0)->channels.at(0).cSampleNums;
            channel.cSampleTime = (quint16)(seg2files.at(0)->getSampleInterval()*1e6);

            float temp[N];
            for(int k=0; k<N; k++){
                temp[k] = seg2files.at(j)->channels.at(i).cChannelData[k];
                //if(j>=10)
                //    temp[k] = seg2files.at(aa[j])->channels.at(i).cChannelData[k];
                //if(j<10 && j>5){
                //    if(k+cc[j-6]>N) break;
                //    temp[k] = seg2files.at(aa[j])->channels.at(i).cChannelData[k+cc[j-6]];
                //}
                //if(j<=5)
                //    temp[k] = seg2files.at(aa[j])->channels.at(bb[i]).cChannelData[k];
            }
            memcpy((char*)(channel.data),(char*)(temp),N*4);
            file->channels.append(channel);
        }
        segyfiles.append(file);
    }

    for(int i=0; i<n; i++){
        segyfiles.at(i)->writeAll();
    }

}

void Seg2sToSegys::clearSeg2Files()
{
    foreach(Seg2File *file, seg2files){
        delete file;
    }
    seg2files.clear();
}

void Seg2sToSegys::clearSegyFiles()
{
    foreach(SegyFile *file, segyfiles){
        delete file;
    }
    segyfiles.clear();
}
