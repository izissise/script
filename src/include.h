/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef INCLUDE_H_INCLUDED
# define INCLUDE_H_INCLUDED

# define _GNU_SOURCE
# define _XOPEN_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <getopt.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <unistd.h>
# include <pty.h>

# define SETFLAG(x, y) (x) |= (y)
# define UNSETFLAG(x, y) (x) &= ~(y)
# define SWITCHFLAG(x, y) (x) ^= (y)
# define GETFLAG(x, y) (x) & (y)

typedef struct	s_script
{
  char		*shell;
  char		*file;
  char		append;
  char		returnex;
  char		flush;
  char		force;
  char		quiet;
  char		timing;
  char		*timingout;
}		t_script;

char	*get_envvar(char *var, char **env);

int	parse_opt(int ac, char **av, char **envp, t_script *script);

#endif // INCLUDE_H_INCLUDED
