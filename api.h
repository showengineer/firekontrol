#if !defined(_FWESP_API_H)
#define _FWESP_API_H
#include <WebServer.h>
WebServer* setupAPI(int (*armHandle)(bool), int (*fireHandle)(int));

#endif
