#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Filters.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_applyButton_clicked();

private:
    Ui::MainWindow *ui;
    Image image;
    bool loaded = false;
    void showImage();
};
#endif // MAINWINDOW_H
