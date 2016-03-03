#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    ui->NumOfPoints->setRange(2,10000);
    ui->NumOfPoints->setValue(100);

    redPen.setColor(Qt::red);
    redPen.setWidthF(1.5);
    bluePen.setColor(Qt::blue);
    bluePen.setWidthF(1.5);

    QStringList comboList;
    comboList << "Hp" << "ROCD" << "CAS/TAS" << "GRAD" << "FFLow" << "FWeight" << "ACMass" << "Distance" << "Air Temperature" << "Air Pressure" << "Air Density" << "Thrust" << "Drag" << "Mach" << "Energy Share Factor";

    ui->comboBox_1->insertItems(0,comboList);
    ui->comboBox_2->insertItems(0,comboList);
    ui->comboBox_3->insertItems(0,comboList);
    ui->comboBox_4->insertItems(0,comboList);
    ui->comboBox_5->insertItems(0,comboList);
    ui->comboBox_6->insertItems(0,comboList);

    ui->comboBox_1->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(1);
    ui->comboBox_3->setCurrentIndex(2);
    ui->comboBox_4->setCurrentIndex(3);
    ui->comboBox_5->setCurrentIndex(4);
    ui->comboBox_6->setCurrentIndex(5);

    ui->QwtPlot_1->setCanvasBackground(QColor(Qt::white));
    ui->QwtPlot_2->setCanvasBackground(QColor(Qt::white));
    ui->QwtPlot_3->setCanvasBackground(QColor(Qt::white));
    ui->QwtPlot_4->setCanvasBackground(QColor(Qt::white));
    ui->QwtPlot_5->setCanvasBackground(QColor(Qt::white));
    ui->QwtPlot_6->setCanvasBackground(QColor(Qt::white));

    connect(ui->comboBox_1, SIGNAL(currentIndexChanged(QString)), this, SLOT(combo_1_clicked(QString)));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(combo_2_clicked(QString)));
    connect(ui->comboBox_3, SIGNAL(currentIndexChanged(QString)), this, SLOT(combo_3_clicked(QString)));
    connect(ui->comboBox_4, SIGNAL(currentIndexChanged(QString)), this, SLOT(combo_4_clicked(QString)));
    connect(ui->comboBox_5, SIGNAL(currentIndexChanged(QString)), this, SLOT(combo_5_clicked(QString)));
    connect(ui->comboBox_6, SIGNAL(currentIndexChanged(QString)), this, SLOT(combo_6_clicked(QString)));
}

Graph::~Graph()
{
    delete ui;
}

void Graph::drawGraph()
{
    QString value_1 = ui->comboBox_1->currentText();
    QString value_2 = ui->comboBox_2->currentText();
    QString value_3 = ui->comboBox_3->currentText();
    QString value_4 = ui->comboBox_4->currentText();
    QString value_5 = ui->comboBox_5->currentText();
    QString value_6 = ui->comboBox_6->currentText();

    combo_1_clicked(value_1);
    combo_2_clicked(value_2);
    combo_3_clicked(value_3);
    combo_4_clicked(value_4);
    combo_5_clicked(value_5);
    combo_6_clicked(value_6);
}

double Graph::maximum(const QVector<double> &vector)
{
    double max = 0.0;

    for(int i=0; i<vector.size(); i++)
    {
        if(vector[i] > max)
        {
            max = vector[i];
        }
    }

    return max;
}

double Graph::minimum(const QVector<double> &vector)
{
    double min = 999999;

    for(int i=0; i<vector.size(); i++)
    {
        if(vector[i] < min)
        {
            min = vector[i];
        }
    }

    return min;
}

void Graph::setGrid(QwtPlot *qwtPlot)
{
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::black, 1, Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray, 1, Qt::DotLine));
    grid->attach(qwtPlot);
}

