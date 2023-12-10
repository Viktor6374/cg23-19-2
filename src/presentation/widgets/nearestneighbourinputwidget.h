#ifndef NEARESTNEIGHBOURINPUTWIDGET_H
#define NEARESTNEIGHBOURINPUTWIDGET_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class NearestNeighbourInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NearestNeighbourInputWidget(ImageService *service, ImageEditor *editor = nullptr);
    ~NearestNeighbourInputWidget();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QLineEdit *_line_edit_new_width;
    QLineEdit *_line_edit_new_height;
    QLineEdit *_line_edit_dx;
    QLineEdit *_line_edit_dy;
    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // NEARESTNEIGHBOURINPUTWIDGET_H
