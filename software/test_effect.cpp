#include "test_effect.h"
#include <QDial>
#include <QSlider>

namespace effects
{

Test::Test()
    : BaseEffect("Test Effect", ":/forms/test_effect_ctrl.ui")
{
    m_speed = EFFECT_UPDATE_RATE_HZ;
    m_brightness = 1.0f;

    if (NULL != m_pCtrls)
    {
        QSlider *pSpeedSlider = m_pCtrls->findChild<QSlider*>("slider_speed");
        QDial *pBrightnessDial = m_pCtrls->findChild<QDial*>("dial_brightness");

        connect(pBrightnessDial, SIGNAL(valueChanged(int)), this, SLOT(setBrightness(int)));
        connect(pSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
    }
}

Test::~Test()
{

}

void Test::start()
{
    memset(m_cube, 0, sizeof(m_cube));

    m_counter = 0;
    m_curr_layer = 0;

    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            m_cube[x][0][z] = 1.0f;
}

void Test::stop()
{
    // Nothing to do
}

void Test::update(boost::asio::serial_port &port)
{
    if (m_counter >= m_speed)
    {
        m_counter = 0;

        for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        {
            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            {
                m_cube[x][m_curr_layer][z] = 0.0f;
            }
        }

        ++m_curr_layer;
        if (m_curr_layer >= CUBE_SIZE)
            m_curr_layer = 0;
    }
    else
    {
        ++m_counter;
    }

    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t z = 0; z < CUBE_SIZE; ++z)
        {
            m_cube[x][m_curr_layer][z] = m_brightness;
        }
    }

    send(port);
}

void Test::setBrightness(int brightness)
{
    QDial *pBrightnessDial = m_pCtrls->findChild<QDial*>("dial_brightness");
    m_brightness = (float)brightness/pBrightnessDial->maximum();
}

} // namespace effects
