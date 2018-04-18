
#ifndef FT_SCRIPT_H
# define    FT_SCRIPT_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"


# define FLAGS  "adkpqrft"
# define FLAGDASH   '-'
# define AFLG   0b00000001
# define DFLG   0b00000010
# define KFLG   0b00000100
# define PFLG   0b00001000
# define QFLG   0b00010000
# define RFLG   0b00100000
# define FFLG   0b01000000
# define TFLG   0b10000000
# define DEFAULTFILE    "typescript"
/*
char **lex[5] = {
    "ft_script",
    "-adkpqr",
    "-F pipe",
    "-t time",
    "file [command ...]",
    NULL
};
*/

typedef struct          s_env
{
    char                *pipe;
    int                 time;
    char                *file;
    unsigned char       flags;
}                       t_env;


#endif