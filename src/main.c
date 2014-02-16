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

int	retransmit(int in, int out1, int out2)
{
  int	read_ret;
  char	buff[4096];

  while ((read_ret = read(in, buff, 4096)) > 0)
    {
      write(out1, buff, read_ret);
      if (out2 != -1)
        write(out2, buff, read_ret);
    }
  if (read_ret == -1)
    {
      perror("retransmits");
      return (1);
    }
  return (0);
}

pid_t	my_forkpty(t_script *s, struct termios *t)
{
  pid_t	shellpid;
  pid_t	childio;
  int	waitret;

  shellpid = fork();
  if (shellpid > 0)
    {
      if (open_files(s))
        return (1);

      childio = fork();
      if (childio > 0)
        {
          while ((waitret = waitpid(shellpid, &(s->retvalue), WNOHANG)) == 0)
            retransmit(s->masterfd, s->filefd, 1);
          waitret = waitpid(childio, &waitret, 0);
        }
      else
        {
          retransmit(0, s->slavefd, -1);
        }
    }
  else if (shellpid == 0)
    {
      close(s->masterfd);
      if (!(my_login_tty(s->slavefd) || init_term(t, s->slavefd)))
        {
          //close(s->slavefd);
          exec_command(s->shell);
        }
      perror(NULL);
      exit(-1);
      close(s->slavefd);
    }
  else
    {
      perror(NULL);
      return (0);
    }
  return (shellpid);
}

int	main(int ac, char *av[], char *env[])
{
  t_script	script;
  int		master_fd;
  int		slave_fd;
  struct termios	t;

  if (parse_opt(ac, av, env, &script) || my_openpty(&master_fd, &slave_fd))
    return (1);
  script.masterfd = master_fd;
  script.slavefd = slave_fd;
  if ((my_forkpty(&script, &t)) == 0)
    return (1);
  tcsetattr(master_fd, TCSANOW, &t);
  close(master_fd);
  close(slave_fd);
  return (0);
}



