#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pol/pol.c"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , count_open_br(0)
    , count_close_br(0)
    , point_flag(true)
    , point_zero(true)
    , point_x(false)
    , point_res(false)
{
    ui->setupUi(this);
    ui->Okno->setText(" ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Close_br_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if ((LAST_SIM_IS_NUM || ui->Okno->text().back() == ')') && count_open_br > count_close_br) {
        ui->Okno->setText(ui->Okno->text() + ")");
        count_close_br += 1;
    }
}


void MainWindow::on_Open_Br_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "(");
        count_open_br += 1;
    }
}


void MainWindow::on_NumX_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (!(LAST_SIM_IS_NUM) && ui->Okno->text().back() != ')') {
        ui->Okno->setText(ui->Okno->text() + "x");
        point_x = true;
    }
}

void MainWindow::on_Point_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM && point_flag) {
        if (ui->Okno->text().back() != 'x') {
            ui->Okno->setText(ui->Okno->text() + ".");
            point_flag = false;
            point_zero = true;
        }
    }
}

void MainWindow::MessageEvent(int error_target, QString &strValue) {
    if (error_target == 1) {
        QMessageBox::warning(this,"WARNING","Нельзя вычислять отрицательный корень");
        strValue = ' ';
    } else if (error_target == 2) {
        QMessageBox::warning(this,"WARNING","Нельзя делить на ноль");
        strValue = ' ';
    } else if (error_target == 3) {
        QMessageBox::warning(this,"WARNING","Результат вышел в inf");
        strValue = ' ';
    } else {
        QMessageBox::warning(this,"WARNING","Результат вышел в NAN");
        strValue = ' ';
    }
}

void MainWindow::Clalc_start() {
    QString text = ui->Okno->text();
    std::string text_str = text.toStdString();
    char const *mas = text_str.c_str();
    int error_target = 0;
    double res = pol_hendler(mas, 0, &error_target);
    QString strValue = QString::number(res, 'f', 7);
    if (error_target) {
        MessageEvent(error_target, strValue);
    } else {
        for(int i = strValue.size() - 1, stop_target = 0; ; i--) {
            if (strValue[i] == '0') {
                strValue.remove(i, 1);
            } else if (strValue[i] == '.') {
                strValue.remove(i, 1);
                stop_target = 1;
            } else {
                stop_target = 1;
            }
            if (stop_target) {
                break;
            }
        }
    }
    ui->Okno->setText(strValue);


    point_res = true;
    count_open_br = 0;
    count_close_br = 0;
    point_flag = true;
    point_zero = true;
    point_x = false;
}

void MainWindow::Print_graf() {
    double MaxX = ui->MaxX->value(), MinX = ui->MinX->value();
    if (MaxX <= MinX) {
        QMessageBox::warning(this,"WARNING","MaxX не может быть меньше или равен MinX");
    } else {
        double StepX = (MaxX - MinX)/1000;
        long double res_max = 2.22507385850720138e-308, res_min = 1.79769313486231571e+308;
        QString text = ui->Okno->text();
        std::string text_str = text.toStdString();
        char const *mas = text_str.c_str();
        for (double X = MinX; X < MaxX; X += StepX) {
            int error_target = 0;
            double res = pol_hendler(mas, X, &error_target);
            if (res_min > res) res_min = res;
            if (res_max < res) res_max = res;
            if (res >= -1000000 && res <= 1000000 && !error_target) {
                y.push_back(res);
                x.push_back(X);
            }
       }

       ui->widget->xAxis->setRange(MinX - StepX, MaxX + StepX);
       ui->widget->yAxis->setRange(res_min - StepX, res_max + StepX);
       ui->widget->addGraph();
       ui->widget->graph(0)->addData(x,y);
       ui->widget->replot();
       ui->widget->setInteraction(QCP::iRangeZoom, true);
       ui->widget->setInteraction(QCP::iRangeDrag, true);
       point_res = true;
       count_open_br = 0;
       count_close_br = 0;
       point_flag = true;
       point_zero = true;
       point_x = false;
    }
}

void MainWindow::on_Result_clicked()
{
    x.clear();
    y.clear();
    ui->widget->clearGraphs();
    ui->widget->replot();
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (count_open_br == count_close_br && (LAST_SIM_IS_NUM || ui->Okno->text().back() == ')')) {
        if (point_x) {
            Print_graf();
        } else {
            Clalc_start();
        }
    } else {
        QMessageBox::warning(this,"WARNING","Ошибка при вводе уравнения");
    }
}


