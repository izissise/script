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
  printf("shell: %s, file: %s, append: %d, returnex: %d, flush: %d, force: %d, quiet: %d, timing: %d\n",
         script.shell,
         script.file,
         script.append,
         script.returnex,
         script.flush,
         script.force,
         script.quiet,
         script.timing
        );
  return (0);
}
