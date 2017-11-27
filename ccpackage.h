#ifndef CCPACKAGE_H
#define CCPACKAGE_H
#define POLYNOMIAL 0x08408

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "commands.h"

typedef std::vector<unsigned char> vec_bytes;
typedef unsigned char byte;

class CCPackage
{
    // Message transmission start code [02H], fixed
    // Бит синхронизации (фиксированный)
    const byte m_sync = 0x02;

    // Peripheral Addresses - CashCode
    // Перифирийный адресс оборудования для CashCode (фіксований)
    const byte m_adr = 0x03;

    byte m_cmd;
    vec_bytes m_data;
public:
    CCPackage();
    CCPackage(byte cmd, vec_bytes data);

    // GET & SET m_cmd
    void set_cmd(byte cmd);
    byte get_cmd();

    // GET & SET m_data
    vec_bytes get_data();
    void set_data(vec_bytes data);

    // Methods
    // Возвращает массив байтов пакета
    vec_bytes getBytes();

    // Возвращает строку шестнадцатиричного представления байтов пакета
    std::string getBytesHex();

    // Возвращает длину пакета
    int getLength();

    // CRC или контрольная сумма пакета
    vec_bytes GetCRC16(vec_bytes bufData, int sizeData);

    // Проверка CRC
    bool ChechCRC16(vec_bytes buff);

    vec_bytes createResponse(ValidatorCommands type);
};

#endif // CCPACKAGE_H
