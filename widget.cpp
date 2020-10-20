#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "math.h"
#include <QString>

#define PI 3.141592653897

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Edit_dia->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_ratio_1->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_ratio_2->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_pulse->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_period->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字

    ui->Edit_Roll_rpm->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_roll_ratio_1->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_roll_pulse->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字
    ui->Edit_period_2->setValidator(new QRegExpValidator(QRegExp("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)")));   //只能输入数字

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_calculate_button_clicked()
{
    if(ui->Edit_dia->text()==nullptr||ui->Edit_dia->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No diameter input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        diameter = ui->Edit_dia->text().toFloat();
        perimeterr = diameter * PI;
        qDebug()<<"dia = "<<diameter;
        qDebug()<<"perimeterr = "<<perimeterr;
    }

    if(ui->Edit_ratio_1->text()==nullptr||ui->Edit_ratio_2->text()==nullptr||
            ui->Edit_ratio_1->text()==0||ui->Edit_ratio_2->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No reduction_ratio input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        float ratio_1 = ui->Edit_ratio_1->text().toFloat();
        float ratio_2 = ui->Edit_ratio_2->text().toFloat();
        reduction_ratio = ratio_1 / ratio_2;
        qDebug()<<"reduction_ratio = "<<reduction_ratio;
    }


    if(ui->Edit_pulse->text()==nullptr||ui->Edit_pulse->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No round_pulse input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        gather_mode = float(ui->comboBox->currentIndex()==0?2:1);
        qDebug()<<"gather_mode = "<<gather_mode;
        round_pulse = (ui->Edit_pulse->text().toFloat())*gather_mode;
        qDebug()<<"round_pulse = "<<round_pulse;
    }

    if(ui->Edit_period->text()==nullptr||ui->Edit_period->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No round_pulse input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        period = (ui->Edit_period->text().toFloat());
        qDebug()<<"period = "<<period;
    }
    //wheel_wide 计算写入
    wheel_wide = ((1/round_pulse) * (reduction_ratio))*perimeterr;
    qDebug()<<"wheel_wide = "<<wheel_wide;

    QString data = QString("%1").arg(wheel_wide);
    ui->Edit_WIDE->setText(data);

    //wheel_turn 计算写入
    wheel_turn = ((((1/perimeterr)*(1/reduction_ratio))*round_pulse)/1000)*period;
    qDebug()<<"wheel_turn = "<<wheel_turn;

    data = QString("%1").arg(wheel_turn);
    ui->Edit_TURN->setText(data);

}

void Widget::on_calculate_button_roll_clicked()
{
    if(ui->Edit_Roll_rpm->text()==nullptr||ui->Edit_Roll_rpm->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No rpm input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        rpm_roll = ui->Edit_Roll_rpm->text().toFloat();
        qDebug()<<"rpm_roll = "<<rpm_roll;
    }

    if(ui->Edit_roll_ratio_1->text()==nullptr||ui->Edit_roll_ratio_2->text()==nullptr||
            ui->Edit_roll_ratio_1->text()==0||ui->Edit_roll_ratio_2->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No reduction_ratio input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        float ratio_1 = ui->Edit_roll_ratio_1->text().toFloat();
        float ratio_2 = ui->Edit_roll_ratio_2->text().toFloat();
        reduction_ratio_roll = ratio_1 / ratio_2;
        qDebug()<<"reduction_ratio = "<<reduction_ratio_roll;
    }


    if(ui->Edit_roll_pulse->text()==nullptr||ui->Edit_roll_pulse->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No round_pulse input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        gather_mode_roll = float(ui->comboBox_2->currentIndex()==0?2:1);
        qDebug()<<"gather_mode = "<<gather_mode_roll;
        round_pulse_roll = (ui->Edit_roll_pulse->text().toFloat())*gather_mode_roll;
        qDebug()<<"round_pulse = "<<round_pulse_roll;
    }

    if(ui->Edit_period_2->text()==nullptr||ui->Edit_period_2->text()==0){
        qDebug()<<"error";
        QMessageBox::warning(this,"ERROR","No round_pulse input",QMessageBox::Cancel|QMessageBox::Escape|QMessageBox::Default,0);
        return;
    }else{
        period_roll = (ui->Edit_period_2->text().toFloat());
        qDebug()<<"period = "<<period_roll;
    }


    hope_pulse = (((((rpm_roll/60)*(1/reduction_ratio_roll)))/1000)*period_roll)*round_pulse_roll;
     qDebug()<<"hope_pulse = "<<hope_pulse;

     QString data = QString("%1").arg(hope_pulse);
     ui->Edit_roll_hope->setText(data);
}
