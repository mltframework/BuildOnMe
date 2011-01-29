#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Mlt.h>
#ifdef Q_WS_MAC
#   include "glwidget.h"
#endif

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initializeMlt ();
#ifdef Q_WS_MAC
    void showFrame (Mlt::Frame&);
#endif

private:
    void resizeEvent (QResizeEvent * event);

    Ui::MainWindow *ui;
    Mlt::Profile *m_profile;
    Mlt::Producer *m_producer;
    Mlt::Consumer *m_consumer;

#ifdef Q_WS_MAC
    GLWidget* m_gl;
    static void on_frame_show(mlt_consumer, MainWindow*, mlt_frame);
#endif

signals:
    void showImageSignal(QImage);

public slots:
    void openVideo ();
    void play ();
    void pause ();

};

#endif // MAINWINDOW_H
