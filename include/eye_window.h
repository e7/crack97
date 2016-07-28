#ifndef __CRACK97_EYE_WINDOW_H__
#define __CRACK97_EYE_WINDOW_H__


#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include <QLabel>
#include <QDesktopWidget>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "ui_main_window.h"
#include "singleton.h"


class QEyeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QEyeWindow(void);
    ~QEyeWindow(void)
    {
    }

private:
    QTimer *screen_shot_timer;
    QLabel *label_img;
    Ui::MainWindow ui;

private slots:
    void onOpenImage(void)
    {
        QString file_name(QFileDialog::getOpenFileName(
            this, tr("open image"), "/", tr("image files (*.png *.jpg)")
        ));

        if (0 == file_name.size()) {
            return;
        }

        qDebug(file_name.toAscii().data());

        QImage *image = new QImage(file_name);
        QScopedPointer<QImage> free_image(image);

        this->label_img->setPixmap(QPixmap::fromImage(*image));
        this->label_img->resize(QSize(image->width(), image->height()));
    }

    void onScreenShot(void)
    {
        // 截屏
        QPixmap screen(QPixmap::grabWindow(QApplication::desktop()->winId()));
        this->label_img->setPixmap(screen);
    }

    void onProcess(void)
    {
        // 控制滚动条
        int cur_val = ui.progress_bar->value();

        if (cur_val < ui.progress_bar->maximum()) {
            ui.progress_bar->setValue(cur_val + 1);
        }
    }
};
#endif // __CRACK97_EYE_WINDOW_H__
