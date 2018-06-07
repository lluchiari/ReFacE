#include <GUI/SetMatchParamWindow.h>
#include <GUI/ui_setmatchparamwindow.h>

SetMatchParamWindow::SetMatchParamWindow(string mode, Matching *matchModule, QWidget *parent) :
    QDialog(parent), ui(new Ui::SetMatchParamWindow)
{
    ui->setupUi(this);
    this->_matchModule = matchModule;
    this->_mode = mode;
    this->_config();
}

SetMatchParamWindow::~SetMatchParamWindow()
{
    delete ui;
}

void SetMatchParamWindow::on_ApplyButton_clicked()
{
    //TODO : Eliminate this Button

}

void SetMatchParamWindow::on_SaveButton_clicked()
{
//TODO: Create this function
}

void SetMatchParamWindow::on_CancelButton_clicked()
{
  //TODO: Create this function
}

void SetMatchParamWindow::_config(){
    this->ui->Window_SizeHorizontalSlider->setValue(this->_matchModule->getWindowSize());
    this->ui->Window_SizeHorizontalSlider->setMaximum(100);
    this->ui->Window_SizeLineEdit->setText(QString::number(this->_matchModule->getWindowSize()));

    this->ui->Max_DisparityHorizontalSlider->setValue(this->_matchModule->getMaxDisparity());
    this->ui->Max_DisparityHorizontalSlider->setMinimum(16);
    this->ui->Max_DisparityHorizontalSlider->setMaximum(1024);
    this->ui->Max_DisparityHorizontalSlider->setSingleStep(16);
    this->ui->Max_DisparityHorizontalSlider->setPageStep(16);
    this->ui->Max_DisparityLineEdit->setText(QString::number(this->_matchModule->getMaxDisparity()));

    this->ui->PreFilterCarpHorizontalSlider->setValue(this->_matchModule->getPreFilterCarp());
    this->ui->PreFilterCarpHorizontalSlider->setMinimum(1);
    this->ui->PreFilterCarpHorizontalSlider->setMaximum(63);
    this->ui->PreFilterCarpLineEdit->setText(QString::number(this->_matchModule->getPreFilterCarp()));

    this->ui->TextureThresholdHorizontalSlider->setValue(this->_matchModule->getTextureThreshold());
    this->ui->TextureThresholdHorizontalSlider->setMinimum(0);
    this->ui->TextureThresholdHorizontalSlider->setMaximum(999);
    this->ui->TextureThresholdLineEdit->setText(QString::number(this->_matchModule->getTextureThreshold()));

    this->ui->UniquenessRatioHorizontalSlider->setValue(this->_matchModule->getUniquenessRatio());
    this->ui->UniquenessRatioHorizontalSlider->setMinimum(0);
    this->ui->UniquenessRatioHorizontalSlider->setMaximum(100);
    this->ui->UniquenessRatioLineEdit->setText(QString::number(this->_matchModule->getUniquenessRatio()));

    this->ui->SpeckleWindowSizeHorizontalSlider->setValue(this->_matchModule->getSpeckleWindowSize());
    this->ui->SpeckleWindowSizeHorizontalSlider->setMinimum(0);
    this->ui->SpeckleWindowSizeHorizontalSlider->setMaximum(999);
    this->ui->SpeckleWindowSizeLineEdit->setText(QString::number(this->_matchModule->getSpeckleWindowSize()));

    this->ui->SpeckleRangeHorizontalSlider->setValue(this->_matchModule->getSpeckleRange());
    this->ui->SpeckleRangeHorizontalSlider->setMinimum(0);
    this->ui->SpeckleRangeHorizontalSlider->setMaximum(99);
    this->ui->SpeckleRangeLineEdit->setText(QString::number(this->_matchModule->getSpeckleRange()));

    this->ui->Disp12MaxDiffHorizontalSlider->setValue(this->_matchModule->getDisp12MaxDiff());
    this->ui->Disp12MaxDiffHorizontalSlider->setMinimum(0);
    this->ui->Disp12MaxDiffHorizontalSlider->setMaximum(999);
    this->ui->Disp12MaxDiffLineEdit->setText(QString::number(this->_matchModule->getDisp12MaxDiff()));

    if(!this->_mode.compare(consts::MATCHING_BM)){
        _has_textureThreshold = true;
        _has_algorithm = false;
        this->ui->Algorithm->hide();
        this->ui->TextureThresholdHorizontalSlider->setValue(this->_matchModule->getTextureThreshold());
        this->ui->Window_SizeHorizontalSlider->setMinimum(5);
    }
    else if(!this->_mode.compare(consts::MATCHING_SGBM)){
        _has_textureThreshold = false;
        _has_algorithm = true;
        ui->TextureThreshold->hide();
        ui->AlgorithmComboBox->addItem(QString("STEREO_SGBM"));
        ui->AlgorithmComboBox->addItem(QString("STEREO_HH"));
        ui->AlgorithmComboBox->addItem(QString("STEREO_3WAY"));
        this->ui->Window_SizeHorizontalSlider->setMinimum(3);
    }
}


