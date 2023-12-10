#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"
#include "../domain/algorithms/converttogammaalgorithm.h"
#include "../domain/algorithms/createhistogramalgorithm.h"
#include "../domain/algorithms/drawhistogramalgorithm.h"
#include "../domain/scaling/closestneighbouralgorithm.h"
#include "widgets/nearestneighbourinputwidget.h"
#include "widgets/bilinearinputwidget.h"
#include "widgets/lanczos3inputwidget.h"
#include "widgets/bcsplineinputwidget.h"
#include <QPixmap>
#include <QMessageBox>
#include <string>
#include <stdexcept>
#include <unistd.h>

ImageEditor::ImageEditor(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::ImageEditor)
{
    _image_converter = new ImageConverter();
    _image_service = new ImageService();

    _channel_masks[0] = 1;
    _channel_masks[1] = 1;
    _channel_masks[2] = 1;

    _line_drawing_options = LineDrawingOptions();
    _dithering_options = DitheringOptions();

    _ui->setupUi(this);
}

ImageEditor::~ImageEditor()
{
    delete _image_converter;
    delete _image_service;
    delete _ui;
}

void ImageEditor::update_image_view()
{
    if (_image_service->current_image() == nullptr)
        return;

    std::vector<Pixel> pixels;

    for (auto pixel : _image_service->current_image()->pixels())
    {
         for (int i = 0; i < 3; ++i)
             if (_channel_masks[i] == 0)
                 pixel.channels[i] = 0;

         pixels.push_back(pixel);
    }

    Image image = Image(
                _image_service->current_image()->width(),
                _image_service->current_image()->height(),
                pixels);

    update_hists(&image);

    auto converter = ColorSpaceConverter();
    converter.convert(&image, _image_service->current_color_cpace(), RGB);

    auto algorithm = ConvertToGammaAlgorithm();
    algorithm.execute(&image, _image_service->current_gamma(), 2.2);

    QImage *qImage = _image_converter->convert_to_QImage(&image, _dithering_options.type, _dithering_options.bytes_count);

    QPixmap pixmap = QPixmap::fromImage(*qImage);

//    double scale = (double)_ui->label_pic->height() / qImage->height();
//    pixmap = pixmap.scaled(qImage->width() * scale, qImage->height() * scale);

    _ui->label_pic->setPixmap(pixmap);

    delete qImage;
}

void ImageEditor::update_hists(Image *image)
{
    auto algorithm = CreateHistogramAlgorithm();
    Histogram *hist = algorithm.execute(image, _dithering_options.type, _dithering_options.bytes_count);

    update_hist1(hist->get_channel_values()[0]);
    update_hist2(hist->get_channel_values()[1]);
    update_hist3(hist->get_channel_values()[2]);

    delete hist;
}

void ImageEditor::update_hist1(const std::vector<int> &channel_values)
{
    auto algorithm = DrawHistogramAlgorithm();
    Image *hist = algorithm.execute(channel_values);

    QImage *qImage = _image_converter->convert_to_QImage(hist, "Disabled", 8);

    QPixmap pixmap = QPixmap::fromImage(*qImage);

//    double scale = (double)_ui->label_hist1->height() / qImage->height();
//    pixmap = pixmap.scaled(qImage->width() * scale, qImage->height() * scale);

    _ui->label_hist1->setPixmap(pixmap);

    delete hist;
}

void ImageEditor::update_hist2(const std::vector<int> &channel_values)
{
    auto algorithm = DrawHistogramAlgorithm();
    Image *hist = algorithm.execute(channel_values);

    QImage *qImage = _image_converter->convert_to_QImage(hist, "Disabled", 8);

    QPixmap pixmap = QPixmap::fromImage(*qImage);

//    double scale = (double)_ui->label_hist1->height() / qImage->height();
//    pixmap = pixmap.scaled(qImage->width() * scale, qImage->height() * scale);

    _ui->label_hist2->setPixmap(pixmap);

    delete hist;
}

