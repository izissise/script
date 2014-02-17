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
  if (!(my_login_tty(s->slavefd) || init_term(t, s->slavefd)))
    {
      close(s->slavefd);
      setsid();
      ioctl(0, TIOCSCTTY, 1);
      exec_command(s->shell);
    }
  close(s->slavefd);
  close_files(s);
  perror(NULL);
  exit(1);
}

pid_t	my_forkpty(t_script *s, struct termios *t)
{
  pid_t	shellpid;
  int	ret;

  shellpid = fork();
  if (shellpid > 0)
    {
      if (open_files(s))
        return (1);
      else
        {
          io_handling(s);
          ret = waitpid(shellpid, &(s->retvalue), 0);
          return (0);
        }
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
  if ((tcgetattr(slave_fd, &t) == -1) || my_forkpty(&script, &t))
    return (1);
  tcsetattr(master_fd, TCSANOW, &t);
  close(master_fd);
  return (0);
}
