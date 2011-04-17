#include "sphere_effect.h"
#include <math.h>

#define MAX_SPHERE_SIZE (5.0f)

#define MIN_GROW_SPEED (0.1f)
#define MAX_GROW_SPEED (1.0f)

namespace effects
{

Sphere::Sphere()
    : BaseEffect("Sphere", ":/forms/sphere_effect_ctrl.ui")
    , m_size(0.0f)
    , m_expand_speed(0.4f)
    , m_inverted(false)
    , m_falloff(true)
{
    m_pSlider_speed  = m_pCtrls->findChild<QSlider*>("slider_speed");
    m_pCheck_falloff = m_pCtrls->findChild<QCheckBox*>("check_falloff");

    connect(m_pSlider_speed, SIGNAL(valueChanged(int)), this, SLOT(set_speed(int)));
    connect(m_pCheck_falloff, SIGNAL(toggled(bool)), this, SLOT(set_falloff(bool)));

    m_pSlider_speed->setValue(convert(m_expand_speed, MIN_GROW_SPEED, MAX_GROW_SPEED,
                                      m_pSlider_speed->minimum(), m_pSlider_speed->maximum()));
    m_pCheck_falloff->setChecked(m_falloff);
}

void Sphere::start()
{
    m_size = 0.0f;
    m_inverted = false;
}

void Sphere::stop()
{
    // Nothing to do
}

void Sphere::update(boost::asio::serial_port &port)
{
    const float center = static_cast<float>(CUBE_SIZE - 1)/2.0f;

    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t y = 0; y < CUBE_SIZE; ++y)
        {
            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            {
                const float x2 = static_cast<float>(x) - center;
                const float y2 = static_cast<float>(y) - center;
                const float z2 = static_cast<float>(z) - center;
                float distance = m_size/sqrt((x2*x2) + (y2*y2) + (z2*z2)); // Affect the distance based on the size of the cube

                if (m_falloff)
                {
                    // Clamp the distance for the following (1.0f - distance) calculation to avoid negative distance
                    if (distance > 1.0f)
                    {
                        distance = 1.0f;
                    }

                    m_cube[x][y][z] = m_inverted ? (1.0f - distance) : distance;
                }
                else
                {
                    // Don't use falloff, so don't use the distance value directly.
                    // The LEDs are on if the size of the cube is big enough to "engulf" it
                    const float value = m_inverted ? 0.0f : 1.0f;
                    m_cube[x][y][z] = (distance > 0.5f) ? value : (1.0f - value);
                }
            }
        }
    }

    // Grow the size of the sphere
    if (m_size > MAX_SPHERE_SIZE)
    {

        m_size = 0;
        m_inverted = !m_inverted;
    }
    else
    {
        m_size += m_expand_speed;
    }

    send(port);
}

void Sphere::set_speed(int speed)
{
    m_expand_speed = convert(speed, m_pSlider_speed->minimum(), m_pSlider_speed->maximum(),
                             MIN_GROW_SPEED, MAX_GROW_SPEED);
}

void Sphere::set_falloff(bool falloff)
{
    m_falloff = falloff;
}

} // namespace effects
