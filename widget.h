#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_calculate_button_clicked();

    void on_calculate_button_roll_clicked();

private:
    Ui::Widget *ui;

    float diameter;         //轮组直径
    float reduction_ratio;  //减速比 1:x
    float round_pulse;      //转一圈电机脉冲数
    float gather_mode;      //采样模式  上下沿采集时 为2
    float period;           //周期

    float perimeterr;       //周长
    float wheel_turn;
    float wheel_wide;

    float rpm_roll;
    float reduction_ratio_roll;  //减速比 1:x
    float round_pulse_roll;      //转一圈电机脉冲数
    float gather_mode_roll;      //采样模式  上下沿采集时 为2
    float period_roll;           //周期

    float hope_pulse;

};

#endif // WIDGET_H
