

void OLED_PM()
{
    // To switch display back on
    if (OLEDPowerStatus == "PowerON")
    {

        display.ssd1306_command(SSD1306_DISPLAYON);                   
        display.clearDisplay();

        OLED_StatusScreen_Face();
        OLED_StatusScreen_Amp();
        OLED_StatusScreen_Volt();
        OLED_StatusScreen_PumpState();
        OLED_StatusScreen_WellLevel();
        OLED_OutputScreen();

        display.display();
        delay(100);

        CurrentTime_OLED_PM = millis();
        if (CurrentTime_OLED_PM - PreviousTime_OLEDTimeOut >= Event_timer_OLEDTimeOut)
        {
            OLEDPowerStatus = "PowerOFF";
            delay(25);
            PreviousTime_OLEDTimeOut = CurrentTime_OLED_PM;
        }

    }
    // To switch display off
    else if (OLEDPowerStatus == "PowerOFF")
    {
        display.ssd1306_command(SSD1306_DISPLAYOFF);
    }                


}














void OLED_StatusScreen_Face()
{

    display.fillRect(25, 1, 1, 15, WHITE);  //solid bar seperator

    if ((TripStatusAmp == "OK") && (TripStatusVolt == "OK") && (WellLevel == "OK"))
    {
        // smiley face to indicate All system ok.



        display.drawCircle(13, 8, 8, WHITE);    //big circle
        display.fillCircle(9, 4, 1, WHITE);     //left eye
        display.fillCircle(17, 4, 1, WHITE);    //right eye

        display.drawPixel(9, 10, WHITE);       //smiley mouth
        display.drawPixel(10, 11, WHITE);
        display.drawPixel(11, 11, WHITE);
        display.drawPixel(12, 12, WHITE);
        display.drawPixel(13, 12, WHITE);
        display.drawPixel(14, 12, WHITE);
        display.drawPixel(15, 11, WHITE);
        display.drawPixel(16, 11, WHITE);
        display.drawPixel(17, 10, WHITE);


    }

    else
    {

        // sad face to indicate system abnormal



        display.drawCircle(13, 8, 8, WHITE);    //big circle
        display.fillCircle(9, 4, 1, WHITE);     //left eye
        display.fillCircle(17, 4, 1, WHITE);    //right eye

        display.drawPixel(9, 13, WHITE);       //sad mouth
        display.drawPixel(10, 12, WHITE);
        display.drawPixel(11, 12, WHITE);
        display.drawPixel(12, 11, WHITE);
        display.drawPixel(13, 11, WHITE);
        display.drawPixel(14, 11, WHITE);
        display.drawPixel(15, 12, WHITE);
        display.drawPixel(16, 12, WHITE);
        display.drawPixel(17, 13, WHITE);


    }
}










void OLED_StatusScreen_Amp()
{

    display.fillRect(50, 1, 1, 15, WHITE);  //solid bar seperator
    //display.fillRect(26, 15, 1, 15, WHITE);  //solid bottom bar seperator

    if (Current == "High")
    {



        //letter I
        display.fillRect(28, 2, 9, 2, WHITE);
        display.fillRect(31, 5, 3, 7, WHITE);
        display.fillRect(28, 12, 9, 2, WHITE);

        //arrow up
        display.fillRect(43, 3, 2, 11, WHITE);
        display.drawPixel(40, 7, WHITE); display.drawPixel(47, 7, WHITE);       //Arrow head
        display.drawPixel(41, 6, WHITE); display.drawPixel(46, 6, WHITE);
        display.drawPixel(41, 5, WHITE); display.drawPixel(46, 5, WHITE);
        display.drawPixel(42, 5, WHITE); display.drawPixel(45, 5, WHITE);
        display.drawPixel(42, 4, WHITE); display.drawPixel(45, 4, WHITE);



    }

    else if (Current == "Low")
    {



        //letter I
        display.fillRect(28, 2, 9, 2, WHITE);
        display.fillRect(31, 5, 3, 7, WHITE);
        display.fillRect(28, 12, 9, 2, WHITE);

        //arrow down
        display.fillRect(43, 3, 2, 11, WHITE);
        display.drawPixel(40, 9, WHITE); display.drawPixel(47, 9, WHITE);       //Arrow head
        display.drawPixel(41, 10, WHITE); display.drawPixel(46, 10, WHITE);
        display.drawPixel(41, 11, WHITE); display.drawPixel(46, 11, WHITE);
        display.drawPixel(42, 11, WHITE); display.drawPixel(45, 11, WHITE);
        display.drawPixel(42, 12, WHITE); display.drawPixel(45, 12, WHITE);



    }
}














