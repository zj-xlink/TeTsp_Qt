#ifndef SEISMICPLOTWIDGET_H
#define SEISMICPLOTWIDGET_H

#include <QWidget>
#include "tetsp.h"

class QCustomPlot;
class SeismicData;

class SeismicPlotWidget : public QWidget
{
    Q_OBJECT
public:
    SeismicPlotWidget(QWidget *parent = 0, int N=SEGY_SIZE_N, int M=SEGY_SIZE_M);

    void initialSeismicPlotWidget();
    void initialSeismicData(SeismicData *seismicDataX, SeismicData *seismicDataY, SeismicData *seismicDataZ);
    void plotAllCustomPlot();
    void setBgColor(QWidget *widget);

signals:


private:
    void plotGraph(QCustomPlot *customPlot, double data[SEGY_SIZE_N][SEGY_SIZE_M], int N, int M, double dataMax);
    void plotCurve(QCustomPlot *customPlot, double data[SEGY_SIZE_N][SEGY_SIZE_M], int N, int M, double dataMax);

    // 绘制各分量数据的窗口
    QCustomPlot *m_customPlotX;
    QCustomPlot *m_customPlotY;
    QCustomPlot *m_customPlotZ;

    // 各分量地震数据
    double m_DataX[SEGY_SIZE_N][SEGY_SIZE_M];
    double m_DataY[SEGY_SIZE_N][SEGY_SIZE_M];
    double m_DataZ[SEGY_SIZE_N][SEGY_SIZE_M];
    // 数据大小
    int m_DataSizeN;
    int m_DataSizeM;
    double m_DataMaxX;
    double m_DataMaxY;
    double m_DataMaxZ;

public slots:
};

#endif // SEISMICPLOTWIDGET_H
