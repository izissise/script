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

# include <stdlib.h>
# include <string.h>
# include <getopt.h>

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
}		t_script;

char	*get_envvar(char *var, char **env);

int	parse_opt(int ac, char **av, char **envp, t_script *script);

#endif // INCLUDE_H_INCLUDED
