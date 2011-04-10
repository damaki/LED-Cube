#include "effect_base.h"
#include <boost/asio.hpp>

#include <QtGui>
#include <QtUiTools/QUiLoader>

namespace effects
{
const uint8_t g_frame_start = 0xFF;

BaseEffect::BaseEffect(const QString &name, const QString &ctrlsFormPath)
    : QListWidgetItem(name)
    , m_pCtrls(NULL)
{
    memset(m_cube, 0, sizeof(m_cube));

    QUiLoader loader;

    QFile file(ctrlsFormPath);
    file.open(QFile::ReadOnly);
    m_pCtrls = loader.load(&file);
    file.close();
}

BaseEffect::~BaseEffect()
{
    if (NULL != m_pCtrls)
    {
        delete m_pCtrls;
        m_pCtrls = NULL;
    }
}

void BaseEffect::send(boost::asio::serial_port &port)
{
    try
    {
        uint8_t packed_cube[256];
        float *unpacked_cube = reinterpret_cast<float*>(m_cube);

        // Pack the cube (2 LEDs into 1 byte)
        for (uint16_t i = 0; i < 512; i += 2)
        {
            // Convert from float in range 0.0f - 1.0f to range 0 - 14.
            // Also convert the brightness scale from a linear scale to a logarithmic one.
            // This has the downside that the brightness is more precise at the higher brightnesses,
            // but is less precise at the lower end of the scale.
            uint8_t x1 = static_cast<uint8_t>((unpacked_cube[i]*unpacked_cube[i]*MAX_BRIGHTNESS) + 0.5f);
            uint8_t x2 = static_cast<uint8_t>((unpacked_cube[i+1]*unpacked_cube[i+1]*MAX_BRIGHTNESS) + 0.5f);

            // Clamp the brightness
            if (x1 > MAX_BRIGHTNESS) x1 = MAX_BRIGHTNESS;
            if (x2 > MAX_BRIGHTNESS) x2 = MAX_BRIGHTNESS;

            packed_cube[i/2] = x1 | (x2 << 4);
        }

        // send frame start character first
        boost::asio::write(port,
                           boost::asio::buffer(&g_frame_start,
                                               sizeof(g_frame_start)));

        // Then send the data
        boost::asio::write(port,
                           boost::asio::buffer(reinterpret_cast<const char*>(packed_cube),
                                               sizeof(packed_cube)));
    }
    catch (...)
    {

    }
}

} // namespace effects
