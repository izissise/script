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

int			init_term(struct termios *cpy, int ttyout)
{
  struct termios	t;
  int			i;

  i = -1;
  if (tcgetattr(ttyout, cpy) == -1)
    return (1);
  t.c_iflag = cpy->c_iflag;
  t.c_oflag = cpy->c_oflag;
  t.c_cflag = cpy->c_cflag;
  t.c_lflag = cpy->c_lflag;
  t.c_line = cpy->c_line;
  while (i++ < NCCS)
    t.c_cc[i] = cpy->c_cc[i];
  t.c_ispeed = cpy->c_ispeed;
  t.c_ospeed = cpy->c_ospeed;
  UNSETFLAG(t.c_lflag, (ECHO | ICANON));
  t.c_cc[VTIME] = 100;
  if (tcsetattr(ttyout, TCSANOW, &t) == -1)
    return (1);
  return (0);
}

char	*my_ptsname(int fdm)
{
  int	sminor;
  char	pts_name[20];

  if (ioctl(fdm, TIOCGPTN, &sminor) < 0)
    return(NULL);
  snprintf(pts_name, sizeof(pts_name), "/dev/pts/%d", sminor);
  return(strdup(pts_name));
}

int	my_grantpt(int fd)
{
  char	*name;
  int	ret;

  name = my_ptsname(fd);
  ret = (chmod(name, S_IRUSR | S_IWUSR | S_IWGRP));
  free(name);
  return (ret);
}

int	my_unlockpt(int fd)
{
  int	lock;

  lock = 0;
  return ioctl(fd, TIOCSPTLCK, &lock);
}

int	my_openpty(int *amaster, int *aslave)
{
  char	*slave_name;

  *amaster = -1;
  *aslave = -1;
  slave_name = NULL;
  if (((*amaster = getpt()) != -1)
      && ((slave_name = my_ptsname(*amaster)) != NULL)
      && (my_grantpt(*amaster) != -1) && (my_unlockpt(*amaster) != -1)
      && ((*aslave = open(slave_name, O_RDWR)) != -1))
    {
      free(slave_name);
      return (0);
    }
  free(slave_name);
  close(*amaster);
  close(*aslave);
  perror(NULL);
  return (1);
}

int	my_login_tty(int slave)
{
  if ((dup2(slave, STDIN_FILENO) != -1) && (dup2(slave, STDOUT_FILENO) != -1)
      && (dup2(slave, STDERR_FILENO) != -1))
    return (0);
  perror(NULL);
  return (1);
}

pid_t	my_forkpty(t_script *s, int master, int slave, struct termios* t)
{
  pid_t	child;
  child = fork();
  if (child > 0)
    {
      if (init_term(t, master))
        {
          perror(NULL);
          close(master);
          close(slave);
          return (1);
        }
        //open file append ?
        //write stuff if not quiet
        //while read
        //write stuff if not quiet
        //close
    }
  else if (child == 0)
    {
      my_login_tty(slave);
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
  if ((my_forkpty(&script, master_fd, slave_fd, &t)) == 0)
    return (1);
  /*
   printf("shell: %s, file: %s, append: %d, returnex: %d, flush: %d, force: %d, quiet: %d, timing: %d\n",
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



