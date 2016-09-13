#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kitty.h"
#include "QString"

kitty *meow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(500,185);
    ui->lblKitty->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbStart_toggled(bool checked)
{    
    if (checked)
    {
        if (meow == NULL)
        {
            meow = new kitty(ui->centralWidget, ui->timeEdit->time().minute(), ui->timeEdit->time().second());
            meow->setGeometry(310,30,180,80);
            meow->display(ui->timeEdit->time().toString());
            meow->show();
        }

        if (ui->lineEdit->text().isEmpty())
        {
            meow->kittyName = QString("Kitty");
        }
        else
        {
            meow->kittyName = QString(ui->lineEdit->text());
        }

        if (ui->timeEdit->text() != QString("00:00"))
        {
         meow->timer->start(1000);
         ui->pbStart->setText("Pause");
         ui->pbStop->setEnabled(true);
         ui->timeEdit->setHidden(true);
         ui->lineEdit->setEnabled(false);
         ui->lineEdit->setHidden(true);
         ui->lblKitty->setHidden(false);
         ui->lblKitty->setText(meow->kittyName);
        }
        else
        {
            ui->pbStart->setChecked(false);
            ui->pbStart->setText("Start");
            ui->pbStop->setEnabled(false);
            ui->timeEdit->setHidden(false);
            meow->setHidden(true);
            ui->lineEdit->setHidden(false);
            ui->lineEdit->setEnabled(true);
            ui->lblKitty->setHidden(true);
            meow = NULL;
        }
    }
    else
    {
        ui->pbStart->setText("Resume");
        ui->pbStop->setEnabled(false);
        meow->timer->stop();
    }
}

void MainWindow::on_pbStop_clicked()
{

    ui->pbStart->setChecked(false);
    ui->pbStart->setText("Start");
    ui->pbStop->setEnabled(false);
    ui->timeEdit->setHidden(false);
    meow->setHidden(true);
    ui->lineEdit->setHidden(false);
    ui->lineEdit->setEnabled(true);
    ui->lblKitty->setHidden(true);
    meow = NULL;
}

void MainWindow::on_pbClose_clicked()
{
    QApplication::quit();
}
