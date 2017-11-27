#ifndef CASHCODEPROTOCOL_H
#define CASHCODEPROTOCOL_H

#include <string>
#include <vector>
#include <iomanip>
#include <boost/thread.hpp>

#include <boost/chrono.hpp>

#include "commands.h"
#include "serialport.h"
#include "cashcodeerrors.h"
#include "ccpackage.h"

class CashCodeProtocol
{
private:
    std::string m_ComPortName;
    int m_LastError;
    bool m_Disposed;
    bool m_IsConnected;
    bool m_IsPowerUp;
    bool m_IsListening;
    bool m_IsEnableBills;
    bool m_ReturnBill;
    SerialPort *ComPort;
    CCPackage Pack;

    // Time-out ожидания ответа от считывателя
    const int POLL_TIMEOUT = 200;

    // Тайм-аут ожидания снятия блокировки
    const int EVENT_WAIT_HANDLER_TIMEOUT = 10000;

    vec_bytes ENABLE_BILL_TYPES_WITH_ESCROW = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    vec_bytes DISABLE_BILL_TYPES_WITH_ESCROW = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    vec_bytes SECURITY_CODE = { 0x00, 0x00, 0x00 };

    // Таблица кодов валют
    int CashCodeTable(byte code);

public:
    CashCodeProtocol();
    enum class BillRecievedStatus { Accepted, Rejected };
    enum class BillCassetteStatus { Inplace, Removed };

    bool IsConnected();

    int m_CashReceived;

    // Отправка команды купюро приемнику
    vec_bytes SendCommand(ValidatorCommands cmd, vec_bytes Data = {});

    // Начало прослушки CashCode
    void StartListening();

    // Остановка прослушки CashCode
    void StopListening();

    // Инициализация и открытие COM-порта для работы с CashCode
    int ConnectValidator();

    // Включение CashCode
    int PowerUpValidator();

    // Включение режима приема купюр
    int EnableValidator();

    // Выключение режима приема купюр
    int DisableValidator();

    // Проверка ответов купюро приемника на наличие ошибок
    bool CheckErrors(vec_bytes &result) ;

    // Enable sequence
    // Включение режима для приема купюр
    int EnableSequence(void);

    // Disable sequence
    // Выключение режима для приема купюр
    int DisableSequence(void);

    // Функция прослушка купюро приемника
    void ValidatorListener();

    void print_b(std::string msg, vec_bytes);
};

#endif // CASHCODEPROTOCOL_H
