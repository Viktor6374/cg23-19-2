#ifndef IMAGEEDITOR_H
#define IMAGEEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ImageEditor; }
QT_END_NAMESPACE

class ImageEditor : public QMainWindow
{
    Q_OBJECT

public:
    ImageEditor(QWidget *parent = nullptr);
    ~ImageEditor();

private:
    Ui::ImageEditor *ui;
};
#endif // IMAGEEDITOR_H
