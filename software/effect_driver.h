#ifndef EFFECT_DRIVER_H
#define EFFECT_DRIVER_H
#include <windef.h>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

namespace effects
{
class IEffect;
}

class EffectDriver
{
public:
    EffectDriver(boost::asio::io_service &ioservice);
    ~EffectDriver();

    void start();
    void stop();

    void run(effects::IEffect *pEffect);

    void open_port(const std::string &port);
    bool is_open() const;
    void close_port();

    void notify_timer_expired(const boost::system::error_code &error);

private:
    void processor_thread();

    effects::IEffect *m_pEffect;

    boost::asio::io_service &m_ioservice;
    boost::asio::serial_port m_port;

    mutable boost::mutex m_mutex;
    mutable boost::condition_variable m_cond;
    boost::thread m_thread;
    volatile bool m_exit_thread;

    boost::asio::deadline_timer m_timer;
    mutable boost::mutex m_timer_mutex;
};

#endif // EFFECT_DRIVER_H
