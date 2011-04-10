#ifndef BALL_EFFECT_H
#define BALL_EFFECT_H
#include "effect_base.h"
#include <QVector3D>
#include <QSlider>

namespace effects
{

struct BallData
{
    QVector3D pos;
    QVector3D direction;

    float speed;
    float size;
};

class Ball : public BaseEffect
{
    Q_OBJECT
public:
    Ball();
    ~Ball();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private slots:
    void set_speed(int speed);
    void set_size(int size);

private:
    BallData m_ball;

    QSlider *m_pSlider_size;
    QSlider *m_pSlider_speed;
};

} // namespace effects

#endif // BALL_EFFECT_H
