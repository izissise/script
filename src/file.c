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

int		check_symlink(t_script *s, char *file)
{
  struct stat	sn;

  if (s->force)
    return (0);
  if (lstat(file, &sn) == 0 && (S_ISLNK(sn.st_mode) || sn.st_nlink > 1))
    {
      fprintf(stderr, "output file `%s' is a link\nUse --force if you really w"
              "ant to use it.\nProgram not started.", file);
      return (1);
    }
  return (0);
}

int	open_files(t_script *s)
{
  int	oopt;

  oopt = O_WRONLY | O_CREAT | (s->append ? O_APPEND : O_TRUNC);
  if (((s->filefd = open(s->file, oopt, 0666)) != -1)
      && (1))
    {
      if (check_symlink(s, s->file) || check_symlink(s, s->timingout))
        return (1);
      //open also timing
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
  //close also timing
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

