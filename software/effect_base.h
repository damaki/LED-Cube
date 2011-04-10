#ifndef EFFECT_BASE_H
#define EFFECT_BASE_H
#include <windef.h>
#include <boost/asio/serial_port.hpp>
#include <QListWidgetItem>
#include <QObject>

#define CUBE_SIZE               8
#define EFFECT_UPDATE_RATE_HZ   30
#define MAX_BRIGHTNESS          14

namespace effects
{

class IEffect
{
public:
    virtual ~IEffect() {}

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void update(boost::asio::serial_port &port) = 0;
};

class BaseEffect : public QObject, public IEffect, public QListWidgetItem
{
public:
    BaseEffect(const QString &name, const QString &ctrlsFormPath);
    virtual ~BaseEffect();

    QWidget* get_controls() const { return m_pCtrls; }

    virtual void send(boost::asio::serial_port &port);

protected:
    float m_cube[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

    QWidget *m_pCtrls;
};

} // namespace effects

#endif // EFFECT_BASE_H
