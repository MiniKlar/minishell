#pragma once

typedef struct 	s_pipe
{
	int			fdpipe[2];
	int			in_fd;
	int			fdpipe_index;
	int			pipe_index;
}				t_pipe;
