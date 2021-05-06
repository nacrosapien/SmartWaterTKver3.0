//wake screen from sleep
void WakeOLED_Panel()
{
	if ((OLEDPowerStatus == "PowerOFF") && (digitalRead(ResetButton) == HIGH))
	{
        OLEDPowerStatus = "PowerON";
        delay(10);

        
	}
}






//reset alarm/trip state
void ResetAlarm_Panel()
{
    if (((Voltage != "OK") || (Current != "OK") || (TripStatusVolt != "OK") || (TripStatusAmp != "OK")) && (digitalRead(ResetButton) == HIGH) && (OLEDPowerStatus = "PowerON"))
    {
        if ((TripStatusVolt != "OK") || (TripStatusAmp != "OK"))
        {
            TripStatusVolt = "OK"; TripStatusAmp = "OK";


           
        }

        else if ((Voltage != "OK") || (Current != "OK"))
        {
            Voltage = "OK"; Current = "OK";


        }

        PreviousTime_OLEDTimeOut = CurrentTime_OLED_PM;

    }
    else if ((Voltage == "OK") && (Current == "OK") && (digitalRead(ResetButton) == HIGH))
    {
        PreviousTime_OLEDTimeOut = CurrentTime_OLED_PM;
    }
    else if (((TripStatusVolt != "OK") || (TripStatusAmp != "OK")) && (Firebase_Reset == "Reset"))
    {
        TripStatusVolt = "OK";
        TripStatusAmp = "OK";
        Firebase_Reset = "OK";
        
    }
}






//Panel LED indicator
void LEDStatus_Panel()
{
    if ((Voltage != "OK") || (Current != "OK"))
    {
        unsigned long CurrentTime_LEDStatus_Panel = millis();
        if (CurrentTime_LEDStatus_Panel - PreviousTime_StabilityTimer_LED >= Event_timer_StabilityTimer_LED)
        {
        
            digitalWrite(StatusLED, HIGH);
            PreviousTime_StabilityTimer_LED = CurrentTime_LEDStatus_Panel;
        }
            
    }
    else if ((Voltage == "OK") || (Current == "OK"))
    {
        unsigned long CurrentTime_LEDStatus_Panel = millis();
        if (CurrentTime_LEDStatus_Panel - PreviousTime_StabilityTimer_LED >= Event_timer_StabilityTimer_LED)
        {

            digitalWrite(StatusLED, LOW);
            PreviousTime_StabilityTimer_LED = CurrentTime_LEDStatus_Panel;
        }

    }
}







