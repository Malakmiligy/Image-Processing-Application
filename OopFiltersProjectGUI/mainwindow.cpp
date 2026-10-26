#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Fill the dropdown here so the order always matches the switch below
    ui->filterCombo->clear();
    ui->filterCombo->addItems({
        "GrayScale",              // 0
        "Black and White",        // 1
        "Invert",                 // 2
        "Frame",                  // 3
        "Flip",                   // 4
        "Rotate",                 // 5
        "Darken and Lighten",     // 6
        "Resize",                 // 7
        "Merge",                  // 8
        "Image Edge",             // 9
        "Crop",                   // 10
        "Blur",                   // 11
        "Brightness Correction",  // 12
        "TV Filter",              // 13
        "Purple",                 // 14
        "Infrared",               // 15
        "Skewing",                // 16
        "Oil Painting"            // 17
    });

    // Lets the label shrink/grow with the window instead of growing with the image
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (loaded) showImage();
}

void MainWindow::on_loadButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Image", "",
                                                "Images (*.png *.jpg *.jpeg *.bmp)");
    if (path.isEmpty()) return;
    image.loadNewImage(path.toStdString());
    loaded = true;
    showImage();
}

void MainWindow::on_saveButton_clicked()
{
    if (!loaded) return;
    QString path = QFileDialog::getSaveFileName(this, "Save Image", "",
                                                "Images (*.png *.jpg *.bmp)");
    if (path.isEmpty()) return;
    image.saveImage(path.toStdString());
}

void MainWindow::on_applyButton_clicked()
{
    if (!loaded) {
        QMessageBox::information(this, "No image", "Load an image first.");
        return;
    }

    bool ok = false;

    switch (ui->filterCombo->currentIndex()) {
    case 0: GrayScaleConversion(image); break;
    case 1: BlackAndWhiteFilter(image); break;
    case 2: Invert(image); break;

    case 3: { // Frame
        QStringList types = {"Simple frame", "Decorated frame"};
        QString t = QInputDialog::getItem(this, "Frame", "Frame type:", types, 0, false, &ok);
        if (!ok) return;
        QColor c = QColorDialog::getColor(Qt::red, this, "Frame color");
        if (!c.isValid()) return;
        mframe(image, types.indexOf(t) + 1, c.red(), c.green(), c.blue());
        break;
    }

    case 4: { // Flip
        QStringList opts = {"Vertically", "Horizontally"};
        QString s = QInputDialog::getItem(this, "Flip", "Flip:", opts, 0, false, &ok);
        if (!ok) return;
        Flip(image, opts.indexOf(s) + 1);   // 1 = vertical, 2 = horizontal
        break;
    }

    case 5: { // Rotate
        QStringList opts = {"90", "180", "270"};
        QString s = QInputDialog::getItem(this, "Rotate", "Angle:", opts, 0, false, &ok);
        if (!ok) return;
        RotateImage(image, s.toInt());
        break;
    }

    case 6: { // Darken and Lighten
        int p = QInputDialog::getInt(this, "Darken/Lighten",
                                     "Percentage (0-49 darkens, 50 = no change, 51-100 lightens):",
                                     50, 0, 100, 1, &ok);
        if (!ok) return;
        DarkenandLighten(image, p);
        break;
    }

    case 7: { // Resize
        QStringList opts = {"Dimensions (width & height)", "Ratio"};
        QString s = QInputDialog::getItem(this, "Resize", "Resize by:", opts, 0, false, &ok);
        if (!ok) return;
        int w, h;
        if (opts.indexOf(s) == 0) {
            w = QInputDialog::getInt(this, "Resize", "Width:", image.width, 1, 10000, 1, &ok);
            if (!ok) return;
            h = QInputDialog::getInt(this, "Resize", "Height:", image.height, 1, 10000, 1, &ok);
            if (!ok) return;
        } else {
            double r = QInputDialog::getDouble(this, "Resize", "Ratio (e.g. 0.5):",
                                               1.0, 0.01, 10.0, 2, &ok);
            if (!ok) return;
            w = qMax(1, int(image.width * r));
            h = qMax(1, int(image.height * r));
        }
        ::resize(image, w, h);   // "::" = your filter, not QWidget::resize
        break;
    }

    case 8: { // Merge
        QString path = QFileDialog::getOpenFileName(this, "Image to merge", "",
                                                    "Images (*.png *.jpg *.jpeg *.bmp)");
        if (path.isEmpty()) return;
        Image image2;
        image2.loadNewImage(path.toStdString());
        int choice = 1;
        if (image.width != image2.width || image.height != image2.height) {
            QStringList opts = {"Resize then merge", "Merge common area"};
            QString s = QInputDialog::getItem(this, "Merge", "The sizes differ:", opts, 0, false, &ok);
            if (!ok) return;
            choice = opts.indexOf(s) + 1;
        }
        Merge(image, image2, choice);
        break;
    }

    case 9: ImageEdge(image); break;

    case 10: { // Crop
        QString msg = QString("Image is %1 x %2").arg(image.width).arg(image.height);
        int x = QInputDialog::getInt(this, "Crop", msg + "\nStart x:", 0, 0, image.width - 1, 1, &ok);
        if (!ok) return;
        int y = QInputDialog::getInt(this, "Crop", "Start y:", 0, 0, image.height - 1, 1, &ok);
        if (!ok) return;
        int W = QInputDialog::getInt(this, "Crop", "Width:", image.width - x, 1, image.width - x, 1, &ok);
        if (!ok) return;
        int H = QInputDialog::getInt(this, "Crop", "Height:", image.height - y, 1, image.height - y, 1, &ok);
        if (!ok) return;
        if (!CropImage(image, x, y, W, H)) {
            QMessageBox::warning(this, "Crop", "Invalid values.");
            return;
        }
        break;
    }

    case 11: { // Blur
        int r = QInputDialog::getInt(this, "Blur", "Blur level (1, 2, 3...):", 2, 1, 20, 1, &ok);
        if (!ok) return;
        blur(image, r);
        break;
    }

    case 12: WanoSunlightCorrection(image); break;
    case 13: TvFilter(image); break;
    case 14: PurpleFilter(image); break;
    case 15: infrared(image); break;

    case 16: { // Skewing
        double d = QInputDialog::getDouble(this, "Skew", "Degrees (-60 to 60):",
                                           20, -60, 60, 1, &ok);
        if (!ok) return;
        skewing(image, d);
        break;
    }

    case 17: oilpainting(image); break;
    }

    showImage();
}

void MainWindow::showImage()
{
    if (!loaded) return;

    QImage::Format fmt;
    if (image.channels == 4)      fmt = QImage::Format_RGBA8888;
    else if (image.channels == 1) fmt = QImage::Format_Grayscale8;
    else                          fmt = QImage::Format_RGB888;

    QImage qimg(image.imageData, image.width, image.height,
                image.width * image.channels, fmt);

    ui->imageLabel->setPixmap(
        QPixmap::fromImage(qimg).scaled(ui->imageLabel->size(),
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation));
}
