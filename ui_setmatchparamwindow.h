/********************************************************************************
** Form generated from reading UI file 'setmatchparamwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETMATCHPARAMWINDOW_H
#define UI_SETMATCHPARAMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetMatchParamWindow
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *Window_Size;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Window_SizeLabel;
    QSlider *Window_SizeHorizontalSlider;
    QLineEdit *Window_SizeLineEdit;
    QWidget *Max_Disparity;
    QHBoxLayout *horizontalLayout_3;
    QLabel *Max_DisparityLabel;
    QSlider *Max_DisparityHorizontalSlider;
    QLineEdit *Max_DisparityLineEdit;
    QWidget *PreFilterCarp;
    QHBoxLayout *horizontalLayout_4;
    QLabel *PreFilterCarpLabel;
    QSlider *PreFilterCarpHorizontalSlider;
    QLineEdit *PreFilterCarpLineEdit;
    QWidget *TextureThreshold;
    QHBoxLayout *horizontalLayout_5;
    QLabel *TextureThresholdLabel;
    QSlider *TextureThresholdHorizontalSlider;
    QLineEdit *TextureThresholdLineEdit;
    QWidget *UniquenessRatio;
    QHBoxLayout *horizontalLayout_6;
    QLabel *UniquenessRatioLabel;
    QSlider *UniquenessRatioHorizontalSlider;
    QLineEdit *UniquenessRatioLineEdit;
    QWidget *SpeckleWindowSize;
    QHBoxLayout *horizontalLayout_7;
    QLabel *SpeckleWindowSizeLabel;
    QSlider *SpeckleWindowSizeHorizontalSlider;
    QLineEdit *SpeckleWindowSizeLineEdit;
    QWidget *SpeckleRange;
    QHBoxLayout *horizontalLayout_8;
    QLabel *SpeckleRangeLabel;
    QSlider *SpeckleRangeHorizontalSlider;
    QLineEdit *SpeckleRangeLineEdit;
    QWidget *Disp12MaxDiff;
    QHBoxLayout *horizontalLayout_9;
    QLabel *Disp12MaxDiffLabel;
    QSlider *Disp12MaxDiffHorizontalSlider;
    QLineEdit *Disp12MaxDiffLineEdit;
    QWidget *Algorithm;
    QVBoxLayout *verticalLayout_9;
    QLabel *AlgorithmLabel;
    QComboBox *AlgorithmComboBox;
    QSpacerItem *verticalSpacer;
    QWidget *ControlButtons;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *ApplyButton;
    QPushButton *SaveButton;
    QPushButton *CancelButton;

    void setupUi(QDialog *SetMatchParamWindow)
    {
        if (SetMatchParamWindow->objectName().isEmpty())
            SetMatchParamWindow->setObjectName(QStringLiteral("SetMatchParamWindow"));
        SetMatchParamWindow->resize(566, 601);
        verticalLayout = new QVBoxLayout(SetMatchParamWindow);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 10);
        Window_Size = new QWidget(SetMatchParamWindow);
        Window_Size->setObjectName(QStringLiteral("Window_Size"));
        horizontalLayout_2 = new QHBoxLayout(Window_Size);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Window_SizeLabel = new QLabel(Window_Size);
        Window_SizeLabel->setObjectName(QStringLiteral("Window_SizeLabel"));
        Window_SizeLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_2->addWidget(Window_SizeLabel);

        Window_SizeHorizontalSlider = new QSlider(Window_Size);
        Window_SizeHorizontalSlider->setObjectName(QStringLiteral("Window_SizeHorizontalSlider"));
        Window_SizeHorizontalSlider->setMaximum(256);
        Window_SizeHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Window_SizeHorizontalSlider);

        Window_SizeLineEdit = new QLineEdit(Window_Size);
        Window_SizeLineEdit->setObjectName(QStringLiteral("Window_SizeLineEdit"));
        Window_SizeLineEdit->setMaximumSize(QSize(30, 16777215));
        Window_SizeLineEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(Window_SizeLineEdit);


        verticalLayout->addWidget(Window_Size);

        Max_Disparity = new QWidget(SetMatchParamWindow);
        Max_Disparity->setObjectName(QStringLiteral("Max_Disparity"));
        horizontalLayout_3 = new QHBoxLayout(Max_Disparity);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Max_DisparityLabel = new QLabel(Max_Disparity);
        Max_DisparityLabel->setObjectName(QStringLiteral("Max_DisparityLabel"));
        Max_DisparityLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_3->addWidget(Max_DisparityLabel);

        Max_DisparityHorizontalSlider = new QSlider(Max_Disparity);
        Max_DisparityHorizontalSlider->setObjectName(QStringLiteral("Max_DisparityHorizontalSlider"));
        Max_DisparityHorizontalSlider->setMinimum(1);
        Max_DisparityHorizontalSlider->setMaximum(1024);
        Max_DisparityHorizontalSlider->setSingleStep(16);
        Max_DisparityHorizontalSlider->setPageStep(16);
        Max_DisparityHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(Max_DisparityHorizontalSlider);

        Max_DisparityLineEdit = new QLineEdit(Max_Disparity);
        Max_DisparityLineEdit->setObjectName(QStringLiteral("Max_DisparityLineEdit"));
        Max_DisparityLineEdit->setMaximumSize(QSize(30, 16777215));
        Max_DisparityLineEdit->setReadOnly(true);

        horizontalLayout_3->addWidget(Max_DisparityLineEdit);


        verticalLayout->addWidget(Max_Disparity);

        PreFilterCarp = new QWidget(SetMatchParamWindow);
        PreFilterCarp->setObjectName(QStringLiteral("PreFilterCarp"));
        horizontalLayout_4 = new QHBoxLayout(PreFilterCarp);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        PreFilterCarpLabel = new QLabel(PreFilterCarp);
        PreFilterCarpLabel->setObjectName(QStringLiteral("PreFilterCarpLabel"));
        PreFilterCarpLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_4->addWidget(PreFilterCarpLabel);

        PreFilterCarpHorizontalSlider = new QSlider(PreFilterCarp);
        PreFilterCarpHorizontalSlider->setObjectName(QStringLiteral("PreFilterCarpHorizontalSlider"));
        PreFilterCarpHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(PreFilterCarpHorizontalSlider);

        PreFilterCarpLineEdit = new QLineEdit(PreFilterCarp);
        PreFilterCarpLineEdit->setObjectName(QStringLiteral("PreFilterCarpLineEdit"));
        PreFilterCarpLineEdit->setEnabled(true);
        PreFilterCarpLineEdit->setMaximumSize(QSize(30, 16777215));
        PreFilterCarpLineEdit->setReadOnly(true);

        horizontalLayout_4->addWidget(PreFilterCarpLineEdit);


        verticalLayout->addWidget(PreFilterCarp);

        TextureThreshold = new QWidget(SetMatchParamWindow);
        TextureThreshold->setObjectName(QStringLiteral("TextureThreshold"));
        horizontalLayout_5 = new QHBoxLayout(TextureThreshold);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        TextureThresholdLabel = new QLabel(TextureThreshold);
        TextureThresholdLabel->setObjectName(QStringLiteral("TextureThresholdLabel"));
        TextureThresholdLabel->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextureThresholdLabel->sizePolicy().hasHeightForWidth());
        TextureThresholdLabel->setSizePolicy(sizePolicy);
        TextureThresholdLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_5->addWidget(TextureThresholdLabel);

        TextureThresholdHorizontalSlider = new QSlider(TextureThreshold);
        TextureThresholdHorizontalSlider->setObjectName(QStringLiteral("TextureThresholdHorizontalSlider"));
        TextureThresholdHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(TextureThresholdHorizontalSlider);

        TextureThresholdLineEdit = new QLineEdit(TextureThreshold);
        TextureThresholdLineEdit->setObjectName(QStringLiteral("TextureThresholdLineEdit"));
        TextureThresholdLineEdit->setEnabled(true);
        TextureThresholdLineEdit->setMaximumSize(QSize(30, 16777215));
        TextureThresholdLineEdit->setReadOnly(true);

        horizontalLayout_5->addWidget(TextureThresholdLineEdit);


        verticalLayout->addWidget(TextureThreshold);

        UniquenessRatio = new QWidget(SetMatchParamWindow);
        UniquenessRatio->setObjectName(QStringLiteral("UniquenessRatio"));
        horizontalLayout_6 = new QHBoxLayout(UniquenessRatio);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        UniquenessRatioLabel = new QLabel(UniquenessRatio);
        UniquenessRatioLabel->setObjectName(QStringLiteral("UniquenessRatioLabel"));
        UniquenessRatioLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_6->addWidget(UniquenessRatioLabel);

        UniquenessRatioHorizontalSlider = new QSlider(UniquenessRatio);
        UniquenessRatioHorizontalSlider->setObjectName(QStringLiteral("UniquenessRatioHorizontalSlider"));
        UniquenessRatioHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(UniquenessRatioHorizontalSlider);

        UniquenessRatioLineEdit = new QLineEdit(UniquenessRatio);
        UniquenessRatioLineEdit->setObjectName(QStringLiteral("UniquenessRatioLineEdit"));
        UniquenessRatioLineEdit->setEnabled(true);
        UniquenessRatioLineEdit->setMaximumSize(QSize(30, 16777215));
        UniquenessRatioLineEdit->setReadOnly(true);

        horizontalLayout_6->addWidget(UniquenessRatioLineEdit);


        verticalLayout->addWidget(UniquenessRatio);

        SpeckleWindowSize = new QWidget(SetMatchParamWindow);
        SpeckleWindowSize->setObjectName(QStringLiteral("SpeckleWindowSize"));
        horizontalLayout_7 = new QHBoxLayout(SpeckleWindowSize);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        SpeckleWindowSizeLabel = new QLabel(SpeckleWindowSize);
        SpeckleWindowSizeLabel->setObjectName(QStringLiteral("SpeckleWindowSizeLabel"));
        sizePolicy.setHeightForWidth(SpeckleWindowSizeLabel->sizePolicy().hasHeightForWidth());
        SpeckleWindowSizeLabel->setSizePolicy(sizePolicy);
        SpeckleWindowSizeLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_7->addWidget(SpeckleWindowSizeLabel);

        SpeckleWindowSizeHorizontalSlider = new QSlider(SpeckleWindowSize);
        SpeckleWindowSizeHorizontalSlider->setObjectName(QStringLiteral("SpeckleWindowSizeHorizontalSlider"));
        SpeckleWindowSizeHorizontalSlider->setMaximum(999);
        SpeckleWindowSizeHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(SpeckleWindowSizeHorizontalSlider);

        SpeckleWindowSizeLineEdit = new QLineEdit(SpeckleWindowSize);
        SpeckleWindowSizeLineEdit->setObjectName(QStringLiteral("SpeckleWindowSizeLineEdit"));
        SpeckleWindowSizeLineEdit->setEnabled(true);
        SpeckleWindowSizeLineEdit->setMaximumSize(QSize(30, 16777215));
        SpeckleWindowSizeLineEdit->setReadOnly(true);

        horizontalLayout_7->addWidget(SpeckleWindowSizeLineEdit);


        verticalLayout->addWidget(SpeckleWindowSize);

        SpeckleRange = new QWidget(SetMatchParamWindow);
        SpeckleRange->setObjectName(QStringLiteral("SpeckleRange"));
        horizontalLayout_8 = new QHBoxLayout(SpeckleRange);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        SpeckleRangeLabel = new QLabel(SpeckleRange);
        SpeckleRangeLabel->setObjectName(QStringLiteral("SpeckleRangeLabel"));
        SpeckleRangeLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_8->addWidget(SpeckleRangeLabel);

        SpeckleRangeHorizontalSlider = new QSlider(SpeckleRange);
        SpeckleRangeHorizontalSlider->setObjectName(QStringLiteral("SpeckleRangeHorizontalSlider"));
        SpeckleRangeHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(SpeckleRangeHorizontalSlider);

        SpeckleRangeLineEdit = new QLineEdit(SpeckleRange);
        SpeckleRangeLineEdit->setObjectName(QStringLiteral("SpeckleRangeLineEdit"));
        SpeckleRangeLineEdit->setEnabled(true);
        SpeckleRangeLineEdit->setMaximumSize(QSize(30, 16777215));
        SpeckleRangeLineEdit->setReadOnly(true);

        horizontalLayout_8->addWidget(SpeckleRangeLineEdit);


        verticalLayout->addWidget(SpeckleRange);

        Disp12MaxDiff = new QWidget(SetMatchParamWindow);
        Disp12MaxDiff->setObjectName(QStringLiteral("Disp12MaxDiff"));
        horizontalLayout_9 = new QHBoxLayout(Disp12MaxDiff);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        Disp12MaxDiffLabel = new QLabel(Disp12MaxDiff);
        Disp12MaxDiffLabel->setObjectName(QStringLiteral("Disp12MaxDiffLabel"));
        Disp12MaxDiffLabel->setMinimumSize(QSize(99, 0));

        horizontalLayout_9->addWidget(Disp12MaxDiffLabel);

        Disp12MaxDiffHorizontalSlider = new QSlider(Disp12MaxDiff);
        Disp12MaxDiffHorizontalSlider->setObjectName(QStringLiteral("Disp12MaxDiffHorizontalSlider"));
        Disp12MaxDiffHorizontalSlider->setMaximum(999);
        Disp12MaxDiffHorizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(Disp12MaxDiffHorizontalSlider);

        Disp12MaxDiffLineEdit = new QLineEdit(Disp12MaxDiff);
        Disp12MaxDiffLineEdit->setObjectName(QStringLiteral("Disp12MaxDiffLineEdit"));
        Disp12MaxDiffLineEdit->setEnabled(true);
        Disp12MaxDiffLineEdit->setMaximumSize(QSize(30, 16777215));
        Disp12MaxDiffLineEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(Disp12MaxDiffLineEdit);


        verticalLayout->addWidget(Disp12MaxDiff);

        Algorithm = new QWidget(SetMatchParamWindow);
        Algorithm->setObjectName(QStringLiteral("Algorithm"));
        verticalLayout_9 = new QVBoxLayout(Algorithm);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        AlgorithmLabel = new QLabel(Algorithm);
        AlgorithmLabel->setObjectName(QStringLiteral("AlgorithmLabel"));

        verticalLayout_9->addWidget(AlgorithmLabel);

        AlgorithmComboBox = new QComboBox(Algorithm);
        AlgorithmComboBox->setObjectName(QStringLiteral("AlgorithmComboBox"));
        AlgorithmComboBox->setEditable(false);

        verticalLayout_9->addWidget(AlgorithmComboBox);


        verticalLayout->addWidget(Algorithm);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        ControlButtons = new QWidget(SetMatchParamWindow);
        ControlButtons->setObjectName(QStringLiteral("ControlButtons"));
        horizontalLayout = new QHBoxLayout(ControlButtons);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ApplyButton = new QPushButton(ControlButtons);
        ApplyButton->setObjectName(QStringLiteral("ApplyButton"));

        horizontalLayout->addWidget(ApplyButton);

        SaveButton = new QPushButton(ControlButtons);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));

        horizontalLayout->addWidget(SaveButton);

        CancelButton = new QPushButton(ControlButtons);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        horizontalLayout->addWidget(CancelButton);


        verticalLayout->addWidget(ControlButtons);


        retranslateUi(SetMatchParamWindow);

        QMetaObject::connectSlotsByName(SetMatchParamWindow);
    } // setupUi

    void retranslateUi(QDialog *SetMatchParamWindow)
    {
        SetMatchParamWindow->setWindowTitle(QApplication::translate("SetMatchParamWindow", "Dialog", nullptr));
        Window_SizeLabel->setText(QApplication::translate("SetMatchParamWindow", "Window Size", nullptr));
        Window_SizeLineEdit->setText(QString());
        Max_DisparityLabel->setText(QApplication::translate("SetMatchParamWindow", "Max Disparity", nullptr));
        Max_DisparityLineEdit->setText(QString());
        PreFilterCarpLabel->setText(QApplication::translate("SetMatchParamWindow", "Pre Filter Carp", nullptr));
        PreFilterCarpLineEdit->setText(QString());
        TextureThresholdLabel->setText(QApplication::translate("SetMatchParamWindow", "Texture Threshold", nullptr));
        TextureThresholdLineEdit->setText(QString());
        UniquenessRatioLabel->setText(QApplication::translate("SetMatchParamWindow", "Uniqueness Ratio", nullptr));
        UniquenessRatioLineEdit->setText(QString());
        SpeckleWindowSizeLabel->setText(QApplication::translate("SetMatchParamWindow", "Speckle Window Size", nullptr));
        SpeckleWindowSizeLineEdit->setText(QString());
        SpeckleRangeLabel->setText(QApplication::translate("SetMatchParamWindow", "Speckle Range", nullptr));
        SpeckleRangeLineEdit->setText(QString());
        Disp12MaxDiffLabel->setText(QApplication::translate("SetMatchParamWindow", "Disp12 Max Diff", nullptr));
        Disp12MaxDiffLineEdit->setText(QString());
        AlgorithmLabel->setText(QApplication::translate("SetMatchParamWindow", "SGBM Algorithm", nullptr));
        ApplyButton->setText(QApplication::translate("SetMatchParamWindow", "Apply", nullptr));
        SaveButton->setText(QApplication::translate("SetMatchParamWindow", "Save", nullptr));
        CancelButton->setText(QApplication::translate("SetMatchParamWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetMatchParamWindow: public Ui_SetMatchParamWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETMATCHPARAMWINDOW_H
