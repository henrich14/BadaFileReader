#include "dialog.h"
#include "ui_dialog.h"

// math constants
const double PI = 3.14159265359;

/////// ATMOSPHERE MODEL PARAMETERS ///////
// definitions
const double T0 = 288.15;  // standard atmospheric temperatire at MSL [K]
const int p0 = 101325;     // standard atmospheric pressure at MSL [Pa]
const double ro0 = 1.225;  // standard atmospehric density at MSL [kg/m^3]
const double a0 = 340.294; // speed of sound [m/s]

// expressions
const double kappa = 1.4;          // adiabatic index of air
const double R = 287.05287;        // real gas constant for air
const double g0 = 9.80665;         // grafitational acceleration
const double betaT_less = -0.0065; // ISA temperature gradient with altitude below the tropopause
///////////////////////////////////////////

// initial conditions
const double deltaT = 0;    // temperature difference
const double deltaP = 0;    // pressure difference

// standard atmosphere model
const double Hp_Hp0 = 0.0; // standard Mean Sea Level subindex _Hp0
const double p_Hp0 = p0;
const double T_ISA_Hp0 = T0;
const double T_Hp0 = T0 + deltaT;

const double H_MSL = 0.0;
const double p_MSL = p0 + deltaP;
const double Hp_MSL = (T0/betaT_less) * ( qPow((p_MSL/p0),-(betaT_less*R/g0)) - 1 );
const double T_ISA_MSL = T0 + betaT_less * Hp_MSL;
const double T_MSL = T0 + deltaT + betaT_less * Hp_MSL;

const double H_Hp0 = (1/betaT_less) * (T0 - T_ISA_MSL + deltaT * qLn(T0 / T_ISA_MSL));

const double Hp_trop = 11000; // [m] altitude of tropopause
///////////////////////////////////////////


/////// GLOBAL AIRCRAFT PARAMETERS ///////
// descend speed increment [KCAS = CAS in kt]
const int v_dDES1 = 5;
const int v_dDES2 = 10;
const int v_dDES3 = 20;
const int v_dDES4 = 50;
const int v_dDES5 = 5;
const int v_dDES6 = 100;
const int v_dDES7 = 200;

// minimum speed coeficinets [-]
const double C_Vmin = 1.3;
const double C_VminTO = 1.2;

// configuration altitude threshold [ft]
const int H_max_TO = 400;
const int H_max_IC = 2000;
const int H_max_AP = 8000;
const int H_max_LD = 3000;

// expedite descent factor
const double C_des_exp = 1.6;
/////////////////////////////////////////

// initial conditions
//const double machTransLevel = 30000; //Mach transition level/altitude [ft]      // dopocitat podla Section 3.1
//const double Hp = 20000; // geopotential pressure altitude (altitude above MSL) [ft]


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->CAS_MACH_rb->setChecked(true);
    ui->ICAOcodeLineEdit->setText("B738__");
    ui->ACMassLineEdit->setText("65300");
    ui->CASLineEdit->setText("290");
    ui->ROCDLineEdit->setText("-1500");
    ui->GradientLineEdit->setText("3");
    ui->MachLineEdit->setText("0.78");
    ui->Hp_0LineEdit->setText("38000");
    ui->Hp_nLineEdit->setText("0");
    ui->delta_HpLineEdit->setText("2000");

    ui->ROCDLineEdit->setEnabled(false);
    ui->GradientLineEdit->setEnabled(false);

    timer = new QTimer(this);

    connect(ui->parsePushButton, SIGNAL(clicked()), this, SLOT(parse_clicked()));
    connect(ui->CAS_MACH_rb, SIGNAL(clicked()), this, SLOT(CASMACH_selected()));
    connect(ui->ROCD_rb, SIGNAL(clicked()), this, SLOT(ROCD_selected()));
    connect(ui->Gradient_rb, SIGNAL(clicked()), this, SLOT(Gradient_selected()));
    connect(ui->EmergencyDescent_rb, SIGNAL(clicked()), this, SLOT(EmergencyDescent_selected()));
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeOut()));

    // read APF and OPF file
    QString path = "C:/Users/KA/Desktop/BADA Files/Release Files/";
    //QString path = "C:/Users/Henrich/Desktop/BADA Files/Release Files/";
    QString apfFile = ui->ICAOcodeLineEdit->text();
    QString opfFile = ui->ICAOcodeLineEdit->text();

    readAPFfile(path + apfFile + ".APF");
    readOPFfile(path + opfFile + ".OPF");

    timer_const = 1;    // timer in [s]
    Hp_actual = ui->Hp_0LineEdit->text().toDouble();
    CAS_actual = ui->CASLineEdit->text().toDouble();
    ACMass_actual = ui->ACMassLineEdit->text().toDouble();
    //double initROCD = ui->ROCDLineEdit->text().toDouble();
    //double initGrad = ui->GradientLineEdit->text().toDouble();
    //double initMach = ui->MachLineEdit->text().toDouble();
    //double lastHp = ui->Hp_nLineEdit->text().toDouble();
    //double delta_Hp = ui->delta_HpLineEdit->text().toDouble();


    timer->start(timer_const*1000);
}

Dialog::~Dialog()
{
    delete ui;
}


double Dialog::temperatureDetermination(const double &altitude)
{
    // determine the temperature based on the altitude
    // input altitude [m]
    // output temperature [K]

    double temperature = 0.0;

    if(altitude < Hp_trop)
    {
        temperature = T0 + deltaT + betaT_less * altitude;  // T_less
    }
    else if(altitude == Hp_trop)
    {
        temperature = T0 + deltaT + betaT_less * Hp_trop;  // T_trop
    }
    else if(altitude > Hp_trop)
    {
        temperature = T0 + deltaT + betaT_less * Hp_trop;  // T_more = T_trop
    }

    return temperature;
}

double Dialog::airPressureDetermination(const double &altitude)
{
    // determine the air pressure based on the temperature
    // input altitude [m]
    // output air pressure [Pa]

    double pressure = 0.0;
    double temperature = temperatureDetermination(altitude);

    if(altitude < Hp_trop)
    {
        pressure = p0 * qPow((temperature - deltaT) / T0, -(g0 / (betaT_less*R)));
    }
    else if(altitude == Hp_trop)
    {
        pressure = p0 * qPow((temperature - deltaT) / T0, -(g0 / (betaT_less*R)));
    }
    else if(altitude > Hp_trop)
    {
        double temp_ISA_trop = T0 + betaT_less*Hp_trop;
        pressure = p0 * qPow((temperature - deltaT) / T0, -(g0 / (betaT_less*R))) * qExp(-(g0/(R*temp_ISA_trop)) * (altitude - Hp_trop));
    }

    return pressure;
}

double Dialog::airDensityDetermination(const double &temperature, const double &pressure)
{
    // determine the air density calcualted from pressure p and temperature T at altitude using the perfect gas law
    // input temperature [°C]; pressure [Pa]
    // output air density [kg/m^3]

    double density = 0.0;

    density = pressure / (R * temperature);

    return density;
}

double Dialog::speedOfSoundDetermination(const double &temperature)
{
    // determine the speed of sound a, the speed at which the pressure waves travel through a fluid
    // input temperature [°C]
    // output speed of sound [m/s]

    double a = 0.0;

    a = qSqrt(kappa * R * temperature);

    return a;
}

double Dialog::CAStoTAS(const double &vCAS, const double &pressure, const double &density)
{
    // conversion CAS speed into TAS speed
    // input CAS [m/s]; pressure [Pa]; density [kg/m^3]
    // output TAS [m/s]

    double TASspeed = 0.0;

    double mikro = (kappa - 1) / kappa;
    double fraction1 = qPow(1 + (mikro/2) * (ro0/p0) * vCAS*vCAS, 1/mikro) - 1;
    double fraction2 = qPow(1 + (p0/pressure) * fraction1, mikro) - 1;
    TASspeed = qSqrt((2/mikro) * (pressure/density) * fraction2);

    return TASspeed;
}

double Dialog::TAStoCAS(const double &vTAS, const double &pressure, const double &density)
{
    // conversion TAS speed into CAS speed
    // input TAS [m/s]; pressure [Pa]; density [kg/m^3]
    // output CAS [m/s]

    double CASspeed = 0.0;

    double mikro = (kappa - 1) / kappa;
    double fraction1 = qPow(1 + (mikro/2) * (density/pressure) * vTAS*vTAS, 1/mikro) - 1;
    double fraction2 = qPow(1 + (pressure/p0) * fraction1, mikro) - 1;
    CASspeed = qSqrt((2/mikro) * (p0/ro0) * fraction2);

    return CASspeed;
}

