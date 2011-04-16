#ifndef TEXT_SCROLL_EFFECT_H
#define TEXT_SCROLL_EFFECT_H
#include "effect_base.h"
#include <QString>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QPixmap>
#include <boost/thread.hpp>

namespace effects
{

class TextScroll : public BaseEffect
{
    Q_OBJECT
public:
    TextScroll();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private slots:
    void set_speed(int speed);
    void set_text();

private:
    void drawFace(uint8_t face);

    QString m_string;
    float m_pos;
    float m_scrollrate;

    boost::mutex m_mutex; // To protect m_string

    QSlider *m_pSlider_speed;
    QLineEdit *m_pEdit_text;
    QPushButton *m_pBtn_start;

    QImage m_bitmap;
};

} // namespace effects

#endif // TEXT_SCROLL_EFFECT_H
