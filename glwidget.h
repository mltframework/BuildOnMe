
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget (QWidget *parent = 0);
    ~GLWidget ();

    QSize minimumSizeHint () const;
    QSize sizeHint () const;
    void setImageAspectRatio (double ratio) {
        m_display_ratio = ratio;
    }

private:
    int x, y, w, h;
    int m_image_width, m_image_height;
    GLuint m_texture;
    double m_display_ratio;

public slots:
    void showImage (QImage image);

protected:
    void initializeGL ();
    void resizeGL (int width, int height);
    void resizeEvent (QResizeEvent* event);
    void paintGL ();
};

#endif
