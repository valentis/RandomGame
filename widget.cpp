#include <QDebug>
#include <QThread>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->listWidgetDone->setCurrentItem(0);
    if(ui->listWidgetDone->currentItem() != nullptr)
        ui->listWidgetDone->currentItem()->setSelected(true);
    ui->listWidgetUndone->setCurrentItem(0);
    if(ui->listWidgetUndone->currentItem() != nullptr)
        ui->listWidgetUndone->currentItem()->setSelected(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    unsigned int cnt = ui->listWidgetDone->count();
    qint64 doneNumber[4] = {-1, -1, -1, -1};
    for(int i = 0; i < 4; i++) {
        qint64 value = qrand() % cnt;
        qDebug() << value;
        for(int j = 0; j < i; j++) {
            if(doneNumber[j] == value) {
                i--;
                continue;
            }
        }
        if(doneNumber[i] == -1) {
            doneNumber[i] = value;
        }
        switch (i) {
        case 0:
            ui->lineEdit1->setText(ui->listWidgetDone->item(doneNumber[i])->text());
            break;
        case 1:
            ui->lineEdit2->setText(ui->listWidgetDone->item(doneNumber[i])->text());
            break;
        case 2:
            ui->lineEdit3_1->setText(ui->listWidgetDone->item(doneNumber[i])->text());
            break;
        case 3:
            ui->lineEdit3_2->setText(ui->listWidgetDone->item(doneNumber[i])->text());
            break;
        }
    }

    qint64 nextValue = qrand() % ui->listWidgetUndone->count();
    ui->lineEditNext->setText(ui->listWidgetUndone->item(nextValue)->text());
}

void Widget::on_pushButtonLeftAdd_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name : "), QLineEdit::Normal,
                                         nullptr, &ok);
    if (ok && !text.isEmpty())
        ui->listWidgetUndone->addItem(text);
}

void Widget::on_pushButtonRightAdd_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("User name : "), QLineEdit::Normal,
                                         nullptr, &ok);
    if (ok && !text.isEmpty())
        ui->listWidgetDone->addItem(text);
}

void Widget::on_toolButtonLeft_clicked()
{
    if(ui->listWidgetDone->currentItem() != nullptr) {
        if(ui->listWidgetUndone->currentItem() != nullptr) {
            ui->listWidgetUndone->insertItem(ui->listWidgetUndone->currentIndex().row()+1,
                                             ui->listWidgetDone->currentItem()->text());
        } else {
            ui->listWidgetUndone->addItem(ui->listWidgetDone->currentItem()->text());
        }
        delete ui->listWidgetDone->currentItem();
    } else {
        QMessageBox::warning(this, tr("에러"), tr("이동할 아이템을 선택해주세요"), QMessageBox::Ok);
    }
}

void Widget::on_toolButtonRight_clicked()
{
    if(ui->listWidgetUndone->currentItem() != nullptr) {
        if(ui->listWidgetDone->currentItem() != nullptr) {
            ui->listWidgetDone->insertItem(ui->listWidgetDone->currentIndex().row()+1,
                                           ui->listWidgetUndone->currentItem()->text());
        } else {
            ui->listWidgetDone->addItem(ui->listWidgetUndone->currentItem()->text());
        }
        delete ui->listWidgetUndone->currentItem();
    } else {
        QMessageBox::warning(this, tr("에러"), tr("이동할 아이템을 선택해주세요"), QMessageBox::Ok);
    }
}


void Widget::on_pushButtonLeftLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Data"), ".", tr("Data Files (*.data *.txt *.db)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray data = file.readAll();
    file.close();

    QString str(data);

    ui->listWidgetUndone->clear();
    QStringList strList = str.split(QRegExp("\\s+"));
    for(int i = 0; i < strList.count(); i++) {
        if(strList.at(i).length())
            ui->listWidgetUndone->addItem(strList.at(i));
    }
}

void Widget::on_pushButtonRightLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Data"), ".", tr("Data Files (*.data *.txt *.db)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QByteArray data = file.readAll();
    file.close();

    QString str(data);

    ui->listWidgetDone->clear();
    QStringList strList = str.split(QRegExp("\\s+"));
    for(int i = 0; i < strList.count(); i++) {
        if(strList.at(i).length())
            ui->listWidgetDone->addItem(strList.at(i));
    }
}
