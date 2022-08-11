//This example demonstrates the ESP RainMaker with a standard Switch device.
#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

#define DEFAULT_POWER_MODE true
const char *service_name = "PROV_1234";
const char *pop = "abcd1234";

static int gpio_0 = 0;
static int gpio_1 = 13;
static int gpio_2 = 14;
static int gpio_3 = 26;
static int gpio_4 = 33;
static int gpio_switch1 = 4;
static int gpio_switch2 = 5;
static int gpio_switch3 = 21;
static int gpio_switch4 = 22;

/* Variable for reading pin status*/
bool switch_state = true;
bool switch1_state = true;
bool switch2_state = true;
bool switch3_state = true;
bool switch4_state = true;

//The framework provides some standard device types like switch, lightbulb, fan, temperaturesensor.
static Switch my_switch1("Switch1", &gpio_switch1);
static Switch my_switch2("Switch2", &gpio_switch2);
static Switch my_switch3("Switch3", &gpio_switch3);
static Switch my_switch4("Switch4", &gpio_switch4);

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32S2
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
        printQR(service_name, pop, "softap");
#else
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#endif         
        break;
        default:;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(param_name, "Power") == 0) {

    if (strcmp(device_name,"Switch1") == 0){
            Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
            switch_state = val.val.b;
            (switch_state == false) ? digitalWrite(gpio_switch1, LOW) : digitalWrite(gpio_switch1, HIGH);
            param->updateAndReport(val);
    }
    if (strcmp(device_name,"Switch2") == 0){
            Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
            switch_state = val.val.b;
            (switch_state == false) ? digitalWrite(gpio_switch2, LOW) : digitalWrite(gpio_switch2, HIGH);
            param->updateAndReport(val);

    }
    if (strcmp(device_name,"Switch3") == 0){
            Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
            switch_state = val.val.b;
            (switch_state == false) ? digitalWrite(gpio_switch3, LOW) : digitalWrite(gpio_switch3, HIGH);
            param->updateAndReport(val);

    }
    if (strcmp(device_name,"Switch4") == 0){
            Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
            switch_state = val.val.b;
            (switch_state == false) ? digitalWrite(gpio_switch4, LOW) : digitalWrite(gpio_switch4, HIGH);
            param->updateAndReport(val);

    }
  }
}

/*void write_callback1(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        Serial.printf("CALLBACK1");
        switch1_state = val.val.b;
        (switch1_state == false) ? digitalWrite(gpio_switch1, LOW) : digitalWrite(gpio_switch1, HIGH);
        param->updateAndReport(val);
    }
}

void write_callback2(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        Serial.printf("CALLBACK2");
        switch2_state = val.val.b;
        (switch2_state == false) ? digitalWrite(gpio_switch2, LOW) : digitalWrite(gpio_switch2, HIGH);
        param->updateAndReport(val);
    }
}

void write_callback3(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        Serial.printf("CALLBACK3");
        switch3_state = val.val.b;
        (switch3_state == false) ? digitalWrite(gpio_switch3, LOW) : digitalWrite(gpio_switch3, HIGH);
        param->updateAndReport(val);
    }
}
*/
void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
    pinMode(gpio_1, INPUT);
    pinMode(gpio_2, INPUT);
    pinMode(gpio_3, INPUT);
    pinMode(gpio_4, INPUT);
    
    pinMode(gpio_switch1, OUTPUT);
    pinMode(gpio_switch2, OUTPUT);
    pinMode(gpio_switch3, OUTPUT);
    pinMode(gpio_switch4, OUTPUT);

      
    digitalWrite(gpio_switch1, DEFAULT_POWER_MODE);
    digitalWrite(gpio_switch2, DEFAULT_POWER_MODE);
    digitalWrite(gpio_switch3, DEFAULT_POWER_MODE);
    digitalWrite(gpio_switch4, DEFAULT_POWER_MODE);

    Node my_node1;    
    my_node1 = RMaker.initNode("ESP RainMaker Node1");

    //Standard switch device
    my_switch1.addCb(write_callback);
    my_switch2.addCb(write_callback);
    my_switch3.addCb(write_callback);
    my_switch4.addCb(write_callback);
    
    //Add switch device to the node   
    my_node1.addDevice(my_switch1);
    my_node1.addDevice(my_switch2);
    my_node1.addDevice(my_switch3);
    my_node1.addDevice(my_switch4);

    //This is optional 
    RMaker.enableOTA(OTA_USING_PARAMS);
    //If you want to enable scheduling, set time zone for your region using setTimeZone(). 
    //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
    // RMaker.setTimeZone("Asia/Shanghai");
    // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
    RMaker.enableTZService();

    RMaker.enableSchedule();

    RMaker.start();

    WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32S2
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#else
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#endif
}

void loop()
{
    if(digitalRead(gpio_0) == LOW) { //Push button pressed

        // Key debounce handling
        delay(100);
        int startTime = millis();
        while(digitalRead(gpio_0) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // If key pressed for more than 10secs, reset all
          Serial.printf("Reset to factory.\n");
          RMakerFactoryReset(2);
      
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Reset Wi-Fi.\n");
          // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
          RMakerWiFiReset(2);
       
        } 
        
    }  
      
/*      if(digitalRead(gpio_1) == HIGH) { //Push button pressed   
        switch1_state = !switch1_state;
        Serial.printf("Toggle State1 to %s.\n", switch1_state ? "true" : "false");
        my_switch1.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, switch1_state);
        (switch1_state == false) ? digitalWrite(gpio_switch1, LOW) : digitalWrite(gpio_switch1, HIGH);
        delay(100);
      }
      
      if(digitalRead(gpio_2) == HIGH) { //Push button pressed
        switch2_state = !switch2_state;
        Serial.printf("Toggle State2 to %s.\n", switch2_state ? "true" : "false");
        my_switch2.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, switch2_state);
        (switch2_state == false) ? digitalWrite(gpio_switch2, LOW) : digitalWrite(gpio_switch2, HIGH);
        delay(100);
      }
      
      if(digitalRead(gpio_3) == HIGH) { //Push button pressed
        switch3_state = !switch3_state;
        Serial.printf("Toggle State3 to %s.\n", switch3_state ? "true" : "false");
        my_switch3.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, switch3_state);
        (switch3_state == false) ? digitalWrite(gpio_switch3, LOW) : digitalWrite(gpio_switch3, HIGH);
        delay(100);
      }
     
      if(digitalRead(gpio_4) == HIGH) { //Push button pressed
        switch4_state = !switch4_state;
        Serial.printf("Toggle State4 to %s.\n", switch4_state ? "true" : "false");
        my_switch4.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, switch4_state);
        (switch4_state == false) ? digitalWrite(gpio_switch4, LOW) : digitalWrite(gpio_switch4, HIGH);
        delay(100);
      }
      */
    
    delay(100);
}
