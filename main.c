
#include "ft_script.h"

char    get_flags(int count, char **input, t_env *env)
{
    unsigned char   flg;
    int             index;
    int             letter;

    letter = 0;
    index = 0;
    flg = 0;
    while (index < count)
    {
        if (input[index][0] == FLAGDASH)
            while (ft_strchr(FLAGS, input[index][letter]))
            {
                (input[index][letter] == 'a') ? (flg |= AFLG ) : (0);
                (input[index][letter] == 'd') ? (flg |= DFLG ) : (0);
                (input[index][letter] == 'k') ? (flg |= KFLG ) : (0);
                (input[index][letter] == 'p') ? (flg |= PFLG ) : (0);
                (input[index][letter] == 'q') ? (flg |= QFLG ) : (0);
                (input[index][letter] == 'r') ? (flg |= RFLG ) : (0);
                (input[index][letter] == 'f') ? (flg |= FFLG ) : (0);
                if (input[index][letter] == 'f')
                    get_file_name();
                (input[index][letter] == 't') ? (flg |= TFLG ) : (0);
                if (input[index][letter] == 't')
                    get_number();                
                letter++;
            }
            if (index == (count - 1))
                get_file_nme();
        index++;
    }
    return (flg);
}

int main(int argc, char **argv)
{
    unsigned char   flags;
    t_env           env;
    flags = get_flags(argc, argv, env);
    
    return(0);
}