void OLED_StatusScreen_Volt()
{

    display.fillRect(75, 1, 1, 15, WHITE);  //solid bar seperator
    //display.fillRect(51, 15, 1, 15, WHITE);  //solid bottom bar seperator

    if (Voltage == "High")
    {



        //letter V
        display.fillRect(52, 2, 1, 4, WHITE); display.fillRect(63, 2, 1, 4, WHITE);
        display.fillRect(53, 4, 1, 4, WHITE); display.fillRect(62, 4, 1, 4, WHITE);
        display.fillRect(54, 6, 1, 4, WHITE); display.fillRect(61, 6, 1, 4, WHITE);
        display.fillRect(55, 8, 1, 4, WHITE); display.fillRect(60, 8, 1, 4, WHITE);
        display.fillRect(56, 10, 1, 4, WHITE); display.fillRect(59, 10, 1, 4, WHITE);
        display.fillRect(57, 12, 1, 2, WHITE); display.fillRect(58, 12, 1, 2, WHITE);

        //arrow up
        display.fillRect(69, 3, 2, 11, WHITE);
        display.drawPixel(66, 7, WHITE); display.drawPixel(73, 7, WHITE);       //Arrow up
        display.drawPixel(67, 6, WHITE); display.drawPixel(72, 6, WHITE);
        display.drawPixel(67, 5, WHITE); display.drawPixel(72, 5, WHITE);
        display.drawPixel(68, 5, WHITE); display.drawPixel(71, 5, WHITE);
        display.drawPixel(68, 4, WHITE); display.drawPixel(71, 4, WHITE);



    }

    else if (Voltage == "Low")
    {



        //letter V
        display.fillRect(52, 2, 1, 4, WHITE); display.fillRect(63, 2, 1, 4, WHITE);
        display.fillRect(53, 4, 1, 4, WHITE); display.fillRect(62, 4, 1, 4, WHITE);
        display.fillRect(54, 6, 1, 4, WHITE); display.fillRect(61, 6, 1, 4, WHITE);
        display.fillRect(55, 8, 1, 4, WHITE); display.fillRect(60, 8, 1, 4, WHITE);
        display.fillRect(56, 10, 1, 4, WHITE); display.fillRect(59, 10, 1, 4, WHITE);
        display.fillRect(57, 12, 1, 2, WHITE); display.fillRect(58, 12, 1, 2, WHITE);

        //arrow down
        display.fillRect(69, 3, 2, 11, WHITE);
        display.drawPixel(66, 9, WHITE); display.drawPixel(73, 9, WHITE);       //Arrow down
        display.drawPixel(67, 10, WHITE); display.drawPixel(72, 10, WHITE);
        display.drawPixel(67, 11, WHITE); display.drawPixel(72, 11, WHITE);
        display.drawPixel(68, 11, WHITE); display.drawPixel(71, 11, WHITE);
        display.drawPixel(68, 12, WHITE); display.drawPixel(71, 12, WHITE);



    }

}










void OLED_TripReset()
{
    const unsigned long Event_timer_OLEDMsgTimeout = 3000;    //3 sec

    display.clearDisplay();

    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(60, 40);            // Start at top-left corner
    display.println("Trip RESET.");

    display.display();
    delay(Event_timer_OLEDMsgTimeout);
    display.clearDisplay();
}













void OLED_StatusScreen_PumpState()
{

    display.fillRect(100, 1, 1, 15, WHITE);  //solid bar seperator
    //display.fillRect(76, 15, 1, 15, WHITE);  //solid bottom bar seperator

    if (PumpRelayStatus == "Relay_ON")
    {



        //impeller rotation.
        display.drawCircle(88, 8, 3, WHITE);    //impeller hub.


        display.fillRect(87, 2, 3, 3, WHITE);   //impeller fin vertical
        display.fillRect(86, 2, 1, 2, WHITE);
        display.fillRect(90, 2, 1, 2, WHITE);
        display.drawPixel(85, 14, WHITE);
        display.drawPixel(88, 5, WHITE);
        display.drawPixel(91, 2, WHITE);

        display.fillRect(87, 12, 3, 3, WHITE);   //impeller fin
        display.fillRect(86, 13, 1, 2, WHITE);
        display.fillRect(90, 13, 1, 2, WHITE);
        display.drawPixel(85, 2, WHITE);
        display.drawPixel(88, 11, WHITE);
        display.drawPixel(91, 14, WHITE);




    }

    else if (PumpRelayStatus == "Relay_OFF")
    {

        //impeller static.
        display.drawCircle(88, 8, 3, WHITE);    //impeller hub.


    }
}

















void OLED_StatusScreen_WellLevel()
{

    if (WellLevel == "LOW")
    {

        //empty well
        display.fillRect(110, 2, 1, 12, WHITE);
        display.fillRect(116, 2, 1, 12, WHITE);
        display.fillRect(110, 13, 7, 1, WHITE);


    }

    else if (WellLevel == "OK")
    {



        //ok well
        display.fillRect(110, 2, 1, 12, WHITE);
        display.fillRect(116, 2, 1, 12, WHITE);
        display.fillRect(110, 13, 7, 1, WHITE);

        display.fillRect(111, 8, 5, 5, WHITE);


    }
}













void OLED_OutputScreen()
{



    /////display Irms value/////
    ////////////////////////////
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(2, 18);            // Start at top-left corner
    display.print("Irms = "); display.print(Irms, 2); display.print("A");

    /////display Vrms value/////
    ////////////////////////////
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(2, 30);            // Start at top-left corner
    display.print("Vrms = "); display.print(Vrms); display.print("V");

    /////display AP value/////
    //////////////////////////
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(2, 42);            // Start at top-left corner
    display.print("RP = "); display.print(RP); display.print("W");

    /////display pF value/////
    //////////////////////////
    display.setTextSize(1);             // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);        // Draw white text
    display.setCursor(2, 54);            // Start at top-left corner
    display.print("pF: "); display.print(pF); display.print(" "); display.print("AP: "); display.print(AP, 2); display.print("W");

    /////display TK float switch activation/////
    ////////////////////////////////////////////
    if (digitalRead(HL_CutOut) == HIGH)
    {
        display.fillRect(110, 26, 4, 4, WHITE);
    }      //HL float

    else if (digitalRead(HL_CutOut) == LOW)
    {
        display.drawRect(110, 26, 4, 4, WHITE);
    }      //HL float

    if (digitalRead(LL_CutIn) == HIGH)
    {
        display.fillRect(110, 36, 4, 4, WHITE);
    }      //LL float

    else if (digitalRead(LL_CutIn) == LOW)
    {
        display.drawRect(110, 36, 4, 4, WHITE);
    }      //LL float
//////////////////////////////////////////////////////////////////  
    delay(25);

}

