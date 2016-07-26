#include <QTextCodec>
#include <QScopedPointer>
#include <QCleanlooksStyle>

#include <opencv2/core/core.hpp>

#include "eye_window.h"


e7::common::singleton_mng crack97::g_singleton_mng;


int main(int argc, char *argv[])
{
    int rslt;
    QApplication *qapp;
    QEyeWindow *eye_window;
    QStyle *p_style = NULL;

    // qt初始化
    qapp = new QApplication(argc, argv);
    if (-1 == crack97::g_singleton_mng.append("Crack97::QApplication", qapp)) {
            return EXIT_FAILURE;
    }

    if (-1 == crack97::g_singleton_mng.append(
        "Crack97::QEyeWindow", new QEyeWindow)
    ) {
        return EXIT_FAILURE;
    }

    // 初始化
    p_style = new QCleanlooksStyle();
    if (NULL == p_style) {
        return -1;
    }
    QScopedPointer<QStyle> free_p_style(p_style);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    qapp->setStyle(p_style);

    rslt = qapp->exec();

    return rslt;
}
