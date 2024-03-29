/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/

#if 0
//template
void zmain(void){
    
    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
}
#endif

#if 0
// Task 2.1 Beep light test
void zmain(void)
{
    while(true)
    {
        if ((SW1_Read() == 0)){
            for(int i = 0; i < 3; i++){
                BatteryLed_Write(1);
                Beep(750, 30);
                vTaskDelay(500);
                BatteryLed_Write(0);
                vTaskDelay(500);
            }
            for(int i = 0; i<3; i++){
                BatteryLed_Write(1);
                Beep(750, 30);
                vTaskDelay(1000);
                BatteryLed_Write(0);
                vTaskDelay(500);
            }
            for(int i = 0; i < 3; i++){
                BatteryLed_Write(1);
                Beep(750, 30);
                vTaskDelay(500);
                BatteryLed_Write(0);
                vTaskDelay(500);
            }
        }
    }
    
    
 }   
#endif

#if 0
// Task 2.2 Name and age
void zmain(void)
{
    TickType_t start;
    TickType_t end;
    char name[32];
    int age;
    
    
    printf("\n\n");
    
    printf("Enter your name: ");
    //fflush(stdout);
    start = xTaskGetTickCount();
    scanf("%s", name);
    printf("Enter your age: ");
    //fflush(stdout);
    scanf("%d", &age);
    end = xTaskGetTickCount();
    int time_long = end - start;
    //printf("You are [%s], age = %d\n", name, age);
    if (age <= 21){
        if(time_long < 3000){
            printf("\nSuper fast dude!");
        }
        else if((time_long >= 3000)&&(time_long <=5000)){
            printf("\nSo mediocre.");
        }
        else{
            printf("\nMy granny is faster than you!");
        }
    }
    else if((age >= 22)&&(age<=50)){
        if(time_long < 3000){
            printf("\nBe quick or be dead");
        }
        else if((time_long >= 3000)&&(time_long <=5000)){
            printf("\nYou're so average.");
        }
        else{
            printf("\nHave you been smoking something illegal?");
        }
    }
    else{
        if(time_long <= 3000){
            printf("\nStill going strong");
        }
        else if((time_long >= 4000)&&(time_long <=5000)){
            printf("\nYou are doing ok for your age.");
        }
        else{
            printf("\nDo they still allow you to drive?");
        }
    }
    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
 }   
#endif


#if 0
//Task 2.3 battery level//
void zmain(void)
{
	ADC_Battery_Start();   	 

	int16 adcresult =0;
	float volts = 0.0;

	printf("\nBoot\n");

	//BatteryLed_Write(1); // Switch led on
	//BatteryLed_Write(0); // Switch led off
	//uint8 button;
	//button = SW1_Read(); // read SW1 on pSoC board
	// SW1_Read() returns zero when button is pressed
	// SW1_Read() returns one when button is not pressed

	while(true)
	{
    	char msg[80];
    	ADC_Battery_StartConvert(); // start sampling
    	if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
        	adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
        	volts=(adcresult*5/4095)*(30/20);
        	// convert value to Volts
        	// you need to implement the conversion
       	 
        	// Print both ADC results and converted value
        	printf("%d %f\r\n",adcresult, volts);
       	 
    	if (volts<4){
        	while(SW1_Read()){
            	BatteryLed_Write(1);
            	vTaskDelay(500);
            	BatteryLed_Write(0);
            	vTaskDelay(500);
        	}
    	}
    	}
    	vTaskDelay(500);
	}
 }  

   
#endif

#if 0
// button
void zmain(void)
{
    while(true) {
        printf("Press button within 5 seconds!\n");
        int i = 50;
        while(i > 0) {
            if(SW1_Read() == 0) {
                break;
            }
            vTaskDelay(100);
            --i;
        }
        if(i > 0) {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
        else {
            printf("You didn't press the button\n");
        }
    }
}
#endif

#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    while(true)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led) printf("Led is ON\n");
            else printf("Led is OFF\n");
            Beep(1000, 150);
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   
#endif

#if 0
    void tankturn_left(uint8 speed_left, uint8 speed_right, int delay);
    
void zmain(void)
{
    Ultra_Start(); //start ultrasonic sensor
    motor_start(0,0);
    motor_forward(0,0);
    
    vTaskDelay(3000);
    
    while(true){
    int distance = Ultra_GetDistance(); //get distace between object and ultrasonic sensor
    
    if(distance <= 10 && distance !=0){
        motor_backward(50,500);
        Beep(150, 200);
        motor_turn(150,150, 500);
        motor_forward(0,0);
     }
    motor_turn(200,100,50);
    }   
}
#endif

#if 0
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    
    while(true) {
        int d = Ultra_GetDistance();
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        vTaskDelay(200);
    }
}   
#endif

