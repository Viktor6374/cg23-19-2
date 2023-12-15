#ifndef THRESHOLDFILTERINPUTWIDGET_H
#define THRESHOLDFILTERINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class ThresholdFilterInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThresholdFilterInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~ThresholdFilterInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QLineEdit *_line_edit_new_border1;
    QLineEdit *_line_edit_new_border2;
    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // THRESHOLDFILTERINPUTWIDGET_H
