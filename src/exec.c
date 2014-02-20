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

int	mwrite(int fd, void *buff, int size)
{
  int	len;

  while ((len = write(fd, buff, size)) != size)
    {
      if ((len == -1) && (errno != EINTR))
        return (-1);
      buff = &(((char*)buff)[len]);
      size -= len;
    }
  return (0);
}

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

void	shell(t_script *s)
{
  close(s->masterfd);
  close(s->filefd);
  setsid();
  if ((ioctl(s->slavefd, TIOCSCTTY, 1) != -1) && !my_login_tty(s->slavefd))
    {
      close(s->slavefd);
      exec_command(s->shell, s->cmd);
    }
  close(s->slavefd);
  perror("Exec");
  exit(1);
}