#if 0
//Task 4.1 IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       // motor forward
                        Beep(60,80);
                    }
                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            
            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                    if(dig.l3 == 1 && dig.r3 == 1 ){
                        motor_turn(50,50,50);       // motor forward
                        vTaskDelay(50);
                        count++;
                        printf("count %d \n",count);
                        if(count >= 7){
                            motor_forward(0,0);       // Stop motors
                            loop = false;
                        }
                    }
                    else{
                         motor_turn(50,50,50);       // motor forward
                        Beep(100,100);
                    }
                }
                else {
                    printf("Led is OFF\n");
                    loop = false;
                }
               
            }    
        }
    }
 }   
#endif


#if 0
//Task 4.2 IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true/*, crossline= true*/;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,0);       // motor forward
                        //Beep(60,80);
                    }
                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            
            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    //do {
                        // read raw sensor values
                    //reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                   
                        /*if(dig.l3 == 1 && dig.l2 == 1 && dig.l1 == 1 && dig.r3 == 1 && dig.r2 == 1 && dig.r1 == 1){
                            motor_forward(0,0);
                            count++;
                            if(count==1){
                                motor_turn(50,50,50);       // motor forward
                            }
                            if (count==2){
                                motor_turn_left(10,100,500);
                            }
                            if (count<=4){
                                motor_turn_right(100,10,500);
                            }
                            if (count==5){
                                motor_forward(0,0);       // Stop motors
                                led = false;
                                BatteryLed_Write(led);
                            }
                        } */
                        if(dig.r2 == 1 && dig.r1 == 1){
                            //count++;
                            motor_turn(100,10,0);       // motor turn left
                            //Beep(20,20);
                            vTaskDelay(0);
                            
                            printf("count %d \n",count);
                        }
                        if(dig.l2 == 1 && dig.l1 == 1){
                            //count++;
                            motor_turn(10,100,0);       // motor turn right
                           // Beep(20,20);
                            vTaskDelay(0);
                            
                            printf("count %d \n",count);
                        }
                       // printf("count %d \n",count);
                        if (dig.l1 == 1 && dig.r1 == 1){
                            
                            motor_turn(50,50,0);       // motor forward
                            vTaskDelay(0);
                            //Beep(50,50);
                            //count++;
                            printf("count %d \n",count);
                        }
                   
                }
                else {
                    printf("Led is OFF\n");
                    loop = false;
                }
               
            }    
        }
    }
 }  
#endif

#if 0
//Task 4.3 IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    //IR receiverm - how to wait for IR remote commands
void zmain(void);

    uint8_t button_;
    printf("\nStart\n");

    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");

            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       // motor forward
                        Beep(60,80);
                    }

                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   

            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 

                    if(dig.l3 == 1 && dig.r3 == 1 && dig.l1 == 1 && dig.r1 == 1){
                        count++;
                        printf("\nStart\n");
                        printf("count %d \n",count);


                        while (dig.r3 == 1 && dig.l3 == 1){
                         motor_turn(50,49,0);
                        reflectance_digital(&dig);
                        }
                        if(count >= 2){
                            motor_forward(210,0);       // Stop motors
                        }
                    }

                    else if (dig.l1 == 1 && dig.r1 == 1){
                        motor_turn(210,210,0);   //goes forward lul
                        printf("%5d %5d", ref.l1, ref.r1);
                    }
                    else if (dig.l1 == 0 && dig.r1 == 1){
                        motor_turn(210,0,0);  //turns right lul
                        printf("%5d %5d", ref.l1, ref.r1);
                    }
                    else if (dig.l1 == 1 && dig.r1 == 0){
                        motor_turn(0,210,0);   ///should turn left, right lul??   
                        printf("%5d %5d", ref.l1, ref.r1);
                    }
                    else if (dig.l3 == 1 && dig.r3 == 1 && dig.l1 == 1 && dig.r1 == 1 && dig.l2 == 1 && dig.r2 == 1) {
                        motor_turn(0,0,100000);   ///should stop, right lul??   


                        }
                    }
                }


            }    
        }

}   
#endif


