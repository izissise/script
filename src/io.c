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
  int	write_ret;
  char	buff[4096];

  read_ret = read(in, buff, sizeof(buff));
  write_ret = 0;
  if (read_ret > 0)
    {
      write_ret = write(out1, buff, read_ret);
      if (out2 != -1)
        write_ret = write(out2, buff, read_ret);
      if (flush)
        fsync(out1);
      if (flush && out2 != -1)
        fsync(out2);
      return (read_ret);
    }
  else if (read_ret == -1 || write_ret == -1)
    {
      perror(NULL);
      return (1);
    }
  return (0);
}

void		calc_timing(t_script *s, struct timespec *start,
                    struct timespec *end, int nbread)
{
  size_t	elapsed;

  if (s->timing && nbread >= 0)
    {
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, end);
      elapsed = (end->tv_sec - start->tv_sec) * 1000000000
                + (end->tv_nsec - start->tv_nsec);
      dprintf(s->timingfd, "%f %d\n", ((elapsed) / 250000.0), nbread);
      *start = *end;
    }
}

int	redirect(t_script *s, fd_set *sfd,
             struct timespec *start, struct timespec *end)
{
  int	nbread;

  nbread = 0;
  if (FD_ISSET(0, sfd))
    nbread = retransmit(0, s->masterfd, -1, s->flush);
  else if (FD_ISSET(s->masterfd, sfd))
    {
      nbread = retransmit(s->masterfd, s->filefd, 1, s->flush);
      calc_timing(s, start, end, nbread);
    }
  return ((nbread == -1) ? 1 : 0);
}

int			io_handling(t_script *s, pid_t shellpid)
{
  fd_set		selectfd;
  struct timespec	start;
  struct timespec	end;

  close(s->slavefd);
  while (1)
    {
      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
      FD_ZERO(&selectfd);
      FD_SET(0, &selectfd);
      FD_SET(s->masterfd, &selectfd);
      if (select(s->masterfd + 1, &selectfd, NULL, NULL, NULL) == -1)
        break;
      if (waitpid(shellpid, &(s->retvalue), WNOHANG) > 0)
        {
          calc_timing(s, &start, &end,
                      retransmit(s->masterfd, s->filefd, 1, s->flush));
          return (0);
        }
      if (redirect(s, &selectfd, &start, &end) == -1)
        break;
    }
  perror(NULL);
  return (1);
}
