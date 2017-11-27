#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "cashcodeprotocol.h"

using namespace std;

int main(int argc, char *argv[])
{
    CashCodeProtocol CCValidator;
    CCValidator.ConnectValidator();
    CCValidator.PowerUpValidator();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    bool is_thread = false;

    for(int i = 0; i < 5; i++)
    {
        cout << "-----------[ TRY " << i << " ]------------\n";
        CCValidator.EnableSequence();
        std::this_thread::sleep_for(std::chrono::seconds(10));

        if( ! is_thread) {
            CCValidator.StartListening();
            is_thread = true;
        }

        cout << "Total Cash: " << dec << CCValidator.m_CashReceived << endl;

        std::this_thread::sleep_for(std::chrono::seconds(35));

        CCValidator.DisableSequence();
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    cout << "Done\n";

    return 0;
}
