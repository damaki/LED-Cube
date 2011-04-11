#ifndef WAVE_EFFECT_H
#define WAVE_EFFECT_H
#include "effect_base.h"

namespace effects
{

class Wave : public BaseEffect
{
    Q_OBJECT
public:
    Wave();
    ~Wave();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private slots:
    void set_speed(int speed);
    void set_width(int width);
    void set_height(int height);

private:
    float m_speed;
    float m_pos;
    float m_width;
    float m_height;

    QSlider *m_pSlider_speed;
    QSlider *m_pSlider_width;
    QSlider *m_pSlider_height;
};

} // namespace effects

#endif // WAVE_EFFECT_H