double Dialog::MtoTAS(const double &vM, const double &temperature)
{
    // conversion M to TAS
    // iunput Mach [-]; temperature [°C]
    // output TAS [m/s]

    double TASspeed = 0.0;

    TASspeed = vM * qSqrt(kappa * R * temperature);

    return TASspeed;
}

double Dialog::TAStoM(const double &vTAS, const double &temperature)
{
    // conversion TAS to M
    // input TAS [m/s]; temperature [°C]
    // output Mach [-]

    double Mspeed = 0.0;

    Mspeed = vTAS / (qSqrt(kappa * R * temperature));

    return Mspeed;
}

double Dialog::transitionAltitude(const double &vCAS, const double &vM)
{
    // calculate the transition altitude (crossover altitude)
    // input CAS [m/s]; Mach [-]
    // output transitionAltitude (CrossOver Altitude) Hp_trans [ft]

    double Hp_trans = 0.0;

    double num = qPow(1 + ((kappa-1)/2) * qPow(vCAS/a0, 2), kappa/(kappa-1)) - 1;
    double den = qPow(1 + ((kappa-1)/2) * vM*vM, kappa/(kappa-1)) - 1;
    double delta_trans = num / den;
    double theta_trans = qPow(delta_trans, -(betaT_less*R) / g0);

    Hp_trans = (1000/(0.3048*6.5)) * (T0*(1-theta_trans));

    return Hp_trans;
}

void Dialog::readAPFfile(const QString &fileName)
{
    // read APF file from "fileName" and parse all parameters

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file: " << file.fileName() << " for reading!";
    }

    QTextStream stream(&file);
    QString line;
    QStringList apfList;
    Vcl1.clear(); Vcl2.clear(); Mcl.clear(); Vcr1.clear(); Vcr2.clear(); Mcr.clear(); Mdes.clear(); Vdes1.clear(); Vdes2.clear();
    int counter = 0;
    while(!stream.atEnd())
    {
        line = stream.readLine();

        // this is the data line, and can be parsed to acquire futher information
        if(line.contains("CD"))
        {
            counter += 1;
            if(counter == 1)
            {
                apfList = parseLine(line);
                companyName = apfList.at(3) + " " + apfList.at(4);
            }
            if(counter == 2)
            {
                apfList = parseLine(line);

                Vcl1.insertMulti("LO",apfList.at(3).toInt());
                Vcl2.insertMulti("LO",apfList.at(4).toInt());
                Mcl.insertMulti("LO",apfList.at(5).toInt());

                Vcr1.insertMulti("LO",apfList.at(6).toInt());
                Vcr2.insertMulti("LO",apfList.at(7).toInt());
                Mcr.insertMulti("LO",apfList.at(8).toInt());

                Mdes.insertMulti("LO",apfList.at(9).toInt());
                Vdes2.insertMulti("LO",apfList.at(10).toInt());
                Vdes1.insertMulti("LO",apfList.at(11).toInt());
            }
            if(counter == 3)
            {
                apfList = parseLine(line);

                Vcl1.insertMulti("AV",apfList.at(3).toInt());
                Vcl2.insertMulti("AV",apfList.at(4).toInt());
                Mcl.insertMulti("AV",apfList.at(5).toInt());

                Vcr1.insertMulti("AV",apfList.at(6).toInt());
                Vcr2.insertMulti("AV",apfList.at(7).toInt());
                Mcr.insertMulti("AV",apfList.at(8).toInt());

                Mdes.insertMulti("AV",apfList.at(9).toInt());
                Vdes1.insertMulti("AV",apfList.at(10).toInt());
                Vdes2.insertMulti("AV",apfList.at(11).toInt());
            }
            if(counter == 4)
            {
                apfList = parseLine(line);

                Vcl1.insertMulti("HI",apfList.at(3).toInt());
                Vcl2.insertMulti("HI",apfList.at(4).toInt());
                Mcl.insertMulti("HI",apfList.at(5).toInt());

                Vcr1.insertMulti("HI",apfList.at(6).toInt());
                Vcr2.insertMulti("HI",apfList.at(7).toInt());
                Mcr.insertMulti("HI",apfList.at(8).toInt());

                Mdes.insertMulti("HI",apfList.at(9).toInt());
                Vdes1.insertMulti("HI",apfList.at(10).toInt());
                Vdes2.insertMulti("HI",apfList.at(11).toInt());
            }
        }
    }
}

void Dialog::readOPFfile(const QString &fileName)
{
    // read OPF file from "fileName" and parse all parameters

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file: " << file.fileName() << " for reading!";
    }

    QTextStream stream(&file);
    QString line;
    QStringList opfList;

    V_stall.clear(); C_D0.clear(); C_D2.clear(); PhaseChar.clear();

    int counter = 0;
    while(!stream.atEnd())
    {
        line = stream.readLine();

        if(line.startsWith("CD"))
        {
            opfList = parseLine(line);
            counter += 1;

            // Aircraft Type Block
            if(counter == 1)
            {

                ICAO = opfList.at(1);
                NumOfEngines = opfList.at(2).toInt();
                EngineType = opfList.at(4);
                WakeCat = opfList.at(5);
            }
            // Mass Block
            if(counter == 2)
            {
                m_ref = opfList.at(1).toDouble() * 1000;
                m_min = opfList.at(2).toDouble() * 1000;
                m_max = opfList.at(3).toDouble() * 1000;
                m_pyld = opfList.at(4).toDouble() * 1000;
                G_w = opfList.at(5).toDouble();
            }
            // Flight Envelope Block
            if(counter == 3)
            {
                V_MO = opfList.at(1).toDouble();
                M_MO = opfList.at(2).toDouble();
                h_MO = opfList.at(3).toDouble();
                h_max = opfList.at(4).toDouble();
                G_t = opfList.at(5).toDouble();
            }
            // Aerodynamics Block - Wing Area and Buffet Coefficients
            if(counter == 4)
            {
                S = opfList.at(2).toDouble();
                C_lbo = opfList.at(3).toDouble();
                k = opfList.at(4).toDouble();
                C_M16 = opfList.at(5).toDouble();
            }
            // Aerodynamics Block - Configuration characteristics
            if(counter >= 5 && counter <= 9)
            {
                V_stall.insertMulti(opfList.at(2), opfList.at(4).toDouble());
                C_D0.insertMulti(opfList.at(2), opfList.at(5).toDouble());
                C_D2.insertMulti(opfList.at(2), opfList.at(6).toDouble());
                PhaseChar.insertMulti(opfList.at(2), opfList.at(3));
            }
            if(counter == 13)
            {
                C_D0deltaLDG = opfList.at(3).toDouble();
            }
            // Engine Thrust Block - Max climb thrust coefficients (SIM)
            if(counter == 16)
            {
                C_Tc1 = opfList.at(1).toDouble();
                C_Tc2 = opfList.at(2).toDouble();
                C_Tc3 = opfList.at(3).toDouble();
                C_Tc4 = opfList.at(4).toDouble();
                C_Tc5 = opfList.at(5).toDouble();
            }
            if(counter == 17)
            {
                C_Tdeslow = opfList.at(1).toDouble();
                C_Tdeshigh = opfList.at(2).toDouble();
                H_pdes =opfList.at(3).toDouble();
                C_Tdesapp = opfList.at(4).toDouble();
                C_Tdesld = opfList.at(5).toDouble();
            }
            if(counter == 18)
            {
                 V_desref= opfList.at(1).toDouble();
                 M_desref= opfList.at(2).toDouble();
            }
            // Fuel Consumption Block - Thrust Sepcific Fuel Consumption Coefficients
            if(counter == 19)
            {
                C_f1 = opfList.at(1).toDouble();
                C_f2 = opfList.at(2).toDouble();
            }
            // Fuel Consumption Block - Descent Fuel Flow Coeficients
            if(counter == 20)
            {
                C_f3 = opfList.at(1).toDouble();
                C_f4 = opfList.at(2).toDouble();
            }
            if(counter == 21)
            {
                C_fcr = opfList.at(1).toDouble();
            }
            // Ground Movement Block
            if(counter == 22)
            {
                TOL = opfList.at(1).toDouble();
                LDL = opfList.at(2).toDouble();
                span = opfList.at(3).toDouble();
                length = opfList.at(4).toDouble();
            }
        }
    }

    //qDebug() << "ICAO:"<< ICAO << "NumOfEngine:" << NumOfEngines << "EngType:" << EngineType << "WakeCategory: " << WakeCat;
    //qDebug() << "m_ref=" << m_ref << "m_min=" << m_min << "m_max=" << m_max << "m_pyld=" << m_pyld << "G_w=" << G_w;
    //qDebug() << "V_M0=" << V_MO << "M_M0=" << M_MO<< "h_M0=" << h_MO << "h_max=" << h_max << "G_t=" << G_t;
    //qDebug() << "S=" << S << "C_lbo=" << C_lbo << "k=" << k << "C_M16=" << C_M16;
    //qDebug() << "V_stall=" << V_stall << "C_D0=" << C_D0 << "C_D2=" << C_D2 << "PhaseChar=" << PhaseChar;
    //qDebug() << "C_D0deltaLDG=" << C_D0deltaLDG;
    //qDebug() << "C_Tc1=" << C_Tc1 << "C_Tc2=" << C_Tc2 << "C_Tc3=" << C_Tc3 << "C_Tc4=" << C_Tc4 << "C_Tc5=" << C_Tc5;
    //qDebug() << "C_Tdeslow=" << C_Tdeslow << "C_Tdeshigh=" << C_Tdeshigh << "H_pdes=" << H_pdes << "C_Tdesapp=" << C_Tdesapp << "C_Tdesld=" << C_Tdesld;
    //qDebug() << "V_desref=" << V_desref << "M_desref=" << M_desref;
    //qDebug() << "C_f1=" << C_f1 << "C_f2=" << C_f2 << "C_f3=" << C_f3 << "C_f4=" << C_f4 << "C_fcr=" << C_fcr;
    //qDebug() << "TOL=" << TOL << "LDL=" << LDL << "span=" << span << "length=" << length;
}

