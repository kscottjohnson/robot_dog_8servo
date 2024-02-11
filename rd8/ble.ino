// Bluetooh Low Energy communication functions

void startBleAdv(){
  Bluefruit.begin(1, 0);
  Bluefruit.Periph.setConnectCallback(prph_connect_callback);
  Bluefruit.Periph.setDisconnectCallback(prph_disconnect_callback);
  Bluefruit.setTxPower(4); 
  bleuart.begin();
  bleuart.setRxCallback(prph_bleuart_rx_callback);
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);        // 0 = Don't stop advertising after n seconds  
}

void prph_connect_callback(uint16_t conn_handle)
{
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char peer_name[32] = { 0 };
  connection->getPeerName(peer_name, sizeof(peer_name));

  Serial.print("[Prph] Connected to ");
  Serial.println(peer_name);

  connectedMs = millis();
}

void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.println();
  Serial.println("[Prph] Disconnected");
}

void prph_bleuart_rx_callback(uint16_t conn_handle){
  (void) conn_handle;
  
  bleuart.read(controlMsg, 6);

  //Serial.print("[Prph] RX: ");
  //Serial.println((char*) controlMsg);  

  lx = controlMsg[0];
  ly = controlMsg[1];
  rx = controlMsg[2];
  ry = controlMsg[3];

  buttonAR = controlMsg[4] & 1;
  buttonBR = controlMsg[4] & 2;
  buttonCR = controlMsg[4] & 4;
  buttonL = controlMsg[4] & 8;
  buttonR = controlMsg[4] & 16;

  mode = controlMsg[5];

}
