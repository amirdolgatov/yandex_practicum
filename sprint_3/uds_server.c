#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define QLEN 10
/*
* Создает точку соединения на стороне сервера.
* Возвращает fd в случае успеха, <0 – в случае ошибки.
*/
int
serv_listen(const char *name)
{
int
fd, len, err, rval;
struct sockaddr_un un;
if (strlen(name) >= sizeof(un.sun_path)) {
errno = ENAMETOOLONG;
return(-1);
}
/* создать сокет домена UNIX типа SOCK_STREAM */
if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
return(-2);
unlink(name); /* если name уже существует */
/* заполнить структуру с адресом */
memset(&un, 0, sizeof(un));
un.sun_family = AF_UNIX;
strcpy(un.sun_path, name);
len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
/* присвоить имя дескриптору */
if (bind(fd, (struct sockaddr *)&un, len) < 0) {
rval = -3;
goto errout;
}
/* сообщить ядру, что процесс является сервером */
if (listen(fd, QLEN) < 0) {
rval = -4;
goto errout;
}
return(fd);