/*
 * Copyright (c) 2013 Yannik Li(Yanqing Li)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <arch/text.h>

void __puts(const char *str)
{
	while (*str) {
		while (UART_FR & UART_FR_TXFF);

		UART_DR = *str;

		if (*str == '\n') {
			while (UART_FR & UART_FR_TXFF);

			UART_DR = '\r';
		}
		str++;
	}
	while (UART_FR & UART_FR_BUSY);
}

void putchar(char c)
{
	while (UART_FR & UART_FR_TXFF);
	UART_DR = c;
	while (UART_FR & UART_FR_BUSY);
}

int getchar(void)
{
	unsigned int data;

	while (UART_FR & UART_FR_RXFE);
	
	data = UART_DR;

	if (data & 0xFFFFFF00) {
		UART_ECR = 0xFFFFFFFF;
		return -1;
	}
	
	return (int) data;
}

void __console_init(void)
{
}