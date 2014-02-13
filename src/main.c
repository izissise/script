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
    return (0);
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
    return (0);
  return (1);
}

void	restore_term(struct termios *t, int ttyout)
{
  tcsetattr(ttyout, TCSANOW, t);
}

int	my_openpty(int *amaster, int *aslave, char *name)
{

}

int	main(int ac, char *av[], char *env[])
{
  t_script	script;
  int		master_fd;
  char		*slave_name;
  int		slave_fd;
  struct termios	t;

  if (parse_opt(ac, av, env, &script))
    return (1);
  pid_t pid =  forkpty(&master_fd, slave_name, &t, NULL);
  if (pid == 0)
    {

      return (0);
    }
  else
    {
      if (!init_term(&t, master_fd))
        return (1);
    }

  /* master_fd = getpt();
   slave_name = ptsname(master_fd);
   slave_fd = open(slave_name, O_RDWR);
   if (!grantpt(slave_fd))
     {
     }

   if (!unlockpt(slave_fd))
     {
     }

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
  return (0);
}
