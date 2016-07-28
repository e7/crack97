#include "eye_window.h"


QEyeWindow::QEyeWindow(void)
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

    this->label_img = new QLabel;
    ui.scrollArea->setWidget(this->label_img);

    this->screen_shot_timer = new QTimer(this);
    QObject::connect(
        this->screen_shot_timer,
        SIGNAL(timeout(void)), this, SLOT(onScreenShot(void))
    );
    this->screen_shot_timer->start(20);

    show();
}
