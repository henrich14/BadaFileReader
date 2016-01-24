/********************************************************************************
** Form generated from reading UI file 'graph.ui'
**
** Created: Fri 22. Jan 13:59:05 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Graph
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *NumOfPoints;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox_1;
    QwtPlot *QwtPlot_1;
    QComboBox *comboBox_3;
    QwtPlot *QwtPlot_3;
    QComboBox *comboBox_5;
    QwtPlot *QwtPlot_5;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_2;
    QwtPlot *QwtPlot_2;
    QComboBox *comboBox_4;
    QwtPlot *QwtPlot_4;
    QComboBox *comboBox_6;
    QwtPlot *QwtPlot_6;

    void setupUi(QDialog *Graph)
    {
        if (Graph->objectName().isEmpty())
            Graph->setObjectName(QString::fromUtf8("Graph"));
        Graph->resize(967, 424);
        verticalLayout_3 = new QVBoxLayout(Graph);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Graph);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        NumOfPoints = new QSpinBox(Graph);
        NumOfPoints->setObjectName(QString::fromUtf8("NumOfPoints"));

        horizontalLayout->addWidget(NumOfPoints);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        comboBox_1 = new QComboBox(Graph);
        comboBox_1->setObjectName(QString::fromUtf8("comboBox_1"));

        verticalLayout->addWidget(comboBox_1);

        QwtPlot_1 = new QwtPlot(Graph);
        QwtPlot_1->setObjectName(QString::fromUtf8("QwtPlot_1"));
        QwtPlot_1->setMouseTracking(false);

        verticalLayout->addWidget(QwtPlot_1);

        comboBox_3 = new QComboBox(Graph);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        verticalLayout->addWidget(comboBox_3);

        QwtPlot_3 = new QwtPlot(Graph);
        QwtPlot_3->setObjectName(QString::fromUtf8("QwtPlot_3"));
        QwtPlot_3->setMouseTracking(false);

        verticalLayout->addWidget(QwtPlot_3);

        comboBox_5 = new QComboBox(Graph);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));

        verticalLayout->addWidget(comboBox_5);

        QwtPlot_5 = new QwtPlot(Graph);
        QwtPlot_5->setObjectName(QString::fromUtf8("QwtPlot_5"));
        QwtPlot_5->setMouseTracking(false);

        verticalLayout->addWidget(QwtPlot_5);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        comboBox_2 = new QComboBox(Graph);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        verticalLayout_2->addWidget(comboBox_2);

        QwtPlot_2 = new QwtPlot(Graph);
        QwtPlot_2->setObjectName(QString::fromUtf8("QwtPlot_2"));
        QwtPlot_2->setMouseTracking(false);

        verticalLayout_2->addWidget(QwtPlot_2);

        comboBox_4 = new QComboBox(Graph);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        verticalLayout_2->addWidget(comboBox_4);

        QwtPlot_4 = new QwtPlot(Graph);
        QwtPlot_4->setObjectName(QString::fromUtf8("QwtPlot_4"));
        QwtPlot_4->setMouseTracking(false);

        verticalLayout_2->addWidget(QwtPlot_4);

        comboBox_6 = new QComboBox(Graph);
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));

        verticalLayout_2->addWidget(comboBox_6);

        QwtPlot_6 = new QwtPlot(Graph);
        QwtPlot_6->setObjectName(QString::fromUtf8("QwtPlot_6"));
        QwtPlot_6->setMouseTracking(false);

        verticalLayout_2->addWidget(QwtPlot_6);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        QwtPlot_1->raise();
        QwtPlot_2->raise();
        QwtPlot_3->raise();
        QwtPlot_4->raise();
        QwtPlot_5->raise();
        QwtPlot_6->raise();
        comboBox_1->raise();
        comboBox_2->raise();
        comboBox_3->raise();
        comboBox_4->raise();
        comboBox_5->raise();
        comboBox_6->raise();
        QwtPlot_6->raise();
        NumOfPoints->raise();
        label->raise();

        retranslateUi(Graph);

        QMetaObject::connectSlotsByName(Graph);
    } // setupUi

    void retranslateUi(QDialog *Graph)
    {
        Graph->setWindowTitle(QApplication::translate("Graph", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Graph", "Number of Points:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Graph: public Ui_Graph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_H
