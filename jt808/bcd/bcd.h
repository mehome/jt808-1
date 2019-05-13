#ifndef JT808_BCD_BCD_H_
#define JT808_BCD_BCD_H_


unsigned char BcdFromHex(const unsigned char &src);
unsigned char HexFromBcd(const unsigned char &src);
char *BcdFromStringCompress(const char *src, char *dst, const int &srclen);
char *StringFromBcdCompress(const char *src, char *dst, const int &srclen);

#endif // JT808_BCD_BCD_H_