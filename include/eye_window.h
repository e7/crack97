#ifndef __CRACK97_EYE_WINDOW_H__
#define __CRACK97_EYE_WINDOW_H__


#include <QDebug>
#include <QFileDialog>
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
    cv::Mat img;
    int x;
    Ui::MainWindow m_ui;

private slots:
    void onOpenImage(void)
    {
        QString file_name(QFileDialog::getOpenFileName(
            this, tr("open image"), ".", tr("image files (*.png *.jpg)")
        ));

        qDebug(file_name.toAscii().data());
        this->img = cv::imread(file_name.toAscii().data());
        imshow("input", this->img);
    }

    void onProcess(void)
    {
        qDebug("afasdf");
    }
};
#endif // __CRACK97_EYE_WINDOW_H__
