#ifndef ls_h
#define ls_h

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <getopt.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sysexits.h>
#include <time.h>
#include <unistd.h>

#define BUF_SZ 4096

const char* cur_dir = ".";

int listFiles(int t_argc, char *t_argv[]);

struct opts
{
    bool using_a_opt;
    bool using_d_opt;
    bool using_h_opt;
    bool using_l_opt;
} t_opts;

/*
t_argc - Integer, No. of arguments,
t_argv - Array of Strings representing args (similar like command like args).
   Ex. : t_args[0] - name of the prog. here it can be 'ls'
         t_args[1] - {path of a folder} or {ls opts}
		"ls opts" = {-a, -d, -h -l} 

         so t_argv = "ls . -l"  or "ls -l" or "ls -l -a" 
*/

int lsFunc(int t_argc, char *t_argv[])
{
	listFiles(t_argc, t_argv);
}

void init_opts()
{
    t_opts.using_a_opt = false;
    t_opts.using_d_opt = false;
    t_opts.using_h_opt = false;
    t_opts.using_l_opt = false;
}

void get_opts(int count, char* args[])
{
    int opt = 0;
    int i = 0;
    init_opts();

    static struct option long_opts[] = {
        { "all",             optional_argument, NULL, 'a' },
        { "directory",       optional_argument, NULL, 'd' },
        { "human-readable",  optional_argument, NULL, 'h' },
        { "long list",       optional_argument, NULL, 'l' },
        { NULL,              0,                 NULL,  0  }
    };
   
    optind = 1; 
    
    while ((opt = getopt_long(count, args, 
        "adhl", long_opts, NULL)) != -1)
    {
        switch (opt)
        {
            case 'a': t_opts.using_a_opt = true; break;
            case 'd': t_opts.using_d_opt = true; break;
            case 'h': t_opts.using_h_opt = true; break;
            case 'l': t_opts.using_l_opt = true; break;
            case '?' : t_opts.using_h_opt = true; break;
        }
    }
}

