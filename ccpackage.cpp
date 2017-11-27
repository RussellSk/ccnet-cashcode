#include "ccpackage.h"

CCPackage::CCPackage(){}

CCPackage::CCPackage(byte cmd, vec_bytes data) : m_cmd(cmd), m_data(data) {}

void CCPackage::set_cmd(byte cmd)
{
    this->m_cmd = cmd;
}

byte CCPackage::get_cmd()
{
    return this->m_cmd;
}

vec_bytes CCPackage::get_data()
{
    return this->m_data;
}

void CCPackage::set_data(vec_bytes data)
{
    this->m_data = data;
}

vec_bytes CCPackage::getBytes()
{
    vec_bytes buffer;

    // Байт 1: Флаг синхронизации
    buffer.push_back(this->m_sync);

    // Байт 2: адрес устройства
    buffer.push_back(this->m_adr);

    // Байт 3: длина пакета
    // рассчитаем длину пакета
    int length = this->getLength();

    // Если длина пакета вместе с байтами SYNC, ADR, LNG, CRC, CMD  больше 250
    if(length > 250) {
        // то делаем байт длины равный 0, а действительная длина сообщения будет в DATA
        buffer.push_back(0x00);
    } else {
        // DEC 2 HEX conversion
        buffer.push_back((unsigned char)length & 0xFF);
    }

    // Байт 4: Команда
    buffer.push_back(this->m_cmd);

    // Байт 5-N: Данные
    if(length > 0)
        for(unsigned char& c : this->m_data)
            buffer.push_back(c);

    // Последний 2 Байта это CRC
    vec_bytes CRC = this->GetCRC16(buffer, buffer.size());
    buffer.insert(std::end(buffer), std::begin(CRC), std::end(CRC));

    return buffer;
}

int CCPackage::getLength()
{
    return this->m_data.size() + 6;
}

vec_bytes CCPackage::GetCRC16(vec_bytes bufData, int sizeData)
{
    unsigned int TmpCRC, CRC;
    unsigned char j;
    CRC = 0;
    for(int i=0; i < sizeData; i++)
    {
        TmpCRC = CRC ^ bufData[i];
        for(j=0; j < 8; j++)
        {
            if(TmpCRC & 0x0001)
            {
                TmpCRC >>= 1; TmpCRC ^= POLYNOMIAL;
            }
            else
            {
                TmpCRC >>= 1;
            }
        }
        CRC = TmpCRC;
    }

    vec_bytes v_CRC;
    v_CRC.push_back((unsigned char)CRC & 0xFF);
    v_CRC.push_back((unsigned char)((CRC >> 8) & 0xFF));

    return v_CRC;
}

vec_bytes CCPackage::createResponse(ValidatorCommands type)
{
    // Буффер пакета (без 2-х байт CRC). Первые четыре байта это SYNC, ADR, LNG, CMD
    vec_bytes buffer;

    // Байт 1: Флаг синхронизации
    buffer.push_back(this->m_sync);

    // Байт 2: адрес устройства
    buffer.push_back(this->m_adr);

    // Байт 3: длина пакета, всегда 6
    buffer.push_back(0x06);

    // Байт 4: Данные ответа
    if(type == ValidatorCommands::ACK)
        buffer.push_back(0x00);
    else if(type == ValidatorCommands::NAK)
        buffer.push_back(0xFF);

    vec_bytes CRC = this->GetCRC16(buffer, buffer.size());
    buffer.insert(std::end(buffer), std::begin(CRC), std::end(CRC));

    return buffer;
}
