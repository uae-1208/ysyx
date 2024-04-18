#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <string.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) 
{
	char str_temp[100];

	va_list ap;
	int ret;

	str_temp[0] = '\0';    //clear the out string
	va_start(ap, fmt);
	ret = vsprintf(str_temp, fmt, ap);    assert(ret >= 0);
	va_end(ap);

	for(const char *p = str_temp; *p; p++) 
		putch(*p);
	return ret;
}


// the num must be positive
void int2str(int num, char *str) {
	int one = num % 10;
	int temp = num / 10;
	char num_str[2] = {'\0', '\0'};

	if(temp != 0)
		int2str(temp, str);
	
	num_str[0] = one + '0';
	strcat(str, num_str);
}

#define APPEND(c) do {   \
	def_str[0] = c;        \
	strcat(out, def_str);  \
} while(0)

int vsprintf(char *out, const char *fmt, va_list ap) {
	int d, ch_num = 0;
	char *s;
	char ch;
	char int_str[10];
	char def_str[2] = {'\0', '\0'};

	while (*fmt) {
		switch (*fmt) {
		case 'c':              /* char */
			if(*(fmt - 1) != '%')  //%s
				APPEND('c');
			else{
				ch = (char)va_arg(ap, int);
				APPEND(ch);
			}
			break;		
		case 's':              /* string */
			if(*(fmt - 1) != '%')  //%s
				APPEND('s');
			else{
				s = va_arg(ap, char *);
				strcat(out, s);
			}
			break;
		case 'd':              /* int */
			if(*(fmt - 1) != '%')  //%d
				APPEND('d');
			else{
				d = va_arg(ap, int); //the int is negative
				if(d < 0){
					strcat(out, "-");
					d = -d;
				}
				int_str[0] = '\0';
				int2str(d, int_str);
				int_str[strlen(int_str)] = '\0';
				strcat(out, int_str);
			}
			break;
		case '%':    
			if(*(fmt + 1) == 'd' || *(fmt + 1) == 's' || *(fmt + 1) == 'c')  // %d or %s or %c
				break;
			else
				panic("\%s or \%d or \%c!!!!");
		default:
			APPEND(*fmt);
			break;
		}
		fmt++;
   		ch_num++;
	}
  return ch_num;
}

int sprintf(char *out, const char *fmt, ...) {
	va_list ap;
	int ret;

	out[0] = '\0';    //clear the out string
	va_start(ap, fmt);
	ret = vsprintf(out, fmt, ap);    assert(ret >= 0);
	va_end(ap);
	return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
