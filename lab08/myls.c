// myls.c ... my very own "ls" implementation

#include <stdlib.h>
#include <stdio.h>
#include <bsd/string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[])
{
    // string buffers for various names
    char dirname[MAXDIRNAME];
    char uname[MAXNAME+1];
    char gname[MAXNAME+1];
    char mode[MAXNAME+1];

    // collect the directory name, with "." as default
    if (argc < 2)
        strlcpy(dirname, ".", MAXDIRNAME);
    else
        strlcpy(dirname, argv[1], MAXDIRNAME);

    // check that the name really is a directory
    struct stat info;
    if (stat(dirname, &info) < 0)
        { perror(argv[0]); exit(EXIT_FAILURE); }
    if ((info.st_mode & S_IFMT) != S_IFDIR)
        { fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); }

    // open the directory to start reading
    DIR *df;
    df = opendir(dirname);

    struct stat sh;
    char entry_loc[BUFSIZ];
    char entry_name[BUFSIZ];
    
    // read directory entries
    struct dirent *entry;
    while ((entry = readdir(df)) != NULL) {
        if (entry->d_name[0] == '.') continue;
        snprintf(entry_loc, BUFSIZ, "%s/%s", dirname, entry->d_name);
        lstat(entry_loc, &sh);
        if ((sh.st_mode & S_IFMT) == S_IFLNK) {
            char link[BUFSIZ];
            readlink(entry_loc, link, BUFSIZ);
            snprintf(entry_name, BUFSIZ, "%s -> %s", entry->d_name, link);
        }
        else {
            snprintf(entry_name, BUFSIZ, "%s", entry->d_name);
        }
        printf("%s  %-12.12s %-12.12s %10lld  %s\n",
            rwxmode(sh.st_mode, mode),
            username(sh.st_uid, uname),
            groupname(sh.st_gid, gname),
            (long long)sh.st_size,
            entry_name);
    }

    // finish up
    closedir(df);
    return EXIT_SUCCESS;
}

// convert octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str)
{
    switch (mode & S_IFMT) {
        case S_IFBLK:  str[0] = 'b';        break;
        case S_IFCHR:  str[0] = 'c';        break;
        case S_IFDIR:  str[0] = 'd';        break;
        case S_IFIFO:  str[0] = 'f';        break;
        case S_IFLNK:  str[0] = 'l';        break;
        case S_IFREG:  str[0] = '-';        break;
        case S_IFSOCK: str[0] = 's';        break;
        default:       str[0] = '?';        break;
    }
    int i = 1;
    for (; i < 10; i++) {
        if (mode >> (9 - i) & 1)  { // 1
            if (i % 3 == 1) {
                str[i] = 'r';
            }
            else if (i % 3 == 2) {
                str[i] = 'w';
            }
            else {
                str[i] = 'x';
            }
        }
        else {  // 0
            str[i] = '-';
        }
    }
    str[10] = '\0';
    return str;
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
