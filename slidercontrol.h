#ifndef SLIDERCONTROL_H
#define SLIDERCONTROL_H

#include "ui_slidercontrol.h"

class SliderControl : public QWidget, public Ui::SliderControl
{
    Q_OBJECT

public:
    explicit SliderControl(QWidget *parent = 0);
    explicit SliderControl(const QString &name,const double &max,const double &min,const double &defaultValue,const double &changeValue,QWidget *parent = 0);
signals:
     void  sendValueChangeMessage();
public slots:
     void  sendMessage();
     void slotDoubleSpinbox_Slider();
     void slotSlider_DoubleSpinbox();
     double getValue();

     void reload(const QString &name,const double &max,const double &min,const double &defaultValue,const double &changeValue=1);
     void reload(const QString &name);
};

#endif // SLIDERCONTROL_H
