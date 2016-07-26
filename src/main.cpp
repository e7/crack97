#include <QTextCodec>
#include <QCleanlooksStyle>
#include "ui_main_window.h"


#define EXTENDS     public
#define PUBLIC      public:
#define PROTECTED   protected:
#define PRIVATE     private:


// ***** QEyeWindow {{
class QEyeWindow : EXTENDS QMainWindow
{
    PUBLIC explicit QEyeWindow(void);
    PUBLIC ~QEyeWindow(void);

    PRIVATE Ui::MainWindow m_ui;
};

QEyeWindow::QEyeWindow(void)
{
    m_ui.setupUi(this);
    show();
}

QEyeWindow::~QEyeWindow(void)
{
}
// }} QEyeWindow *****


int main(int argc, char *argv[])
{
    QStyle *p_style = NULL;
    QApplication app(argc, argv);
    QEyeWindow eye_window;

    // qt初始化
    p_style = new QCleanlooksStyle();
    if (NULL == p_style) {
        return -1;
    }

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    app.setStyle(p_style);

    return app.exec();
}
