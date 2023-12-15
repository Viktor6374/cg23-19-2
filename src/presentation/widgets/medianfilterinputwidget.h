#ifndef MEDIANFILTERINPUTWIDGET_H
#define MEDIANFILTERINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class MedianFilterInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MedianFilterInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~MedianFilterInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QLineEdit *_line_edit_new_r;
    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // MEDIANFILTERINPUTWIDGET_H
