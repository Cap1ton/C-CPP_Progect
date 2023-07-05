#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "qcustomplot.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "pol/pol.h"
#ifdef __cplusplus
}
#endif

#define LAST_SIM_IS_NUM (ui->Okno->text().back() >= '0' && ui->Okno->text().back() <= '9') || ui->Okno->text().back() == 'x'
#define LAST_SIM_IS_BIN_OP (ui->Okno->text().back() == '+' || ui->Okno->text().back() == '-' || \
                            ui->Okno->text().back() == '*' || ui->Okno->text().back() == '/' || \
                            ui->Okno->text().back() == 'd' || ui->Okno->text().back() == '^')
#define CHECK_LAST_SIM_TO_NUM ui->Okno->text().back() != ')' && ui->Okno->text().back() != 'x'

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void MessageEvent(int error_target, QString &strValue);

    void Print_graf();

    void Clalc_start();

    void on_Close_br_clicked();

    void on_Open_Br_clicked();

    void on_NumX_clicked();

    void on_Point_clicked();

    void on_Result_clicked();

    void on_Num0_clicked();

    void on_Num1_clicked();

    void on_Num2_clicked();

    void on_Num3_clicked();

    void on_Num4_clicked();

    void on_Num5_clicked();

    void on_Num6_clicked();

    void on_Num7_clicked();

    void on_Num8_clicked();

    void on_Num9_clicked();

    void on_Umn_clicked();

    void on_Del_clicked();

    void on_Sum_clicked();

    void on_Sub_clicked();

    void on_Exp_clicked();

    void on_Mod_clicked();

    void on_Sin_clicked();

    void on_Cos_clicked();

    void on_Tan_clicked();

    void on_Asin_clicked();

    void on_Acos_clicked();

    void on_Atan_clicked();

    void on_Sqrt_clicked();

    void on_Ln_clicked();

    void on_Log_clicked();

    void on_AC_clicked();

    void on_calculation_clicked();


private:
    Ui::MainWindow *ui;
    int count_open_br;
    int count_close_br;
    bool point_flag;
    bool point_zero;
    bool point_x;
    bool point_res;
    QVector<double> x,y;
};
#endif // MAINWINDOW_H
