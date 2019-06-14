#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonLeftAdd_clicked();

    void on_pushButtonRightAdd_clicked();

    void on_toolButtonLeft_clicked();

    void on_toolButtonRight_clicked();


    void on_pushButtonLeftLoad_clicked();

    void on_pushButtonRightLoad_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