#if 0
//reflectance
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    

    while(true)
    {
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        
        
        vTaskDelay(200);
    }
}   
#endif


#if 0
//motor
void zmain(void)
{
    struct sensors_ ref;
    struct sensors_ dig;

    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    reflectance_digital(&dig);
    
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(3000);
    
    if(dig.l3, dig.l2, dig.l1){
        
    }
    motor_forward(100,2000);     // moving forward
    motor_turn(200,50,2000);     // turn
    motor_turn(50,200,2000);     // turn
    motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    while(true)
    {
        vTaskDelay(100);
    }
}
#endif

#if 0
/* Task 3.3*/
void zmain(void)
{
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    motor_start();              // enable motor controller
    motor_forward(0,0);
    srand(time(NULL));   // Initialization, should only be called once.
    int r=0, counter=0;
    while(true)
    {
        LSM303D_Read_Acc(&data);
       
        motor_forward(200,20);
        //vTaskDelay(200);
        if (counter == 0) r = rand() % 2;
        if (counter > 19){
            counter = 0;
            r = rand() % 2;
        }// Returns a pseudo-random integer between 0 and RAND_MAX.
            if(r == 0){
                motor_turn(200,50,5);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            else if(r == 1){
                motor_turn(50,200,5);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            else {
                motor_forward(200,20);
                vTaskDelay(0);
            }
        LSM303D_Read_Acc(&data);
        if((data.accX<-4000)){
            int r = rand() % 2;      // Returns a pseudo-random integer between 0 and RAND_MAX.
            if(r == 0){
                motor_backward(80,50);
                motor_turn(200,50,500);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            else{
                motor_backward(80,50);
                motor_turn(50,200,500);
                vTaskDelay(0);
                //motor_forward(0,0);
            }
            motor_forward(100,100);
        }
        counter++;
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        vTaskDelay(0);
    }
 }   
#endif    

#if 0
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    while(true)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
 }   
#endif

#if 0

//Task 5.2   
void zmain(void)
{
    Ultra_Start(); //start ultasonic sensor
    motor_start(0,0);
    motor_forward(0,0);
    
    vTaskDelay(3000);
    
    while(true){
        int distance = Ultra_GetDistance();
    
        if(distance <= 10 && distance !=0){
            int r = rand() % 2;      // Returns a pseudo-random integer between 0 and RAND_MAX.
            if(r == 0){
                motor_turn(50,200,500);
                vTaskDelay(0);
                print_mqtt("Zumo006/turn", "left");
                //motor_forward(0,0);
            }
            else{
                motor_turn(200,50,500);
                vTaskDelay(0);
                print_mqtt("Zumo006/turn", "right");
                //motor_forward(0,0);
            }
            motor_forward(100,100);
        }
        
    }   
}
#endif

#if 0
//Task 5.3 IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    time_t myTime;
    struct tm * timeinfo;
    time( &myTime );
    timeinfo = localtime( &myTime );
    
    // set current time
    now.Hour = timeinfo->tm_hour;
    now.Min = timeinfo->tm_min;
    now.Sec = timeinfo->tm_sec;
    now.DayOfMonth = timeinfo->tm_mday;
    now.Month = timeinfo->tm_mon+1;
    now.Year = timeinfo->tm_year+1900;
    RTC_WriteTime(&now); // write the time to real time clock
    
    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();              // enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       // motor forward
                        Beep(60,80);
                    }
                    else{
                        motor_forward(0,0);       // Stop motors
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            
            // Toggle led when IR signal is received
            while(loop)
            {   
                if(led){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                    if(dig.l3 == 1 && dig.r3 == 1 ){
                        motor_turn(50,50,50);       // motor forward
                        motor_forward(0,0);       // Stop motors
                        vTaskDelay(50);
                        count++;
                        printf("count %d \n",count);
                        printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
                        print_mqtt("Zumo006/lap", "%2d:%02d.%02d", now.Hour, now.Min, now.Sec);
                        /*if(count >= 7){
                            motor_forward(0,0);       // Stop motors
                            loop = false;
                        }*/
                    }
                    else{
                         motor_turn(50,50,50);       // motor forward
                        Beep(100,100);
                    }
                }
                else {
                    printf("Led is OFF\n");
                    loop = false;
                }
               
            }    
        }
    }
 }
