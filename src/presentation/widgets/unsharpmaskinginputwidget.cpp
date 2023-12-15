#include "unsharpmaskinginputwidget.h"

UnsharpMaskingInputWidget::UnsharpMaskingInputWidget(ImageService *service, ImageEditor *editor)
{
    _service = service;
    _editor = editor;

    auto main_layout = new QHBoxLayout();

    _execute_button = new QPushButton("Execute");
    _cancel_button = new QPushButton("Cancel");

    main_layout->addWidget(_execute_button);
    main_layout->addWidget(_cancel_button);

    setLayout(main_layout);

    connect(_execute_button, SIGNAL(clicked()), this, SLOT(on_execute_button_clicked()));
    connect(_cancel_button, SIGNAL(clicked()), this, SLOT(on_cancel_button_clicked()));
}

UnsharpMaskingInputWidget::~UnsharpMaskingInputWidget()
{
    delete _execute_button;
    delete _cancel_button;
}

void UnsharpMaskingInputWidget::on_execute_button_clicked()
{
    close();
    _editor->update_image_view();
}

void UnsharpMaskingInputWidget::on_cancel_button_clicked()
{
    close();
}
