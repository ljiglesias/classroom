# IEE2463 - Material de apoyo

En esta carpeta encontrarás material de apoyo útil para el curso. El archivo github-git-cheat-sheet.pdf contiene una lista de comandos útiles de Git.

## Microcontroladores

Los recursos asociados a los microcontroladores utilizados en este curso los pueden encontrar en sus respectivas páginas

### MSP430F5529 Launchpad

Las encontrarán en la carpeta MSP430 y en los siguientes links:

- [Link del fabricante](http://www.ti.com/tool/MSP-EXP430F5529LP)
- [Launchpad User's Guide](http://www.ti.com/lit/ug/slau533d/slau533d.pdf)
- [User's Guide](http://www.ti.com/lit/ug/slau208q/slau208q.pdf)
- [MSP430F551x Mixed-Signal Microcontrollers](http://www.ti.com/lit/ds/symlink/msp430f5529.pdf)

Para programarla pueden utilizar Code Composer Studio
- [Code Composer Studio (Recomendado)](http://www.ti.com/tool/CCSTUDIO)
	- [Download page](http://processors.wiki.ti.com/index.php/Download_CCS)

### ATmega328P Xplained Mini 

Las encontrarán en la carpeta ATmega328P y en los siguientes links. En la carpeta además hay un archivo llamado optiboot_xplained328p.hex, este es el [bootloader](https://www.engineersgarage.com/tutorials/bootloader-how-to-program-use-bootloader) que utiliza el microcontrolador para funcionar, en caso de alguna falla, volver a cargar este archivo podría ser un paso útil. 

- [Link del fabricante](https://www.microchip.com/developmenttools/ProductDetails/ATMEGA328P-XMINI)
- [Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
- [User's Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/50002659A.pdf)

Para programarla pueden utilizar Atmel Studio, avr-gcc
- [AtmelStudio 7](https://www.microchip.com/mplab/avr-support/atmel-studio-7)
- [avr-gcc](https://www.nongnu.org/avr-libc/)
	- [Tutorial instalación](http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/)
