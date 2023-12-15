#ifndef SOBELFILTERINPUTWIDGET_H
#define SOBELFILTERINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class SobelFilterInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SobelFilterInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~SobelFilterInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // SOBELFILTERINPUTWIDGET_H
