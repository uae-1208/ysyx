#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#include <string.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
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
	char int_str[10];
	char def_str[2] = {'\0', '\0'};

	while (*fmt) {
		switch (*fmt) {
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
			break;
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
	ret = vsprintf(out, fmt, ap);
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
