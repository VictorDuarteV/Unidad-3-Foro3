/**********************************************************
 * FileName:        main.c
 * Dependencies:    msp.h, stdint.h
 * Processor:       MSP432
 * Board:           MSP432P401R
 * Program version: CCS V10 TI
 * Company:         TecNM /IT Chihuahua
 * Description:     ACCESO A MEMORIA DE REGISTROS DE PERIFERICO GPIO CON "ESTRUCTURAS_V2"
 * Authors:         ALFREDO CHACON
 * Updated:         03/2021
 * Nota: no se están usando las estructuras definidas en los sorucefiles dados por el BSP de TI, Aqui se declran las estructuras
 *       los punteros declarados se incializan con las direcciones de memoria de los registros de los perifericos en cuestión
 * Created on: 6 oct. 2021
 * updated: 20/11/2021
 **************************************************/

/************************************************************************************************
 * * Copyright (C) 2021 by Alfredo Chacon - TecNM /IT Chihuahua
 *
 * Se permite la redistribución, modificación o uso de este software en formato fuente o binario
 * siempre que los archivos mantengan estos derechos de autor.
 * Los usuarios pueden modificar esto y usarlo para aprender sobre el campo de software embebido.
 * Alfredo Chacon y el TecNM /IT Chihuahua no son responsables del mal uso de este material.
 *************************************************************************************************/
/************************************************
  HEADER FILES
 ************************************************/
#include<stdint.h>
#include "msp.h"
#include "DRIVERS\BSP.h"

void main(void)
{
    /************************************************
              DECLARACION DE VARIABLES
     ************************************************/
    uint32_t i;
    uint8_t bandera = 0;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;           // DETIENE EL TIMER DEL WATCHDOG
    /************************************************
        CONFIGURACION DE GPIO
    ************************************************/
    GPIO_setPinEntradaconPullUp(PORT1,BUTTON1);                 //PIN P1.4 COMO ENTRADA

    GPIO_setPinSalida(PORT2, LEDROJORGB | LEDVERDERGB |LEDAZULRGB);   // CONFIGURA PINES 2.0,2.1,2.2  COMO SALIDA (LEDS RGB)"
    GPIO_setPinSalida(PORT1, LEDRED);                          // Configura pin 1.0 como salida (Led rojo)"
    GPIO_setPinBajo(PORT2, LEDROJORGB | LEDVERDERGB |LEDAZULRGB);     // LEDS RGB APAGADOS
    GPIO_setPinAlto(PORT1, LEDRED);                            // Led rojo prendido


    while(1)
    {

        if ( Gpio_Pin_in(0x10) != 1)                // ENTRA AL PRESIONAR EL SWITCH DEL PUERTO P1.4 (CUANDO ESTA EN BAJO)
                {
                GPIO_setPinBajo(PORT1, LEDRED);  //Apaga led rojo
                    if(bandera == FALSE)
                        {
                            bandera = TRUE;                                 //BANDERA EN ALTO
                            while (bandera==TRUE){
                                GPIO_setPinBajo(PORT2, LEDAZULRGB);    //APAGA BLUE
                                GPIO_setPinAlto(PORT2,LEDROJORGB);    //ENCIENDE RED
                                for(i=RETARDO; i>0 ;i--);
                                GPIO_setPinBajo(PORT2, LEDROJORGB);    //APAGA RED
                                GPIO_setPinAlto(PORT2,LEDVERDERGB);    //ENCIENDE GREEN
                                for(i=RETARDO; i>0 ;i--);
                                GPIO_setPinBajo(PORT2, LEDVERDERGB);    //APAGA GREEN
                                GPIO_setPinAlto(PORT2,LEDAZULRGB);    //ENCIENDE BLUE
                                for(i=RETARDO; i>0 ;i--);
                             if ( Gpio_Pin_in(0x10) != 1) bandera=FALSE;    // ENTRA CUANDO PRESIONAMOS BOTON DE P1.4
                             while( Gpio_Pin_in(0x10) != 1);                //MIENTRAS ESTE PRESIONADO EL BOTON
                            }
                        }
                 GPIO_setPinBajo(PORT2, LEDROJORGB | LEDVERDERGB |PIN2);  //APAGA TODOS
                 GPIO_setPinAlto(PORT1, LEDRED);                         // Led rojo prendido
                }
        for(i=RETARDO; i>0 ;i--);

    }

}