QStringList Dialog::parseLine(const QString &line)
{
    // create List from a string of parameters, parsing with " "

    QStringList parsedList;

    QStringList fileList;
    fileList = line.split(" ");
    QListIterator<QString> iter(fileList);
    while(iter.hasNext())
    {
        QString word = iter.next();
        if(word != "") parsedList << word;
    }

    return parsedList;
}

double Dialog::CASschedule(const double &altitude, const double &transAlt, const QString &phase, const double &ACMass, const QString &EngType)
{
    // calculate the CAS schedule based on altitude; stall speed is corrected for the difference in ACMass from the referrence mass
    // input altitude [ft]; transition Altitude [ft]; phase [TO / IC / CR / AP / LD]; Actual Aircraft Mass [kg]
    // output CAS_min [kt]

    double CAS_min = 0.0;
    double v_min = 0.0;
    double corV_stall_LD = correctedSpeed(V_stall["LD"], ACMass);

    // calculate speed schedule depending on altitude
    if(EngType == "Jet" || EngType == "Turboprop")
    {
        if(altitude >= 0 && altitude < 1000)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES1;
        }
        else if(altitude >= 1000 && altitude < 1500)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES2;
        }
        else if(altitude >= 1500 && altitude < 2000)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES3;
        }
        else if(altitude >= 2000 && altitude < 3000)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES4;
        }
        else if(altitude >= 3000 && altitude < 6000)
        {
            CAS_min = qMin(Vdes1["AV"],220);
        }
        else if(altitude >= 6000 && altitude < 10000)
        {
            CAS_min = qMin(Vdes1["AV"],250);
        }
        else if(altitude >= 10000 && altitude < transAlt)
        {
            CAS_min = Vdes2["AV"];
        }
        else if(altitude >= transAlt)
        {
            CAS_min = Mdes["AV"];   // switch from CAS to MACH speed
        }
    }
    else if(EngType == "Piston")
    {
        if(altitude >= 0 && altitude < 500)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES5;
        }
        else if(altitude >= 500 && altitude < 1000)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES6;
        }
        else if(altitude >= 1000 && altitude < 1500)
        {
            CAS_min = C_Vmin * corV_stall_LD + v_dDES7;
        }
        else if(altitude >= 1500 && altitude < 10000)
        {
            CAS_min = Vdes1["AV"];
        }
        else if(altitude >= 10000 && altitude < transAlt)
        {
            CAS_min = Vdes2["AV"];
        }
        else if(altitude >= transAlt)
        {
            CAS_min = Mdes["AV"];   // switch from CAS to MACH speed
        }
    }

    // check minimal speed for each phase of flight

    v_min = calculateVmin(phase);
    CAS_min = qMin(v_min,CAS_min);

    return CAS_min;
}

double Dialog::calculateShareFactor(const double &M, const double &T, const QString &factor)
{
    // calculate the share factor based on mach speed and what kind of descent/climb I want
    // input Mach [-]; temperature [°C]
    // input factor [CONSTANT_MACH_ABOVE_TROPOPAUSE / CONSTANT_MACH_BELOW_TROPOPAUSE / CONSTANT_CAS_BELOW_TROPOPAUSE / CONSTANT_CAS_ABOVE_TROPOPAUSE / ACCELERATION_IN_DESCENT / DECELERATION_IN_DECENT]
    // output share factor [-]

    double shareFactor = 1.0;
    //double T = temperatureDetermination(ftTOm(altitude));

    // docasne definovane hodnoty pre teplotu
    //double T = T0;

    // fractions
    double fraction1 = ((kappa*R*betaT_less) / (2*g0)) * (M*M) * ((T-deltaT)/T);
    double fraction2 = qPow(1 + ((kappa-1)/2)*(M*M), (-1)/(kappa-1));
    double fraction3 = qPow(1 + ((kappa-1)/2)*(M*M), (kappa)/(kappa-1)) - 1;


    if(factor == "CONSTANT_MACH_ABOVE_TROPOPAUSE")
    {
        // constant Mach number in stratosphere (above tropopause)
        shareFactor = 1.0;
    }
    else if(factor == "CONSTANT_MACH_BELOW_TROPOPAUSE")
    {
        // constant Mach number below tropopause
        shareFactor = qPow(1+fraction1,-1);
    }
    else if(factor == "CONSTANT_CAS_BELOW_TROPOPAUSE")
    {
        // constant calibrated Airspeed CAS below tropopause
        shareFactor = qPow(1 + fraction1 + fraction2*fraction3,-1);
    }
    else if(factor == "CONSTANT_CAS_ABOVE_TROPOPAUSE")
    {
        // constant calibrated Airspeed CAS above tropopause
        shareFactor = qPow(1 + fraction2*fraction3,-1);
    }
    else if(factor == "ACCELERATION_IN_DESCENT")
    {
        shareFactor = 1.7;
    }
    else if(factor == "DECELERATION_IN_DECENT")
    {
        shareFactor = 0.3;
    }

    return shareFactor;
}

double Dialog::calculateMaxClimbThrust(const double &altitude, const double &vTAS, const QString &EngType)
{
    // calculate the maximum climb thrust
    // input altitude [ft]; TAS [kt]; Engine tpe [Jet / Turboprop / Piston]
    // output max climb thrust [N]

    double Thr = 1.0;

    // max climb thrust for Jet engines
    if(EngType == "Jet")
    {
        Thr = C_Tc1 * (1 - altitude/C_Tc2 + C_Tc3*altitude*altitude);
    }
    else if(EngType == "Turboprop")
    {
        Thr = (C_Tc1/vTAS) * (1 - altitude/C_Tc2) + C_Tc3;
    }
    else if(EngType == "Piston")
    {
        Thr = C_Tc1 * (1 - altitude/C_Tc2) + C_Tc3/vTAS;
    }

    // corrected max climb thrust for temperature deviations from standard atmosphere
    double deltaT_eff = deltaT - C_Tc4;
    if((deltaT_eff*C_Tc5) < 0)
    {
        deltaT_eff = 0;
    }
    else if((deltaT_eff*C_Tc5) > 0.4)
    {
        deltaT_eff = 0.4;
    }

    Thr = Thr * (1 - C_Tc5*deltaT_eff);

    return Thr;
}

double Dialog::calculateDescentThrust(const double &altitude, const double &Thr_max_climb, const QString &config)
{
    // calculate descent thrust
    // input altitude [ft]; config [CR / AP / LD]
    // output thrust [N]

    double Thr = 0.0;
    //double Thr_max_climb = calculateMaxClimbThrust(altitude);

    if(altitude > H_pdes)
    {
        Thr = C_Tdeshigh * Thr_max_climb;
    }

    else if(altitude <= H_pdes)
    {
        if(config == "CR")
        {
            Thr = C_Tdeslow * Thr_max_climb;
        }
        else if(config == "AP")
        {
            Thr = C_Tdesapp * Thr_max_climb;
        }
        else if(config == "LD")
        {
            Thr = C_Tdesld * Thr_max_climb;
        }
    }

    return Thr;
}

