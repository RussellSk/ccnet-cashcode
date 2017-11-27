#include "serialport.h"

void SerialPort::read_complete(const boost::system::error_code &error, size_t bytes_transferred)
{
    read_error = (error || bytes_transferred == 0);
    // Read has finished, cancel the timer
    this->timer->cancel();
}

void SerialPort::time_out(const boost::system::error_code &error)
{
    // Timeout was cancelled?
    if(error)
        return ; // Yes

    // no, we have timed out, so kill
    // the read operation
    // The read callback will be called
    // with an error
    this->p_port->cancel();
}

SerialPort::SerialPort(size_t timeout) :
    timeout(timeout),
    read_error(true) {}

SerialPort::~SerialPort(void)
{
    stop();
}

bool SerialPort::start(const char *com_port_name, int baud_rate)
{
    boost::system::error_code error_code;

    // Check if Port already in use
    if(this->p_port)
    {
        std::cout << "Error: Port is already opened." << std::endl;
        return false;
    }

    // Open Serial Port
    this->p_port = serial_port_ptr(new boost::asio::serial_port(this->m_io_service));
    this->timer = new boost::asio::deadline_timer(this->m_io_service);
    this->p_port->open(com_port_name, error_code);
    if(error_code)
    {
        std::cout << "Error: this->_port->open() failed. Com port name="
                  << com_port_name << ", Error Code=" << error_code.message().c_str() << std::endl;
    }

    // Set options
    this->p_port->set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    this->p_port->set_option(boost::asio::serial_port_base::character_size(8));
    this->p_port->set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    this->p_port->set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    this->p_port->set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
    return true;
}

void SerialPort::stop()
{
    if(this->p_port)
    {
        this->p_port->cancel();
        this->p_port->close();
    }
    this->m_io_service.stop();
    this->m_io_service.reset();
}

bool SerialPort::read_char(byte &val)
{
    val = c = '\n';
    // After a timeout & cancel it seems we need
    // to do a reset for subsequent reads to work.
    this->p_port->get_io_service().reset();

    // Asynchronously read 1 character.
    boost::asio::async_read(*this->p_port, boost::asio::buffer(&c, 1),
                   boost::bind(&SerialPort::read_complete,
                            this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));

    // Setup a deadline time to implement our timeout.
    this->timer->expires_from_now(boost::posix_time::milliseconds(this->timeout));
    this->timer->async_wait(boost::bind(&SerialPort::time_out,
                                       this, boost::asio::placeholders::error));
    // This will block until a character is read
    // or until the it is cancelled.
    this->p_port->get_io_service().run();

    if(!read_error)
        val = c;

    return !read_error;
}

vec_bytes SerialPort::readLine()
{
    vec_bytes result;

    while(true) {
        this->read_char(c);
        switch(c)
        {
            case '\r':
                break;
            case '\n':
                // Конвертируем BIN 2 HEX и возвращаем
                return result;
            default:
                result.push_back(c);
        }
    }
}

int SerialPort::write_data(vec_bytes buf)
{
    if(buf.size() == 0)
        return 0;
    boost::system::error_code error_code;
    this->p_port->write_some(boost::asio::buffer(buf, buf.size()), error_code);
}

