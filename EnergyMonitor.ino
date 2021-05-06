void EnergyMon()
{
	eMon.calcVI(20, 2000);									 // Calculate all. No.of half wavelengths (crossings), time-out
	//eMon.serialprint();										 // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

	RP = eMon.realPower;									 //extract Real Power into variable
	AP = eMon.apparentPower;								 //extract Apparent Power into variable
	pF = eMon.powerFactor;								 //extract Power Factor into Variable
	Vrms = eMon.Vrms;									 //extract Vrms into Variable
	Irms = eMon.Irms;									 //extract Irms into Variable
}
