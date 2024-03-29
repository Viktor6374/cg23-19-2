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

    void update_image_view();

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

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_comboBox_5_currentTextChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionNearest_neighbour_triggered();

    void on_actionBilinear_triggered();

    void on_actionLanczos3_triggered();

    void on_actionBC_spline_triggered();

    void on_actionInfo_triggered();

    void on_actionThreshold_triggered();

    void on_actionOtsu_threshold_triggered();

    void on_actionMedian_filter_triggered();

    void on_actionGauss_filter_triggered();

    void on_actionbox_blur_triggered();

    void on_actionUnsharp_masking_triggered();

    void on_actionContrast_adaptive_sharpening_triggered();

    void on_actionSobel_filter_triggered();

    void on_actionCanny_edge_detector_triggered();

private:
    void update_hists(Image *image);
    void update_hist1(const std::vector<int> &channel_values);
    void update_hist2(const std::vector<int> &channel_values);
    void update_hist3(const std::vector<int> &channel_values);

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
