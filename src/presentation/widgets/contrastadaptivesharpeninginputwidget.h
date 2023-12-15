#ifndef CONTRASTADAPTIVESHARPENINGINPUTWIDGET_H
#define CONTRASTADAPTIVESHARPENINGINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class ContrastAdaptiveSharpeningInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastAdaptiveSharpeningInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~ContrastAdaptiveSharpeningInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QLineEdit *_line_edit_new_sharpness;
    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // CONTRASTADAPTIVESHARPENINGINPUTWIDGET_H
