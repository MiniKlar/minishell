#include "minishell.h"

// void set_signal_action(void)
// {
//     struct sigaction act;
//     ft_bzero(&act, sizeof(act));
//     act.sa_handler = &sig_handler;
//     sigaction(SIGINT, &act, NULL);
//     sigaction(SIGQUIT, &act, NULL);
// }

// void sig_handler(int signal)
// {
//     if (signal == SIGINT)
//     {
//         write(STDOUT_FILENO, "\n", 1);
//         //rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
//     else if (signal == SIGQUIT)
//     {
//         rl_on_new_line();
//         rl_redisplay();
//     }
//     else
//     {
//         write(STDOUT_FILENO, "Signal not handled\n", 19);
//     }
// }
