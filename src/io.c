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

  while ((read_ret = read(in, buff, sizeof(buff))) > 0)
    {
      write(out1, buff, read_ret);
      if (out2 != -1)
        write(out2, buff, read_ret);
      if (flush)
        fsync(out1);
      if (flush && out2 != -1)
        fsync(out2);
    }
  if (read_ret == -1)
    {
      perror(NULL);
      return (1);
    }
  return (0);
}

int	io_handling(t_script *s, pid_t shellpid)
{
  pid_t	childio;
  int	waitret;

  childio = fork();
  if (childio > 0)
    {
      close(s->slavefd);
      retransmit(s->masterfd, s->filefd, 1, s->flush);
      printf("waiting\n");
      waitret = waitpid(childio, &waitret, 0);
      waitret = waitpid(shellpid, &(s->retvalue), 0);
      close(s->masterfd);
      close_files(s);
    }
  else if (childio == 0)
    {
      retransmit(0, s->masterfd, s->filefd, s->flush);
      close(s->slavefd);
      close(s->masterfd);
      close(s->filefd);
      printf("bye\n");
      exit(0);
    }
  else
    {
      perror(NULL);
      return (1);
    }
  return (0);
}

