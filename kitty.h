//kitty.h File

#ifndef KITTY_H
#define KITTY_H

#include <QMessageBox>
#include <QLCDNumber>
#include <QString>
#include <QTimer>
#include <QTime>
//#include <strstream>
#include <QDebug>

class kitty: public QLCDNumber
{
  Q_OBJECT

  public:
  int min;
  int sec;
  QTimer * timer;
  QTime timeValue;
  QString kittyName;
  QPalette kPa;

  public:
    kitty (QWidget * parentWidget, int minutes, int seconds)
    {
        this->kPa = this->palette();
        this->kPa.setColor(QPalette::Normal, QPalette::Dark, QColor::fromRgb(204, 0, 255, 0));
        this->setPalette(kPa);
        this->min = minutes;
        this->sec = seconds;
        this->reset(this->min, this->sec);
        this->timer = new QTimer();
        this->setParent(parentWidget);
        QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));
    }

    ~ kitty(){}

    void reset(int minutes, int seconds)
    {
        this->timeValue.setHMS(0, minutes, seconds);
    }

   public slots:
    void setDisplay()
    {
        if (this->timeValue.operator > (QTime::fromString("00:00")))
        {
            this->timeValue.setHMS(0, this->timeValue.addSecs(-1).minute(), this->timeValue.addSecs(-1).second());
            //qDebug() << QString("Minutes = ") + this->timeValue.minute() + QString(", Seconds = ") + this->timeValue.second();
            this->display(this->timeValue.toString());
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText(QString("Time to pet ") + this->kittyName + QString("!"));
            msgBox.exec();
            this->reset(this->min, this->sec);
            //this->timer->stop();
        }
    }
   //private:
};

#endif // KITTY_H
