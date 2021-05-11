#ifndef LIBH
#define LIBH

#ifdef __cplusplus
extern "C" {
#endif

extern int calc(void);
extern int sum(int arr[3]);
extern int *make_buf(unsigned size);
extern int call_void(int (*fun)(void *), void *arg);

#ifdef __cplusplus
}
#endif

#endif