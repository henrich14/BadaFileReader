#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QFile>
#include <QDebug>
#include <QHash>
#include <QTextStream>
#include <QTime>
#include <QTimer>
#include "graph.h"

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

    void readSynomymFile();
    void readAPFfile(const QString &fileName);
    void readOPFfile(const QString &fileName);
    QStringList parseLine(const QString &line);
    double CASschedule(const double &altitude, const double &transAlt, const QString &phase, const double &ACMass, const QString &EngType);
    double calculateShareFactor(const double &M, const double &T, const QString &factor);
    double calculateMaxClimbThrust(const double &altitude, const double &vTAS, const QString &EngType);
    double calculateMaxCruiseThrust(const double &maxClimbThrust);
    double calculateReducedClimbPower(const double &altitude, const double &actualACMass, const QString &EngType);
    double calculateDescentThrust(const double &altitude, const double &Thr_max_climb, const QString &config);
    double calculateDrag(const double &m, const double &ro, const double &vTAS, const double &bankAngle, const QString &config, const bool &expedite);
    QString getFlightConfiguration(const QString &phase, const double &altitude, const double &rwyElevation, const double &vCAS);
    double getFlightTime(const double &ROCD, const double &delta_Hp);
    double getFlightDistance(const double &time, const double &vTAS, const double &BankAngle);
    double getGradient(const double &delta_Hp, const double &distance);
    double nominalFuelFlow(const double &vTAS, const double &Thr, const QString &EngType); // thrust specific fuel consumption
    double minimalFuelFlow(const double &altitude, const QString &EngType);
    double cruiseFuelFlow(const double &Thr, const double &vTAS, const QString &EngType);
    double fuelFlow(const double &vTAS, const double &Thr, const double &altitude, const QString &phase, const QString flightConfig, const QString &EngType, const bool &Idle);
    double fuelWeight(const double &fuelflow, const double &time);
    double rateTurn(const double &BankAngle, const double &vTAS);
    double turnAngle(const double &rateOfTurn, const double &time);
    double turnRadius(const double &vTAS, const double &rateOfTurn);

    void flightEnvelope_operational();
    void flightEnvelope_certified();

    bool validationTests(const QString &EngType, const double &actualACMass, const double &minCAS, const double &vCAS, const double &Altitude, bool &minCASLimit, bool &maxCASLimit, bool &maxAltLimit);
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
    double r2d(const double &rad);
    double d2r(const double &deg);

    double ROCDcalc(const double &T, const double &vTAS, const double &thrust, const double &drag, const double &m, const double &shareFactor, const double &C_pow_red, const QString &phase);
    void run();
    void runTestFlightTrajectory();
    void exportData(const QString &filename, const QVector<double> &Hp, const QVector<double> &ACMass, const QVector<double> &CAS, const QVector<double> &TAS, const QVector<double> &MACH, const QVector<double> &ROCD, const QVector<double> &gradient, const QVector<double> &FuelFlow, const QVector<double> &Fuel, const QVector<double> &Time, const QVector<double> &Distance, const QVector<double> &Thr, const QVector<double> &D, const QVector<double> &fM);
    QVector<double> BADAcalc(const QString activePhaseOfFlight, const QString &flightOption, const double &Hp, const double &vCAS, const double &vMach, const double &vROCD, const double &vGrad, const double &ACMass, const double &BankAngle, const double &time_c);

signals:
    void send_data(const QVector<double> &DATA);
    void start_signal();
    
private:
    Ui::Dialog *ui;

    Graph *graphWindow;

    QTimer *timer;
    double timer_const;

    QString activePhaseOfFlight;
    QString activeFlightOption;

    double Hp_actual;
    double CAS_init;
    double MACH_init;
    double ROCD_init;
    double Grad_init;
    double ACMass_actual;
    double BankAngle_actual;
    double FWeight_actual;

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
    void typeOfFlight_changed();
    void optionOfFlight_changed();
    void parse_clicked();
    void CASMACH_selected();
    void ROCD_selected();
    void Gradient_selected();
    void EmergencyDescent_selected();
    void TimeOut();
    void start_clicked();
    void stop_clicked();
    void AircraftChanged(const QString &ICAOFileCode);
};

#endif // DIALOG_H
