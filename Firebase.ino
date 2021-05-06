void swTK_tx_FireBase()
{


	json.set("/Vrms", Vrms);
	json.set("/Irms", Irms);
	json.set("/PowerFactor", pF);
	json.set("/ApparentPower", AP);
	json.set("/RealPower", RP);

	json.set("/TankLevel", TankLevel);
	json.set("/WellLevel", WellLevel);
	json.set("Pump Status", PumpRelayStatus);
	json.set("OLED", OLEDPowerStatus);
	json.set("Voltage", Voltage);
	json.set("Current", Current);
	json.set("VoltageTimeOut", Voltage_TimeOut);
	json.set("CurrentTimeOut", Current_TimeOut);
	json.set("/TripStatusAmp", TripStatusAmp);
	json.set("/TripStatusVolt", TripStatusVolt);
	Firebase.updateNode(firebaseData, "/SWTKv2", json);

	//json.set("/FirebaseReset", Firebase_Reset);
	String path = "/SWTKv2";
	if (Firebase.getString(firebaseData, path + "/FirebaseReset"))
	{
		if (firebaseData.stringData() == "Reset")
		{
			Firebase_Reset = "Reset";
		}
	}
	if (Firebase.getString(firebaseData, path + "/OTAMode"))
	{
		if (firebaseData.stringData() == "ON")
		{
			OTAmode = "ON";
		}
		else if (firebaseData.stringData() == "OFF")
		{
			OTAmode = "OFF";
		}

	}
}








