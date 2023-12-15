#ifndef CANNYEDGEDETECTORINPUTFILTER_H
#define CANNYEDGEDETECTORINPUTFILTER_H

#include "../../application/imageservice.h"
#include "../imageeditor.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

class CannyEdgeDetectorInputFilter : public QWidget
{
    Q_OBJECT
public:
    explicit CannyEdgeDetectorInputFilter(ImageService *service, ImageEditor *editor = nullptr);
    ~CannyEdgeDetectorInputFilter();

private slots:
    void on_execute_button_clicked();
    void on_cancel_button_clicked();

private:
    ImageService *_service;
    ImageEditor *_editor;

    QPushButton *_execute_button;
    QPushButton *_cancel_button;
};

#endif // CANNYEDGEDETECTORINPUTFILTER_H
