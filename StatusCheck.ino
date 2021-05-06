






void StatusChecker_FloatSwitch()
{
	


	
	//tank high level
	if ((digitalRead(HL_CutOut) == HIGH) && (digitalRead(LL_CutIn) == HIGH))
	{
		unsigned long CurrentTime_StatusChecker = millis();
		if (CurrentTime_StatusChecker - PreviousTime_StabilityTimer_FloatSwitch >= Event_timer_StabilityTimer_FloatSwitch)
		{
			TankLevel = "FULL";

			PreviousTime_StabilityTimer_FloatSwitch = CurrentTime_StatusChecker;
		}
	}

	//tank low level
	else if ((digitalRead(HL_CutOut) == LOW) && (digitalRead(LL_CutIn) == LOW))
	{
		unsigned long CurrentTime_StatusChecker = millis();
		if (CurrentTime_StatusChecker - PreviousTime_StabilityTimer_FloatSwitch >= Event_timer_StabilityTimer_FloatSwitch)
		{
			TankLevel = "LOW";
			unsigned long CurrentTime_LowLevelTimeOut = millis();

			//tank low level time out- tank @ low level for too long
			if (CurrentTime_LowLevelTimeOut - PreviousTime_LowLevelTimeOut >= Event_timer_LowLevelTimeOut)
			{
				TankLevel = "LOW_TimeOut";


				PreviousTime_LowLevelTimeOut = CurrentTime_LowLevelTimeOut;
			}

			PreviousTime_StabilityTimer_FloatSwitch = CurrentTime_StatusChecker;
		}


	}

	//abnormal float switch signal
	else if ((digitalRead(HL_CutOut) == LOW) && (digitalRead(LL_CutIn) == HIGH))
	{
		unsigned long CurrentTime_StatusChecker = millis();
		if (CurrentTime_StatusChecker - PreviousTime_StabilityTimer_FloatSwitch >= Event_timer_StabilityTimer_FloatSwitch)
		{
			TankLevel = "Float_Error";

			PreviousTime_StabilityTimer_FloatSwitch = CurrentTime_StatusChecker;
		}
	}
}





















void PumpRunStatus()
{

	if (digitalRead(PumpRelay) == HIGH)
	{
		PumpRelayStatus = "Relay_ON";
	}
	else if (digitalRead(PumpRelay) == LOW)
	{
		PumpRelayStatus = "Relay_OFF";
	}

}

















void StatusChecker_eMon_Voltage()
{


	//High voltage
	if (Vrms > HighVoltage)
	{
		//Serial.print("HV Detection");
		unsigned long CurrentTime_StatusChecker_eMon_Voltage = millis();
		if (CurrentTime_StatusChecker_eMon_Voltage - PreviousTime_StabilityTimer_eMon_Voltage >= Event_timer_StabilityTimer_eMon_Voltage)
		{
			
			Voltage = "High";
			
			unsigned long CurrentTime_StatusChecker_eMon_Voltage_TimeOut = millis();

			PreviousTime_StabilityTimer_eMon_Voltage = CurrentTime_StatusChecker_eMon_Voltage;

			//high voltage timeout 
			if (CurrentTime_StatusChecker_eMon_Voltage_TimeOut - PreviousTime_VoltageTimeOut >= Event_timer_VoltageTimeOut)
			{
				Voltage_TimeOut = "TimeOut";

				PreviousTime_VoltageTimeOut = CurrentTime_StatusChecker_eMon_Voltage_TimeOut;
			}
		}
	}
	//under voltage
	else if (Vrms < LowVoltage)
	{
		//Serial.print("LV Detection");
		unsigned long CurrentTime_StatusChecker_eMon_Voltage = millis();
		if (CurrentTime_StatusChecker_eMon_Voltage - PreviousTime_StabilityTimer_eMon_Voltage >= Event_timer_StabilityTimer_eMon_Voltage)
		{
			
			Voltage = "Low";
			
			unsigned long CurrentTime_StatusChecker_eMon_Voltage_TimeOut = millis();

			PreviousTime_StabilityTimer_eMon_Voltage = CurrentTime_StatusChecker_eMon_Voltage;

			//under voltage timeout 
			if (CurrentTime_StatusChecker_eMon_Voltage_TimeOut - PreviousTime_VoltageTimeOut >= Event_timer_VoltageTimeOut)
			{
				Voltage_TimeOut = "TimeOut";

				PreviousTime_VoltageTimeOut = CurrentTime_StatusChecker_eMon_Voltage_TimeOut;
			}


		}
	}
}