void print_perm(mode_t mode)
{
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

void print_ftype(mode_t mode)
{
    switch (mode & S_IFMT)
    {
        case S_IFREG:  putchar('-'); break;
        case S_IFDIR:  putchar('d'); break;
        case S_IFLNK:  putchar('l'); break;
        case S_IFCHR:  putchar('c'); break;
        case S_IFBLK:  putchar('b'); break;
        case S_IFSOCK: putchar('s'); break;
        case S_IFIFO:  putchar('f'); break;
    }
}

void print_fsize(off_t size)
{
    const char* units[] = { "", "K", "M", "G", "T" };
    char fsize_buf[BUF_SZ]; 
    int i;

    for (i = 0; size > 1024; ++i, size /= 1024);

    snprintf(fsize_buf, sizeof(fsize_buf), 
        "%*jd%s ", i, (intmax_t)size, units[i]);

    printf(" %8s", fsize_buf);
}

void print_time(time_t mod_time)
{
    // get current time with year
    time_t ctime;
    struct tm *t = NULL;
    char time_buf[BUF_SZ];

    time(&ctime);
    t = localtime(&ctime);

    const int curr_mon = t->tm_mon;
    const int curr_yr = 1970 + t->tm_year;

    // get modified time and year
    t = localtime(&mod_time);
    const int mod_mon = t->tm_mon;
    const int mod_yr = 1970 + t->tm_year;

    // determine format based on modification time
    // (past six months)
    const char* fmt = (mod_yr == curr_yr)
                       && (mod_mon >= (curr_mon - 6))
                           ? "%b %e %H:%M"
                           : "%b %e  %Y";

    const size_t bytes_written = 
        strftime(time_buf, sizeof(time_buf), fmt, t);

    if (bytes_written <= 0)
    {
        return;
    }

    printf("%s", time_buf);
}

struct stat get_stats(const char* fname)
{
    char pbuf[BUF_SZ];
    struct stat sb; 
    const int bytes_written = snprintf(pbuf, sizeof(pbuf),  
        	"%s/%s", cur_dir, fname);

    memset(&sb, 0, sizeof(struct stat));
    if (bytes_written <= 0)
    {
	return sb;
    }

    if (lstat(pbuf, &sb) < 0)
    {   
        perror(pbuf);
	return sb;
    }

    return sb;
}

int is_dir(const char* fname)
{
    struct stat sb = get_stats(fname);

    if (lstat(fname, &sb) < 0)
    {
        perror(fname);
	return 0;
    }

    return sb.st_mode & S_IFDIR;
}

bool is_in_dir(const char* dir, const char* fname)
{
    DIR *dfd = opendir(dir);
    struct dirent *dp = NULL;

    dfd = opendir(dir);
    if (!dfd)
    {
        perror(dir);
	return true;
    }

    dp = readdir(dfd);
    while (dp)
    {
        if (strcmp(fname, dp->d_name) == 0)
        {
            closedir(dfd);
            return true;
        }      

        dp = readdir(dfd);
    }

    fprintf(stderr, "file \'%s\' not found\n", fname);

    closedir(dfd);

    return false;
}

void print_link(const char* dir, const char* fname)
{
    char pbuf[BUF_SZ];
    char link_buf[BUF_SZ];

    const int bytes_written = 
        snprintf(pbuf, sizeof(pbuf), 
        "%s/%s", dir, fname);

    if (bytes_written <= 0)
    {
	return ;
    }

    const ssize_t count = 
        readlink(pbuf, link_buf, sizeof(link_buf));

    if (count == -1)
    {
        perror("readlink");
	return ;
    }

    link_buf[count] = '\0';

    printf(" %s -> %s \n", fname, link_buf);
}

void print_name(const char* fname)
{
    printf(" %s", fname);

    if (is_dir(fname))
    {
        putchar('/');
    }

    putchar('\n');
}

void display_stats(const char* dir, const char* fname)
{
    struct stat sb;

    if (!is_in_dir(dir, fname))
    {
        return;
    }

    if (!t_opts.using_l_opt)
    {
        printf("%s\n", fname);

        return;
    }

    sb = get_stats(fname);

    // print inode number
    printf("%ju ", (uintmax_t)sb.st_ino);

    print_ftype(sb.st_mode);

    print_perm(sb.st_mode);

    printf(" %jd ", (intmax_t)sb.st_nlink);

    // print owner
    printf("%10s ", getpwuid(sb.st_uid)->pw_name);

    // print group
    printf("%10s", getgrgid(sb.st_gid)->gr_name);

    // print file size
    printf("%10jd ", (intmax_t)sb.st_size);

    print_time(sb.st_mtime);

    // print name/link
    if ((sb.st_mode & S_IFMT) == S_IFLNK)
    {
        print_link(dir, fname);
    }
    else
    {
        print_name(fname);
    }
}

void parse_dir_entries(DIR* dfd, char** entries, size_t* entries_count)
{
    struct dirent* dp = readdir(dfd);

    *entries_count = 0;
    while (dp)
    {
        const bool omit_hidden = !t_opts.using_a_opt
                              && dp->d_name[0] == '.';

        if (!omit_hidden)
        {
            if (*entries_count >= BUF_SZ)
            {
                entries = realloc(
                    entries, sizeof(entries) * BUF_SZ);

                if (!entries)
                {
                    perror("realloc");
                    abort();
                }
            }

            entries[*entries_count] = dp->d_name;
            ++(*entries_count);
        }

        dp = readdir(dfd);
    }
}

void display_dir_entries(const char* dir)
{
    DIR *dfd;
    char **entries = malloc(BUF_SZ * sizeof(char*));
    size_t entries_count;
    size_t i = 0;
 
    if (!entries)
    {
        perror("malloc");
        abort();
    }

    dfd = opendir(dir);

    parse_dir_entries(dfd, entries, &entries_count);

    for (i = 0; i < entries_count; ++i)
    {
        display_stats(dir, entries[i]);
    }

    closedir(dfd);

    free(entries);
}

void display_dir_args(int argc, char* argv[])
{
    const bool no_dirs_given = (argc - optind) == 0;
    int i = 0;

    if (no_dirs_given)
    {
        display_stats(".", ".");
    }

    for (i = optind; i < argc; ++i)
    {
        display_stats(".", argv[i]);
    }
}

void scan_dir_entries(int argc, char* argv[])
{
    const bool multiple_dirs = (argc - optind) >= 2;
    int i = 0;

    for (i = optind; i < argc; ++i)
    {
        if (!is_dir(argv[i]))
        {
            display_stats(".", argv[i]);
            continue;
        }

        if (!is_in_dir(".", argv[i]))
        {
            continue;
        }

        if (multiple_dirs)
        {
            printf("\n%s:\n", argv[i]);
        }

        display_dir_entries(argv[i]);
    }
}

int listFiles(int t_argc, char **t_argv)
{
    int i = 0;
    get_opts(t_argc, t_argv);

    if (t_opts.using_d_opt)
    {
        display_dir_args(t_argc, t_argv);
        return EX_OK;
    }
    else
    {
        if (optind == t_argc)
        {
            display_dir_entries(".");
            return EX_OK;
        }

        scan_dir_entries(t_argc, t_argv);
    }

    optind = 1;
}
#endif
