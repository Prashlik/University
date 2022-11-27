#include "Header.h"

void PORT1(HANDLE readEnd, HANDLE writeEnd, HANDLE hFile, HANDLE hExit, HANDLE hWork)
{
    string buffer;
    while (WaitForSingleObject(hExit, 1) == WAIT_TIMEOUT)
    {
        if (WaitForSingleObject(hWork, 1) != WAIT_TIMEOUT)
        {
            WaitForSingleObject(writeEnd, INFINITE);
            if (WaitForSingleObject(hExit, 1) != WAIT_TIMEOUT)
                return;
            buffer.clear();
            buffer = read(hFile);
            cout << "Message from COM2: " << buffer << endl;
            SetEvent(readEnd);
        }
        SetEvent(hWork);
        cout << "Message: ";
        cin >> buffer;
        buffer += '\n';
        if (!write(hFile, buffer))
        {
            SetEvent(hExit);
            SetEvent(writeEnd);
            return;
        }
        else
        {
            SetEvent(writeEnd);
            WaitForSingleObject(readEnd, INFINITE);
        }
    }
}

int Server()
{
    HANDLE readEnd = CreateEvent(NULL, FALSE, FALSE, L"readEnd");
    HANDLE writeEnd = CreateEvent(NULL, FALSE, FALSE, L"writeEnd");
    HANDLE hExit = CreateEvent(NULL, FALSE, FALSE, L"exit");
    HANDLE hWork = CreateEvent(NULL, FALSE, FALSE, L"work");

    HANDLE hFile = CreateFile(L"COM1", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == NULL)
    {
        printf("Error\n");
        exit(GetLastError());
    }
    SetCommMask(hFile, EV_RXCHAR);                      
    SetupComm(hFile, 1500, 1500);                       

    COMMTIMEOUTS CommTimeOuts;                          
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;      
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;        
    CommTimeOuts.ReadTotalTimeoutConstant = 1200;       
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;       
    CommTimeOuts.WriteTotalTimeoutConstant = 1200;      

    if (!SetCommTimeouts(hFile, &CommTimeOuts))
    {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
        return 1;
    }

    DCB ComDCM;                               
    memset(&ComDCM, 0, sizeof(ComDCM));       
    ComDCM.DCBlength = sizeof(DCB);           
    GetCommState(hFile, &ComDCM);             
    ComDCM.BaudRate = setBaudrate();          
    ComDCM.ByteSize = 8;                      
    ComDCM.Parity = NOPARITY;                 
    ComDCM.StopBits = ONESTOPBIT;             
    ComDCM.fAbortOnError = TRUE;              
    ComDCM.fDtrControl = DTR_CONTROL_DISABLE; 
    ComDCM.fRtsControl = RTS_CONTROL_DISABLE; 
    ComDCM.fBinary = TRUE;                    
    ComDCM.fParity = FALSE;                   
    ComDCM.fInX = FALSE;                      
    ComDCM.fOutX = FALSE;                     
    ComDCM.XonChar = 0;                       
    ComDCM.XoffChar = (unsigned char)0xFF;    
    ComDCM.fErrorChar = FALSE;                
    ComDCM.fNull = FALSE;                     
    ComDCM.fOutxCtsFlow = FALSE;              
    ComDCM.fOutxDsrFlow = FALSE;              
    ComDCM.XonLim = 128;                      
    ComDCM.XoffLim = 128;                     

    if (!SetCommState(hFile, &ComDCM))
    {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
        return 2;
    }

    PORT1(readEnd, writeEnd, hFile, hExit, hWork);

    CloseHandle(hFile);
    return 0;
}

int main()
{
    system("cls");
    puts("COM1 - port");
    int response = Server();
    if (!response)
        puts("Work ended");
    else
        puts("COM1 can not be opened");
    return 0;
}