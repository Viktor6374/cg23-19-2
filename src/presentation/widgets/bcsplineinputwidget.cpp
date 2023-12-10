#include "bcsplineinputwidget.h"
#include "../../domain/scaling/bcsplinealgorithm.h"

BCSplineInputWidget::BCSplineInputWidget(ImageService *service, ImageEditor *editor)
{
    _service = service;
    _editor = editor;

    auto main_layout = new QVBoxLayout();
    auto layout1 = new QHBoxLayout();
    auto layout2 = new QHBoxLayout();
    auto layout3 = new QHBoxLayout();
    auto layout = new QHBoxLayout();
    auto layout4 = new QHBoxLayout();

    main_layout->addLayout(layout1);
    main_layout->addLayout(layout2);
    main_layout->addLayout(layout3);
    main_layout->addLayout(layout);
    main_layout->addLayout(layout4);

    _line_edit_new_width = new QLineEdit(QString::number(service->current_image()->width()));
    _line_edit_new_height = new QLineEdit(QString::number(service->current_image()->height()));
    _line_edit_dx = new QLineEdit("0");
    _line_edit_dy = new QLineEdit("0");
    _line_edit_b = new QLineEdit("0");
    _line_edit_c = new QLineEdit("0.5");
    _execute_button = new QPushButton("Execute");
    _cancel_button = new QPushButton("Cancel");

    layout1->addWidget(new QLabel("New width: "));
    layout1->addWidget(_line_edit_new_width);
    layout2->addWidget(new QLabel("New height"));
    layout2->addWidget(_line_edit_new_height);
    layout3->addWidget(new QLabel("Shift (dx, dy):"));
    layout3->addWidget(_line_edit_dx);
    layout3->addWidget(_line_edit_dy);
    layout->addWidget(new QLabel("B, C: "));
    layout->addWidget(_line_edit_b);
    layout->addWidget(_line_edit_c);
    layout4->addWidget(_execute_button);
    layout4->addWidget(_cancel_button);

    setLayout(main_layout);

    connect(_execute_button, SIGNAL(clicked()), this, SLOT(on_execute_button_clicked()));
    connect(_cancel_button, SIGNAL(clicked()), this, SLOT(on_cancel_button_clicked()));
}

BCSplineInputWidget::~BCSplineInputWidget()
{
    delete _line_edit_new_width;
    delete  _line_edit_new_height;
    delete  _line_edit_dx;
    delete _line_edit_dy;
    delete _execute_button;
    delete _cancel_button;
}

void BCSplineInputWidget::on_execute_button_clicked()
{
    float b = _line_edit_b->text().toFloat();
    float c = _line_edit_c->text().toFloat();

    auto algorithm = new BCSplineAlgorithm(b, c);

    int new_wigth = _line_edit_new_width->text().toInt();
    int new_height = _line_edit_new_height->text().toInt();
    float dx = _line_edit_dx->text().toFloat();
    float dy = _line_edit_dy->text().toFloat();

    _service->scale(new_wigth, new_height, Point(dx, dy, 0), algorithm);

    delete algorithm;

    close();
    _editor->update_image_view();
}

void BCSplineInputWidget::on_cancel_button_clicked()
{
    close();
}
