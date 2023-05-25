#ifndef _UTILS_H_
#define _UTILS_H_

#define ARRAY_LEN(arr) sizeof((arr)) / sizeof((arr)[0])

float rand_float();
void init_seed();
float sigmoidf(float x);
float reluf(float x);
float preluf(float x, float alpha);

#endif //_UTILS_H_