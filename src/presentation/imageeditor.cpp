#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"
#include <string>

ImageEditor::ImageEditor(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::ImageEditor)
{
    _image_service = new ImageService();

    _ui->setupUi(this);
}

ImageEditor::~ImageEditor()
{
    delete _image_service;
    delete _ui;
}


void ImageEditor::on_pushButton_clicked()
{
    std::string file_path = _ui->lineEdit->text().toStdString();

    _image_service->load_image(file_path);
}


void ImageEditor::on_pushButton_2_clicked()
{
    std::string file_path = _ui->lineEdit_2->text().toStdString();
    std::string file_format = _ui->comboBox->currentText().toStdString();

    _image_service->save_image(file_path, file_format);
}

