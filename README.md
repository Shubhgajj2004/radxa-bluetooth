# Radxa Bluetooth Host

This application turns your Radxa board into a Bluetooth host that waits for a connection from a mobile device and logs received audio data.

## Prerequisites

Before you can compile and run this application, you need to install the BlueZ development libraries on your Radxa board. You can do this with the following command:

```bash
sudo apt-get update
sudo apt-get install libbluetooth-dev
```

## Compilation

To compile the application, navigate to the `radxa-bluetooth` directory on your Radxa board and run the `make` command:

```bash
make
```

This will create an executable file named `bluetooth_host`.

## Running the Application

To run the application, execute the following command:

```bash
sudo ./bluetooth_host
```

The application will start and wait for a Bluetooth connection from a mobile device.

## Smartphone Application

The smartphone application needs to be able to:

1.  **Discover and pair** with the Radxa board's Bluetooth.
2.  **Connect to the RFCOMM channel** that the `bluetooth_host` application is listening on (channel 1).
3.  **Stream audio data** in WAV format to the Radxa board.

The `my_spex` Flutter application that was previously developed can be adapted for this purpose. The `flutter_bluetooth_serial` package can be used to connect to the Radxa board and send data.

### Example Smartphone Code (Flutter)

Here's a conceptual example of how you might connect and send data from a Flutter app:

```dart
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

// ...

// Get the Radxa board's BluetoothDevice object
BluetoothDevice radxaDevice = ...;

// Connect to the device
BluetoothConnection connection = await BluetoothConnection.toAddress(radxaDevice.address);

// Send audio data
List<int> audioData = ...; // Your WAV audio data
connection.output.add(audioData);
await connection.output.allSent;

// ...
```

This provides a complete setup for the Radxa Bluetooth host and instructions for the smartphone client.
