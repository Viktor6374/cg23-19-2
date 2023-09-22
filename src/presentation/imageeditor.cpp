#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"
#include <QPixmap>
#include <string>

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
    QImage *image = _image_converter->convert_to_QImage(_image_service->base_image());

    QPixmap pixmap = QPixmap::fromImage(*image);

    _ui->label_pic->setPixmap(pixmap);

    delete image;
}

void ImageEditor::on_pushButton_clicked()
{
    std::string file_path = _ui->lineEdit->text().toStdString();

    _image_service->load_image(file_path);

    update_image_view();
}

void ImageEditor::on_pushButton_2_clicked()
{
    std::string file_path = _ui->lineEdit_2->text().toStdString();
    std::string file_format = _ui->comboBox->currentText().toStdString();

    _image_service->save_image(file_path, file_format);
}

