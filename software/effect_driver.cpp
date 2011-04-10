#include "effect_driver.h"
#include "effect_base.h"

#define EFFECT_UPDATE_PERIOD_MS (1000/EFFECT_UPDATE_RATE_HZ)

EffectDriver::EffectDriver(boost::asio::io_service &ioservice)
    : m_pEffect(NULL)
    , m_ioservice(ioservice)
    , m_port(ioservice)
    , m_thread(boost::bind(boost::mem_fn(&EffectDriver::processor_thread), boost::ref(*this)))
    , m_exit_thread(false)
    , m_timer(ioservice)
{

}

EffectDriver::~EffectDriver()
{
    try
    {
        stop();
    }
    catch (...)
    {}

    try
    {
        close_port();
    }
    catch (...)
    {}

    // Exit the processing thread
    m_exit_thread = true;
    m_cond.notify_all();
    m_thread.join();
}

void EffectDriver::start()
{
    boost::unique_lock<boost::mutex> lock(m_timer_mutex);
    // Setup the timer
    m_timer.expires_from_now(boost::posix_time::milliseconds(EFFECT_UPDATE_PERIOD_MS));
    m_timer.async_wait(boost::bind(boost::mem_fn(&EffectDriver::notify_timer_expired), boost::ref(*this), _1));
}

void EffectDriver::stop()
{
    {
        boost::unique_lock<boost::mutex> lock (m_timer_mutex);
        // Stop the update timer
        m_timer.cancel();
    }
}

void EffectDriver::run(effects::IEffect *pEffect)
{
    {
        boost::unique_lock<boost::mutex> lock(m_mutex);

        if (NULL != m_pEffect)
            m_pEffect->stop();

        if (NULL != pEffect)
            pEffect->start();

        m_pEffect = pEffect;
    }
}

void EffectDriver::open_port(const std::string &port)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if (m_port.is_open())
        m_port.close();

    m_port.open(port);

    try
    {
        m_port.set_option(boost::asio::serial_port_base::baud_rate(125000)); // 125Kbps
        m_port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none)); // No parity
        m_port.set_option(boost::asio::serial_port_base::character_size(8)); // 8 data bits
        m_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one)); // 1 stop bit
    }
    catch (...)
    {
        m_port.close();
        throw;
    }
}

bool EffectDriver::is_open() const
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    return m_port.is_open();
}

void EffectDriver::close_port()
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    if (m_port.is_open())
        m_port.close();
}

void EffectDriver::processor_thread()
{
    for (;;)
    {
        boost::unique_lock<boost::mutex> lock(m_mutex);
        m_cond.wait(lock);

        if (m_exit_thread)
            break;

        try
        {
            if (m_port.is_open() && (NULL != m_pEffect))
            {
                m_pEffect->update(m_port);        // Calculate the next frame while the current one is sending
            }
        }
        catch (...)
        {

        }
    }
}

void EffectDriver::notify_timer_expired(const boost::system::error_code &error)
{
    if (boost::asio::error::operation_aborted != error)
    {
        boost::unique_lock<boost::mutex> lock(m_timer_mutex);

        // Wake up the processor thread to do some work
        m_cond.notify_one();

        m_timer.expires_at(m_timer.expires_at() + boost::posix_time::milliseconds(EFFECT_UPDATE_PERIOD_MS));
        m_timer.async_wait(boost::bind(boost::mem_fn(&EffectDriver::notify_timer_expired),
                                       boost::ref(*this), _1));
    }
}
