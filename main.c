
#include "ft_script.h"

/*
**Checks if there is another argv in line and checks if its a file. 
**if so, assigned to char **name
*/
int    get_file_name(int ac, int index, char **av, char **name)
{
    struct stat     *statbuf;
    
    if (index < ac)
    {
        *name = ft_strdup(av[index]);
        return (1);
    }
    return (0);
}

int     get_number(int count, int index, char **input, t_env *env)
{
    int     ret;

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
                    index += get_file_name(count, index + 1, input, &env->pipe);
                }
                (input[index][letter] == 't') ? (flg |= TFLG ) : (0); //default interval 30 seconds 
                if (input[index][letter] == 't')
                        index += get_number(count, index, input, env);
                letter++;
            }
        }
        //if (index == (count - 1))
        //    index += get_file_name(count, index, input, &env->file);
        if (index == (count - 1) 
        && env->pipe != NULL 
        && ft_strcmp(env->pipe, input[index]))
            get_file_name(count, index, input, &env->file);
        index++;
    }
    if (env->file == NULL)  //assigning standard file name 'typescript'
        env->file = ft_strdup(DEFAULTFILE);
    return (flg);
}

void    print_flags(t_env *env)
{
    printf("env->pipe='%s'\n", env->pipe);
    printf("env->time='%d'\n", env->time);
    printf("env->file='%s'\n", env->file);
    printf("env->flags='%d'\n", (unsigned short)env->flags);
}

int main(int argc, char **argv)
{
    t_env           env;

    env.flags = get_flags(argc, argv, &env);
    //testing
    print_flags(&env);
    return(0);
}