void ImageEditor::update_hist3(const std::vector<int> &channel_values)
{
    auto algorithm = DrawHistogramAlgorithm();
    Image *hist = algorithm.execute(channel_values);

    QImage *qImage = _image_converter->convert_to_QImage(hist, "Disabled", 8);

    QPixmap pixmap = QPixmap::fromImage(*qImage);

//    double scale = (double)_ui->label_hist1->height() / qImage->height();
//    pixmap = pixmap.scaled(qImage->width() * scale, qImage->height() * scale);

    _ui->label_hist3->setPixmap(pixmap);

    delete hist;
}

void ImageEditor::on_pushButton_clicked()
{
    std::string file_path = _ui->lineEdit->text().toStdString();

    try
    {
        _image_service->load_image(file_path);

        _ui->lineEdit_gamma->setText("2.2");

        update_image_view();
    }
    catch (std::logic_error ex)
    {
        _ui->label_pic->setText(ex.what());
    }
}

void ImageEditor::on_pushButton_2_clicked()
{
    std::string file_path = _ui->lineEdit_2->text().toStdString();
    std::string file_format = _ui->comboBox->currentText().toStdString();

    try
    {
        _image_service->save_image(file_path, file_format, _dithering_options.type, _dithering_options.bytes_count);
    }
    catch (std::logic_error ex)
    {
        _ui->label_pic->setText(ex.what());
    }
}

void ImageEditor::resizeEvent(QResizeEvent *event)
{
    update_image_view();
}

ColorSpace get_color_space(const QString &arg1)
{
    if (arg1 == "RGB")
    {
        return RGB;
    }
    else if (arg1 == "HSL")
    {
        return HSL;
    }
    else if (arg1 == "HSV")
    {
        return HSV;
    }
    else if (arg1 == "YCbCr.601")
    {
        return YCbCr601;
    }
    else if (arg1 == "YCbCr.709")
    {
        return YCbCr709;
    }
    else if (arg1 == "YCoCg")
    {
        return YCoCg;
    }
    else if (arg1 == "CMY")
    {
        return CMY;
    }

    throw std::logic_error("unsupported color space");
}

void ImageEditor::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    try
    {
        _image_service->change_color_space(get_color_space(arg1));
    }
    catch (std::logic_error ex)
    {
        _ui->label_pic->setText(ex.what());
    }

    update_image_view();
}


void ImageEditor::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    if (arg1 == "All")
    {
        _channel_masks[0] = 1;
        _channel_masks[1] = 1;
        _channel_masks[2] = 1;
    }
    else if (arg1 == "First")
    {
        _channel_masks[0] = 1;
        _channel_masks[1] = 0;
        _channel_masks[2] = 0;
    }
    else if (arg1 == "Second")
    {
        _channel_masks[0] = 0;
        _channel_masks[1] = 1;
        _channel_masks[2] = 0;
    }
    else if (arg1 == "Third")
    {
        _channel_masks[0] = 0;
        _channel_masks[1] = 0;
        _channel_masks[2] = 1;
    }

    update_image_view();
}


void ImageEditor::on_pushButton_assign_gamma_clicked()
{
    float new_gamma = _ui->lineEdit_gamma->text().toDouble();

    _image_service->assing_gamma(new_gamma);

    update_image_view();
}


void ImageEditor::on_pushButton_convert_gamma_clicked()
{
    float new_gamma = _ui->lineEdit_gamma->text().toDouble();

    _image_service->convert_to_gamma(new_gamma);

    update_image_view();
}


void ImageEditor::on_lineEdit_7_textChanged(const QString &arg1)
{
    float c = arg1.toDouble() / 255;

    _line_drawing_options.color.channels[0] = c;
}


void ImageEditor::on_lineEdit_6_textChanged(const QString &arg1)
{
    float c = arg1.toDouble() / 255;

    _line_drawing_options.color.channels[1] = c;
}


