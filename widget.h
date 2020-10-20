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

};

#endif // WIDGET_H
