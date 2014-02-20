/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef INCLUDE_H_INCLUDED
# define INCLUDE_H_INCLUDED

# define _GNU_SOURCE
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <getopt.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/select.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <unistd.h>
# include <pty.h>
# include <time.h>
# include <paths.h>

typedef struct	s_script
{
  char		*shell;
  char		*cmd;
  char		*file;
  char		append;
  char		returnex;
  char		flush;
  char		force;
  char		quiet;
  char		timing;
  char		*timingout;
  int		masterfd;
  int		slavefd;
  int		retvalue;
  int		filefd;
  int		timingfd;
}		t_script;

char	*get_envvar(char *var, char **env);
int	parse_opt(int ac, char **av, char **envp, t_script *script);
char	*my_ptsname(int fd);
int	my_grantpt(int fd);
int	my_unlockpt(int fd);
int	my_openpty(int *amaster, int *aslave);
int	my_login_tty(int slave);
int	init_term(struct termios *cpy, int ttyout);
int	open_files(t_script *s);
int	close_files(t_script *s);
void	exec_command(char *shell, char *cmd);
int	io_handling(t_script *s, pid_t shellpid);
void	shell(t_script *s);
int	mwrite(int fd, void *buff, int size);
int	gset_resize(int resize);
void	resize_handler(int sig);
int	resize_term(t_script *s);

#endif /* !INCLUDE_H_ */
