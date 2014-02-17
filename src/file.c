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

void	output_time(char *format, int fd)
{
  time_t	ctime;
  char	timebuff[4096];

  ctime = time(NULL);
  strftime(timebuff, sizeof(timebuff), format, localtime(&ctime));
  write(fd, timebuff, strlen(timebuff));
}

int	open_files(t_script *s)
{
  int	oopt;

  oopt = O_WRONLY | O_CREAT | (s->append ? O_APPEND : O_TRUNC);
  if (((s->filefd = open(s->file, oopt, 0666)) != -1)
      && (1))
    {
      //open also timing and output start date
      output_time("Script started on %c\n", s->filefd);
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
    {
      dprintf(STDERR_FILENO, "Script done, file is %s\n", s->file);
      output_time("Script finished on %c\n", s->filefd);
    }
  if (close(s->filefd) == -1)
    {
      perror("close_files");
      return (1);
    }
  return (0);
}

