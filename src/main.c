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

pid_t	my_forkpty(t_script *s, struct termios* t)
{
  pid_t	child;
  child = fork();
  if (child > 0)
    {
      close(s->slavefd);
      if (init_term(t, s->masterfd))
        return (1);
      //open file append ?
      //write stuff if not quiet
      //while wait waitpid(cmd->pid.pid, &(cmd->return_value), WNOHANG);
      //read
      //write stuff if not quiet
      //close
    }
  else if (child == 0)
    {
      close(s->masterfd);
      my_login_tty(s->slavefd);
      execlp(s->shell, s->shell);
      exit(-1);
    }
  else
    {
      perror(NULL);
      return (0);
    }
  return (child);
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
  /*printf("shell: %s, file: %s, append: %d, returnex: %d, flush: %d, force: %d, quiet: %d, timing: %d\n",
          script.shell,
          script.file,
          script.append,
          script.returnex,
          script.flush,
          script.force,
          script.quiet,
          script.timing
         );*/
  tcsetattr(master_fd, TCSANOW, &t);
  close(master_fd);
  close(slave_fd);
  return (0);
}