double Dialog::calculateDrag(const double &m, const double &ro, const double &vTAS, const double &bankAngle, const QString &config, const bool &expedite)
{
    // calculate drag
    // input weight [kg]; air density [kg/m^3]; TAS [m/s]; bank angle [°]; config [CR / AP / LD]
    // output drug [N]

    double CL = (2 * m * g0) / (ro * vTAS*vTAS * S * qCos(bankAngle));
    double CD, D;

    if(C_D0["AP"] == 0 || C_D0["LD"] == 0 || C_D2["AP"] == 0 || C_D2["LD"] == 0 || C_D0deltaLDG == 0)
    {
        CD = C_D0[config]+ C_D2[config] * CL*CL;
    }
    else
    {
        if(config == "CR")
        {
            // nominal conditions
            CD = C_D0[config] + C_D2[config] * CL*CL;
        }
        else if(config == "AP")
        {
            // approach configuration
            CD = C_D0[config]+ C_D2[config] * CL*CL;
        }
        else if(config == "LD")
        {
            // landing configuration
            CD = C_D0[config] + C_D0deltaLDG + C_D2[config] * CL*CL;
        }
    }

    D = (CD * ro * vTAS*vTAS * S) / 2;

    if(expedite)
    {
       D = D * C_des_exp;
    }

    return D;
}

QString Dialog::getFlightConfiguration(const QString &phase, const double &altitude, const double &vCAS)
{
    // input CAS [kt], altitude [ft], phase [CLIMB / DESCENT]
    // output flightConfiguration [TO / IC / CR / AP / LD]

    QString flightConfig = "DEFAULT";
    double v_min_cruise = calculateVmin("CR");
    double v_min_approach = calculateVmin("AP");

    if(phase == "CLIMB")
    {
        if(altitude <= H_max_TO)
        {
            flightConfig = "TO";
        }
        else if(altitude > H_max_TO && altitude <= H_max_IC)
        {
            flightConfig = "IC";
        }
        else if(altitude > H_max_IC)
        {
            flightConfig = "CR";
        }
    }
    else if(phase == "DESCENT")
    {
        if(altitude >= H_max_AP)
        {
            flightConfig = "CR";
        }
        else if(altitude <= H_max_AP && vCAS >= v_min_cruise + 10)
        {
            flightConfig = "CR";
        }
        else if((altitude < H_max_AP && altitude > H_max_LD) && vCAS < v_min_cruise + 10)
        {
            flightConfig = "AP";
        }
        else if(altitude <= H_max_LD && ((vCAS < v_min_cruise + 10) && (vCAS >= v_min_approach + 10)))
        {
            flightConfig = "AP";
        }
        else if(altitude <= H_max_LD && vCAS < v_min_approach + 10)
        {
            flightConfig = "LD";
        }
    }

    return flightConfig;
}

double Dialog::getFlightTime(const double &ROCD, const double &delta_Hp)
{
    // calculate the flight time between 2 Altitudes
    // input ROCD [ft/min]; delta_Hp [ft]
    // output time [s]

    double time = 0.0;

    time = (60 / ROCD) * delta_Hp;

    return time;

}

double Dialog::getFlightDistance(const double &time, const double &vTAS)
{
    // calculate flight distance during the time between 2 altitudes
    // input time [s]; TAS [m/s]
    // output distance [m]

    double distance = 0.0;

    distance = time * vTAS;

    return distance;
}

double Dialog::getGradient(const double &delta_Hp, const double &distance)
{
    // calculate altitude gradient of descent
    // input delta_Hp [m]; distance [m]
    // output gradient [°]

    double gradient = 0.0;

    gradient = qAtan(delta_Hp / distance);

    return (gradient/PI)*180;
}

double Dialog::nominalFuelFlow(const double &vTAS, const double &Thr, const QString &EngType)
{
    // calculate nominal fuel flow based on the thrust specific fuel consumption
    // all flight phases EXCEPT IDLE DESCENT and CRUISE -> use minimal fuel flow
    // input TAS [kt]; Thr [N]; EngType [Jet / Turboprop / Piston]
    // output nominal fuel flow [kg/min]

    double nominalFF = 0.0;
    double fuelCons = 0.0;

    if(EngType == "Piston")
    {
        nominalFF = C_f1;
    }
    else
    {
        if(EngType == "Jet")
        {
            fuelCons = (C_f1 * (1 + vTAS/C_f2)) / 1000;  // divided by 1000 to calculate from [/kN] to [/N]
        }
        else if(EngType == "Turboprop")
        {
            fuelCons = (C_f1 * (1 - vTAS/C_f2) * (vTAS/1000)) / 1000;  // divided by 1000 to calculate from [/kN] to [/N]
        }

        nominalFF = fuelCons * Thr;
    }

    return nominalFF;
}

double Dialog::minimalFuelFlow(const double &altitude, const QString &EngType)
{
    // calculate minimal fuel flow
    // input altitude [ft]; EngType [Jet / Turboprop / Piston]
    // output minimal fuel flow [kg/min]

    double minFF = 0.0;

    if(EngType == "Jet" || EngType == "Turboprop")
    {
        minFF = C_f3 * (1 - altitude/C_f4);
    }
    else if(EngType == "Piston")
    {
        minFF = C_f3;
    }

    return minFF;
}

double Dialog::cruiseFuelFlow(const double &Thr, const double &vTAS, const QString &EngType)
{
    // calculate cruise fuel flow based on the thrust specific fuel consumption
    // input TAS [kt]; Thr [N]; EngType [Jet / Turboprop / Piston]
    // output cruise fuel flow [kg/min]

    double cFF = 0.0;
    double fuelcons = 0.0;

    if(EngType == "Piston")
    {
        cFF = C_f1 * C_fcr;
    }
    else
    {
        fuelcons = C_f1 * (1 + vTAS/C_f2) / 1000;    // divided by 1000 to calculate from [/kN] to [/N]
        cFF = fuelcons * Thr * C_fcr;
    }

    return cFF;
}

double Dialog::fuelFlow(const double &vTAS, const double &Thr, const double &altitude, const QString &phase, const QString flightConfig, const QString &EngType, const bool &Idle)
{
    // calculate Fuelflow
    // input TAS [kt]; Thr [N]; Altitude [ft]; phase [CLIMB \ CRUISE \ DESCENT]; flightConfig [AP \ LD \ CR \ IC \ TO]; EngType [Jet / Turboprop / Piston]; IDLE [true / false]
    // output FF [kg/min]


    double FF = 0.0;
    double nomFF = nominalFuelFlow(vTAS, Thr, EngType);
    double minFF = minimalFuelFlow(altitude, EngType);
    double cruiseFF = cruiseFuelFlow(Thr, vTAS, EngType);

    if(phase == "CLIMB")
    {
        FF = nomFF;
    }
    else if(phase == "CRUISE")
    {
        FF = cruiseFF;
    }
    else if(phase == "DESCENT")
    {
        if(flightConfig == "AP" || flightConfig == "LD")
        {
            FF = qMax(nomFF, minFF);
        }
        else
        {
            if(Idle)
            {
                FF = minFF; // IDLE Descent
            }
            else
            {
                FF = nomFF; // use nominal because it is not idle descent -> when calculating based on fixed ROCD or gradient
            }
        }
    }

    return FF;
}

double Dialog::fuelWeight(const double &fuelflow, const double &time)
{
    // calculate the weight of fuel consumption over time
    // input fuelflow [kg/s]; time [s]
    // output weight [kg]

    double weight = 0.0;

    weight = fuelflow * time;

    return weight;
}

double Dialog::getMinCAS(const double &vmin, const double &buffetLimit, const double &altitude)
{

    double minCAS = 0.0;

    if(altitude < 15000) // in {ft]
    {
        minCAS = vmin;
    }
    else if(altitude >= 15000) // in [ft]
    {
        minCAS = qMax(vmin, buffetLimit);
    }

    return minCAS;
}

double Dialog::buffetingLimit(const double &pressure, const double &ACweight)
{
    // calculate the buffeting limit for JET aircraft only
    // input altitude [ft]; pressure [Pa]; mach [-]; Aircraft Weight [N]
    // output

    QVector<double> limit;

    double a1 = -C_lbo / k;
    double a2 = 0;
    double a3 = (ACweight/S) / (0.583 * pressure * k);

    double Q = (3*a2 - a1*a1) / 9;
    double R = (9*a1*a2 - 27*a3 - 2*a1*a1*a1) / 54;

    double theta = qAcos(R/qSqrt(-Q*Q*Q)) * 180/PI;   // theta in degrees
    double theta1 = (theta/3) * PI/180;         // in radians
    double theta2 = (theta/3 + 120) * PI/180;   // in radians
    double theta3 = (theta/3 + 240) * PI/180;   // in radians

    double X1 = 2*qSqrt(-Q) * qCos(theta1) - a1/3;
    double X2 = 2*qSqrt(-Q) * qCos(theta2) - a1/3;
    double X3 = 2*qSqrt(-Q) * qCos(theta3) - a1/3;

    limit << X1 << X2 << X3;
    double minSpeed = 99; // result is in MACH [-]

    for(int i=0; i<limit.size(); i++)
    {
        if(limit.at(i) >= 0 && limit.at(i) < minSpeed)
        {
            minSpeed = limit.at(i);
        }
    }

    return minSpeed;
}

