#include "ft_script.h"

/*
**Checks if there is another argv in line and checks if its a file. 
**if so, assigned to char **name
*/

int     get_path_fd(char *path, unsigned char flags)
{
    if (flags & AFLG)
        return (open(path, O_CREAT | O_WRONLY | O_APPEND));
    else
        return (open(path, O_CREAT | O_WRONLY));
}

int    open_file_path(int ac, int index, char **av, t_env *env)
{
   if (index < ac)
    {
        env->filepathfd = get_path_fd(av[index], env->flags);
        if (env->filepathfd > 0)
            return (1);
        else
            initial_errors("File path error");
    }
    return (0);
}

int    get_pipe_name(int ac, int index, char **av, char **name)
{
   if (index < ac)
    {
        *name = ft_strdup(av[index]);   //change this to do file shit and save FD
        return (1);
    }
    return (0);
}

int     get_number(int count, int index, char **input, t_env *env)
{
    if ((index + 1) < count)
    {
        if (ft_isdigit((int)input[index + 1]))
            env->time = ft_atoi(input[index + 1]);
        else    //time value not dicated. default 30
            env->time = 30;
        return (1);
    }
    env->time = 30;
    return (0);
}

/*
**Retrieves flags 
**stored as bits within env->
*/

char    get_flags(int count, char **input, t_env *env)
{
    unsigned char   flg;
    int             index;
    int             letter;

    index = 0;
    flg = 0;
    while (index < count)
    {
        if (input[index][0] == FLAGDASH)
        {
            letter = 1;
            while (input[index][letter] && ft_strchr(FLAGS, input[index][letter]))
            {
                (input[index][letter] == 'a') ? (flg |= AFLG ) : (0);
                (input[index][letter] == 'd') ? (flg |= DFLG ) : (0);
                (input[index][letter] == 'k') ? (flg |= KFLG ) : (0);
                (input[index][letter] == 'p') ? (flg |= PFLG ) : (0);
                (input[index][letter] == 'q') ? (flg |= QFLG ) : (0);
                (input[index][letter] == 'r') ? (flg |= RFLG ) : (0);
                //(input[index][letter] == 'f') ? (flg |= FFLG ) : (0);
                if (input[index][letter] == 'f')                        //makes a named pipe ? using mkfifo(1)
                {
                    flg |= FFLG;
                    index += open_file_path(count, index + 1, input, env);
                }
                (input[index][letter] == 't') ? (flg |= TFLG ) : (0); //default interval 30 seconds 
                if (input[index][letter] == 't')
                        index += get_number(count, index, input, env);
                letter++;
            }
        }
        //if (index == (count - 1))
        //    index += get_file_name(count, index, input, &env->file);
        if (index == (count - 1) && (input[index - 1][0] != FLAGDASH))
            open_file_path(count, index, input, env);
        index++;
    }
    if (env->filepathfd != 0)  //assigning standard file name 'typescript'
        env->filepathfd = get_path_fd(DEFAULTFILE, env->flags);     // check for fd. If none, open fd for
    (env->file < 0) ? initial_errors("default file path error") : (0);
    return (flg);
}

void    print_flags(t_env *env)
{
    printf("env->pipe='%s'\n", env->pipe);
    printf("env->time='%d'\n", env->time);
    printf("env->file='%s'\n", env->file);
    printf("env->flags='%d'\n", (unsigned short)env->flags);
    printf("env->filepathfd'%d'\n", env->filepathfd);
}