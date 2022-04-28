#include <stdio.h>
#include <windows.h>

int main()
{
    HANDLE PORT = INVALID_HANDLE_VALUE; // Identifier of the serial port.
    PORT = CreateFile( 
        "\\\\.\\COM13",
        GENERIC_READ | GENERIC_WRITE,
        0,    // Must be opened with exclusive-access.
        NULL, // No security attributes.
        OPEN_EXISTING, // Must use OPEN_EXISTING.
        0,    // Not overlapped I/O.
        NULL  // hTemplate must be NULL for comm devices.
        );
        
    if (PORT == INVALID_HANDLE_VALUE){    
        printf("CreateFile() failed\n");
        return -1;
    }else{
        printf("CreateFile() succeeded\n");
    }

    DCB dcb; // Structure defining port options.
    memset(&dcb, 0, sizeof(DCB)); // this function puts zero to all the memoris pointed by dcb
    if (!GetCommState(PORT, &dcb)){
        printf("GetCommState() failed\n");
        return -1;
    }
    printf("baud rate = %d\n",dcb.BaudRate);
    printf("Parity = %d\n",dcb.Parity);
    printf("Byte Size = %d\n",dcb.ByteSize);
    printf("Stop Bit = %d\n",dcb.StopBits);
    dcb.BaudRate = 9600 ;
        if (!SetCommState(PORT, &dcb)){
        printf("SetCommState() failed\n");
        return -1;
    }
    #define BUFFER_SIZE 256
    char writebuf[BUFFER_SIZE]; 
    strcpy(writebuf, "HELLO");
    int writtenbytes = 0;
    if (WriteFile(PORT, writebuf, 5 , (LPDWORD)&writtenbytes, NULL)){
        if (writtenbytes == 0){
            printf("WriteFile() timed out\n");
            return -1;
        }
    }
    else{
        printf("WriteFile() failed\n");
        return -1;
    }
    printf("%d bytes were written\n",writtenbytes );
    
    if (!CloseHandle(PORT)){
        printf("CloseHandle() failed\n");
        return -1;
    }

    return 0;

}