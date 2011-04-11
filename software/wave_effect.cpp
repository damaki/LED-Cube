#include "wave_effect.h"
#include "math.h"
#include <QSlider>

#define MIN_SPEED (0.01f)
#define MAX_SPEED (2.0f)

#define MIN_WIDTH (0.02f)
#define MAX_WIDTH (3.0f)

#define MIN_HEIGHT (0.1f)
#define MAX_HEIGHT (3.5f)

namespace effects
{

Wave::Wave()
    : BaseEffect("Wave", ":/forms/wave_effect_ctrl.ui")
    , m_speed(0.2f)
    , m_pos(0.0f)
    , m_width(0.5f)
    , m_height(3.5f)
{
    m_pSlider_speed = m_pCtrls->findChild<QSlider*>("slider_speed");
    m_pSlider_width = m_pCtrls->findChild<QSlider*>("slider_width");
    m_pSlider_height = m_pCtrls->findChild<QSlider*>("slider_height");

    connect(m_pSlider_speed, SIGNAL(valueChanged(int)), this, SLOT(set_speed(int)));
    connect(m_pSlider_width, SIGNAL(valueChanged(int)), this, SLOT(set_width(int)));
    connect(m_pSlider_height, SIGNAL(valueChanged(int)), this, SLOT(set_height(int)));

    m_pSlider_speed->setValue(convert(m_speed, MIN_SPEED, MAX_SPEED,
                                      m_pSlider_speed->minimum(), m_pSlider_speed->maximum()));

    m_pSlider_width->setValue(convert(m_width, MIN_WIDTH, MAX_WIDTH,
                                      m_pSlider_width->minimum(), m_pSlider_width->maximum()));

    m_pSlider_height->setValue(convert(m_height, MIN_HEIGHT, MAX_HEIGHT,
                                       m_pSlider_height->minimum(), m_pSlider_height->maximum()));
}

Wave::~Wave()
{

}

void Wave::start()
{
    m_pos = 0.0f;
}

void Wave::stop()
{

}

void Wave::update(boost::asio::serial_port &port)
{
    memset(m_cube, 0, sizeof(m_cube));

    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t y = 0; y < CUBE_SIZE; ++y)
        {
            const float pos = sin(m_pos + (x*m_width))*m_height;

            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
                m_cube[x][(int)(m_height + pos + 0.5f)][z] = 1.0f;
        }
    }

    m_pos += m_speed;

    send(port);
}

void Wave::set_speed(int speed)
{
    m_speed = convert(speed, m_pSlider_speed->minimum(), m_pSlider_speed->maximum(),
                      MIN_SPEED, MAX_SPEED);
}

void Wave::set_width(int width)
{
    m_width = convert(width, m_pSlider_width->minimum(), m_pSlider_width->maximum(),
                      MIN_WIDTH, MAX_WIDTH);
}

void Wave::set_height(int height)
{
    m_height = convert(height, m_pSlider_height->minimum(), m_pSlider_height->maximum(),
                       MIN_HEIGHT, MAX_HEIGHT);
}

} // namespace effects
