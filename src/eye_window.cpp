#include "eye_window.h"


QEyeWindow::QEyeWindow(void)
{
    QApplication *qapp = reinterpret_cast<QApplication *>(
        crack97::g_singleton_mng.get_instance("Crack97::QApplication")
    );

    if (NULL == qapp) {
        ::abort();
    }

    m_ui.setupUi(this);

    QObject::connect(
        m_ui.open_image, SIGNAL(clicked(void)), this, SLOT(onOpenImage(void))
    );
    QObject::connect(
        m_ui.process, SIGNAL(clicked(void)), this, SLOT(onProcess(void))
    );

    show();
}
