#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "../application/imageservice.h"
#include "../presentation/converters/imageconverter.h"
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

    void on_pushButton_2_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    void update_image_view();

    void resizeEvent(QResizeEvent *event);

    Ui::ImageEditor *_ui;

    ImageService *_image_service;
    ImageConverter *_image_converter;
};
#endif // IMAGEEDITOR_H
