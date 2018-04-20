
#include "ft_script.h"

int main(int argc, char **argv)
{
    t_env           env;

    env.flags = get_flags(argc, argv, &env);
    print_flags(&env);  //for testing
    return(0);
}