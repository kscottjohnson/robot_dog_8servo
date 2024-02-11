void startBleScan(){
  Bluefruit.begin(0, 1);
  Bluefruit.setName("rd8 remote");
  clientUart.begin();
  clientUart.setRxCallback(bleuart_rx_callback);
  Bluefruit.setConnLedInterval(250);
  Bluefruit.Central.setConnectCallback(connect_callback);
  Bluefruit.Central.setDisconnectCallback(disconnect_callback);
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0);  // 0 = Don't stop scanning after n seconds
}

void scan_callback(ble_gap_evt_adv_report_t* report){
  // Check if advertising contain BleUart service
  if ( Bluefruit.Scanner.checkReportForService(report, clientUart) ){
    Serial.print("BLE UART service detected. Connecting ... ");

    // Connect to device with bleuart service in advertising
    Bluefruit.Central.connect(report);
  }
  else{      
    // For Softdevice v6: after received a report, scanner will be paused
    // We need to call Scanner resume() to continue scanning
    Bluefruit.Scanner.resume();
  }
}

void connect_callback(uint16_t conn_handle){
  Serial.println("Connected");
  
  Serial.print("Discovering BLE Uart Service ... ");
  if ( clientUart.discover(conn_handle) ){
    Serial.println("Found it");

    Serial.println("Enable TXD's notify");
    clientUart.enableTXD();

    Serial.println("Ready to receive from peripheral");
  }
  else{
    Serial.println("Found NONE");
    
    // disconnect since we couldn't find bleuart service
    Bluefruit.disconnect(conn_handle);
  }  
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason){
  (void) conn_handle;
  (void) reason;
  
  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

void bleuart_rx_callback(BLEClientUart& uart_svc){  
  /*uart_svc.read(robotMsg, 5);

  Serial.print("[RX]: ");
  Serial.println((char*) robotMsg);

  robotBatt = robotMsg[0];*/
} 

void sendControls() {
  if ( Bluefruit.Central.connected() ) {
    if ( clientUart.discovered() ) {
      //clientUart.print((char*) controlMsg);
      clientUart.write(controlMsg, sizeof(controlMsg));
    }
  }
}

