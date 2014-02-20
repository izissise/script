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

int	my_forkpty(t_script *s, struct termios *t)
{
  pid_t	shellpid;

  shellpid = fork();
  if (shellpid > 0)
    {
      if (isatty(0))
        resize_term(s);
      signal(SIGWINCH, &resize_handler);
      if (open_files(s))
        return (1);
      init_term(t, 0);
      io_handling(s, shellpid);
      close_files(s);
      return (0);
    }
  else if (shellpid == 0)
    shell(s);
  else
    {
      perror("Fork");
      return (1);
    }
  return (0);
}

int			main(int ac, char *av[], char *env[])
{
  t_script		script;
  int			master_fd;
  int			slave_fd;
  struct termios	t;

  if (parse_opt(ac, av, env, &script) || my_openpty(&master_fd, &slave_fd))
    return (1);
  script.masterfd = master_fd;
  script.slavefd = slave_fd;
  if ((tcgetattr(0, &t) == -1) || my_forkpty(&script, &t))
    return (1);
  tcsetattr(0, TCSAFLUSH, &t);
  close(master_fd);
  close(slave_fd);
  if (script.returnex)
    return (WEXITSTATUS(script.retvalue));
  return (0);
}
