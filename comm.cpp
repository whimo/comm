#include <stdio.h>
#include <windows.h>

#define BAUD_RATE CBR_9600
#define COM_ID "COM3"

class Serial // A class for serial connection
    {
    private:
        HANDLE fileHandle;
        DCB dcb;
        COMMTIMEOUTS commTimeouts;

    public:
        void init (LPCTSTR COM, DWORD baudRate, DWORD buffSize) // initialize serial connection
            {
            fileHandle = CreateFile (COM, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

            SetupComm (fileHandle, buffSize, buffSize);

            if (!GetCommState (fileHandle, &dcb))
                {
                MessageBox (NULL, "Failed to initialize serial connection.", "Error", MB_OK | MB_ICONERROR);
                return;
                }

            //{ Set up serial port
            dcb.BaudRate = baudRate;
            dcb.Parity   = NOPARITY;
            dcb.ByteSize = 8;
            dcb.StopBits = ONESTOPBIT;
            //}

            //{ Set timeouts
            commTimeouts.ReadIntervalTimeout        = 10;
            commTimeouts.ReadTotalTimeoutMultiplier = 1;
            commTimeouts.ReadTotalTimeoutConstant   = 100;

            commTimeouts.WriteTotalTimeoutMultiplier = 0;
            commTimeouts.WriteTotalTimeoutConstant   = 0;
            //}

            if (!SetCommState (fileHandle, &dcb) || !SetCommTimeouts (fileHandle, &commTimeouts))
                {
                MessageBox (NULL, "Failed to initialize serial connection.", "Error", MB_OK | MB_ICONERROR);
                return;
                }

            MessageBox (NULL, "Initializing serial connection success!", "Success!", MB_OK | MB_ICONINFORMATION);

            //{ Clean buffers
            PurgeComm (fileHandle, PURGE_TXCLEAR);
            PurgeComm (fileHandle, PURGE_RXCLEAR);
            //}
            }
    };


int main ()
    {
    Serial serial;
    serial.init (COM_ID, BAUD_RATE, 1200);

    return 0;
    }























