
void TankLvLControl()
{


	//stop tank filling when full
	if ((TankLevel == "FULL") && (PumpRelayStatus == "Relay_ON"))
	{
		digitalWrite(PumpRelay, LOW);
	}
	//fill tank when level is low
	else if ((TankLevel == "LOW") && (PumpRelayStatus == "Relay_OFF") && (WellLevel == "OK") && (Voltage_TimeOut == "OK") && (Current_TimeOut == "OK") && (TripStatusAmp == "OK") && (TripStatusVolt = "OK"))
	{
		digitalWrite(PumpRelay, HIGH);
	}
	//low tank level timeout signal
	else if ((TankLevel == "LOW_TimeOut") && (PumpRelayStatus == "Relay_ON"))
	{
		WellLevel = "LOW";
		digitalWrite(PumpRelay, LOW);

			unsigned long CurrentTime_TankLvLControl = millis();
			if (CurrentTime_TankLvLControl - PreviousTime_WellLevel_LOW_TimeOut >= Event_timer_WellLevel_LOW_TimeOut)
			{
				WellLevel = "OK";

					PreviousTime_WellLevel_LOW_TimeOut = CurrentTime_TankLvLControl;
			}
	}
	else if ((TankLevel == "LOW_TimeOut") && (PumpRelayStatus == "Relay_OFF"))
	{
		PumpRelayStatus = "Controller_Error";
	}
}






void PumpeMonControl()
{
	
	
	//if voltage/Current timeout signal received, pump should stop
	if ((Voltage_TimeOut == "TimeOut") && (PumpRelayStatus == "Relay_ON"))
	{
		digitalWrite(PumpRelay, LOW);

		unsigned long CurrentTime_PumpeMonControl_Voltage = millis();
		if (CurrentTime_PumpeMonControl_Voltage - PreviousTime_Voltage_TimeOut >= Event_timer_Voltage_TimeOut)
		{
			Voltage_TimeOut = "OK";

			PreviousTime_Voltage_TimeOut = CurrentTime_PumpeMonControl_Voltage;
		}

	}
	else if ((Current_TimeOut == "TimeOut") && (PumpRelayStatus == "Relay_ON"))
	{
		digitalWrite(PumpRelay, LOW);

		unsigned long CurrentTime_PumpeMonControl_Current = millis();
		if (CurrentTime_PumpeMonControl_Current - PreviousTime_Current_TimeOut >= Event_timer_Current_TimeOut)
		{
			Current_TimeOut = "OK";

			PreviousTime_Current_TimeOut = CurrentTime_PumpeMonControl_Current;
		}

	}
	// pump to trip if extreme high/low voltage/Current detected.
	if ((TripStatusVolt == "Trip") || (TripStatusAmp == "Trip") )
	{
		digitalWrite(PumpRelay, LOW);
	}
}





