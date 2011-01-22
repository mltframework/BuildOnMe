#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

namespace Mlt {
    class Profile;
    class Producer;
    class Consumer;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initializeMlt ();

private:
    void resizeEvent (QResizeEvent * event);

    Ui::MainWindow *ui;
    Mlt::Profile *m_profile;
    Mlt::Producer *m_producer;
    Mlt::Consumer *m_consumer;

public slots:
    void openVideo ();
    void play ();
    void pause ();

};

#endif // MAINWINDOW_H