double Dialog::calculateVmin(const QString &phase)
{
    // input phase [TO / IC / CR / AP / LD]
    // output min speed [kt]

    double v_min = 0.0;

    if(phase == "TO")
    {
        v_min = C_VminTO * V_stall["TO"];
    }
    else if(phase == "IC")
    {
        v_min = C_Vmin * V_stall["IC"];
    }
    else if(phase == "CR")
    {
        v_min = C_Vmin * V_stall["CR"];
    }
    else if(phase == "AP")
    {
        v_min = C_Vmin * V_stall["AP"];
    }
    else if(phase == "LD")
    {
        v_min = C_Vmin * V_stall["LD"];
    }

    return v_min;
}

double Dialog::correctedSpeed(const double &v_ref, const double &actualACMass)
{
    // calculate the operating speed based on actual aircraft mass
    // input ref speed [kt]; ACMass [kg]
    // output speed [kt]

    double speed = 0.0;

    speed = v_ref * qSqrt(actualACMass / m_ref);

    return speed;
}

double Dialog::getMaxAltitude(const double &ActualACMass)
{
    // calculate the max altitude based on the actual ACMass
    // input ACMAss [kg]
    // output max altitude [ft]

    double maxAlt = 0.0;
    double tempT = (deltaT - C_Tc4);
    if(tempT < 0)
    {
        tempT = 0;
    }

    if(h_max != 0)
    {
        maxAlt = qMin(h_MO, h_max + G_t*(tempT) + G_w*(m_max - ActualACMass));
    }
    else
    {
        maxAlt = h_MO;
    }

    return maxAlt;
}

double Dialog::knotsTOmps(const double &knots)
{
    // convert [kt] to [m/s]

    double mps = 0.0;
    mps = knots * 0.51444444444;
    return mps;
}

double Dialog::mpsTOknots(const double &mps)
{
    // convert [m/s] to [kt]

    double knots = 0.0;
    knots = mps * 1.9438444924574;
    return knots;
}

double Dialog::mpsTOftpmin(const double &mps)
{
    // convert [m/s] to [ft/min]

    double ftpmin = 0.0;

    ftpmin = (mps * 60) * 3.2808399;

    return ftpmin;
}

double Dialog::ftpminTOmps(const double &ftpmin)
{
    // convert [ft/min] to [m/s]

    double mps = 0.0;

    mps = (ftpmin / 60) * 0.3048;

    return mps;
}

double Dialog::ftTOm(const double &ft)
{
    // convert [ft] to [m]

    double meter = 0.0;
    meter = ft * 0.3048;
    return meter;
}

double Dialog::mTOft(const double &meter)
{
    // convert [m] to [ft]

    double ft = 0.0;
    ft = meter * 3.2808399;
    return ft;
}

double Dialog::mtoNM(const double &meter)
{
    // convert [m] to [NM]

    double NM = 0.0;
    NM = meter * 0.00053995680345572;
    return NM;
}

double Dialog::NMtom(const double &NM)
{
    // convert [NM] to [m]

    double meter = 0.0;

    meter = NM * 1852;

    return meter;
}

double Dialog::ROCDcalc(const double &T, const double &vTAS, const double &thrust, const double &drag, const double &m, const double &shareFactor)
{
    // calculate the ROCD  - speed and throttle controlled, speed is maintained at some constant CAS or M
    // input phase [CRUISE / APPROACH / LANDING];
    // input factor [[CONSTANT_MACH_ABOVE_TROPOPAUSE / CONSTANT_MACH_BELOW_TROPOPAUSE / CONSTANT_CAS_BELOW_TROPOPAUSE / CONSTANT_CAS_ABOVE_TROPOPAUSE / ACCELERATION_IN_DESCENT / DECELERATION_IN_DECENT]]
    // output ROCD [m/s]

    double ROCD = 0.0;

    ROCD = ((T-deltaT)/T) * (((thrust - drag)*vTAS)/(m*g0)) * shareFactor;

    return ROCD;
}

