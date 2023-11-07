#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"
#include "../domain/algorithms/converttogammaalgorithm.h"
#include <QPixmap>
#include <string>
#include <stdexcept>

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

    auto converter = ColorSpaceConverter();
    converter.convert(&image, _image_service->current_color_cpace(), RGB);

    auto algorithm = ConvertToGammaAlgorithm();
    algorithm.execute(&image, _image_service->current_gamma(), 2.2);

    QImage *qImage = _image_converter->convert_to_QImage(&image);

    double scale = (double)_ui->label_pic->height() / qImage->height();

    QPixmap pixmap = QPixmap::fromImage(*qImage)
            .scaled(qImage->width() * scale, qImage->height() * scale);

    _ui->label_pic->setPixmap(pixmap);

    delete qImage;
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
        _image_service->save_image(file_path, file_format);
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

    _line_drawing_options.width = w;
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
