#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main() {
    int server_sock, client_sock;
    struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
    char buf[1024] = {0};
    socklen_t opt = sizeof(rem_addr);

    // Create socket
    server_sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    if (server_sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set local address
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = 1; // RFCOMM channel 1

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&loc_addr, sizeof(loc_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(1);
    }

    // Listen for connections
    if (listen(server_sock, 1) < 0) {
        perror("Listen failed");
        close(server_sock);
        exit(1);
    }

    // Set Bluetooth device name to "SpexGlasses"
    system("hciconfig hci0 name SpexGlasses");
    printf("Bluetooth host 'SpexGlasses' waiting for connection...\n");

    // Accept connection
    client_sock = accept(server_sock, (struct sockaddr *)&rem_addr, &opt);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_sock);
        exit(1);
    }

    // Log connection
    char addr[18];
    ba2str(&rem_addr.rc_bdaddr, addr);
    printf("Smartphone connected: %s\n", addr);

    // Close sockets
    close(client_sock);
    close(server_sock);
    return 0;
}