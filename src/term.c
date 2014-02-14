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
  if (tcgetattr(ttyout, cpy) != -1)
    {
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
      if (tcsetattr(ttyout, TCSANOW, &t) != -1)
        return (0);
    }
  perror(NULL);
  close(ttyout);
  return (1);
}