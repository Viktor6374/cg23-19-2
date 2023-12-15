#ifndef BOXBLURINPUTWIDGET_H
#define BOXBLURINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class BoxBlurInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoxBlurInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~BoxBlurInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QLineEdit *_line_edit_r;
    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // BOXBLURINPUTWIDGET_H
