#include <map>
#include <string>

#ifndef CASHCODEERRORS_H
#define CASHCODEERRORS_H

class CashCodeError
{
    int ErrorCode;
public:
    std::map<int, std::string> ErrorList;
    CashCodeError(int ErrCode)
    {
        ErrorCode = ErrCode;
        ErrorList[0x00] = "Неизвестная ошибка.";
        ErrorList[0x01] = "Ошибка открытия COM-порта.";
        ErrorList[0x02] = "Ошибка отпраки команды включения купюроприемника.";
        ErrorList[0x03] = "Ошибка отпраки команды включения купюроприемника. От купюроприемник не прислал команду - POWER UP.";
        ErrorList[0x04] = "Ошибка отпраки команды включения купюроприемника. От купюроприемник не прислал команду - ACK.";
        ErrorList[0x05] = "Ошибка отпраки команды включения купюроприемника. От купюроприемник не прислал команду - INITIALIZE.";
        ErrorList[0x06] = "Ошибка проверки статуса купюроприемника. Stacker отсутствует.";
        ErrorList[0x07] = "Ошибка проверки статуса купюроприемника. Stacker переполнен.";
        ErrorList[0x08] = "Ошибка проверки статуса купюроприемника. В валидаторе застряла купюра.";
        ErrorList[0x09] = "Ошибка проверки статуса купюроприемника. В Stacker-e застряла купюра.";
        ErrorList[0x10] = "Ошибка проверки статуса купюроприемника. Фальшивая купюра.";

        ErrorList[0x50] = "Stack Motor Failure. Drop Cassette Motor failure";
        ErrorList[0x51] = "Transport Motor Speed Failure.";
        ErrorList[0x52] = "Transport Motor Failure";
        ErrorList[0x53] = "Aligning Motor Failure";
        ErrorList[0x54] = "Initial Cassette Status Failure";
        ErrorList[0x55] = "Optic Canal Failure";
        ErrorList[0x56] = "Magnetic Canal Failure";
        ErrorList[0x5F] = "Capacitance Canal Failure";

        ErrorList[0x60] = "REJECTING - Rejecting due to Insertion. Insertion error";
        ErrorList[0x61] = "REJECTING - Rejecting due to Magnetic. Magnetic error";
        ErrorList[0x62] = "REJECTING - Rejecting due to bill Remaining in the head. Bill remains in the head, and new bill is rejected.";
        ErrorList[0x63] = "REJECTING - Rejecting due to Multiplying. Compensation error/multiplying factor error";
        ErrorList[0x64] = "REJECTING - Rejecting due to Conveying. Conveying error";
        ErrorList[0x65] = "REJECTING - Rejecting due to Identification1. Identification error";
        ErrorList[0x66] = "REJECTING - Rejecting due to Verification. Verification error";
        ErrorList[0x67] = "REJECTING - Rejecting due to Optic. Optic error";
        ErrorList[0x68] = "REJECTING - Rejecting due to Inhibit. Returning by inhibit denomination error";
        ErrorList[0x69] = "REJECTING - Rejecting due to Capacity. Capacitance error";
        ErrorList[0x6A] = "REJECTING - Rejecting due to Operation. Operation error.";
        ErrorList[0x6C] = "REJECTING - Rejecting due to Length. Length error";
        ErrorList[0x6D] = "REJECTING - Rejecting due to UV optic. Banknote UV properties do not meet the predefined criteria";
        ErrorList[0x92] = "REJECTING - Rejecting due to unrecognised barcode. Bill taken was treated as a barcode but no reliable data can be read from it.";
        ErrorList[0x93] = "REJECTING - Rejecting due to incorrect number of characters in barcode. Barcode data was read (at list partially) but is inconsistent";
        ErrorList[0x94] = "REJECTING - Rejecting due to unknown barcode start sequence. Barcode was not read as no synchronization was established.";
        ErrorList[0x95] = "REJECTING - Rejecting due to unknown barcode stop sequence. Barcode was read but trailing data is corrupt.";

    }

    std::string getMessage() {
        return this->ErrorList[this->ErrorCode];
    }
};

#endif // CASHCODEERRORS_H
