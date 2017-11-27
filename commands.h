#ifndef COMMANDS_H
#define COMMANDS_H

// Controller Commands
enum class ValidatorCommands : unsigned char
{
    ACK = 0x00,
    NAK = 0xFF,
    RESET = 0x30,
    GET_STATUS = 0x31,
    SET_SECURITY = 0x32,
    IDENTIFICATION = 0x37,
    ENABLE_BILL_TYPES = 0x34,
    STACK = 0x35,
    RETURN = 0x36,
    HOLD = 0x38,
    POLL = 0x33,
    REQUEST_STATISTICS = 0x60,
};

#endif // COMMANDS_H
