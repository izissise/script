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

int	retransmit(int in, int out1, int out2, int flush)
{
  int	read_ret;
  char	buff[10];

  read_ret = read(in, buff, sizeof(buff));
  if (read_ret > 0)
    {
      write(out1, buff, read_ret);
      if (out2 != -1)
        write(out2, buff, read_ret);
      if (flush)
        fsync(out1);
      if (flush && out2 != -1)
        fsync(out2);
    }
  else if (read_ret == -1)
    {
      perror(NULL);
      return (1);
    }
  return (0);
}

int	io_handling(t_script *s)
{
  fd_set	selectfd;

  close(s->slavefd);
  while (1)
    {
      FD_ZERO(&selectfd);
      FD_SET(0, &selectfd);
      FD_SET(s->masterfd, &selectfd);
      if (select(s->masterfd + 1, &selectfd, NULL, NULL, NULL) == -1)
        break;
      if (FD_ISSET(0, &selectfd))
        retransmit(0, s->masterfd, -1, s->flush);
      else if (FD_ISSET(s->masterfd, &selectfd))
        retransmit(s->masterfd, s->filefd, 1, s->flush);
    }
  close_files(s);
  return (0);
}

