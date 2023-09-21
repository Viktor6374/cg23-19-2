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

