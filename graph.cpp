#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);

    ui->NumOfPoints->setRange(2,1000);
    ui->NumOfPoints->setValue(10);

    redPen.setColor(Qt::red);
    redPen.setWidthF(1.5);
    bluePen.setColor(Qt::blue);
    bluePen.setWidthF(1.5);

    QStringList comboList;
    comboList << "Hp" << "ROCD" << "CAS/TAS" << "GRAD" << "FFLow" << "ACMass";

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

    if(Hp_vect.size()>= points)
    {
        QwtPlotCurve *Hp_line = new QwtPlotCurve("Hp");
        Hp_line->setPen(redPen);
        Hp_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), Hp_vect.mid(Hp_vect.size()-points, points));

        QwtPlotCurve *ROCD_line = new QwtPlotCurve("ROCD");
        ROCD_line->setPen(redPen);
        ROCD_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), ROCD_vect.mid(ROCD_vect.size()-points, points));

        QwtPlotCurve *CAS_line = new QwtPlotCurve("CAS");
        CAS_line->setPen(redPen);
        CAS_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), CAS_vect.mid(CAS_vect.size()-points, points));

        QwtPlotCurve *TAS_line = new QwtPlotCurve("TAS");
        TAS_line->setPen(bluePen);
        TAS_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), TAS_vect.mid(TAS_vect.size()-points, points));

        QwtPlotCurve *GRAD_line = new QwtPlotCurve("Grad");
        GRAD_line->setPen(redPen);
        GRAD_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), GRAD_vect.mid(GRAD_vect.size()-points, points));

        QwtPlotCurve *FFlow_line = new QwtPlotCurve("FFlow");
        FFlow_line->setPen(redPen);
        FFlow_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), FFLow_vect.mid(FFLow_vect.size()-points, points));

        QwtPlotCurve *ACMass_line = new QwtPlotCurve("ACMass");
        ACMass_line->setPen(redPen);
        ACMass_line->setSamples(TIME_vect.mid(TIME_vect.size()-points, points), ACtualMass_vect.mid(ACtualMass_vect.size()-points, points));

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
        else if(value == "ACMass")
        {
            ACMass_line->attach(qwtPlot);
            addTextLabel(qwtPlot, QString::number(ACtualMass_vect.last()) + " [kg]");
        }
    }
    else
    {
        QwtPlotCurve *Hp_line = new QwtPlotCurve("Hp");
        Hp_line->setPen(redPen);
        Hp_line->setSamples(TIME_vect, Hp_vect);

        QwtPlotCurve *ROCD_line = new QwtPlotCurve("ROCD");
        ROCD_line->setPen(redPen);
        ROCD_line->setSamples(TIME_vect, ROCD_vect);

        QwtPlotCurve *CAS_line = new QwtPlotCurve("CAS");
        CAS_line->setPen(redPen);
        CAS_line->setSamples(TIME_vect, CAS_vect);

        QwtPlotCurve *TAS_line = new QwtPlotCurve("TAS");
        TAS_line->setPen(bluePen);
        TAS_line->setSamples(TIME_vect, TAS_vect);

        QwtPlotCurve *GRAD_line = new QwtPlotCurve("Grad");
        GRAD_line->setPen(redPen);
        GRAD_line->setSamples(TIME_vect, GRAD_vect);

        QwtPlotCurve *FFlow_line = new QwtPlotCurve("FFlow");
        FFlow_line->setPen(redPen);
        FFlow_line->setSamples(TIME_vect, FFLow_vect);

        QwtPlotCurve *ACMass_line = new QwtPlotCurve("ACMass");
        ACMass_line->setPen(redPen);
        ACMass_line->setSamples(TIME_vect, ACtualMass_vect);

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
        else if(value == "ACMass")
        {
            ACMass_line->attach(qwtPlot);
            addTextLabel(qwtPlot, QString::number(ACtualMass_vect.last()) + " [kg]");
        }
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
    //            << "fM =" << DATA[9] << "ROCD =" << DATA[10] << "time =" << DATA[11] << "dist =" << DATA[12] << "delta_Hp =" << DATA[13] << "grad =" << DATA[14] << "FFlow =" << DATA[15]
    //            << "FWeigth =" << DATA[16] << "ActualACMass =" << DATA[17];

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
    FWeight_vect.append(DATA[16]);
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
