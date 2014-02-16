/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "include.h"

void	exec_command(char *cmd)
{
  char	*cmdname;

  cmdname = strrchr(cmd, '/');
  cmdname = cmdname ? (&(cmdname[1])) : cmd;
  execlp(cmdname, cmd, NULL);
}