void ImageEditor::on_lineEdit_3_textChanged(const QString &arg1)
{
    float c = arg1.toDouble() / 255;

    _line_drawing_options.color.channels[2] = c;
}


void ImageEditor::on_lineEdit_4_textChanged(const QString &arg1)
{
    float t = arg1.toDouble();

    _line_drawing_options.trans = t;
}


void ImageEditor::on_lineEdit_5_textChanged(const QString &arg1)
{
    float w = arg1.toDouble();

    _line_drawing_options.width = w / 2;
}

void ImageEditor::mousePressEvent(QMouseEvent *event)
{
    if (_image_service->current_image() == nullptr)
        return;

    QPoint cursorPos = QCursor::pos();
    QPoint windowPos = QMainWindow::pos();
    QPoint labelPos = _ui->label_pic->pos();

    Point *point = new Point(
                1.0 * (cursorPos.x() - windowPos.x() - labelPos.x()) / _ui->label_pic->width() * _image_service->current_image()->width(),
                1.0 * (cursorPos.y() - windowPos.y() - labelPos.y() - 45) / _ui->label_pic->height() * _image_service->current_image()->height(),
                1.0);

    if (point->x < 0 || point->x >= _image_service->current_image()->width()
            || point->y < 0 || point->x >= _image_service->current_image()->height())
    {
        delete point;
        return;
    }

    if (_line_drawing_options.point1 == nullptr)
    {
        _line_drawing_options.point1 = point;
    }
    else
    {
        _image_service->draw_line(
                    *_line_drawing_options.point1,
                    *point,
                    _line_drawing_options.color,
                    _line_drawing_options.width,
                    _line_drawing_options.trans);

        update_image_view();

        delete _line_drawing_options.point1;
        delete point;

        _line_drawing_options.point1 = nullptr;
    }
}

void ImageEditor::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    _dithering_options.type = arg1.toStdString();

    update_image_view();
}


void ImageEditor::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    _dithering_options.bytes_count = arg1.toInt();

    update_image_view();
}


void ImageEditor::on_pushButton_3_clicked()
{
     _image_service->generate_gradient(_ui->label_pic->width(), _ui->label_pic->height());

    _ui->comboBox_2->setCurrentIndex(0);
    _ui->lineEdit_gamma->setText("2.2");

    update_image_view();
}


void ImageEditor::on_pushButton_4_clicked()
{
    float skip = _ui->lineEdit_8->text().toDouble();

    if (_image_service->current_image() == nullptr || skip < 0 || skip >= 0.5)
        return;

    _image_service->autocorrect_brightness(skip);

    update_image_view();
}

void ImageEditor::on_actionInfo_triggered()
{
    QMessageBox message_box;

    QString info;

    if (_image_service->current_image() == nullptr)
    {
        info.append("No image");
    }
    else
    {
        info.append("Image width: " + QString::number(_image_service->current_image()->width()) + "\n");
        info.append("Image height: " + QString::number(_image_service->current_image()->height()));
    }

    message_box.setText(info);

    message_box.exec();
}

void ImageEditor::on_actionNearest_neighbour_triggered()
{
    if (_image_service->current_image() == nullptr)
        return;

    auto w = new NearestNeighbourInputWidget(_image_service, this);

    w->show();

    update_image_view();
}

void ImageEditor::on_actionBilinear_triggered()
{
    if (_image_service->current_image() == nullptr)
        return;

    auto w = new BilinearInputWidget(_image_service, this);

    w->show();

    update_image_view();
}


void ImageEditor::on_actionLanczos3_triggered()
{
    if (_image_service->current_image() == nullptr)
        return;

    auto w = new Lanczos3InputWidget(_image_service, this);

    w->show();

    update_image_view();
}


void ImageEditor::on_actionBC_spline_triggered()
{
    if (_image_service->current_image() == nullptr)
        return;

    auto w = new BCSplineInputWidget(_image_service, this);

    w->show();

    update_image_view();
}
