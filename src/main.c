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

void	shell(t_script *s, struct termios *t)
{
  close(s->masterfd);
  close(s->filefd);
  setsid();
  ioctl(s->slavefd, TIOCSCTTY, 1);
  if (!(my_login_tty(s->slavefd) || init_term(t, s->slavefd)))
    {
      close(s->slavefd);
      exec_command(s->shell, s->cmd);
    }
  close(s->slavefd);
  perror(NULL);
  exit(-1);
}

int	my_forkpty(t_script *s, struct termios *t)
{
  pid_t	shellpid;

  shellpid = fork();
  if (shellpid > 0)
    {
      if (open_files(s))
        return (1);
      else
        return (io_handling(s, shellpid));
    }
  else if (shellpid == 0)
    shell(s, t);
  else
    {
      perror(NULL);
      return (1);
    }
  return (0);
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
  if ((my_forkpty(&script, &t)))
    return (1);
  tcsetattr(master_fd, TCSANOW, &t);
  close(master_fd);
  close(slave_fd);
  if (script.returnex)
    return (WEXITSTATUS(script.retvalue));
  return (0);
}
