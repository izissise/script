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

int	open_files(t_script *s)
{
  int	oopt;

  oopt = O_WRONLY | O_CREAT | (s->append ? O_APPEND : 0);
  if (((s->filefd = open(s->file, oopt, 0666)) != -1)
      && (1))
    {
      //open also timing and output start date
      if (!s->quiet)
        dprintf(STDERR_FILENO, "Script started, file is %s\n", s->file);
      return (0);
    }
  perror("open_files");
  return (1);
}

int	close_files(t_script *s)
{
  //close also timing and output end date
  if (!s->quiet)
    dprintf(STDERR_FILENO, "Script done, file is %s\n", s->file);
  if (close(s->filefd) == -1)
    {
      perror("close_files");
      return (1);
    }
  return (0);
}

