#ifndef OTSUTHRESHOLDFILTERINPUTWIDGET_H
#define OTSUTHRESHOLDFILTERINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class OtsuThresholdFilterInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OtsuThresholdFilterInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~OtsuThresholdFilterInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // OTSUTHRESHOLDFILTERINPUTWIDGET_H