void Dialog::run()
{
    double actualACMass = ui->ACMassLineEdit->text().toDouble();
    double initCAS = ui->CASLineEdit->text().toDouble();
    double initROCD = ui->ROCDLineEdit->text().toDouble();
    double initGrad = ui->GradientLineEdit->text().toDouble();
    double initMach = ui->MachLineEdit->text().toDouble();
    double initHp = ui->Hp_0LineEdit->text().toDouble();
    double lastHp = ui->Hp_nLineEdit->text().toDouble();
    double delta_Hp = ui->delta_HpLineEdit->text().toDouble();

    bool expedite;
    if(ui->expediteChB->isChecked())
    {
        expedite = true;
    }
    else
    {
        expedite = false;
    }

    double H_trop = mTOft(11000);
    bool minLimitReached = false;
    bool maxCASLimitReached = false;
    bool maxAltLimitReached = false;

    double steps = (initHp-lastHp) / delta_Hp;

    QVector<double> Hp_vect, CAS_vect, MACH_vect, TAS_vect, ROCD_vect, TIME_vect, DIST_vect, GRAD_vect, FUELFLOW_vect, FUEL_vect, ACMass_vect, Thr_vect, D_vect, fM_vect;
    for(int i=0; i<=steps; i++)
    {
        Hp_vect << initHp - i*delta_Hp;     // vector vysok [ft]
    }

    //double actualACMass = ACmass;
    ACMass_vect << actualACMass;

    double T, p, ro, CAS, TAS, Thr, D, mach, fM, transAlt, ROCD, time, dist, grad, FFlow, FWeight;
    QString flightConfig;

    // prevodova vyska - crossover altitude / transition altitude
    transAlt = transitionAltitude(knotsTOmps(initCAS),initMach); // vypocet crossover alt pre definovanu CAS a M

    if(ui->CAS_MACH_rb->isChecked() || ui->EmergencyDescent_rb->isChecked())
    {
        for(int i=0; i<Hp_vect.size(); i++)
        {
            // zavisi len od vysky
            T = temperatureDetermination(ftTOm(Hp_vect.at(i)));
            p = airPressureDetermination(ftTOm(Hp_vect.at(i)));
            ro = airDensityDetermination(T,p);

            double minAlt = qMin(H_trop, transAlt);
            double maxAlt = qMax(H_trop, transAlt);

            if(Hp_vect.at(i) <= minAlt)
            {
                // tu sa udrziava konst CAS a pocita sa mach
                CAS = initCAS;
                CAS_vect << CAS;
                TAS = CAStoTAS(knotsTOmps(CAS),p,ro);
                TAS_vect << mpsTOknots(TAS);
                flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), CAS);

                // test the min speed and buffeting speed limits for Jet
                double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                double minCAS = vmin;
                if(EngineType == "Jet")
                {
                    double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                    minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                }

                if(minCAS > CAS && minLimitReached == false)
                {
                    minLimitReached = true;
                    QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                }

                if(V_MO < CAS && maxCASLimitReached == false)
                {
                    maxCASLimitReached = true;
                    QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                }

                double maxAltitude = getMaxAltitude(actualACMass);
                if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                {
                    maxAltLimitReached = true;
                    QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                         + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                }

                double Thr_max_climb = calculateMaxClimbThrust(Hp_vect.at(i), mpsTOknots(TAS), EngineType);
                Thr = calculateDescentThrust(Hp_vect.at(i),Thr_max_climb, flightConfig);
                D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
                Thr_vect << Thr;
                D_vect << D;

                mach = TAStoM(TAS,T);
                MACH_vect << mach;
                fM = calculateShareFactor(mach, T, "CONSTANT_CAS_BELOW_TROPOPAUSE");
                fM_vect << fM;

                ROCD = ROCDcalc(T,TAS,Thr, D, actualACMass, fM);
                ROCD_vect << mpsTOftpmin(ROCD);

                time = getFlightTime(qAbs(mpsTOftpmin(ROCD)), delta_Hp);
                TIME_vect << time;

                dist = getFlightDistance(time, TAS);
                DIST_vect << mtoNM(dist);

                grad = getGradient(ftTOm(delta_Hp),dist);
                GRAD_vect << grad;

                FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, true) / 60; // in [kg/s]
                FUELFLOW_vect << FFlow;

                FWeight = fuelWeight(FFlow, time);
                FUEL_vect << FWeight;
                actualACMass -= FWeight;
                ACMass_vect << actualACMass;
            }
            else if(Hp_vect.at(i) > minAlt && Hp_vect.at(i) < maxAlt)
            {
                // tu sa udrziava konst mach a pocita sa CAS
                mach = initMach;
                MACH_vect << mach;
                if(minAlt == transAlt)
                {
                    TAS = MtoTAS(mach,T);
                    TAS_vect << mpsTOknots(TAS);
                    CAS = TAStoCAS(TAS,p,ro);
                    CAS_vect << mpsTOknots(CAS);
                    flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), mpsTOknots(CAS));

                    // test the min speed and buffeting speed limits
                    double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                    double minCAS = vmin;
                    if(EngineType == "Jet")
                    {
                        double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                        minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                    }

                    if(minCAS > mpsTOknots(CAS) && minLimitReached == false)
                    {
                        minLimitReached = true;
                        QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(mpsTOknots(CAS)) + " [kt]");
                    }

                    if(V_MO < CAS && maxCASLimitReached == false)
                    {
                        maxCASLimitReached = true;
                        QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                    }

                    double maxAltitude = getMaxAltitude(actualACMass);
                    if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                    {
                        maxAltLimitReached = true;
                        QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                             + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                    }

                    fM = calculateShareFactor(mach, T, "CONSTANT_MACH_BELOW_TROPOPAUSE");
                    fM_vect << fM;
                }
                else if(minAlt == H_trop)
                {
                    CAS = initCAS;
                    CAS_vect << CAS;
                    TAS = CAStoTAS(knotsTOmps(CAS),p,ro);
                    TAS_vect << mpsTOknots(TAS);
                    flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), CAS);

                    mach = TAStoM(TAS,T);
                    MACH_vect << mach;

                    // test the min speed and buffeting speed limits
                    double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                    double minCAS = vmin;
                    if(EngineType == "Jet")
                    {
                        double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                        minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                    }

                    if(minCAS > CAS && minLimitReached == false)
                    {
                        minLimitReached = true;
                        QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                    }

                    if(V_MO < CAS && maxCASLimitReached == false)
                    {
                        maxCASLimitReached = true;
                        QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                    }

                    double maxAltitude = getMaxAltitude(actualACMass);
                    if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                    {
                        maxAltLimitReached = true;
                        QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                             + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                    }

                    fM = calculateShareFactor(mach, T, "CONSTANT_CAS_ABOVE_TROPOPAUSE");
                    fM_vect << fM;
                }

                double Thr_max_climb = calculateMaxClimbThrust(Hp_vect.at(i), mpsTOknots(TAS), EngineType);
                Thr = calculateDescentThrust(Hp_vect.at(i), Thr_max_climb, flightConfig);
                D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
                Thr_vect << Thr;
                D_vect << D;

                ROCD = ROCDcalc(T,TAS,Thr, D, actualACMass, fM);
                ROCD_vect << mpsTOftpmin(ROCD);

                time = getFlightTime(qAbs(mpsTOftpmin(ROCD)), delta_Hp);
                TIME_vect << time;

                dist = getFlightDistance(time, TAS);
                DIST_vect << mtoNM(dist);

                grad = getGradient(ftTOm(delta_Hp),dist);
                GRAD_vect << grad;

                FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, true) / 60; // in [kg/s]
                FUELFLOW_vect << FFlow;

                FWeight = fuelWeight(FFlow, time);
                FUEL_vect << FWeight;
                actualACMass -= FWeight;
                ACMass_vect << actualACMass;
            }
            else if(Hp_vect.at(i) >= maxAlt)
            {
                // tu sa udrziva konst mach a pocita sa CAS
                mach = initMach;
                MACH_vect << mach;
                fM = calculateShareFactor(mach, T, "CONSTANT_MACH_ABOVE_TROPOPAUSE");
                fM_vect << fM;

                TAS = MtoTAS(mach,T);
                TAS_vect << mpsTOknots(TAS);
                CAS = TAStoCAS(TAS,p,ro);
                CAS_vect << mpsTOknots(CAS);
                flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), mpsTOknots(CAS));

                // test the min speed and buffeting speed limits
                double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                double minCAS = vmin;
                if(EngineType == "Jet")
                {
                    double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                    minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                }

                if(minCAS > mpsTOknots(CAS) && minLimitReached == false)
                {
                    minLimitReached = true;
                    QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(mpsTOknots(CAS)) + " [kt]");
                }

                if(V_MO < CAS && maxCASLimitReached == false)
                {
                    maxCASLimitReached = true;
                    QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                }

                double maxAltitude = getMaxAltitude(actualACMass);
                if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                {
                    maxAltLimitReached = true;
                    QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                         + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                }

                double Thr_max_climb = calculateMaxClimbThrust(Hp_vect.at(i), mpsTOknots(TAS), EngineType);
                Thr = calculateDescentThrust(Hp_vect.at(i), Thr_max_climb, flightConfig);
                D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
                Thr_vect << Thr;
                D_vect << D;

                ROCD = ROCDcalc(T,TAS,Thr, D, actualACMass, fM);
                ROCD_vect << mpsTOftpmin(ROCD);

                time = getFlightTime(qAbs(mpsTOftpmin(ROCD)), delta_Hp);
                TIME_vect << time;

                dist = getFlightDistance(time, TAS);
                DIST_vect << mtoNM(dist);

                grad = getGradient(ftTOm(delta_Hp),dist);
                GRAD_vect << grad;

                FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, true) / 60; // in [kg/s]
                FUELFLOW_vect << FFlow;

                FWeight = fuelWeight(FFlow, time);
                FUEL_vect << FWeight;
                actualACMass -= FWeight;
                ACMass_vect << actualACMass;
            }
        }
    }
    else if(ui->ROCD_rb->isChecked()) // Define ROCD and CAS and calculate the rest of flight parameters
    {
        for(int i=0; i<Hp_vect.size(); i++)
        {
            // zavisi len od vysky
            T = temperatureDetermination(ftTOm(Hp_vect.at(i)));
            p = airPressureDetermination(ftTOm(Hp_vect.at(i)));
            ro = airDensityDetermination(T,p);

            CAS = initCAS;
            CAS_vect << CAS;
            TAS = CAStoTAS(knotsTOmps(CAS),p,ro);
            TAS_vect << mpsTOknots(TAS);
            flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), CAS);

            // test the min speed and buffeting speed limits
            double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
            double minCAS = vmin;
            if(EngineType == "Jet")
            {
                double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
            }

            if(minCAS > CAS && minLimitReached == false)
            {
                minLimitReached = true;
                QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                     + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
            }

            if(V_MO < CAS && maxCASLimitReached == false)
            {
                maxCASLimitReached = true;
                QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                     + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
            }

            double maxAltitude = getMaxAltitude(actualACMass);
            if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
            {
                maxAltLimitReached = true;
                QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                     + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
            }

            //Thr = calculateDescentThrust(Hp_vect.at(i), flightConfig);
            D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
            D_vect << D;

            mach = TAStoM(TAS,T);
            MACH_vect << mach;


            // need to know if H_trop is under transition Altitude or it is the other way
            double minAlt = qMin(H_trop, transAlt);
            double maxAlt = qMax(H_trop, transAlt);

            if(Hp_vect.at(i) <= minAlt)
            {
                // tu sa udrziava konst CAS a pocita sa mach
                fM = calculateShareFactor(mach, T, "CONSTANT_CAS_BELOW_TROPOPAUSE");
            }

            else if(Hp_vect.at(i) > minAlt && Hp_vect.at(i) < maxAlt)
            {
                // tu sa udrziava konst mach a pocita sa CAS

                if(minAlt == transAlt)
                {
                    fM = calculateShareFactor(mach, T, "CONSTANT_MACH_BELOW_TROPOPAUSE");
                }
                else if(minAlt == H_trop)
                {
                    fM = calculateShareFactor(mach, T, "CONSTANT_CAS_ABOVE_TROPOPAUSE");
                }
            }
            else if(Hp_vect.at(i) >= maxAlt)
            {
                fM = calculateShareFactor(mach, T, "CONSTANT_CAS_ABOVE_TROPOPAUSE");
            }

            fM_vect << fM;
            ROCD_vect << initROCD;

            Thr = (ftpminTOmps(initROCD)/fM) * (T/(T-deltaT)) * (actualACMass*g0/TAS) + D;  // musim dopocitat tah z ROCD
            Thr_vect << Thr;

            time = getFlightTime(qAbs(initROCD), delta_Hp);
            TIME_vect << time;

            dist = getFlightDistance(time, TAS);
            DIST_vect << mtoNM(dist);

            grad = getGradient(ftTOm(delta_Hp),dist);
            GRAD_vect << grad;

            FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, false) / 60; // in [kg/s]
            FUELFLOW_vect << FFlow;

            FWeight = fuelWeight(FFlow, time);
            FUEL_vect << FWeight;
            actualACMass -= FWeight;
            ACMass_vect << actualACMass;
        }
    }
    else if(ui->Gradient_rb->isChecked())
    {
        for(int i=0; i<Hp_vect.size(); i++)
        {
            // zavisi len od vysky
            T = temperatureDetermination(ftTOm(Hp_vect.at(i)));
            p = airPressureDetermination(ftTOm(Hp_vect.at(i)));
            ro = airDensityDetermination(T,p);

            double minAlt = qMin(H_trop, transAlt);
            double maxAlt = qMax(H_trop, transAlt);

            if(Hp_vect.at(i) <= minAlt)
            {
                // tu sa udrziava konst CAS a pocita sa mach
                CAS = initCAS;
                CAS_vect << CAS;
                TAS = CAStoTAS(knotsTOmps(CAS),p,ro);
                TAS_vect << mpsTOknots(TAS);
                flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), CAS);

                // test the min speed and buffeting speed limits
                double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                double minCAS = vmin;
                if(EngineType == "Jet")
                {
                    double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                    minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                }

                if(minCAS > CAS && minLimitReached == false)
                {
                    minLimitReached = true;
                    QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                }

                if(V_MO < CAS && maxCASLimitReached == false)
                {
                    maxCASLimitReached = true;
                    QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                }

                double maxAltitude = getMaxAltitude(actualACMass);
                if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                {
                    maxAltLimitReached = true;
                    QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                         + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                }

                //Thr = calculateDescentThrust(Hp_vect.at(i), flightConfig);
                D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
                D_vect << D;

                mach = TAStoM(TAS,T);
                MACH_vect << mach;
                fM = calculateShareFactor(mach, T, "CONSTANT_CAS_BELOW_TROPOPAUSE");
                fM_vect << fM;

                //ROCD = ROCDcalc(T,TAS,Thr, D, actualACMass, fM);
                //ROCD_vect << mpsTOftpmin(ROCD);

                //time = getFlightTime(qAbs(mpsTOftpmin(ROCD)), delta_Hp);
                //TIME_vect << time;

                //dist = getFlightDistance(time, TAS);
                //DIST_vect << mtoNM(dist);

                //grad = getGradient(ftTOm(delta_Hp),dist);
                GRAD_vect << initGrad;
                dist = ftTOm(delta_Hp)/qTan((initGrad/180)*PI);
                DIST_vect << mtoNM(dist);

                time = dist / TAS;
                TIME_vect << time;

                ROCD = -(delta_Hp/time) * 60;
                ROCD_vect << ROCD;

                Thr = (ftpminTOmps(ROCD)/fM) * (T/(T-deltaT)) * (actualACMass*g0/TAS) + D;  // musim dopocitat tah z ROCD
                Thr_vect << Thr;

                FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, false) / 60; // in [kg/s]
                FUELFLOW_vect << FFlow;

                FWeight = fuelWeight(FFlow, time);
                FUEL_vect << FWeight;
                actualACMass -= FWeight;
                ACMass_vect << actualACMass;
            }
            else if(Hp_vect.at(i) > minAlt && Hp_vect.at(i) < maxAlt)
            {
                // tu sa udrziava konst mach a pocita sa CAS
                mach = initMach;
                MACH_vect << mach;

                if(minAlt == transAlt)
                {
                    TAS = MtoTAS(mach,T);
                    TAS_vect << mpsTOknots(TAS);
                    CAS = TAStoCAS(TAS,p,ro);
                    CAS_vect << mpsTOknots(CAS);
                    flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), mpsTOknots(CAS));

                    // test the min speed and buffeting speed limits
                    double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                    double minCAS = vmin;
                    if(EngineType == "Jet")
                    {
                        double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                        minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                    }

                    if(minCAS > mpsTOknots(CAS) && minLimitReached == false)
                    {
                        minLimitReached = true;
                        QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(mpsTOknots(CAS)) + " [kt]");
                    }

                    if(V_MO < CAS && maxCASLimitReached == false)
                    {
                        maxCASLimitReached = true;
                        QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                    }

                    double maxAltitude = getMaxAltitude(actualACMass);
                    if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                    {
                        maxAltLimitReached = true;
                        QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                             + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                    }

                    fM = calculateShareFactor(mach, T, "CONSTANT_MACH_BELOW_TROPOPAUSE");
                    fM_vect << fM;
                }
                else if(minAlt == H_trop)
                {
                    CAS = initCAS;
                    CAS_vect << CAS;
                    TAS = CAStoTAS(knotsTOmps(CAS),p,ro);
                    TAS_vect << mpsTOknots(TAS);
                    flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), CAS);

                    mach = TAStoM(TAS,T);
                    MACH_vect << mach;

                    // test the min speed and buffeting speed limits
                    double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                    double minCAS = vmin;
                    if(EngineType == "Jet")
                    {
                        double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                        minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                    }

                    if(minCAS > CAS && minLimitReached == false)
                    {
                        minLimitReached = true;
                        QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                    }

                    if(V_MO < CAS && maxCASLimitReached == false)
                    {
                        maxCASLimitReached = true;
                        QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                             + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                    }

                    double maxAltitude = getMaxAltitude(actualACMass);
                    if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                    {
                        maxAltLimitReached = true;
                        QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                             + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                    }

                    fM = calculateShareFactor(mach, T, "CONSTANT_CAS_ABOVE_TROPOPAUSE");
                    fM_vect << fM;
                }

                //Thr = calculateDescentThrust(Hp_vect.at(i), flightConfig);
                D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
                D_vect << D;

                //ROCD = ROCDcalc(T,TAS,Thr, D, actualACMass, fM);
                //ROCD_vect << mpsTOftpmin(ROCD);

                //time = getFlightTime(qAbs(mpsTOftpmin(ROCD)), delta_Hp);
                //TIME_vect << time;

                //dist = getFlightDistance(time, TAS);
                //DIST_vect << mtoNM(dist);

                //grad = getGradient(ftTOm(delta_Hp),dist);
                //GRAD_vect << grad;

                GRAD_vect << initGrad;
                dist = ftTOm(delta_Hp)/qTan((initGrad/180)*PI);
                DIST_vect << mtoNM(dist);

                time = dist / TAS;
                TIME_vect << time;

                ROCD = -(delta_Hp*60/time);
                ROCD_vect << ROCD;

                Thr = (ftpminTOmps(ROCD)/fM) * (T/(T-deltaT)) * (actualACMass*g0/TAS) + D;  // musim dopocitat tah z ROCD
                Thr_vect << Thr;

                FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, false) / 60; // in [kg/s]
                FUELFLOW_vect << FFlow;

                FWeight = fuelWeight(FFlow, time);
                FUEL_vect << FWeight;
                actualACMass -= FWeight;
                ACMass_vect << actualACMass;
            }
            else if(Hp_vect.at(i) >= maxAlt)
            {
                // tu sa udrziva konst mach a pocita sa CAS
                mach = initMach;
                MACH_vect << mach;
                fM = calculateShareFactor(mach, T, "CONSTANT_MACH_ABOVE_TROPOPAUSE");
                fM_vect << fM;

                TAS = MtoTAS(mach,T);
                TAS_vect << mpsTOknots(TAS);
                CAS = TAStoCAS(TAS,p,ro);
                CAS_vect << mpsTOknots(CAS);
                flightConfig = getFlightConfiguration("DESCENT", Hp_vect.at(i), mpsTOknots(CAS));

                // test the min speed and buffeting speed limits
                double vmin = CASschedule(Hp_vect.at(i),transAlt, flightConfig, actualACMass, EngineType);
                double minCAS = vmin;
                if(EngineType == "Jet")
                {
                    double buffetLimit = mpsTOknots(TAStoCAS(MtoTAS(buffetingLimit(p, actualACMass*g0),T), p, ro));
                    minCAS = getMinCAS(vmin, buffetLimit, Hp_vect.at(i));
                }

                if(minCAS > mpsTOknots(CAS) && minLimitReached == false)
                {
                    minLimitReached = true;
                    QMessageBox::warning(this, "MIN CAS error", "Min CAS speed limit reached CAS =" + QString::number(minCAS) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(mpsTOknots(CAS)) + " [kt]");
                }

                if(V_MO < CAS && maxCASLimitReached == false)
                {
                    maxCASLimitReached = true;
                    QMessageBox::warning(this, "MAX CAS error", "Max CAS speed limit reached CAS =" + QString::number(V_MO) + " [kt] at "
                                         + QString::number(Hp_vect.at(i)) + " [ft] with actual CAS = " + QString::number(CAS) + " [kt]");
                }

                double maxAltitude = getMaxAltitude(actualACMass);
                if(maxAltitude < Hp_vect.at(i) && maxAltLimitReached == false)
                {
                    maxAltLimitReached = true;
                    QMessageBox::warning(this, "MAX ALT error", "Max altitude limit reached MAX_ALT = " + QString::number(maxAltitude)
                                         + " [ft] with actual ALT = " + QString::number(Hp_vect.at(i)) + " [ft]");
                }

                //Thr = calculateDescentThrust(Hp_vect.at(i), flightConfig);
                D = calculateDrag(actualACMass, ro, TAS, 0, flightConfig, expedite);
                D_vect << D;

                //ROCD = ROCDcalc(T,TAS,Thr, D, actualACMass, fM);
                //ROCD_vect << mpsTOftpmin(ROCD);

                //time = getFlightTime(qAbs(mpsTOftpmin(ROCD)), delta_Hp);
                //TIME_vect << time;

                //dist = getFlightDistance(time, TAS);
                //DIST_vect << mtoNM(dist);

                //grad = getGradient(ftTOm(delta_Hp),dist);
                //GRAD_vect << grad;

                GRAD_vect << initGrad;
                dist = ftTOm(delta_Hp)/qTan((initGrad/180)*PI);
                DIST_vect << mtoNM(dist);

                time = dist / TAS;
                TIME_vect << time;

                ROCD = -(delta_Hp*60/time);
                ROCD_vect << ROCD;

                Thr = (ftpminTOmps(ROCD)/fM) * (T/(T-deltaT)) * (actualACMass*g0/TAS) + D;  // musim dopocitat tah z ROCD
                Thr_vect << Thr;

                FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp_vect.at(i), "DESCENT", flightConfig, EngineType, false) / 60; // in [kg/s]
                FUELFLOW_vect << FFlow;

                FWeight = fuelWeight(FFlow, time);
                FUEL_vect << FWeight;
                actualACMass -= FWeight;
                ACMass_vect << actualACMass;
            }
        }
    }

    QString path = "C:/Users/KA/Desktop/outputfile.txt";
    //QString path = "C:/Users/Henrich/Desktop/outputfile.txt";

    exportData(path,Hp_vect , ACMass_vect, CAS_vect, TAS_vect, MACH_vect, ROCD_vect, GRAD_vect, FUELFLOW_vect, FUEL_vect, TIME_vect, DIST_vect, Thr_vect, D_vect, fM_vect);
}

