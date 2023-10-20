#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"
#include <QPixmap>
#include <string>
#include <stdexcept>

ImageEditor::ImageEditor(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::ImageEditor)
{
    _image_converter = new ImageConverter();
    _image_service = new ImageService();

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

    ColorSpace current_color_space = _image_service->current_color_cpace();
    _image_service->change_color_space(RGB);

    QImage *image = _image_converter->convert_to_QImage(_image_service->current_image());

    double scale = (double)_ui->label_pic->height() / image->height();

    QPixmap pixmap = QPixmap::fromImage(*image)
            .scaled(image->width() * scale, image->height() * scale);

    _ui->label_pic->setPixmap(pixmap);

    _image_service->change_color_space(current_color_space);

    delete image;
}

void ImageEditor::on_pushButton_clicked()
{
    std::string file_path = _ui->lineEdit->text().toStdString();

    try
    {
        _image_service->load_image(file_path);

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
}

