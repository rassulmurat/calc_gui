#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int insopernd(QString ch)
{
    QFile file("/dev/operand");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              return 1;
    QTextStream out(&file);
    out << ch;
    return 0;
}

void MainWindow::on_plus_clicked()
{
    QString str = "+";
    int res = insopernd(str);
}

void MainWindow::on_minus_clicked()
{
    QString str = "-";
    int res = insopernd(str);
}

void MainWindow::on_mul_clicked()
{
    QString ch = "*";
    int res = insopernd(ch);
}

void MainWindow::on_dev_clicked()
{
    QString ch = "/";
    int res = insopernd(ch);
}

int insopert(QString data, int opnum)
{
    QString opertr ("/dev/operator");
    QString nm = QString::number(opnum);
    opertr.append(nm);
    QFile file(opertr);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        perror("Could not open file");
        return 1;
    }
    QTextStream out(&file);
    out << data;
    return 0;
}

int getRes(QString *data)
{
    QFile file("/proc/result");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
              return 1;
    QTextStream in(&file);
    in >> *data;
    return 0;
}

void MainWindow::on_calculate_clicked()
{
    insopert(ui->operator0->text(), 0);
    insopert(ui->operator1->text(), 1);
    QString str;
    getRes(&str);
    int counter = 0;
    for (int var = 0; var < str.size(); ++var) {
        QChar ch = str.at(var);
        if (ch == QLatin1Char('\0')) {
            break;
        }
        ++counter;
    }
    str = str.remove(counter, str.size() - counter);
    ui->Result->setText(str);
}

