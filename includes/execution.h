#pragma once

# define FIRST_PIPE		1
# define N_PIPE			2
# define LAST_PIPE		3

typedef struct 	s_pipe
{
	int			fdpipe[2];
	int			in_fd;
	int			fdpipe_index;
	int			pipe_index;
}				t_pipe;
