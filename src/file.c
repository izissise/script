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
  dprintf(fd, "%s", timebuff);
}

int		check_symlink(t_script *s, char *file)
{
  struct stat	sn;

  if (s->force || file == NULL)
    return (0);
  if (lstat(file, &sn) == 0 && (S_ISLNK(sn.st_mode) || sn.st_nlink > 1))
    {
      dprintf(STDERR_FILENO, "Output file `%s' is a link\nUse --force if you r"
              "eally want to use it.\nProgram not started.", file);
      return (1);
    }
  return (0);
}

int	open_files(t_script *s)
{
  int	oopt;

  oopt = O_WRONLY | O_CREAT | (s->append ? O_APPEND : O_TRUNC);
  if (check_symlink(s, s->file) || check_symlink(s, s->timingout))
    return (1);
  if (s->timing)
    s->timingfd = (s->timingout != NULL) ? (open(s->timingout, oopt, 0664))
                  : STDERR_FILENO;
  if ((s->timingfd != -1) && ((s->filefd = open(s->file, oopt, 0664)) != -1))
    {
      output_time("Script started on %c\n", s->filefd);
      if (!s->quiet)
        dprintf(STDIN_FILENO, "Script started, file is %s\n", s->file);
      return (0);
    }
  perror("open_files");
  return (1);
}

int	close_files(t_script *s)
{
  if (!s->quiet)
    {
      dprintf(STDIN_FILENO, "Script done, file is %s\n", s->file);
      output_time("Script finished on %c\n", s->filefd);
    }
  if (s->timing && s->timingfd != STDERR_FILENO)
    close(s->timingfd);
  if (close(s->filefd) == -1)
    {
      perror("close_files");
      return (1);
    }
  return (0);
}