void StatusChecker_eMon_Current()
{

	//High load
	if (Irms > HighCurrent)
	{
		//Serial.print("HC Detection");
		unsigned long CurrentTime_StatusChecker_eMon_Current = millis();
		if (CurrentTime_StatusChecker_eMon_Current - PreviousTime_StabilityTimer_eMon_Current >= Event_timer_StabilityTimer_eMon_Current)
		{
			
			Current = "High";
			
			unsigned long CurrentTime_StatusChecker_eMon_Current_TimeOut = millis();

			PreviousTime_StabilityTimer_eMon_Current = CurrentTime_StatusChecker_eMon_Current;

			//High load time out
			if (CurrentTime_StatusChecker_eMon_Current_TimeOut - PreviousTime_CurrentTimeOut >= Event_timer_CurrentTimeOut)
			{
				Current_TimeOut = "TimeOut";

				PreviousTime_CurrentTimeOut = CurrentTime_StatusChecker_eMon_Current_TimeOut;
			}
		}
	}
	//Low Load
	else if (Irms > LowCurrent)
	{
		//Serial.print("LC Detection");
		unsigned long CurrentTime_StatusChecker_eMon_Current = millis();
		if (CurrentTime_StatusChecker_eMon_Current - PreviousTime_StabilityTimer_eMon_Current >= Event_timer_StabilityTimer_eMon_Current)
		{
			
			Current = "Low";
			
			unsigned long CurrentTime_StatusChecker_eMon_Current_TimeOut = millis();

			PreviousTime_StabilityTimer_eMon_Current = CurrentTime_StatusChecker_eMon_Current;


			//Low load time out
			if (CurrentTime_StatusChecker_eMon_Current_TimeOut - PreviousTime_CurrentTimeOut >= Event_timer_CurrentTimeOut)
			{
				Current_TimeOut = "TimeOut";

				PreviousTime_CurrentTimeOut = CurrentTime_StatusChecker_eMon_Current_TimeOut;
			}
		}
	}

}





void StatusChecker_eMon_Trip()
{


	if ((Vrms > HighVoltage_Trip) || (Vrms < LowVoltage_Trip))
	{
		//Serial.print("Vtrip Detection");
		unsigned long CurrentTime_StatusChecker_eMon_Trip = millis();
		if (CurrentTime_StatusChecker_eMon_Trip - PreviousTime_StabilityTimer_eMon_VoltageTrip >= Event_timer_StabilityTimer_eMon_VoltageTrip)
		{
			
			TripStatusVolt = "Trip";
			Firebase_Reset = "Trip";
			

			PreviousTime_StabilityTimer_eMon_VoltageTrip = CurrentTime_StatusChecker_eMon_Trip;
		}
	}
	else if ((Irms < LowCurrent_Trip) || (Irms > HighCurrent_Trip))
	{
		//Serial.print("Ctrip Detection");
		unsigned long CurrentTime_StatusChecker_eMon_Trip = millis();
		if (CurrentTime_StatusChecker_eMon_Trip - PreviousTime_StabilityTimer_eMon_CurrentTrip >= Event_timer_StabilityTimer_eMon_CurrentTrip)
		{
			
			TripStatusAmp = "Trip";
			Firebase_Reset = "Trip";
			

			PreviousTime_StabilityTimer_eMon_CurrentTrip = CurrentTime_StatusChecker_eMon_Trip;
		}
	}
}


