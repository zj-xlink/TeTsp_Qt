#include <QMessageBox>
#include <QtMath>

#include "seismicplotwidget.h"
#include "qcustomplot.h"
#include "seismicdata.h"


SeismicPlotWidget::SeismicPlotWidget(QWidget *parent, int N, int M) :
    QWidget(parent),
    m_DataSizeM(M),
    m_DataSizeN(N),
    m_DataMaxX(0),
    m_DataMaxY(0),
    m_DataMaxZ(0)
{
    initialSeismicPlotWidget();
}

void SeismicPlotWidget::initialSeismicPlotWidget()
{
    // 创建主面板及水平布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    // 添加XYZ分量绘制坐标
    m_customPlotX = new QCustomPlot(this);
    m_customPlotY = new QCustomPlot(this);
    m_customPlotZ = new QCustomPlot(this);
    mainLayout->addWidget(m_customPlotX);
    mainLayout->addWidget(m_customPlotY);
    mainLayout->addWidget(m_customPlotZ);

    // XYZ面板坐标初始化
    //m_customPlotX->xAxis->setVisible(false);
    //m_customPlotX->xAxis2->setVisible(true);
    m_customPlotX->yAxis->setRangeReversed(true);
    //m_customPlotY->xAxis->setVisible(false);
    //m_customPlotY->xAxis2->setVisible(true);
    m_customPlotY->yAxis->setRangeReversed(true);
    //m_customPlotZ->xAxis->setVisible(false);
    //m_customPlotZ->xAxis2->setVisible(true);
    m_customPlotZ->yAxis->setRangeReversed(true);

    setBgColor(this->parentWidget());
}

void SeismicPlotWidget::initialSeismicData(SeismicData *seismicDataX, SeismicData *seismicDataY, SeismicData *seismicDataZ)
{
    double temp;

    for(int i=0; i<m_DataSizeN; i++){
        for(int j=0; j<m_DataSizeM;j++){
            temp = seismicDataX->m_Data[i][j];
            m_DataX[i][j] = temp;
            if(qAbs(temp)>m_DataMaxX) m_DataMaxX = qAbs(temp);

            temp = seismicDataY->m_Data[i][j];
            m_DataY[i][j] = temp;
            if(qAbs(temp)>m_DataMaxY) m_DataMaxY = qAbs(temp);

            temp = seismicDataZ->m_Data[i][j];
            m_DataZ[i][j] = temp;
            if(qAbs(temp)>m_DataMaxZ) m_DataMaxZ = qAbs(temp);
        }
    }
}

void SeismicPlotWidget::plotGraph(QCustomPlot *customPlot,double data[SEGY_SIZE_N][SEGY_SIZE_M], int N, int M, double dataMax)
{
    QPen pen;

    customPlot->clearGraphs();

    QVector<double> x(N),y(N);
    for(int i=0; i<M;i++){
        customPlot->addGraph();
        pen.setColor(QColor(0,0,0));
        customPlot->graph()->setPen(pen);
        for(int j=0;j<N;j++){
            x[j] = i+1+ data[j][i]/dataMax/2.0;
            y[j] = j;
           // QMessageBox::information(this,QString("%1").arg(dataMax),QString("%1").arg(dataMax));
        }
        customPlot->graph()->setData(x,y);
        customPlot->graph()->rescaleAxes(true);
    }

    // zoom out a bit:
    //customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
    //customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());

    // set blank axis lines:
    //customPlot->xAxis->setTicks(false);
    //customPlot->yAxis->setTicks(true);
    //customPlot->xAxis->setTickLabels(false);
    //customPlot->yAxis->setTickLabels(true);

    // make top right axes clones of bottom left axes:
    // customPlot->axisRect()->setupFullAxesBox();

    customPlot->replot();
}

void SeismicPlotWidget::plotCurve(QCustomPlot *customPlot,double data[SEGY_SIZE_N][SEGY_SIZE_M], int N, int M, double dataMax)
{
    // 清理曲线
    customPlot->clearPlottables();
    customPlot->clearItems();
    customPlot->clearGraphs();

    // 正负曲线(红、蓝)
    QCPCurve *curvePos,*curveNeg;
    // 正负曲线数据
    QVector<QCPCurveData> dataPos(N);
    QVector<QCPCurveData> dataNeg(N);

    double posx, tempx, negx;
    // 绘制每一条曲线
    for(int i=0; i<M; i++){
        // 新建正负曲线
        curvePos = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        curveNeg = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        // 配置曲线数据
        for (int j=0; j<N; j++){
            tempx = data[j][i]/dataMax/2.0*10;
            // 配置正曲线数据
            if(tempx>0){
                posx = i+1+ tempx;
                negx = i+1;
            }else{// 配置负曲线数据
                posx = i+1;
                negx = i+1+tempx;
            }
            // 校正绘制
            if(j==0){
                posx=i+1;
                negx=i+1;
            }
            dataPos[j] = QCPCurveData(j, posx, j/32000.0);
            dataNeg[j] = QCPCurveData(j, negx, j/32000.0);
        }

        // 设置曲线数据
        curvePos->data()->set(dataPos, true);
        curveNeg->data()->set(dataNeg, true);
        // 设置透明画笔和背景色
        curvePos->setPen(QPen(Qt::transparent));
        curvePos->setBrush(QBrush(QColor(255, 0, 0)));
        curveNeg->setPen(QPen(Qt::transparent));
        curveNeg->setBrush(QBrush(QColor(0, 0, 255)));


    }
    // 设置图像参数
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->rescaleAxes();

    customPlot->replot();
}


void SeismicPlotWidget::plotAllCustomPlot()
{
    plotCurve(m_customPlotX,m_DataX, m_DataSizeN, m_DataSizeM, m_DataMaxX);
    plotCurve(m_customPlotY,m_DataY, m_DataSizeN, m_DataSizeM, m_DataMaxY);
    plotCurve(m_customPlotZ,m_DataZ, m_DataSizeN, m_DataSizeM, m_DataMaxZ);
}


void SeismicPlotWidget::setBgColor(QWidget *widget)
{
    QPalette pal = widget->palette();
    QBrush brush = pal.background();

    m_customPlotX->setBackground(brush);
    m_customPlotY->setBackground(brush);
    m_customPlotZ->setBackground(brush);
}
