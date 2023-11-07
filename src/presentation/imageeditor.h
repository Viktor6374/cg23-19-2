#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include "../application/imageservice.h"
#include "converters/imageconverter.h"
#include "models/linedrawingoptions.h"
#include "models/ditheringoptions.h"
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

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_pushButton_assign_gamma_clicked();

    void on_pushButton_convert_gamma_clicked();

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

private:
    void update_image_view();

    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

    Ui::ImageEditor *_ui;

    ImageService *_image_service;
    ImageConverter *_image_converter;

    unsigned char _channel_masks[3];

    LineDrawingOptions _line_drawing_options;
    DitheringOptions _dithering_options;
};
#endif // IMAGEEDITOR_H
