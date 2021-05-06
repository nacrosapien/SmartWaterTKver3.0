// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       SmartWaterTKver3.0.ino
    Created:	5/5/2021 13:47:01
    Author:     DESKTOP-3RRLO0F\Camshaft
*/





#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <credentials.h>
#include "EmonLib.h"             
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "FirebaseESP32.h"




const char* host = "esp32-SmartWaterTKver3.0";
const char* ssid = mySSID;
const char* password = myPASSWORD;

WebServer server(80);









//////////////// 
///Login page///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* loginIndex =
"<form name='loginForm'>"
"<table width='20%' bgcolor='A09F9F' align='center'>"
"<tr>"
"<td colspan=2>"
"<center><font size=4><b>ESP32 Login Page</b></font></center>"
"<br>"
"</td>"
"<br>"
"<br>"
"</tr>"
"<tr>"
"<td>Username:</td>"
"<td><input type='text' size=25 name='userid'><br></td>"
"</tr>"
"<br>"
"<br>"
"<tr>"
"<td>Password:</td>"
"<td><input type='Password' size=25 name='pwd'><br></td>"
"<br>"
"<br>"
"</tr>"
"<tr>"
"<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
"</tr>"
"</table>"
"</form>"
"<script>"
"function check(form)"
"{"
"if(form.userid.value=='admin' && form.pwd.value=='admin')"
"{"
"window.open('/serverIndex')"
"}"
"else"
"{"
" alert('Error Password or Username')/*displays error message*/"
"}"
"}"
"</script>";

/*
 * Server Index Page
 */

const char* serverIndex =
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<input type='file' name='update'>"
"<input type='submit' value='Update'>"
"</form>"
"<div id='prg'>progress: 0%</div>"
"<script>"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
" $.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('progress: ' + Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('success!')"
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////
///Timer definition///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned long Event_timer_StabilityTimer_FloatSwitch = 60000;                     //1min
const unsigned long Event_timer_LowLevelTimeOut = 300000;                               //5min
const unsigned long Event_timer_StabilityTimer_eMon_Voltage = 30000;                    //30sec
const unsigned long Event_timer_StabilityTimer_eMon_Current = 30000;                    //30sec
const unsigned long Event_timer_StabilityTimer_eMon_VoltageTrip = 30000;                //30sec
const unsigned long Event_timer_StabilityTimer_eMon_CurrentTrip = 30000;                //30sec
const unsigned long Event_timer_VoltageTimeOut = 150000;                                //2.5min
const unsigned long Event_timer_CurrentTimeOut = 150000;                                //2.5min
const unsigned long Event_timer_OLEDTimeOut = 180000;                                   //3min
const unsigned long Event_timer_StabilityTimer_LED = 5000;                              //5sec
const unsigned long Event_timer_WellLevel_LOW_TimeOut = 1800000;                        //30min
const unsigned long Event_timer_Voltage_TimeOut = 900000;                               //15min
const unsigned long Event_timer_Current_TimeOut = 900000;                               //15min


unsigned long PreviousTime_StabilityTimer_FloatSwitch = 0;
unsigned long PreviousTime_LowLevelTimeOut = 0;
unsigned long PreviousTime_StabilityTimer_eMon_Voltage = 0;
unsigned long PreviousTime_StabilityTimer_eMon_Current = 0;
unsigned long PreviousTime_StabilityTimer_eMon_VoltageTrip = 0;
unsigned long PreviousTime_StabilityTimer_eMon_CurrentTrip = 0;
unsigned long PreviousTime_VoltageTimeOut = 0;
unsigned long PreviousTime_CurrentTimeOut = 0;
unsigned long PreviousTime_OLEDTimeOut = 0;
unsigned long PreviousTime_StabilityTimer_LED = 0;
unsigned long PreviousTime_WellLevel_LOW_TimeOut = 0;
unsigned long PreviousTime_Voltage_TimeOut = 0;
unsigned long PreviousTime_Current_TimeOut = 0;

unsigned long CurrentTime_OLED_PM = 0;                  //OLED time out counter

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////
///Energy monitor definition///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EnergyMonitor eMon;             //Create an instance

int VoltageCal = 234.26;       //Voltage calibration
int AmpereCal = 111.1;         //Ampere calibration

int HighVoltage = 245;         //Set-point
int HighVoltage_Trip = 250;    //Set-point
int LowVoltage = 210;          //Set-point
int LowVoltage_Trip = 205;     //Set-point 

int HighCurrent = 5;            //Set-point 
int HighCurrent_Trip = 6;       //Set-point 
int LowCurrent = 0.9;           //Set-point 
int LowCurrent_Trip = 0.8;      //Set-point 

float RP = 0;
float AP = 0;
float pF = 0;
float Vrms = 0;
float Irms = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////
///FloatSwitch & PumpRelay definition/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HL_CutOut 15
#define LL_CutIn 2
#define PumpRelay 13

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////
///StatusChecker definition///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String TankLevel = "FULL";
String Voltage = "OK";
String Voltage_TimeOut = "OK";
String Current = "OK";
String Current_TimeOut = "OK";
String PumpRelayStatus = "Relay_OFF";
String OLEDPowerStatus = "PowerON";
String WellLevel = "OK";
String TripStatusAmp = "OK";
String TripStatusVolt = "OK";
String Firebase_Reset = "OK";
String OTAmode = "OTAOFF";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////
///OLED definition///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET    -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////
///Panel definition///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define StatusLED 25
#define ResetButton 4

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////
///Task priority///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//level 0 lowest priority - level 3 highest priority////

