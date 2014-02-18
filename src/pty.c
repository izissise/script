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

char	*my_ptsname(int fd)
{
  int	sminor;
  char	pts_name[40];

  if (ioctl(fd, TIOCGPTN, &sminor) < 0)
    return (NULL);
  snprintf(pts_name, sizeof(pts_name), "/dev/pts/%d", sminor);
  return (strdup(pts_name));
}

int	my_grantpt(int fd)
{
  char	*name;
  int	ret;

  name = my_ptsname(fd);
  ret = chmod(name, S_IRUSR | S_IWUSR | S_IWGRP);
  ret |= chown(name, getuid(), -1);
  free(name);
  return (ret);
}

int	my_unlockpt(int fd)
{
  int	lock;

  lock = 0;
  return (ioctl(fd, TIOCSPTLCK, &lock));
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
  perror(NULL);
  close(*amaster);
  close(*aslave);
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
