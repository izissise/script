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
  char	buff[4096];

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
      return (read_ret);
    }
  else if (read_ret == -1)
    {
      perror(NULL);
      return (1);
    }
  return (0);
}

void	calc_timing(t_script *s, clock_t *start, clock_t *end, int nbread)
{
  if (s->timing && nbread > 0)
    {
      *end = clock();
      dprintf(s->timingfd, "%f %d\n",
              (double)((double)*end - (double)*start) / CLOCKS_PER_SEC, nbread);
      *start = *end;
    }
}

int	io_handling(t_script *s)
{
  fd_set	selectfd;
  clock_t	start;
  clock_t	end;
  int	nbread;

  close(s->slavefd);
  while (1)
    {
      start = clock();
      FD_ZERO(&selectfd);
      FD_SET(0, &selectfd);
      FD_SET(s->masterfd, &selectfd);
      if (select(s->masterfd + 1, &selectfd, NULL, NULL, NULL) == -1)
        break;
      if (FD_ISSET(0, &selectfd))
        retransmit(0, s->masterfd, s->filefd, s->flush);
      else if (FD_ISSET(s->masterfd, &selectfd))
        {
          nbread = retransmit(s->masterfd, s->filefd, 1, s->flush);
          calc_timing(s, &start, &end, nbread);
        }
    }
  close_files(s);
  return (0);
}

