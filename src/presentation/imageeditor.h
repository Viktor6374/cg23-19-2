#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "../application/imageservice.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageEditor; }
QT_END_NAMESPACE

class ImageEditor : public QMainWindow
{
    Q_OBJECT

public:
    ImageEditor(QWidget *parent = nullptr);
    ~ImageEditor();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ImageEditor *_ui;

    ImageService *_image_service;
};
#endif // IMAGEEDITOR_H
