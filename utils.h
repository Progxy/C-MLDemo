#ifndef _UTILS_H_
#define _UTILS_H_

#define ARRAY_LEN(arr) sizeof((arr)) / sizeof((arr)[0])

float rand_float();
void init_seed();
float sigmoidf(float x);
float preluf(float x, float alpha);
float powerf(size_t base, float val);
float signf(float val);

#endif //_UTILS_H_