#include "eye_window.h"


QEyeWindow::QEyeWindow(void)
    : timer_resolution(20)
{
    QApplication *qapp = reinterpret_cast<QApplication *>(
        crack97::g_singleton_mng.get_instance("Crack97::QApplication")
    );

    if (NULL == qapp) {
        ::abort();
    }

    ui.setupUi(this);

    QObject::connect(
        ui.exit, SIGNAL(clicked(void)), qapp, SLOT(quit(void))
    );
    QObject::connect(
        ui.open_image, SIGNAL(clicked(void)), this, SLOT(onOpenImage(void))
    );
    QObject::connect(
        ui.process, SIGNAL(clicked(void)), this, SLOT(onProcess(void))
    );
    QObject::connect(
        ui.toggle_timer, SIGNAL(clicked(void)), this, SLOT(onToggleTimer(void))
    );

    this->label_img = new QLabel;
    ui.scrollArea->setWidget(this->label_img);

    this->screen_shot_timer = new QTimer(this);
    QObject::connect(
        this->screen_shot_timer,
        SIGNAL(timeout(void)), this, SLOT(onScreenShot(void))
    );

    show();
}

void QEyeWindow::onOpenImage(void)
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

	return;
}


void QEyeWindow::onScreenShot(void)
{
    // 截屏
    QPixmap screen(QPixmap::grabWindow(QApplication::desktop()->winId()));
    this->label_img->setPixmap(screen);

	return;
}


void QEyeWindow::onToggleTimer(void)
{
    if (this->screen_shot_timer->isActive()) {
        this->screen_shot_timer->stop();
    } else {
        this->screen_shot_timer->start(this->timer_resolution);
    }
}


void QEyeWindow::onProcess(void)
{
    // 控制滚动条
    // int cur_val = ui.progress_bar->value();

    // if (cur_val < ui.progress_bar->maximum()) {
    //     ui.progress_bar->setValue(cur_val + 1);
    // }

    QImage curt_img(this->label_img->pixmap()->toImage());
    cv::Mat curt_mat(QImage2Mat(curt_img));
    cv::Mat mat_noise;

    medianBlur(curt_mat, mat_noise, 3);

    QImage img_noise(Mat2QImage(mat_noise));
    this->label_img->setPixmap(QPixmap::fromImage(img_noise));
    this->label_img->resize(QSize(img_noise.width(), img_noise.height()));
}
