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

void	exec_command(char *shell, char *cmd)
{
  char	*shellname;

  shellname = strrchr(shell, '/');
  shellname = shellname ? (&(shellname[1])) : shell;
  if (cmd)
    execl(shell, shellname, "-c", cmd, NULL);
  else
    execl(shell, shellname, "-i", NULL);
}
