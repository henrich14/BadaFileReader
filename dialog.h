#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QFile>
#include <QDebug>
#include <QHash>
#include <QTextStream>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    double temperatureDetermination(const double &altitude);
    double airPressureDetermination(const double &altitude);
    double airDensityDetermination(const double &temperature, const double &pressure);
    double speedOfSoundDetermination(const double &temperature);
    double CAStoTAS(const double &vCAS, const double &pressure, const double &density);
    double TAStoCAS(const double &vTAS, const double &pressure, const double &density);
    double MtoTAS(const double &vM, const double &temperature);
    double TAStoM(const double &vTAS, const double &temperature);
    double transitionAltitude(const double &vCAS, const double &vM);

    void readAPFfile(const QString &fileName);
    void readOPFfile(const QString &fileName);
    QStringList parseLine(const QString &line);
    double CASschedule(const double &altitude, const double &transAlt, const QString &phase, const double &ACMass);
    double calculateShareFactor(const double &M, const double &T, const QString &factor);
    double calculateMaxClimbThrust(const double &altitude);
    double calculateDescentThrust(const double &altitude, const QString &config);
    double calculateDrag(const double &m, const double &ro, const double &vTAS, const double &bankAngle, const QString &config);
    QString getFlightConfiguration(const QString &phase, const double &altitude, const double &vCAS);
    double getFlightTime(const double &ROCD, const double &delta_Hp);
    double getFlightDistance(const double &time, const double &vTAS);
    double getGradient(const double &delta_Hp, const double &distance);
    double nominalFuelFlow(const double &vTAS, const double &Thr); // thrust specific fuel consumption
    double minimalFuelFlow(const double &altitude);
    double cruiseFuelFlow(const double &Thr, const double &vTAS);
    double fuelFlow(const double &vTAS, const double &Thr, const double &altitude, const QString &phase, const QString flightConfig);
    double fuelWeight(const double &fuelflow, const double &time);

    double getMinCAS(const double &vmin, const double &buffetLimit, const double &altitude);
    double buffetingLimit(const double &pressure, const double &ACweight);
    double calculateVmin(const QString &phase);
    double correctedSpeed(const double &v_ref, const double &actualACMass);
    double getMaxAltitude(const double &ActualACMass);
    double knotsTOmps(const double &knots);
    double mpsTOknots(const double &mps);
    double mpsTOftpmin(const double &mps);
    double ftpminTOmps(const double &ftpmin);
    double ftTOm(const double &ft);
    double mTOft(const double &meter);
    double mtoNM(const double &meter);
    double NMtom(const double &NM);

    double ROCDcalc(const double &T, const double &vTAS, const double &thrust, const double &drag, const double &m, const double &shareFactor);
    void run();
    void exportData(const QString &filename, const QVector<double> &Hp, const QVector<double> &ACMass, const QVector<double> &CAS, const QVector<double> &TAS, const QVector<double> &MACH, const QVector<double> &ROCD, const QVector<double> &gradient, const QVector<double> &FuelFlow, const QVector<double> &Fuel, const QVector<double> &Time, const QVector<double> &Distance, const QVector<double> &Thr, const QVector<double> &D, const QVector<double> &fM);
    
private:
    Ui::Dialog *ui;

    QString companyName;
    QHash<QString, int> Vcl1;
    QHash<QString, int> Vcl2;
    QHash<QString, int> Mcl;
    QHash<QString, int> Vcr1;
    QHash<QString, int> Vcr2;
    QHash<QString, int> Mcr;
    QHash<QString, int> Mdes;
    QHash<QString, int> Vdes1;
    QHash<QString, int> Vdes2;

    QString ICAO;
    int NumOfEngines;
    QString EngineType;
    QString WakeCat;
    double m_ref;
    double m_min;
    double m_max;
    double m_pyld;
    double G_w;
    double V_MO;
    double M_MO;
    double h_MO;
    double h_max;
    double G_t;
    double S;
    double C_lbo;
    double k;
    double C_M16;
    QHash<QString, double> V_stall;
    QHash<QString, double> C_D0;
    QHash<QString, double> C_D2;
    QHash<QString, QString> PhaseChar;
    double C_D0deltaLDG;

    double C_Tc1;
    double C_Tc2;
    double C_Tc3;
    double C_Tc4;
    double C_Tc5;
    double C_Tdeslow;
    double C_Tdeshigh;
    double H_pdes;
    double C_Tdesapp;
    double C_Tdesld;
    double V_desref;
    double M_desref;

    double C_f1;
    double C_f2;
    double C_f3;
    double C_f4;
    double C_fcr;

    double TOL;
    double LDL;
    double span;
    double length;

private slots:
    void parse_clicked();
    void CASMACH_selected();
    void ROCD_selected();
    void Gradient_selected();
};

#endif // DIALOG_H
