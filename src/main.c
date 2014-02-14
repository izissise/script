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
      write(out2, buff, read_ret);
    }
  if (read_ret == -1)
    {
      perror(NULL);
      return (1);
    }
  return (0);
}

int	open_and_transmit(t_script *s, pid_t shellpid)
{
  int	file;
  int	timingfd;
  int	oopt;
  int	waitret;

  oopt = O_WRONLY | O_CREAT | (s->append ? O_APPEND : 0);
  if (((file = open(s->file, oopt, 0666)) != -1)
      && (1))
    {
      if (!s->quiet)
        dprintf(STDERR_FILENO, "Script started, file is %s\n", s->file);
      while ((waitret = waitpid(shellpid, &(s->retvalue), WNOHANG)) == 0)
        retransmit(s->masterfd, file, 1);
      close(file);
      if (!s->quiet)
        dprintf(STDERR_FILENO, "Script done, file is %s\n", s->file);
      if (waitret != -1)
        return (0);
    }
  perror(NULL);
  return (1);
}

pid_t	my_forkpty(t_script *s, struct termios *t)
{
  pid_t	child;
  pid_t	child2;

  child = fork();
  if (child > 0)
    {
      if (open_and_transmit(s, child))
        return (1);
    }
  else if (child == 0)
    {

      child2 = fork();
      if (child2)
        {
        }
      close(s->masterfd);
      if (!(my_login_tty(s->slavefd) || init_term(t, s->slavefd)))
        execlp(s->shell, s->shell);
      perror(NULL);
      exit(-1);
      close(s->slavefd);
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