void Dialog::exportData(const QString &filename, const QVector<double> &Hp, const QVector<double> &ACMass, const QVector<double> &CAS, const QVector<double> &TAS, const QVector<double> &MACH,
                        const QVector<double> &ROCD, const QVector<double> &gradient, const QVector<double> &FuelFlow, const QVector<double> &Fuel, const QVector<double> &Time, const QVector<double> &Distance,
                        const QVector<double> &Thr, const QVector<double> &D, const QVector<double> &fM)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Cannot open file " + file.fileName() + " for writing!";
    }

    QTextStream stream(&file);

    stream << "Hp[ft]\t\tACMass[kg]\t\tCAS[kt]\t\tTAS[kt]\t\tM[-]\t\tROCD[ft/min]\t\tGrad[deg]\t\tFuelFlow[kg/s]\t\tFuel[kg]\t\tTime[s]\t\tDistance[NM]"
              "\t\tThr[N]\t\tD[N]\t\tfM[-]" << "\n";

    for(int i=0; i<Hp.size(); i++)
    {
        stream << Hp.at(i) << "\t\t" << ACMass.at(i) << "\t\t" << CAS.at(i) << "\t\t" << TAS.at(i) << "\t\t" << MACH.at(i) << "\t\t"
               << ROCD.at(i) << "\t\t" << gradient.at(i) << "\t\t" << FuelFlow.at(i) << "\t\t" << Fuel.at(i) << "\t\t" << Time.at(i) << "\t\t" << Distance.at(i) << "\t\t"
               << Thr.at(i) << "\t\t" << D.at(i) << "\t\t" << fM.at(i) << "\n";
    }

    qDebug() << "Data successfully saved to:" << file.fileName();
    file.close();
}