#endif

#if 0
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    while(true)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            //print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
            //print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            //print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
//Task 5.1
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    while(true)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); // Disable Interrupt of RTC Component
            now = *RTC_ReadTime(); // copy the current time to a local variable
            RTC_EnableInt(); // Enable Interrupt of RTC Component

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            print_mqtt("Zumo006/time", "%2d:%02d.%02d", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

#if 0
//project 1
//Line following competition by Andrey Verovskiy
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    //IR receiverm - how to wait for IR remote commands
void zmain(void);

    uint8_t button_;
    printf("\nStart\n");
    
    while(true){
        button_ = SW1_Read();
        if(button_==0){
            IR_Start();
            printf("\n\nIR test\n");
            struct sensors_ ref;
            struct sensors_ dig;
            bool led = false,loop = true, startline= true;
            int count =0;
            motor_start();// enable motor controller 
            IR_flush(); // clear IR receive buffer
            printf("Buffer cleared\n");
            
            reflectance_start();
            // set center sensor threshold to 11000 and others to 9000
            reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); 
            vTaskDelay(200);
                while(startline){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    if(dig.l3 != 1 && dig.r3 != 1){
                        motor_turn(50,50,50);       //goes forward
                        Beep(60,80);
                    }
                    
                    else{
                        motor_forward(0,0);       // Stop motors
                        printf("line");
                        print_mqtt("Zumo006/ready", "line");
                        startline = false;
                    }
                }
            IR_wait();  // wait for IR command
            led = !led;
            BatteryLed_Write(led);   
            int start;
            start = xTaskGetTickCount();
            print_mqtt("Zumo006/start", "%d", start);
            
            // main loop when IR signal is recieved
            while(loop)
            {   
                if(led){
                    // read raw sensor values
                    reflectance_read(&ref);
                    reflectance_digital(&dig); 
                    
                    if(dig.l3 == 1 && dig.r3 == 1 && dig.l2 == 1 && dig.r2 == 1){
                         motor_turn(50,50,50); //goes forward
	                        vTaskDelay(50);
                        count++;    //counts the lines that sensors detect
                        
                        printf("count %d \n",count);
                        if(count >= 7){//stops on the third line
                            motor_forward(0,0);// Stop motors
                            int stop;
                            stop=xTaskGetTickCount();
                            //prints stop time
                            print_mqtt("Zumo006/stop", "%d",stop ); 
                            //addition of time variable
                            int time= stop - start;  
                            //prints overall time 
                            print_mqtt("Zumo006/time", "%d",time);    
                            vTaskDelay(1000000);
                            break;
                        }
                    }
                    //goes forward if sensors l1 and r1 detect the line
                    else if (dig.l1 == 1 && dig.r1 == 1){
                        motor_turn(100,100,0);
                        printf("%5d %5d", ref.l1, ref.r1);
                    }
                    //turns right if left sensor does not detect the line
                    else if (dig.l1 == 0 && dig.r1 == 1){
                        motor_turn(100,0,0);  
                        printf("%5d %5d", ref.l1, ref.r1);
                    }
                    //turns left if right sensor does not detect the line
                    else if (dig.l1 == 1 && dig.r1 == 0){
                        motor_turn(0,100,0);      
                        printf("%5d %5d", ref.l1, ref.r1);
                    }
                    
                    }
                }
                
               
            }    
        }

}  
#endif

