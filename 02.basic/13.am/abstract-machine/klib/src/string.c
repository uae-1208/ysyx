#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;
  assert(s);
  while(*s++ != '\0')
      len ++;
  return len;
}

char *strcpy(char *dst, const char *src) {
	assert((dst != NULL) && (src != NULL));
  char *ret = dst;
  while((*dst++ = *src ++) != '\0')
  {
    ;
  }
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
	assert((dst != NULL) && (src != NULL));
	assert(n >= 0);
	char* ret = dst;    
  while((*dst++ = *src ++) != '\0' && n-- != 0)
  {
    ;
  }
	return ret;  
}

char *strcat(char *dst, const char *src) {
	assert((dst != NULL) && (src != NULL));
	char *ret = dst;
	while (*dst != '\0')
		dst++;
	while ((*dst++ = *src++) != '\0')
  {
    ;
  }
	return ret;
}

int strcmp(const char *s1, const char *s2) {
	assert((s1 != NULL) && (s2 != NULL));
	while (*(unsigned char*)s1 == *(unsigned char*)s2)
	{  
    if( *(unsigned char*)s1 =='\0')
      return 0;
    s1++; 
		s2++;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
	assert((s1 != NULL) && (s2 != NULL));
	assert(n >= 0);
	while ((*(unsigned char*)s1 == *(unsigned char*)s2) && n)
	{  
    if( *(unsigned char*)s1 !='\0')
      return 0;
    s1++; 
		s2++;
    n--;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void *memset(void *s, int c, size_t n) {
  assert(s != NULL);
	char *str = (char*)s;
	for(int i=0; i<n; i++)
		str[i] = c;
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
	assert((dst != NULL) && (src != NULL));
  char *char_dst = (char *)dst;
  char *char_src = (char *)src;
  if (dst < src){
    for (int i = 0; i < n; ++i)
      char_dst[i] = char_src[i];
  }else if(dst > src){        //overloop
    for (int i = n-1; i >= 0; --i)
      char_dst[i] = char_src[i];
  }
  return dst;}

void *memcpy(void *out, const void *in, size_t n) {
	assert((out != NULL) && (in != NULL) && (n >= 0));
	char *tmp = out;
	const char *s = in;

	while (n--)
		*tmp++ = *s++;
	return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  char *char_s1 = (char *)s1;
  char *char_s2 = (char *)s2;

  int i;
  for (i = 0; i < n; ++i){
    if (char_s1[i] != char_s2[i])
      return (int)(char_s1[i]) - (int)(char_s2[i]);
  }
  if (i == n)
    return 0;
  return (int)(char_s1[i]) - (int)(char_s2[i]);
}

#endif
