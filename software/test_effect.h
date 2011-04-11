#ifndef TEST_EFFECT_H
#define TEST_EFFECT_H
#include "effect_base.h"

namespace effects
{

class Test : public BaseEffect
{
    Q_OBJECT
public:
    Test();
    virtual ~Test();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private slots:
    void setBrightness(int brightness);
    void setSpeed(int speed);

private:
    uint32_t m_counter;
    uint8_t m_curr_layer;

    uint32_t m_speed;
    float m_brightness;
};

} // namespace effects

#endif // TEST_EFFECT_H
