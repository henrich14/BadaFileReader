#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <qwt.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_textlabel.h>

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT
    
public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();

    void drawGraph();
    double maximum(const QVector<double> &vector);
    double minimum(const QVector<double> &vector);

    void setGrid(QwtPlot *qwtPlot);
    void setCurve(QwtPlot *qwtPlot, const QString &value);
    void setLegend(QwtPlot *qwtPlot);
    void addTextLabel(QwtPlot *qwtPlot, const QString &text);
    
private:
    Ui::Graph *ui;

    QVector<double> Hp_vect;
    QVector<double> T_vect;
    QVector<double> p_vect;
    QVector<double> ro_vect;
    QVector<double> CAS_vect;
    QVector<double> TAS_vect;
    QVector<double> THR_vect;
    QVector<double> D_vect;
    QVector<double> MACH_vect;
    QVector<double> fM_vect;
    QVector<double> ROCD_vect;
    QVector<double> TIME_vect;
    QVector<double> DIST_vect;
    QVector<double> DeltaHp_vect;
    QVector<double> GRAD_vect;
    QVector<double> FFLow_vect;
    QVector<double> FWeight_vect;
    QVector<double> ACtualMass_vect;

    double FWeight_init;
    double DIST_init;

    QPen redPen;
    QPen bluePen;

    int points;

private slots:
    void receive_data(const QVector<double> &DATA);
    void startClicked_slot();

    void combo_1_clicked(const QString &value);
    void combo_2_clicked(const QString &value);
    void combo_3_clicked(const QString &value);
    void combo_4_clicked(const QString &value);
    void combo_5_clicked(const QString &value);
    void combo_6_clicked(const QString &value);
};

#endif // GRAPH_H
