#ifndef GAUSSFILTERINPUTWIDGET_H
#define GAUSSFILTERINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class GaussFilterInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GaussFilterInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~GaussFilterInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QLineEdit *_line_edit_arg;
    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // GAUSSFILTERINPUTWIDGET_H
