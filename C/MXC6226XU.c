// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MXC6226XU
// This code is designed to work with the MXC6226XU_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MXC6226XU_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MXC6226XU I2C address is 0x16(22)
	ioctl(file, I2C_SLAVE, 0x16);

	// Select detection register(0x40)
	// Power up(0x00)
	char config[2] = {0};
	config[0] = 0x40;
	config[1] = 0x00;
	write(file, config, 2);
	sleep(1);

	// Read 2 bytes of data from register(0x00)
	// xAccl, yAccl
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Error : Input/Output error \n");
		exit(1);
	}
	else
	{
		// Convert the data
		int xAccl = data[0];
		if(xAccl > 127)
		{
			xAccl -= 256;
		}

		int yAccl = data[1];
		if(yAccl > 127)
		{
			yAccl -= 256;
		}

		// Output data to screen
		printf("Acceleration in X-Axis : %d \n", xAccl);
		printf("Acceleration in Y-Axis : %d \n", yAccl);
	}
}
