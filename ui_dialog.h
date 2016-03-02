/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue 1. Mar 21:52:53 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *ICAOcomboBox;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_21;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_18;
    QLabel *EngineLabel;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_25;
    QLabel *MassLowLabel;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_19;
    QLabel *VmoLabel;
    QLabel *label_22;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_31;
    QLabel *WakeLabel;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_26;
    QLabel *MassNomLabel;
    QLabel *label_29;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_20;
    QLabel *MmoLabel;
    QLabel *label_23;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_32;
    QLabel *WingSpanLabel;
    QLabel *label_37;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_27;
    QLabel *MassHighLabel;
    QLabel *label_30;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_21;
    QLabel *HmoLabel;
    QLabel *label_24;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_33;
    QLabel *ACLengthLabel;
    QLabel *label_36;
    QLabel *label_34;
    QLabel *label_35;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_9;
    QRadioButton *CAS_MACH_rb;
    QRadioButton *ROCD_rb;
    QRadioButton *Gradient_rb;
    QRadioButton *EmergencyDescent_rb;
    QCheckBox *expediteChB;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_12;
    QLineEdit *ACMassLineEdit;
    QLabel *label_13;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *CASLineEdit;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_14;
    QLineEdit *ROCDLineEdit;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_16;
    QLineEdit *GradientLineEdit;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *MachLineEdit;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_38;
    QLineEdit *BankAngleLineEdit;
    QLabel *label_39;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *Hp_0LineEdit;
    QLabel *label_9;
    QLabel *label_5;
    QLineEdit *Hp_nLineEdit;
    QLabel *label_10;
    QLabel *label_6;
    QLineEdit *delta_HpLineEdit;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *parsePushButton;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *startPushButton;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *stopPushButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(550, 515);
        verticalLayout_5 = new QVBoxLayout(Dialog);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        ICAOcomboBox = new QComboBox(Dialog);
        ICAOcomboBox->setObjectName(QString::fromUtf8("ICAOcomboBox"));

        horizontalLayout_2->addWidget(ICAOcomboBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_2);

        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_21 = new QHBoxLayout(groupBox_2);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_11->addWidget(label_18);

        EngineLabel = new QLabel(groupBox_2);
        EngineLabel->setObjectName(QString::fromUtf8("EngineLabel"));

        horizontalLayout_11->addWidget(EngineLabel);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_12->addWidget(label_25);

        MassLowLabel = new QLabel(groupBox_2);
        MassLowLabel->setObjectName(QString::fromUtf8("MassLowLabel"));

        horizontalLayout_12->addWidget(MassLowLabel);

        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_12->addWidget(label_28);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_15->addWidget(label_19);

        VmoLabel = new QLabel(groupBox_2);
        VmoLabel->setObjectName(QString::fromUtf8("VmoLabel"));

        horizontalLayout_15->addWidget(VmoLabel);

        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_15->addWidget(label_22);


        verticalLayout->addLayout(horizontalLayout_15);


        horizontalLayout_21->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_31 = new QLabel(groupBox_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        horizontalLayout_18->addWidget(label_31);

        WakeLabel = new QLabel(groupBox_2);
        WakeLabel->setObjectName(QString::fromUtf8("WakeLabel"));

        horizontalLayout_18->addWidget(WakeLabel);


        verticalLayout_2->addLayout(horizontalLayout_18);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_13->addWidget(label_26);

        MassNomLabel = new QLabel(groupBox_2);
        MassNomLabel->setObjectName(QString::fromUtf8("MassNomLabel"));

        horizontalLayout_13->addWidget(MassNomLabel);

        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        horizontalLayout_13->addWidget(label_29);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_16->addWidget(label_20);

        MmoLabel = new QLabel(groupBox_2);
        MmoLabel->setObjectName(QString::fromUtf8("MmoLabel"));

        horizontalLayout_16->addWidget(MmoLabel);

        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_16->addWidget(label_23);


        verticalLayout_2->addLayout(horizontalLayout_16);


        horizontalLayout_21->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        horizontalLayout_19->addWidget(label_32);

        WingSpanLabel = new QLabel(groupBox_2);
        WingSpanLabel->setObjectName(QString::fromUtf8("WingSpanLabel"));

        horizontalLayout_19->addWidget(WingSpanLabel);

        label_37 = new QLabel(groupBox_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        horizontalLayout_19->addWidget(label_37);


        verticalLayout_3->addLayout(horizontalLayout_19);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_14->addWidget(label_27);

        MassHighLabel = new QLabel(groupBox_2);
        MassHighLabel->setObjectName(QString::fromUtf8("MassHighLabel"));

        horizontalLayout_14->addWidget(MassHighLabel);

        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        horizontalLayout_14->addWidget(label_30);


        verticalLayout_3->addLayout(horizontalLayout_14);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_17->addWidget(label_21);

        HmoLabel = new QLabel(groupBox_2);
        HmoLabel->setObjectName(QString::fromUtf8("HmoLabel"));

        horizontalLayout_17->addWidget(HmoLabel);

        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_17->addWidget(label_24);


        verticalLayout_3->addLayout(horizontalLayout_17);


        horizontalLayout_21->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_33 = new QLabel(groupBox_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        horizontalLayout_20->addWidget(label_33);

        ACLengthLabel = new QLabel(groupBox_2);
        ACLengthLabel->setObjectName(QString::fromUtf8("ACLengthLabel"));

        horizontalLayout_20->addWidget(ACLengthLabel);

        label_36 = new QLabel(groupBox_2);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        horizontalLayout_20->addWidget(label_36);


        verticalLayout_4->addLayout(horizontalLayout_20);

        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        verticalLayout_4->addWidget(label_34);

        label_35 = new QLabel(groupBox_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        verticalLayout_4->addWidget(label_35);


        horizontalLayout_21->addLayout(verticalLayout_4);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 50));
        horizontalLayout_9 = new QHBoxLayout(groupBox);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        CAS_MACH_rb = new QRadioButton(groupBox);
        CAS_MACH_rb->setObjectName(QString::fromUtf8("CAS_MACH_rb"));

        horizontalLayout_9->addWidget(CAS_MACH_rb);

        ROCD_rb = new QRadioButton(groupBox);
        ROCD_rb->setObjectName(QString::fromUtf8("ROCD_rb"));

        horizontalLayout_9->addWidget(ROCD_rb);

        Gradient_rb = new QRadioButton(groupBox);
        Gradient_rb->setObjectName(QString::fromUtf8("Gradient_rb"));

        horizontalLayout_9->addWidget(Gradient_rb);

        EmergencyDescent_rb = new QRadioButton(groupBox);
        EmergencyDescent_rb->setObjectName(QString::fromUtf8("EmergencyDescent_rb"));

        horizontalLayout_9->addWidget(EmergencyDescent_rb);


        verticalLayout_5->addWidget(groupBox);

        expediteChB = new QCheckBox(Dialog);
        expediteChB->setObjectName(QString::fromUtf8("expediteChB"));

        verticalLayout_5->addWidget(expediteChB);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_12 = new QLabel(Dialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_6->addWidget(label_12);

        ACMassLineEdit = new QLineEdit(Dialog);
        ACMassLineEdit->setObjectName(QString::fromUtf8("ACMassLineEdit"));

        horizontalLayout_6->addWidget(ACMassLineEdit);

        label_13 = new QLabel(Dialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_6->addWidget(label_13);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        CASLineEdit = new QLineEdit(Dialog);
        CASLineEdit->setObjectName(QString::fromUtf8("CASLineEdit"));

        horizontalLayout_3->addWidget(CASLineEdit);

        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_14 = new QLabel(Dialog);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_7->addWidget(label_14);

        ROCDLineEdit = new QLineEdit(Dialog);
        ROCDLineEdit->setObjectName(QString::fromUtf8("ROCDLineEdit"));

        horizontalLayout_7->addWidget(ROCDLineEdit);

        label_15 = new QLabel(Dialog);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_7->addWidget(label_15);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_16 = new QLabel(Dialog);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_8->addWidget(label_16);

        GradientLineEdit = new QLineEdit(Dialog);
        GradientLineEdit->setObjectName(QString::fromUtf8("GradientLineEdit"));

        horizontalLayout_8->addWidget(GradientLineEdit);

        label_17 = new QLabel(Dialog);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_8->addWidget(label_17);


        verticalLayout_5->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        MachLineEdit = new QLineEdit(Dialog);
        MachLineEdit->setObjectName(QString::fromUtf8("MachLineEdit"));

        horizontalLayout_4->addWidget(MachLineEdit);

        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_38 = new QLabel(Dialog);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        horizontalLayout_23->addWidget(label_38);

        BankAngleLineEdit = new QLineEdit(Dialog);
        BankAngleLineEdit->setObjectName(QString::fromUtf8("BankAngleLineEdit"));

        horizontalLayout_23->addWidget(BankAngleLineEdit);

        label_39 = new QLabel(Dialog);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        horizontalLayout_23->addWidget(label_39);


        verticalLayout_5->addLayout(horizontalLayout_23);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        Hp_0LineEdit = new QLineEdit(Dialog);
        Hp_0LineEdit->setObjectName(QString::fromUtf8("Hp_0LineEdit"));

        horizontalLayout_5->addWidget(Hp_0LineEdit);

        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_5->addWidget(label_9);

        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        Hp_nLineEdit = new QLineEdit(Dialog);
        Hp_nLineEdit->setObjectName(QString::fromUtf8("Hp_nLineEdit"));

        horizontalLayout_5->addWidget(Hp_nLineEdit);

        label_10 = new QLabel(Dialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_5->addWidget(label_10);

        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        delta_HpLineEdit = new QLineEdit(Dialog);
        delta_HpLineEdit->setObjectName(QString::fromUtf8("delta_HpLineEdit"));

        horizontalLayout_5->addWidget(delta_HpLineEdit);

        label_11 = new QLabel(Dialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_5->addWidget(label_11);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        parsePushButton = new QPushButton(Dialog);
        parsePushButton->setObjectName(QString::fromUtf8("parsePushButton"));

        horizontalLayout->addWidget(parsePushButton);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        startPushButton = new QPushButton(Dialog);
        startPushButton->setObjectName(QString::fromUtf8("startPushButton"));

        horizontalLayout_10->addWidget(startPushButton);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_4);

        stopPushButton = new QPushButton(Dialog);
        stopPushButton->setObjectName(QString::fromUtf8("stopPushButton"));

        horizontalLayout_22->addWidget(stopPushButton);


        verticalLayout_5->addLayout(horizontalLayout_22);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "ICAO File code:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Aircarft parameters:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("Dialog", "Engine:", 0, QApplication::UnicodeUTF8));
        EngineLabel->setText(QApplication::translate("Dialog", "jet", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("Dialog", "Mass_low:", 0, QApplication::UnicodeUTF8));
        MassLowLabel->setText(QApplication::translate("Dialog", "41000", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("Dialog", "[kg]", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("Dialog", "Vmo:", 0, QApplication::UnicodeUTF8));
        VmoLabel->setText(QApplication::translate("Dialog", "340", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("Dialog", "[kt]", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("Dialog", "WTC:", 0, QApplication::UnicodeUTF8));
        WakeLabel->setText(QApplication::translate("Dialog", "Wake Cat:", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("Dialog", "Mass_nom:", 0, QApplication::UnicodeUTF8));
        MassNomLabel->setText(QApplication::translate("Dialog", "65000", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("Dialog", "[kg]", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("Dialog", "Mmo:", 0, QApplication::UnicodeUTF8));
        MmoLabel->setText(QApplication::translate("Dialog", "0.82", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("Dialog", "[ - ]", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("Dialog", "Wing Span:", 0, QApplication::UnicodeUTF8));
        WingSpanLabel->setText(QApplication::translate("Dialog", "Wing Span:", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("Dialog", "[m]", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("Dialog", "Mass_high:", 0, QApplication::UnicodeUTF8));
        MassHighLabel->setText(QApplication::translate("Dialog", "78000", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("Dialog", "[kg]", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("Dialog", "Hmo:", 0, QApplication::UnicodeUTF8));
        HmoLabel->setText(QApplication::translate("Dialog", "41000", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("Dialog", "AC Length:", 0, QApplication::UnicodeUTF8));
        ACLengthLabel->setText(QApplication::translate("Dialog", "length", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("Dialog", "[m]", 0, QApplication::UnicodeUTF8));
        label_34->setText(QString());
        label_35->setText(QString());
        groupBox->setTitle(QApplication::translate("Dialog", "Type of Descent", 0, QApplication::UnicodeUTF8));
        CAS_MACH_rb->setText(QApplication::translate("Dialog", "CAS/MACH", 0, QApplication::UnicodeUTF8));
        ROCD_rb->setText(QApplication::translate("Dialog", "ROCD", 0, QApplication::UnicodeUTF8));
        Gradient_rb->setText(QApplication::translate("Dialog", "Gradient", 0, QApplication::UnicodeUTF8));
        EmergencyDescent_rb->setText(QApplication::translate("Dialog", "Emergency descent", 0, QApplication::UnicodeUTF8));
        expediteChB->setText(QApplication::translate("Dialog", "expedite descent", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Dialog", "ACMass", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("Dialog", "[kg]", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Dialog", "CAS", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Dialog", "[kt]", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("Dialog", "ROCD", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("Dialog", "[ft/min]", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("Dialog", "Grad", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("Dialog", "[\302\260]", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Dialog", "MACH", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Dialog", "[-]", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("Dialog", "BANK angle", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("Dialog", "[\302\260]", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "Hp_0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "Hp_n", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog", "delta_Hp", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        parsePushButton->setText(QApplication::translate("Dialog", "Parse", 0, QApplication::UnicodeUTF8));
        startPushButton->setText(QApplication::translate("Dialog", "START", 0, QApplication::UnicodeUTF8));
        stopPushButton->setText(QApplication::translate("Dialog", "STOP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
