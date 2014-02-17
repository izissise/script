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

  memset(script, 0, sizeof(t_script));
  script->file = "typescript";
  script->shell = _PATH_BSHELL;
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
  dprintf(STDERR_FILENO, "Usage:\n");
  dprintf(STDERR_FILENO, " script [options] [file]\n");
  dprintf(STDERR_FILENO, "Options:\n");
  dprintf(STDERR_FILENO, " -a, --append            append the output\n");
  dprintf(STDERR_FILENO, " -c, --command <command> run command rather than int"
          "eractive shell\n");
  dprintf(STDERR_FILENO, " -r, --return            return exit code of the chi"
          "ld process\n");
  dprintf(STDERR_FILENO, " -f, --flush             run flush after each write"
          "\n");
  dprintf(STDERR_FILENO, "     --force             use output file even when i"
          "t is a link\n");
  dprintf(STDERR_FILENO, " -q, --quiet             be quiet\n");
  dprintf(STDERR_FILENO, " -t, --timing[=<file>]   output timing data to stder"
          "r (or to FILE)\n");
  dprintf(STDERR_FILENO, " -V, --version           output version information "
          "and exit\n");
  dprintf(STDERR_FILENO, " -h, --help              display this help and exit"
          "\n");
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
      c = getopt_long(ac, av, "ac: efqt::vh", options, &option_index);
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
        script->cmd = optarg;
    }
  if (optind != ac)
    script->file = av[optind];
  return (0);
}