QVector<double> Dialog::BADAcalc(const double &Hp, const double &vCAS, const double &ACMass, const double &time_c)
{
    QVector<double> outVect;

    double T, p, ro, CAS, TAS, Thr_max_climb, Thr, D, mach, fM, transAlt, ROCD, time, dist, grad, FFlow, FWeight;
    QString flightConfig;

    bool expedite = false;

    T = temperatureDetermination(ftTOm(Hp));
    p = airPressureDetermination(ftTOm(Hp));
    ro = airDensityDetermination(T,p);

    CAS = vCAS;                          // knots
    TAS = CAStoTAS(knotsTOmps(CAS),p,ro);   // [m/s]
    flightConfig = getFlightConfiguration("DESCENT", Hp, CAS);

    Thr_max_climb = calculateMaxClimbThrust(Hp, mpsTOknots(TAS), EngineType);
    Thr = calculateDescentThrust(Hp,Thr_max_climb, flightConfig);
    D = calculateDrag(ACMass, ro, TAS, 0, flightConfig, expedite);

    mach = TAStoM(TAS,T);
    fM = calculateShareFactor(mach, T, "CONSTANT_CAS_BELOW_TROPOPAUSE");

    ROCD = mpsTOftpmin(ROCDcalc(T, TAS, Thr, D, ACMass, fM));


    time = time_c;   // hodnota timera [s]
    dist = getFlightDistance(time, TAS); // [m]
    double delta_Hp = (ROCD / 60) * time;  // [ft]

    grad = getGradient(ftTOm(delta_Hp),dist);

    FFlow = fuelFlow(mpsTOknots(TAS), Thr, Hp, "DESCENT", flightConfig, EngineType, true) / 60; // in [kg/s]

    FWeight = fuelWeight(FFlow, time);  // [kg]
    double actualACMass = ACMass - FWeight;    // [kg]

    outVect.clear();
    outVect << Hp << T << p << ro << CAS << TAS << Thr << D << mach << fM << ROCD << time << dist << delta_Hp << grad << FFlow << FWeight << actualACMass;

    //qDebug() << "Hp =" << Hp << "ft " << "ROCD =" << ROCD << "ft/min" << actualACMass;

    return outVect;
}

void Dialog::parse_clicked()
{
    //QString path = "C:/Users/KA/Desktop/BADA Files/Release Files/";
    //QString path = "C:/Users/Henrich/Desktop/BADA Files/Release Files/";
    //QString apfFile = ui->ICAOcodeLineEdit->text();
    //QString opfFile = ui->ICAOcodeLineEdit->text();

    //readAPFfile(path + apfFile + ".APF");
    //readOPFfile(path + opfFile + ".OPF");

    run();
}

void Dialog::CASMACH_selected()
{
    ui->GradientLineEdit->setEnabled(false);
    ui->ROCDLineEdit->setEnabled(false);
    ui->expediteChB->setChecked(false);
    ui->expediteChB->setEnabled(true);
}

void Dialog::ROCD_selected()
{
    ui->ROCDLineEdit->setEnabled(true);
    ui->GradientLineEdit->setEnabled(false);
    ui->expediteChB->setChecked(false);
    ui->expediteChB->setEnabled(false);
}

void Dialog::Gradient_selected()
{
    ui->GradientLineEdit->setEnabled(true);
    ui->ROCDLineEdit->setEnabled(false);
    ui->expediteChB->setChecked(false);
    ui->expediteChB->setEnabled(false);
}

void Dialog::EmergencyDescent_selected()
{
    ui->GradientLineEdit->setEnabled(false);
    ui->ROCDLineEdit->setEnabled(false);
    ui->expediteChB->setChecked(true);
    ui->expediteChB->setEnabled(false);

    ui->CASLineEdit->setText(QString::number(V_MO));
    ui->MachLineEdit->setText(QString::number(M_MO));
}

void Dialog::TimeOut()
{
    QVector<double> vect = BADAcalc(Hp_actual, CAS_actual, ACMass_actual, timer_const);
    Hp_actual += vect[13];
    ACMass_actual = vect[17];


    qDebug() << "Hp_actual =" << vect[0] << "T =" << vect[1] << "p =" << vect[2] << "ro =" << vect[3] << "CAS =" << vect[4] << "TAS =" << vect[5] << "Thr =" << vect[6] << "D =" << vect[7] << "mach =" << vect[8]
                << "fM =" << vect[9] << "ROCD =" << vect[10] << "time =" << vect[11] << "dist =" << vect[12] << "delta_Hp =" << vect[13] << "grad =" << vect[14] << "FFlow =" << vect[15]
                   << "FWeigth =" << vect[16] << "ActualACMass =" << vect[17];


}
