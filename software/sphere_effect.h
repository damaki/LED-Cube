#ifndef SPHERE_EFFECT_H
#define SPHERE_EFFECT_H
#include "effect_base.h"

#include <QSlider>
#include <QCheckBox>

namespace effects
{

class Sphere : public BaseEffect
{
    Q_OBJECT

public:
    Sphere();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private slots:
    void set_speed(int speed);
    void set_falloff(bool falloff);

private:
    QSlider *m_pSlider_speed;
    QCheckBox *m_pCheck_falloff;

    float m_size;
    float m_expand_speed;
    bool m_inverted;
    bool m_falloff;
};

} // namespace effects

#endif // SPHERE_EFFECT_H
