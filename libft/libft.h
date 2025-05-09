/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgretic <bgretic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:37:32 by bgretic           #+#    #+#             */
/*   Updated: 2024/09/19 19:04:23 by bgretic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t				ft_linelen(char **str_arr);

char				*get_next_line(int fd, int *error);

char				*ft_strchr(const char *str, int c);

void				free_str_arr(char ***arr);

void				free_that(char **buffer);

char				*ft_strdup(const char *s);

char				*ft_strjoin(const char *s1, const char *s2);

int					ft_printf(const char *str, ...);

size_t				ft_print_c(int c);

size_t				ft_print_s(char *arg);

size_t				ft_print_d(int n);

size_t				ft_print_u(unsigned int n);

size_t				ft_print_x(unsigned int x);

size_t				ft_print_upper_x(unsigned int X);

size_t				ft_print_p(void *p);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstadd_front(t_list **lst, t_list *new);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstclear(t_list **lst, void (*del)(void *));

void				ft_lstdelone(t_list *lst, void (*del)(void *));

t_list				*ft_lstnew(void *content);

int					ft_lstsize(t_list *lst);

int					ft_atoi(const char *nptr);

void				ft_bzero(void *s, size_t n);

void				*ft_calloc(size_t nmemb, size_t size);

void				*ft_realloc(void *old_memory, size_t old_size,
						size_t new_size);

int					ft_isalnum(int argument);

int					ft_isalpha(int argument);

int					ft_isascii(int c);

int					ft_isdigit(int arg);

int					ft_isprint(int c);

void				*ft_memchr(const void *s, int c, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memcpy(void *dest, const void *src, size_t n);

void				*ft_memmove(void *dest, const void *src, size_t n);

void				*ft_memset(void *s, int c, size_t n);

char				*ft_strchr(const char *str, int c);

char				*ft_strdup(const char *s);

size_t				ft_strlcat(char *dest, const char *src, size_t size);

size_t				ft_strlcpy(char *dest, const char *src, size_t size);

size_t				ft_strlen(const char *str);

bool				ft_cmp(char *s1, char *s2);

int					ft_strncmp(const char *str1, const char *str2, size_t num);

char				*ft_strnstr(const char *big, const char *little,
						size_t len);

char				*ft_strrchr(char *str, int c);

int					ft_tolower(int ch);

int					ft_toupper(int ch);

char				*ft_substr(char const *s, unsigned int start, size_t len);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(char const *s1, char const *set);

char				*ft_itoa(int n);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

void				ft_putchar_fd(char c, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_putnbr_fd(int nb, int fd);

char				**ft_split(char const *s, char c);

#endif
