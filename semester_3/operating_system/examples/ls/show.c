/*
 * ls/ls.c --
 *
 *	A very basic implementation of 'ls' demonstrating how to read
 *	directories and obtain status information about files using
 *	POSIX interfaces.
 */

#define _POSIX_C_SOURCE 200112L
#define FS_SIZE_64_BIT

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <assert.h>
#include <inttypes.h>

#include "ls.h"

static void
show_mode(mode_t mode)
{
    char c = '?';
    
    if (S_ISDIR(mode)) {
        c = 'd';
    } else if (S_ISREG(mode)) {
        c = '-';
    } else if (S_ISCHR(mode)) {
        c = 'c';
    } else if (S_ISBLK(mode)) {
        c = 'b';
#ifdef S_ISLNK
    } else if (S_ISLNK(mode)) {
        c = 'l';
#endif
#ifdef S_ISSOCK
    } else if (S_ISSOCK(mode)) {
        c = 's';
#endif
    } else if (S_ISFIFO(mode)) {
        c = 'f';
    }
    
    putchar(c);
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

static void
show_user(uid_t uid, int flags)
{
    struct passwd *pwd;
    
    pwd = getpwuid(uid);
    if (!(flags & LS_FLAG_NUMERIC) && pwd) {
        printf(" %6s", pwd->pw_name);
    } else {
        printf(" %6u", (unsigned) uid);
    }
}

static void
show_group(gid_t gid, int flags)
{
    struct group *grp;
    
    grp = getgrgid(gid);
    if (!(flags & LS_FLAG_NUMERIC) && grp) {
        printf(" %6s", grp->gr_name);
    } else {
        printf(" %6u", (unsigned) gid);
    }
}

static void
show_time(time_t t, time_t now)
{
    struct tm *tm;
    char buffer[80];
    const time_t delta = 7905600;       /* 366/2 * 12 * 3600 seconds */
    size_t n = 0;

    tm = localtime(&t);
    if (now != (time_t) -1 && t < now - delta) {
        n = strftime(buffer, sizeof(buffer), "%b %d  %Y", tm);
    } else {
        n = strftime(buffer, sizeof(buffer), "%b %d %H:%M", tm);
    }
    if (n) {
        printf(" %12s", buffer);
    } else {
        printf(" %12lu", (unsigned long) t);
    }
}

void
show(struct dirent *e, int flags)
{
    struct stat s;
    time_t now;
    int r;
    
    r = stat(e->d_name, &s);
    if (r == -1) {
	r = lstat(e->d_name, &s);
    }
    if (r == -1) {
	perror("state or lstate");
	return;
    }
    show_mode(s.st_mode);
    printf(" %4ju", (uintmax_t) s.st_nlink);
    show_user(s.st_uid, flags);
    show_group(s.st_gid, flags);
    printf(" %9ju", (uintmax_t) s.st_size);
    now = time(NULL);
    show_time(s.st_mtime, now);
    printf(" %s", e->d_name);
#ifdef S_ISLNK
    if (S_ISLNK(s.st_mode)) {
	char path[PATH_MAX];
	int len = 0;
	len = readlink(e->d_name, path, sizeof(path));
	if (len == -1) {
	    perror("readlink");
	} else {
	    printf(" -> %*s", len, path);
	}
    }
#endif
    puts("");
}
