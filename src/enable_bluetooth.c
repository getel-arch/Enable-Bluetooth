#include <windows.h>
#include <bluetoothapis.h>
#include <stdio.h>

int main() {
    BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };
    HANDLE hRadio = NULL;
    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

    if (hFind == NULL) {
        printf("No Bluetooth radio found.\n");
        return 1;
    }

    do {
        BLUETOOTH_RADIO_INFO bri = { sizeof(bri) };
        if (BluetoothGetRadioInfo(hRadio, &bri) == ERROR_SUCCESS) {
            printf("Bluetooth radio found: %s\n", bri.szName);
            DWORD dwMode = 0;
            if (BluetoothEnableDiscovery(hRadio, TRUE) == ERROR_SUCCESS) {
                printf("Bluetooth discovery enabled.\n");
            } else {
                printf("Failed to enable Bluetooth discovery.\n");
            }
            if (BluetoothEnableIncomingConnections(hRadio, TRUE) == ERROR_SUCCESS) {
                printf("Bluetooth incoming connections enabled.\n");
            } else {
                printf("Failed to enable Bluetooth incoming connections.\n");
            }
        }
        CloseHandle(hRadio);
    } while (BluetoothFindNextRadio(hFind, &hRadio));

    BluetoothFindRadioClose(hFind);
    return 0;
}
