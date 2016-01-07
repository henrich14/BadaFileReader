/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Wed 6. Jan 09:35:46 2016
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
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ICAOcodeLineEdit;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_9;
    QRadioButton *CAS_MACH_rb;
    QRadioButton *ROCD_rb;
    QRadioButton *Gradient_rb;
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

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(302, 297);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        ICAOcodeLineEdit = new QLineEdit(Dialog);
        ICAOcodeLineEdit->setObjectName(QString::fromUtf8("ICAOcodeLineEdit"));

        horizontalLayout_2->addWidget(ICAOcodeLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

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


        verticalLayout->addWidget(groupBox);

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


        verticalLayout->addLayout(horizontalLayout_6);

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


        verticalLayout->addLayout(horizontalLayout_3);

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


        verticalLayout->addLayout(horizontalLayout_7);

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


        verticalLayout->addLayout(horizontalLayout_8);

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


        verticalLayout->addLayout(horizontalLayout_4);

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


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        parsePushButton = new QPushButton(Dialog);
        parsePushButton->setObjectName(QString::fromUtf8("parsePushButton"));

        horizontalLayout->addWidget(parsePushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Dialog", "ICAO code", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "GroupBox", 0, QApplication::UnicodeUTF8));
        CAS_MACH_rb->setText(QApplication::translate("Dialog", "CAS/MACH", 0, QApplication::UnicodeUTF8));
        ROCD_rb->setText(QApplication::translate("Dialog", "ROCD", 0, QApplication::UnicodeUTF8));
        Gradient_rb->setText(QApplication::translate("Dialog", "Gradient", 0, QApplication::UnicodeUTF8));
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
        label_4->setText(QApplication::translate("Dialog", "Hp_0", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "Hp_n", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Dialog", "delta_Hp", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Dialog", "[ft]", 0, QApplication::UnicodeUTF8));
        parsePushButton->setText(QApplication::translate("Dialog", "Parse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
