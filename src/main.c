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

int	main(int ac, char *av[], char *env[])
{
  t_script	script;

  if (parse_opt(ac, av, env, &script))
    return (1);
  return (0);
}