void Graph::setCurve(QwtPlot *qwtPlot, const QString &value)
{
    points = ui->NumOfPoints->value();

    QwtPlotCurve *Hp_line = new QwtPlotCurve("Hp");
    Hp_line->setPen(redPen);
    QwtPlotCurve *ROCD_line = new QwtPlotCurve("ROCD");
    ROCD_line->setPen(redPen);
    QwtPlotCurve *CAS_line = new QwtPlotCurve("CAS");
    CAS_line->setPen(redPen);
    QwtPlotCurve *TAS_line = new QwtPlotCurve("TAS");
    TAS_line->setPen(bluePen);
    QwtPlotCurve *GRAD_line = new QwtPlotCurve("Grad");
    GRAD_line->setPen(redPen);
    QwtPlotCurve *FFlow_line = new QwtPlotCurve("FFlow");
    FFlow_line->setPen(redPen);
    QwtPlotCurve *FWeight_line = new QwtPlotCurve("FWeight");
    FWeight_line->setPen(redPen);
    QwtPlotCurve *ACMass_line = new QwtPlotCurve("ACMass");
    ACMass_line->setPen(redPen);
    QwtPlotCurve *DIST_line = new QwtPlotCurve("Distance");
    DIST_line->setPen(redPen);
    QwtPlotCurve *T_line = new QwtPlotCurve("Air Temperature");
    T_line->setPen(redPen);
    QwtPlotCurve *p_line = new QwtPlotCurve("Air Pressure");
    p_line->setPen(redPen);
    QwtPlotCurve *ro_line = new QwtPlotCurve("Air Density");
    ro_line->setPen(redPen);
    QwtPlotCurve *THR_line = new QwtPlotCurve("Thrust");
    THR_line->setPen(redPen);
    QwtPlotCurve *D_line = new QwtPlotCurve("Drag");
    D_line->setPen(redPen);
    QwtPlotCurve *MACH_line = new QwtPlotCurve("Mach");
    MACH_line->setPen(redPen);
    QwtPlotCurve *fM_line = new QwtPlotCurve("Energy Share Factor");
    fM_line->setPen(redPen);

    if(value == "Hp")
    {
        Hp_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(Hp_vect.last()) + " [ft]");
    }
    else if(value == "ROCD")
    {
        ROCD_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(ROCD_vect.last()) + " [ft/min]");
    }
    else if(value == "CAS/TAS")
    {
        CAS_line->attach(qwtPlot);
        TAS_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(CAS_vect.last()) + "/" + QString::number(TAS_vect.last()) + " [kt]");
    }
    else if(value == "GRAD")
    {
        GRAD_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(GRAD_vect.last()) + " [°]");
    }
    else if(value == "FFLow")
    {
        FFlow_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(FFLow_vect.last()) + " [kg/s]");
    }
    else if(value == "FWeight")
    {
        FWeight_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(FWeight_vect.last()) + " [kg]");
    }
    else if(value == "ACMass")
    {
        ACMass_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(ACtualMass_vect.last()) + " [kg]");
    }
    else if(value == "Distance")
    {
        DIST_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(DIST_vect.last()) + " [NM]");
    }
    else if(value == "Air Temperature")
    {
        T_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(T_vect.last()) + " [K]");
    }
    else if(value == "Air Pressure")
    {
        p_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(p_vect.last()) + " [Pa]");
    }
    else if(value == "Air Density")
    {
        ro_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(ro_vect.last()) + " [kg/m3]");
    }
    else if(value == "Thrust")
    {
        THR_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(THR_vect.last()) + " [N]");
    }
    else if(value == "Drag")
    {
        D_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(D_vect.last()) + " [N]");
    }
    else if(value == "Mach")
    {
        MACH_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(MACH_vect.last()) + " [-]");
    }
    else if(value == "Energy Share Factor")
    {
        fM_line->attach(qwtPlot);
        addTextLabel(qwtPlot, QString::number(fM_vect.last()) + " [-]");
    }





    if(Hp_vect.size()>= points)
    {
        Hp_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), Hp_vect.mid(Hp_vect.size()-points, points));
        ROCD_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), ROCD_vect.mid(ROCD_vect.size()-points, points));
        CAS_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), CAS_vect.mid(CAS_vect.size()-points, points));
        TAS_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), TAS_vect.mid(TAS_vect.size()-points, points));
        GRAD_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), GRAD_vect.mid(GRAD_vect.size()-points, points));
        FFlow_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), FFLow_vect.mid(FFLow_vect.size()-points, points));
        FWeight_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), FWeight_vect.mid(FWeight_vect.size()-points, points));
        ACMass_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), ACtualMass_vect.mid(ACtualMass_vect.size()-points, points));
        DIST_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), DIST_vect.mid(DIST_vect.size()-points, points));
        T_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), T_vect.mid(T_vect.size()-points, points));
        p_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), p_vect.mid(p_vect.size()-points, points));
        ro_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), ro_vect.mid(ro_vect.size()-points, points));
        THR_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), THR_vect.mid(THR_vect.size()-points, points));
        D_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), D_vect.mid(D_vect.size()-points, points));
        MACH_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), MACH_vect.mid(MACH_vect.size()-points, points));
        fM_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), fM_vect.mid(fM_vect.size()-points, points));
    }
    else
    {
        Hp_line->setSamples(TIME_vect, Hp_vect);
        ROCD_line->setSamples(TIME_vect, ROCD_vect);
        CAS_line->setSamples(TIME_vect, CAS_vect);
        TAS_line->setSamples(TIME_vect, TAS_vect);
        GRAD_line->setSamples(TIME_vect, GRAD_vect);
        FFlow_line->setSamples(TIME_vect, FFLow_vect);
        FWeight_line->setSamples(TIME_vect, FWeight_vect);
        ACMass_line->setSamples(TIME_vect, ACtualMass_vect);
        DIST_line->setSamples(TIME_vect, DIST_vect);
        T_line->setSamples(TIME_vect, T_vect);
        p_line->setSamples(TIME_vect, p_vect);
        ro_line->setSamples(TIME_vect, ro_vect);
        THR_line->setSamples(TIME_vect, THR_vect);
        D_line->setSamples(TIME_vect, D_vect);
        MACH_line->setSamples(TIME_vect, MACH_vect);
        fM_line->setSamples(TIME_vect, fM_vect);
    }
}

