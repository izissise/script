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

  memcpy(&t, cpy, sizeof(t));
  t.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR
                 | ICRNL | IXON);
  //t.c_oflag &= ~OPOST;
  t.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  t.c_cflag &= ~(CSIZE | PARENB);
  t.c_cflag |= CS8;
  if (tcsetattr(ttyout, TCSANOW, &t) != -1)
    return (0);
  perror(NULL);
  return (1);
}
