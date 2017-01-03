/*
** get_next_line.c for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Mon Jan  2 10:17:21 2017 Arthur Baurens
** Last update Tue Jan  3 14:48:18 2017 Arthur Baurens
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

static int	gnl_strlen(const char *str, char c)
{
  int		i;

  i = -1;
  while (str != NULL && str[++i] && str[i] != c);
  return ((str != NULL) * i);
}

static char	*gnl_strncat(const char *s1, const char *s2, int l, char n)
{
  int		i;
  int		j;
  int		ln;
  char		*res;

  if ((ln = gnl_strlen(s1, '\0') + gnl_strlen(s2, '\0')) > l && l >= 0)
    ln = l;
  if (ln == 0 && n)
    return (NULL);
  if ((res = malloc(sizeof(char) * (ln + 1))) == NULL)
    return (NULL);
  res[ln] = '\0';
  i = 0;
  while (s1 && i < ln && s1[i])
    {
      res[i] = s1[i];
      i++;
    }
  j = -1;
  while (s2 && s2[++j] && i + j < ln)
    res[i + j] = s2[j];
  return (res);
}

char	is_line(const char *str)
{
  int	i;

  i = -1;
  while (str && str[++i])
    {
      if (str[i] == '\n')
	return (1);
    }
  return (0);
}

/*
**	anciene version
** char		*get_next_line(const int fd)
** {
**   char		eof;
**   int		rd;
**   int		len;
**   char		*tmp;
**   char		*line;
**   static char	*save = NULL;
**   char		buff[READ_SIZE + 1];
**
**   eof = 0;
**   while (1)
**     {
**       if ((len = gnl_strlen(save, '\n')) < gnl_strlen(save, '\0') || eof == 1)
** 	{
**
** 	  line = gnl_strncat(NULL, save, len, eof);
** 	  tmp = save;
** 	  save = (save && save[len] ? gnl_strncat(NULL, &save[len + 1], -1, 0) : NULL);
** 	  free(tmp);
** 	  return (line);
** 	}
**       else
** 	{
** 	  if ((rd = read(fd, buff, READ_SIZE)) < 0)
** 	    return (NULL);
** 	  else if (rd == 0)
** 	    eof = 1;
** 	  else
** 	    {
** 	      buff[rd] = '\0';
** 	      tmp = save;
** 	      save = gnl_strncat(save, buff, -1, 0);
** 	      free(tmp);
** 	    }
** 	}
**     }
** }
*/
char		*get_next_line(const int fd)
{
  int		ln[3];
  char		*line[2];
  static char	*save = NULL;
  char		buff[READ_SIZE + 1];

  ln[2] = 0;
  while ((ln[0] = gnl_strlen(save, '\n')) == gnl_strlen(save, '\0') && !ln[2])
    {
      if ((ln[1] = read(fd, buff, READ_SIZE)) < 0)
	return (NULL);
      else if (ln[1] == 0)
	ln[2] = 1;
      else
	{
	  buff[ln[1]] = '\0';
	  line[1] = save;
	  save = gnl_strncat(save, buff, -1, 0);
	  free(line[1]);
	}
    }
  line[0] = gnl_strncat(NULL, save, ln[0], ln[2]);
  line[1] = save;
  save = (save && save[ln[0]] ? gnl_strncat(NULL, &save[ln[0] + 1], -1, 0) : NULL);
  free(line[1]);
  return (line[0]);
}
int	main(int ac, char **av)
{
  int	fd;
  char	*line;

  if (ac != 2)
    return (0);
  fd = open(av[1], O_RDONLY);
  while (line = get_next_line(fd))
    {
      printf("line : %s\n", line);
      free(line);
    }
  line = get_next_line(fd);
  printf("lineN : %s\n", line);
  line = get_next_line(fd);
  printf("lineN : %s\n", line);
  line = get_next_line(fd);
  printf("lineN : %s\n", line);
  return (0);
}