void SetMatchParamWindow::on_Window_SizeHorizontalSlider_valueChanged(int value)
{
    int num = this->ui->Window_SizeHorizontalSlider->value();
    int returnValue = (num % 2) == 1 ? num : num + 1;
    this->_matchModule->setWindowSize(returnValue);
    this->ui->Window_SizeLineEdit->setText(QString::number(returnValue));

}

void SetMatchParamWindow::on_Max_DisparityHorizontalSlider_valueChanged(int value)
{
    int userValue = this->ui->Max_DisparityHorizontalSlider->value();
    int rest = userValue % 16;
    rest != 0 ? (userValue = userValue - rest) : userValue;
    this->_matchModule->setMaxDisparity(userValue);
    this->ui->Max_DisparityLineEdit->setText(QString::number(userValue));

}

void SetMatchParamWindow::on_PreFilterCarpHorizontalSlider_valueChanged(int value)
{
    this->_matchModule->setPreFilterCarp(this->ui->PreFilterCarpHorizontalSlider->value());
    this->ui->PreFilterCarpLineEdit->setText(QString::number(this->ui->PreFilterCarpHorizontalSlider->value()));
}

void SetMatchParamWindow::on_TextureThresholdHorizontalSlider_valueChanged(int value)
{
    this->_matchModule->setTextureThreshold(this->ui->TextureThresholdHorizontalSlider->value());
    this->ui->TextureThresholdLineEdit->setText(QString::number(this->ui->TextureThresholdHorizontalSlider->value()));
}

void SetMatchParamWindow::on_UniquenessRatioHorizontalSlider_valueChanged(int value)
{
    this->_matchModule->setUniquenessRatio(this->ui->UniquenessRatioHorizontalSlider->value());
    this->ui->UniquenessRatioLineEdit->setText(QString::number(this->ui->UniquenessRatioHorizontalSlider->value()));
}

void SetMatchParamWindow::on_SpeckleWindowSizeHorizontalSlider_valueChanged(int value)
{
    this->_matchModule->setSpeckleWindowSize(this->ui->SpeckleWindowSizeHorizontalSlider->value());
    this->ui->SpeckleWindowSizeLineEdit->setText(QString::number(this->ui->SpeckleWindowSizeHorizontalSlider->value()));
}

void SetMatchParamWindow::on_SpeckleRangeHorizontalSlider_valueChanged(int value)
{
    this->_matchModule->setSpeckleRange(this->ui->SpeckleRangeHorizontalSlider->value());
    this->ui->SpeckleRangeLineEdit->setText(QString::number(this->ui->SpeckleRangeHorizontalSlider->value()));
}

void SetMatchParamWindow::on_Disp12MaxDiffHorizontalSlider_valueChanged(int value)
{
    this->_matchModule->setDisp12MaxDiff(this->ui->Disp12MaxDiffHorizontalSlider->value());
    this->ui->Disp12MaxDiffLineEdit->setText(QString::number(this->ui->Disp12MaxDiffHorizontalSlider->value()));
}