void MainWindow::on_Num0_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        if ((!(LAST_SIM_IS_NUM) && ui->Okno->text().back() != '.') && point_zero) {
            ui->Okno->setText(ui->Okno->text() + "0");
            point_zero = false;
        } else if (point_zero) {
            ui->Okno->setText(ui->Okno->text() + "0");
        }
    }
}


void MainWindow::on_Num1_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "1");
    }
}


void MainWindow::on_Num2_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "2");
    }
}


void MainWindow::on_Num3_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "3");
    }
}


void MainWindow::on_Num4_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "4");
    }
}


void MainWindow::on_Num5_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "5");
    }
}


void MainWindow::on_Num6_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "6");
    }
}


void MainWindow::on_Num7_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "7");
    }
}


void MainWindow::on_Num8_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "8");
    }
}


void MainWindow::on_Num9_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (CHECK_LAST_SIM_TO_NUM) {
        ui->Okno->setText(ui->Okno->text() + "9");
    }
}


void MainWindow::on_Umn_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM || ui->Okno->text().back() == ')') {
        ui->Okno->setText(ui->Okno->text() + "*");
        point_flag = true;
    }
}


void MainWindow::on_Del_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM || ui->Okno->text().back() == ')') {
        ui->Okno->setText(ui->Okno->text() + "/");
        point_flag = true;
    }
}


void MainWindow::on_Sum_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM || ui->Okno->text().back() == '(' || ui->Okno->text().back() == ')') {
        ui->Okno->setText(ui->Okno->text() + "+");
        point_flag = true;
    }
}


void MainWindow::on_Sub_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM || ui->Okno->text().back() == '(' || ui->Okno->text().back() == ')' ||  ui->Okno->text().back() == ' ') {
        ui->Okno->setText(ui->Okno->text() + "-");
        point_flag = true;
    }
}


void MainWindow::on_Exp_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM || ui->Okno->text().back() == ')') {
        ui->Okno->setText(ui->Okno->text() + "^");
        point_flag = true;
    }
}


void MainWindow::on_Mod_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_NUM || ui->Okno->text().back() == ')') {
        ui->Okno->setText(ui->Okno->text() + "mod");
        point_flag = true;
    }
}


void MainWindow::on_Sin_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "sin(");
        count_open_br += 1;
    }
}


void MainWindow::on_Cos_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "cos(");
        count_open_br += 1;
    }
}


void MainWindow::on_Tan_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "tan(");
        count_open_br += 1;
    }
}


void MainWindow::on_Asin_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "asin(");
        count_open_br += 1;
    }
}


void MainWindow::on_Acos_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "acos(");
        count_open_br += 1;
    }
}


void MainWindow::on_Atan_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "atan(");
        count_open_br += 1;
    }
}


void MainWindow::on_Sqrt_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "sqrt(");
        count_open_br += 1;
    }
}


void MainWindow::on_Ln_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "ln(");
        count_open_br += 1;
    }
}


void MainWindow::on_Log_clicked()
{
    if (point_res == true) {
        ui->Okno->setText(" ");
        point_res=false;
    }
    if (LAST_SIM_IS_BIN_OP || ui->Okno->text().back() == ' ' ||
        ui->Okno->text().back() == '(') {
        ui->Okno->setText(ui->Okno->text() + "log(");
        count_open_br += 1;
    }
}

void MainWindow::on_AC_clicked()
{
    ui->Okno->setText(" ");
    ui->widget->clearGraphs();
    x.clear();
    y.clear();
    ui->widget->replot();
    count_open_br = 0;
    count_close_br = 0;
    point_flag = true;
    point_zero = true;
    point_x = false;
    point_res=false;
}

void MainWindow::on_calculation_clicked()
{
    double total_value = ui->total_value->value();
    double percent = ui->proc_stav->value();
    int period = ui->srok->value();
    if (ui->period->currentText() == "Лет") {
        period *= 12;
    }
    double platech_mesiaz;
    double credit_result;
    if (ui->annuity->isChecked()) {
            platech_mesiaz = annuity(percent, total_value, period);
         platech_mesiaz *= (double)period;
         ui->credit_result->setText(QString::number(platech_mesiaz));
    }
}