#if 1
//project 2
// Calibrated robot (one of main functions)
void go_forward(uint8 speed, int delay)
{
    MotorDirLeft_Write(0);      
    MotorDirRight_Write(0);    
    PWM_WriteCompare1(speed); 
    PWM_WriteCompare2(speed-7); 
    vTaskDelay(delay);
}

// turn to left  (main functions for left)
void tankturn_left(uint8 speed_left, uint8 speed_right, int delay)
{
    MotorDirLeft_Write(1);      
    MotorDirRight_Write(0);    
    PWM_WriteCompare1(speed_left); 
    PWM_WriteCompare2(speed_right); 
    vTaskDelay(delay);
}

// turn to right  (main functions for right)
void tankturn_right(uint8 speed_left, uint8 speed_right, int delay)
{
    MotorDirLeft_Write(0);      
    MotorDirRight_Write(1);    
    PWM_WriteCompare1(speed_left); 
    PWM_WriteCompare2(speed_right); 
    vTaskDelay(delay);
}
//short for writing 
void go_forward(uint8 speed, int delay);    
void tankturn_right(uint8 speed_left, uint8 speed_right, int delay);    
void tankturn_left(uint8 speed_left, uint8 speed_right, int delay);

void zmain(void)
{
    
    struct accData_ data; 
    LSM303D_Start();
    Ultra_Start();
    
    struct sensors_ dig;
    TickType_t start, end, hit = 0;
    
    reflectance_start();
    reflectance_set_threshold(9500, 9500, 9500, 10000, 11000, 13000);
    
    motor_start();
    motor_forward(0,0);
    IR_Start();
    
  // Prepare for the fight, wait for IR on the line. Press Ok
    while (SW1_Read() == 1) {
        vTaskDelay(150);
    }
    
 // Search circle 
    while (dig.l1 != 1 || dig.l2 != 1 || dig.l3 != 1 ||
          dig.r1 != 1 || dig.r2 != 1 || dig.r3 != 1) {
            reflectance_digital(&dig);
            go_forward(70, 20);
    }
 //wait near circle
    motor_forward(0, 0); 
    print_mqtt("Zumo006/ready", "zumo");
    IR_wait();
    
 // Pass the circle line
    go_forward(100, 200);
 //start for screen
    start = xTaskGetTickCount();
    print_mqtt("Zumo006/start", "%d", start);
    
    // Sumo fighting loop
    while (true) {
        go_forward(150, 5);
        LSM303D_Read_Acc(&data);
        reflectance_digital(&dig);
        
        // Detect hits from diffrent sides
        if (data.accX > 12000 || data.accY > 12000 || data.accX < -12000 || data.accY < -12000) {
            
        // Send the hit message 
            // of 110 seconds
            if (xTaskGetTickCount() - hit > 110) {
                hit = xTaskGetTickCount();
                print_mqtt("Zumo006/attack", "%d", hit);
                
         // Change the direction  and sprint 
                tankturn_left(250, 250, 00);
                motor_forward(0,0);
                go_forward(255, 100); 
                go_forward(230, 100); 
            }
        }
        
     // attack
        if (Ultra_GetDistance() < 17) {
            go_forward(255, 350);
            go_forward(255, 150);
      // screen   
            if (xTaskGetTickCount() - hit > 150) {
                hit = xTaskGetTickCount();
                print_mqtt("Zumo006/hit", "%d", hit);
            }
        }
        
     // end of circle and turn 
        if (dig.l1 == 1 || dig.l2 == 1 || dig.l3 == 1||
        dig.r1 == 1 || dig.r2 == 1 || dig.r3 == 1) {
            motor_backward(220, 200);
            motor_forward(0, 0);
            tankturn_right(220, 220, 400);   
            motor_forward(0, 0);
            go_forward(200, 150); 
        }
        
     // Stop the fight by pressing the user button
        if (SW1_Read() == 0) {
            motor_forward(0,0);
     //end for screen 
            end = xTaskGetTickCount();
            print_mqtt("Zumo006/stop", "%d", end);
            int delta = end - start;
            print_mqtt("Zuome006/time", "%d", delta);
      //stop 
            motor_stop();
            while(true)
                vTaskDelay(100);
        }
    }
}

#endif
/* [] END OF FILE */
