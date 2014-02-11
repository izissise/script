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

void	init_single_opt(struct option *opt, char *name, int has_arg, int ln)
{
  opt->name = name;
  opt->has_arg = has_arg;
  opt->flag = NULL;
  opt->val = ln;
}

void	init_opt(char **envp, t_script *script, struct option *opt)
{
  char	*tmp;

  script->file = "typescript";
  script->returnex = 0;
  script->append = 0;
  script->flush = 0;
  script->force = 0;
  script->quiet = 0;
  script->timing = 0;
  script->timingout = NULL;
  script->shell = "/bin/sh";
  if ((tmp = get_envvar("SHELL", envp)))
    script->shell = tmp;
  init_single_opt(&(opt[0]), "append", no_argument, 'a');
  init_single_opt(&(opt[1]), "command", required_argument, 'c');
  init_single_opt(&(opt[2]), "return", no_argument, 'e');
  init_single_opt(&(opt[3]), "flush", no_argument, 'f');
  init_single_opt(&(opt[4]), "force", no_argument, 'i');
  init_single_opt(&(opt[5]), "quiet", no_argument, 'q');
  init_single_opt(&(opt[6]), "timing", optional_argument, 't');
  init_single_opt(&(opt[7]), "version", no_argument, 'v');
  init_single_opt(&(opt[8]), "help", no_argument, 'h');
  init_single_opt(&(opt[9]), NULL, 0, 0);
}

int		help()
{
  fprintf(stderr, "Version 48, moriss_h\n");
  fprintf(stderr, "Help there\n");
  return (1);
}

int			parse_opt(int ac, char **av, char **envp, t_script *script)
{
  struct option	options[10];
  int			c;
  int			option_index;

  init_opt(envp, script, options);
  c = 0;
  while (c != -1)
    {
      c = getopt_long(ac, av, "ac:efqt::vh", options, &option_index);
      script->append |= (c == 'a');
      script->returnex |= (c == 'e');
      script->flush |= (c == 'f');
      script->force |= (c == 'i');
      script->quiet |= (c == 'q');
      if (!(script->timing) && (script->timing |= (c == 't')))
        script->timingout = optarg;
      if (c == 'v' || c == 'h')
        return (help());
      if (c == 'c')
        script->shell = optarg;
    }
  if (optind != ac)
    script->file = av[optind];
  return (0);
}