const int OTA_Task = 3;
const int eMon_Task = 1;
const int StatChk_Task = 2;
const int Panel_Task = 2;
const int PPAI_Task = 1;
const int OLED_Task = 2;
const int OLEDsub_Task = 1;
const int Loop_Task = 1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////
///Firebase definition///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FIREBASE_HOST "https://swtk-3c4ac-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "vwv3mNBU9vbFFlPiKxBVxNYfhJ5sz6ugQA7fF2gG"

FirebaseData firebaseData;
FirebaseJson json;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////















void setup(void)
{

    Serial.begin(115200);

    // Connect to WiFi network
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());





    ////////////////
    ///OTA Server///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*use mdns for host name resolution*/
    if (!MDNS.begin(host)) { //http://esp32.local
        Serial.println("Error setting up MDNS responder!");
        while (1) {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
    /*return index page which is stored in serverIndex */
    server.on("/", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", loginIndex);
        });
    server.on("/serverIndex", HTTP_GET, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", serverIndex);
        });
    /*handling uploading firmware file */
    server.on("/update", HTTP_POST, []() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        ESP.restart();
        }, []() {
            HTTPUpload& upload = server.upload();
            if (upload.status == UPLOAD_FILE_START) {
                Serial.printf("Update: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_WRITE) {
                /* flashing firmware to ESP*/
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_END) {
                if (Update.end(true)) { //true to set the size to the current progress
                    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                }
                else {
                    Update.printError(Serial);
                }
            }
        });
    server.begin();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





    /////////////////////////
    ///EnergyMonitor Setup///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Serial.println("Initializing eMon");
    eMon.voltage(34, VoltageCal, 1.7);  // Voltage: input pin, calibration, phase_shift
    eMon.current(35, AmpereCal);        // Current: input pin, calibration.

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////////////////
    ///FloatSwitch, PumpRelay Setup & ISR/// 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Serial.println("Initializing Float & Pump relay");
    pinMode(HL_CutOut, INPUT_PULLUP);
    pinMode(LL_CutIn, INPUT_PULLUP);
    pinMode(PumpRelay, OUTPUT);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////
    ///OLED setup///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Serial.println("Initializing OLED");
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {

        Serial.println(F("SSD1306 address failed"));
        for (;;); // Don't proceed, loop forever
    }

    display.clearDisplay();

    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(1, 20);            // Start at top-left corner
    display.println("SmartWTK ver3.0 Beta");

    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(1, 35);            // Start at top-left corner
    display.println("Initializing...");

    display.display();
    delay(2500);
    display.clearDisplay();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////
    ///Firebase setup///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Serial.print("Initializing Firebase");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); Serial.print("1 ");
    Firebase.reconnectWiFi(true);

    //Set database read timeout to 30 sec (max 15 minutes)
    Firebase.setReadTimeout(firebaseData, 1000 * 30);
    //tiny, small, medium, large and unlimited.
    //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
    Firebase.setwriteSizeLimit(firebaseData, "tiny");


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   





    Serial.println("Starting loop");

}

















void loop(void) {

    Serial.println("LOOP - SWTKv3.0_Beta5");


   // if (OTAmode == "ON")
    //{
        Serial.println("OTA ON");
        server.handleClient();
        delay(10);

    //}
    //else
    //{
        Serial.println("OTAOFF");

        



        delay(10);
        WakeOLED_Panel();
        ResetAlarm_Panel();
        ///Energy Monitor
        delay(10);
        EnergyMon();
        delay(10);
        OLED_PM();

        WakeOLED_Panel();
        ResetAlarm_Panel();
        /// Status checking
        delay(10);
        StatusChecker_FloatSwitch();
        delay(10);
        PumpRunStatus();
        delay(10);
        StatusChecker_eMon_Voltage();
        delay(10);
        StatusChecker_eMon_Current();
        delay(10);
        StatusChecker_eMon_Trip();

        WakeOLED_Panel();
        ResetAlarm_Panel();
        OLED_PM();
        ///Panel 
        delay(10);
        LEDStatus_Panel();

        EnergyMon();
        ///PumpAi
        delay(10);
        TankLvLControl();
        delay(10);
        PumpeMonControl();
        delay(10);
        OLED_PM();
        delay(10);


        Serial.println();
        Serial.print("Tank Level - "); Serial.print(TankLevel); Serial.print(" || Pump - "); Serial.println(PumpRelayStatus);
        Serial.print("Well Level - "); Serial.print(WellLevel); Serial.print(" || FB Reset - "); Serial.println(Firebase_Reset);
        Serial.println();
        Serial.print("volt - "); Serial.print(Voltage); Serial.print(" || amps - "); Serial.println(Current);
        Serial.print("Abnormal Volt - "); Serial.print(Voltage_TimeOut); Serial.print(" || Abnormal Amp - "); Serial.println(Current_TimeOut);
        Serial.print("Volt Trip - "); Serial.print(TripStatusVolt); Serial.print(" || Amp Trip - "); Serial.println(TripStatusAmp);
        Serial.println();
        Serial.print("Vrms - "); Serial.print(Vrms, 2); Serial.print(" || Irms - "); Serial.println(Irms, 2);
        Serial.print("OLED state - "); Serial.println(OLEDPowerStatus);
        Serial.println();
        Serial.println();
    //}










    Serial.print("Firebase upload - ");
    swTK_tx_FireBase();
    

}
