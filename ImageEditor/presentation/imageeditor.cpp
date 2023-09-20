#include "imageeditor.h"
#include "presentation/ui_imageeditor.h"

ImageEditor::ImageEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageEditor)
{
    ui->setupUi(this);
}

ImageEditor::~ImageEditor()
{
    delete ui;
}

