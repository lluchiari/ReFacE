#ifndef SETMATCHPARAMWINDOW_H
#define SETMATCHPARAMWINDOW_H

#include <QDialog>

#include <Utils/common.h>
#include <Utils/consts.h>
#include <Modules/matching/Matching.hh>

using namespace std;
using namespace consts;
using namespace myMatching;

namespace Ui {
    class SetMatchParamWindow;
}

class SetMatchParamWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetMatchParamWindow(string mode, Matching *matchModule, QWidget *parent = 0);
    ~SetMatchParamWindow();

private slots:
    void on_ApplyButton_clicked();

    void on_SaveButton_clicked();

    void on_CancelButton_clicked();

    void on_Max_DisparityHorizontalSlider_valueChanged(int value);

    void on_PreFilterCarpHorizontalSlider_valueChanged(int value);

    void on_Window_SizeHorizontalSlider_valueChanged(int value);

    void on_TextureThresholdHorizontalSlider_valueChanged(int value);

    void on_UniquenessRatioHorizontalSlider_valueChanged(int value);

    void on_SpeckleWindowSizeHorizontalSlider_valueChanged(int value);

    void on_SpeckleRangeHorizontalSlider_valueChanged(int value);

    void on_Disp12MaxDiffHorizontalSlider_valueChanged(int value);

private:
    string _mode;
    Matching *_matchModule;
    Ui::SetMatchParamWindow *ui;

    bool _has_textureThreshold;
    bool _has_algorithm;

    void _config();
};

#endif // SETMATCHPARAMWINDOW_H