void Graph::setLegend(QwtPlot *qwtPlot)
{
    QwtLegend *legend = new QwtLegend;
    qwtPlot->insertLegend( legend, QwtPlot::BottomLegend );
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
}

void Graph::addTextLabel(QwtPlot *qwtPlot, const QString &text)
{
    QwtText title(text);
    title.setRenderFlags( Qt::AlignHCenter | Qt::AlignTop );

    QFont font;
    font.setBold( true );
    title.setFont( font );

    QwtPlotTextLabel *titleItem = new QwtPlotTextLabel();
    titleItem->setText( title );
    titleItem->attach(qwtPlot);
}

void Graph::receive_data(const QVector<double> &DATA)
{
    //qDebug() << "Hp_actual =" << DATA[0] << "T =" << DATA[1] << "p =" << DATA[2] << "ro =" << DATA[3] << "CAS =" << DATA[4] << "TAS =" << DATA[5] << "Thr =" << DATA[6] << "D =" << DATA[7] << "mach =" << DATA[8]
    //         << "fM =" << DATA[9] << "ROCD =" << DATA[10] << "time =" << DATA[11] << "dist =" << DATA[12] << "delta_Hp =" << DATA[13] << "grad =" << DATA[14] << "FFlow =" << DATA[15]
    //         << "FWeigth =" << DATA[16] << "ActualACMass =" << DATA[17] << "FWeight_total" << DATA[19];

    Hp_vect.append(DATA[0]);
    T_vect.append(DATA[1]);
    p_vect.append(DATA[2]);
    ro_vect.append(DATA[3]);
    CAS_vect.append(DATA[4]);
    TAS_vect.append(DATA[5]);
    THR_vect.append(DATA[6]);
    D_vect.append(DATA[7]);
    MACH_vect.append(DATA[8]);
    fM_vect.append(DATA[9]);
    ROCD_vect.append(DATA[10]);

    if(TIME_vect.size() > 0)
    {
        TIME_vect.append(TIME_vect.at(TIME_vect.size()-1) + DATA[11]);
    }
    else
    {
        TIME_vect.append(0);
    }

    DIST_vect.append(DATA[12]);
    DeltaHp_vect.append(DATA[13]);
    GRAD_vect.append(DATA[14]);
    FFLow_vect.append(DATA[15]);
    FWeight_vect.append(DATA[19]);
    ACtualMass_vect.append(DATA[17]);

    drawGraph();
}

void Graph::startClicked_slot()
{
    Hp_vect.clear();
    T_vect.clear();
    p_vect.clear();
    ro_vect.clear();
    CAS_vect.clear();
    TAS_vect.clear();
    THR_vect.clear();
    D_vect.clear();
    MACH_vect.clear();
    fM_vect.clear();
    ROCD_vect.clear();
    TIME_vect.clear();
    DIST_vect.clear();
    DeltaHp_vect.clear();
    GRAD_vect.clear();
    FFLow_vect.clear();
    FWeight_vect.clear();
    ACtualMass_vect.clear();
}

void Graph::combo_1_clicked(const QString &value)
{
    // set Grid
    ui->QwtPlot_1->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    setGrid(ui->QwtPlot_1);

    // set Curve
    setCurve(ui->QwtPlot_1, value);

    // set legend
    setLegend(ui->QwtPlot_1);

    ui->QwtPlot_1->replot();
}

void Graph::combo_2_clicked(const QString &value)
{
    // set Grid
    ui->QwtPlot_2->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    setGrid(ui->QwtPlot_2);

    // set Curve
    setCurve(ui->QwtPlot_2, value);

    // set legend
    setLegend(ui->QwtPlot_2);

    ui->QwtPlot_2->replot();
}

void Graph::combo_3_clicked(const QString &value)
{
    ui->QwtPlot_3->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    setGrid(ui->QwtPlot_3);

    // set Curve
    setCurve(ui->QwtPlot_3, value);

    // set legend
    setLegend(ui->QwtPlot_3);

    ui->QwtPlot_3->replot();
}

void Graph::combo_4_clicked(const QString &value)
{
    ui->QwtPlot_4->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    setGrid(ui->QwtPlot_4);

    // set Curve
    setCurve(ui->QwtPlot_4, value);

    // set legend
    setLegend(ui->QwtPlot_4);

    ui->QwtPlot_4->replot();
}

void Graph::combo_5_clicked(const QString &value)
{
    // set Grid
    ui->QwtPlot_5->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    setGrid(ui->QwtPlot_5);

    // set Curve
    setCurve(ui->QwtPlot_5, value);

    // set legend
    setLegend(ui->QwtPlot_5);

    ui->QwtPlot_5->replot();
}

void Graph::combo_6_clicked(const QString &value)
{
    // set Grid
    ui->QwtPlot_6->detachItems(QwtPlotItem::Rtti_PlotItem, false);
    setGrid(ui->QwtPlot_6);

    // set Curve
    setCurve(ui->QwtPlot_6, value);

    // set legend
    setLegend(ui->QwtPlot_6);

    ui->QwtPlot_6->replot();
}
