/********************************************************************************
** Form generated from reading UI file 'qcvwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCVWIDGET_H
#define UI_QCVWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QCvWidget
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelView;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonPlay;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *spinBoxBinaryThreshold;
    QCheckBox *checkBoxEnableBinaryThreshold;

    void setupUi(QWidget *QCvWidget)
    {
        if (QCvWidget->objectName().isEmpty())
            QCvWidget->setObjectName(QStringLiteral("QCvWidget"));
        QCvWidget->resize(613, 459);
        gridLayout_2 = new QGridLayout(QCvWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelView = new QLabel(QCvWidget);
        labelView->setObjectName(QStringLiteral("labelView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelView->sizePolicy().hasHeightForWidth());
        labelView->setSizePolicy(sizePolicy);
        labelView->setStyleSheet(QStringLiteral("border: 1px solid;"));

        verticalLayout->addWidget(labelView);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonPlay = new QPushButton(QCvWidget);
        pushButtonPlay->setObjectName(QStringLiteral("pushButtonPlay"));

        horizontalLayout_2->addWidget(pushButtonPlay);

        groupBox = new QGroupBox(QCvWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxBinaryThreshold = new QSpinBox(groupBox);
        spinBoxBinaryThreshold->setObjectName(QStringLiteral("spinBoxBinaryThreshold"));
        spinBoxBinaryThreshold->setMaximum(255);
        spinBoxBinaryThreshold->setValue(127);

        horizontalLayout->addWidget(spinBoxBinaryThreshold);

        checkBoxEnableBinaryThreshold = new QCheckBox(groupBox);
        checkBoxEnableBinaryThreshold->setObjectName(QStringLiteral("checkBoxEnableBinaryThreshold"));

        horizontalLayout->addWidget(checkBoxEnableBinaryThreshold);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(QCvWidget);

        QMetaObject::connectSlotsByName(QCvWidget);
    } // setupUi

    void retranslateUi(QWidget *QCvWidget)
    {
        QCvWidget->setWindowTitle(QApplication::translate("QCvWidget", "QCvWidget", nullptr));
        labelView->setText(QString());
        pushButtonPlay->setText(QApplication::translate("QCvWidget", ">", nullptr));
        groupBox->setTitle(QApplication::translate("QCvWidget", "Binary Threshold", nullptr));
        label_2->setText(QApplication::translate("QCvWidget", "Threshold: ", nullptr));
        checkBoxEnableBinaryThreshold->setText(QApplication::translate("QCvWidget", "Enable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QCvWidget: public Ui_QCvWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCVWIDGET_H
