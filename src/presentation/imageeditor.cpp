#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"

ImageEditor::ImageEditor(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::ImageEditor)
    , _image_service(new ImageService())
{
    _ui->setupUi(this);
}

ImageEditor::~ImageEditor()
{
    delete _image_service;
    delete _ui;
}

