#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <Mlt.h>

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent)
    , ui (new Ui::MainWindow)
    , m_producer (0)
    , m_consumer (0)
{
    // Create the UI.
    ui->setupUi (this);

    // This is required for SDL embeddding.
    ui->centralWidget->setAttribute (Qt::WA_NativeWindow);

    // These use the icon theme on Linux, with fallbacks to the icons specified in QtDesigner for other platforms.
    ui->actionOpen->setIcon (QIcon::fromTheme ("document-open", ui->actionOpen->icon ()));
    ui->actionPlay->setIcon (QIcon::fromTheme ("media-playback-start", ui->actionPlay->icon ()));
    ui->actionPause->setIcon (QIcon::fromTheme ("media-playback-pause", ui->actionPause->icon ()));

    // Connect signals.
    connect (ui->actionOpen, SIGNAL(triggered()), this, SLOT(openVideo()));
    connect (ui->actionPlay, SIGNAL(triggered()), this, SLOT(play()));
    connect (ui->actionPause, SIGNAL(triggered()), this, SLOT(pause()));
}

MainWindow::~MainWindow ()
{
    delete m_consumer;
    delete m_producer;
    delete m_profile;
    Mlt::Factory::close();
    delete ui;
}

void MainWindow::initializeMlt ()
{
    ui->statusBar->showMessage (tr("Loading plugins..."));

    // Initialize the library and load plugins.
    Mlt::Factory::init (NULL);

    m_profile = new Mlt::Profile ("square_ntsc_wide");
    m_consumer = new Mlt::Consumer (*m_profile, "sdl_preview");

    // Embed the SDL window in our GUI.
    m_consumer->set ("window_id", (int) ui->centralWidget->winId());
    m_consumer->set ("play.audio_buffer", 4096);

    // Load a color producer to clear the video region with black.
    m_producer = new Mlt::Producer (*m_profile, "color:");
    m_consumer->connect (*m_producer);
    m_producer->set_speed (0.0);
    m_consumer->start();

    ui->statusBar->showMessage (tr("Ready"));
}

void MainWindow::openVideo ()
{
	QString filename = QFileDialog::getOpenFileName (this);
	if (!filename.isNull())
	{
		Mlt::Producer * producer = new Mlt::Producer (*m_profile, filename.toUtf8().constData());
		if (producer->is_valid())
		{
			m_consumer->stop();
			m_consumer->connect (*producer);
			delete m_producer;
			m_producer = producer;
			m_consumer->start();
			play();
		}
	}
	// If file invalid, then on some platforms the dialog messes up SDL.
	m_consumer->set ("refresh", 1);
}

void MainWindow::play ()
{
	m_producer->set_speed (1.0);
	// If we are paused, then we need to "unlock" sdl_still.
	m_consumer->set ("refresh", 1);
	ui->statusBar->showMessage (tr("Playing"));
}

void MainWindow::pause ()
{
	m_producer->set_speed (0.0);
	ui->statusBar->showMessage (tr("Paused"));
}

void MainWindow::resizeEvent (QResizeEvent * event)
{
	if (m_consumer)
		// When paused this tells sdl_still to update.
		m_consumer->set ("refresh", 1);
}
