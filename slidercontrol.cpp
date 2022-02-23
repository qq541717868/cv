#include "slidercontrol.h"

SliderControl::SliderControl(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSlider_DoubleSpinbox()));
    connect(spinBox, SIGNAL(valueChanged(double)),  this, SLOT(slotDoubleSpinbox_Slider()));
    connect(horizontalSlider,&QSlider::valueChanged,this,&SliderControl::sendMessage);

    horizontalSlider->setRange(0*100,100*100);
    spinBox->setRange(0,100);
    spinBox->setSingleStep(0.1);
    horizontalSlider->setValue(0*100);

}
SliderControl::SliderControl(const QString &name,const double &max,const double &min,const double &defaultValue,const double &changeValue,QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSlider_DoubleSpinbox()));
    connect(spinBox, SIGNAL(valueChanged(double)),  this, SLOT(slotDoubleSpinbox_Slider()));
    connect(horizontalSlider,&QSlider::valueChanged,this,&SliderControl::sendMessage);
    controlName->setText(name);
    horizontalSlider->setRange(min*100,max*100);
    spinBox->setRange(min,max);
    spinBox->setSingleStep(changeValue);
    horizontalSlider->setValue(defaultValue*100);
}
void SliderControl::reload(const QString &name,const double &max,const double &min,const double &defaultValue,const double &changeValue)
{
    controlName->setText(name);
    horizontalSlider->setRange(min*100,max*100);
    spinBox->setRange(min,max);
    spinBox->setSingleStep(changeValue);
    horizontalSlider->setValue(defaultValue*100);
}
void SliderControl::reload(const QString &name)
{
    controlName->setText(name);
    horizontalSlider->setRange(0*100,100*100);
    spinBox->setRange(0,100);
    spinBox->setSingleStep(0.1);
    horizontalSlider->setValue(0*100);

}

 void  SliderControl::sendMessage()
 {
    emit sendValueChangeMessage();
 }

double  SliderControl::getValue()
{
    return spinBox->value();
}

void SliderControl::slotDoubleSpinbox_Slider()
{
    horizontalSlider->setValue((int)(spinBox->value()*100));
}

void SliderControl::slotSlider_DoubleSpinbox()
{
    spinBox->setValue((double)(horizontalSlider->value())/100);
}
