/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elanna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:06:44 by elanna            #+#    #+#             */
/*   Updated: 2021/06/22 15:30:23 by elanna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <wchar.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

/*
** Structure for bonus part of libft project
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*
** Structure for get_next_line project
*/
typedef struct s_content
{
	char				*buffer;
	int					fd;
	struct s_content	*next;
}				t_content;

/*
** Functions of libft project
*/
void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
							size_t n);
void					*ft_memmove(void *dst, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_strncmp(const char *s1, const char *s2,
							size_t n);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						ft_atoi(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);
char					*ft_strdup(const char *s);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
char					**ft_split(char const *s, char c);
char					*ft_itoa(int n);
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **alst, t_list *new);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					ft_lstadd_back(t_list **alst, t_list *new);
void					ft_lstdelone(t_list *lst, void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
/*
** Start of additionnals independants functions
*/
void					ft_putlenstr_fd(char *s, int fd,
							size_t len);
char					*ft_strtrim_ult(char const *s1,
							char const *set);
void					ft_putchar(char c);
unsigned long long		ft_pow(unsigned long long nb, int power);
char					*ft_uitoa(unsigned int n);
char					*ft_uitobase(unsigned int n,
							char *base);
char					*ft_hexaddr(void *addr);
char					*ft_llitoa(long long n);
char					*ft_ullitoa(unsigned long long n);
char					*ft_ullitobase(unsigned long long n,
							char *base);
void					ft_print_bin_rep(size_t const size,
							void const *ptr);
unsigned long long		ft_bintodec(unsigned long long bin, int start);
int						ft_ishexa(int c);
int						ft_isnumber(char *str);
int						ft_isprintable(char *str);

/*
** Following : All prototypes functions for get_next_line-like.
*/

char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strchr_for_gnl(char *s, int c, int replace);
t_content				*ft_contnew(char *buffer, int fd);
void					ft_contadd_back(t_content **alst, t_content *new);
void					ft_delcont(int fd, t_content **content);
t_content				*ft_lstchr_fd(t_content **lst, int fd);
int						get_content_line(int fd, char **line, ssize_t rd,
							t_content **cont);
void					fill_content_struct(t_content **content, char *buffer,
							int fd);
int						get_next_line(int fd, char **line);

/*
** Following : Functions to print wide characters.
*/
size_t					ft_wcrtomb(char *s, wchar_t wc, mbstate_t *ps);
int						ft_putwstr_fd(wchar_t *w_str, int fd);
int						ft_putlenwstr_fd(wchar_t *w_str,
							int fd, size_t len);

/*
** Following : All prototypes for functions dtoa-like.
** 3 conversions of double to ascii are possible, as those functions
** were made to be used in ft_printf as 'f' (float/double), 'e' (float/double
** with exponent) and 'g' (either f or e, depending of the decimal exponent).
** Some functions of libft are needed to make it work.
** They can be added to libft though it's not well optimised at all.
** For each of them, the precision (number of digits after the '.' or number of
** significants digits) need to be specified.
** Note that a double (64 bits) or float (32 bits) can be 'imprecise' because of
** the way it is stocked inside the memory.
** The number may vary depending of the precision because of that,
** and also because it's rounded.
*/

/*
** Union needed for convertion from double to
** unsigned long long.
*/

typedef union u_dbl_union
{
	double				d;
	unsigned long long	l;
}						t_dbl_union;

/*
** Functions needed for 'f' and useful for others formats
** In : ft_dtoa_bonus.c, ft_dtoa_rounding_bonus.c,
** ft_dtoa_frac_bonus.c & ft_dtoa_ope_bonus.c
*/

char					*apply_dtwo_pten(unsigned int i);
void					apply_ptwo_fill(char **to_add,
							int approx_size);
void					apply_ptwo_init(short exp,
							char **to_add);

char					*del_front_zero(char *to_add,
							int approx_size);
char					*add_chars_to_mall_str(char *mall_str,
							const char *cst, char front_or_end);
void					stock_fill(char **stock_part,
							char *to_add, int s_part, int s_add);
char					*stock_init(char *stock_part,
							char *to_add, char int_or_frac);

unsigned long long		convert_mant_to_frac(unsigned long long mant,
							short exp, unsigned int *i);
char					*get_frac_part(unsigned long long mant,
							short exp);

void					bankers_or_usual_rounding(char **number,
							char **frac_part, unsigned int i);
void					do_rounding(char **number,
							char *frac_part, unsigned i, unsigned size);
char					*get_round_number(char *int_part,
							char *frac_part, int precision);
char					*get_big_int(unsigned long long int_part,
							short exp);
char					*get_int_part(unsigned long long mant,
							short exp);
char					*get_dtoa_number(unsigned long long mant,
							short exp, int precision, int show_exp);
char					*ft_dtoa(double dbl, int precision,
							int show_exp);

/*
** Functions needed for 'e' format
** In : ft_dtoa_exp_bonus.c
*/

char					*add_exp(int exp, char *number,
							int shortest_rep);
void					fill_round_exp_number(char **number,
							int size, int limit_size);
void					exp_rounding_operation(char **number,
							int *exp, int i);
void					do_exp_rounding(char **number, int *exp,
							int precision);
char					*get_round_exp_number(char *int_part,
							char *frac_part, int precision);

/*
** Functions needed for 'g' format
** In : ft_dtoa_shortrep_bonus.c
** & ft_dtoa_shortrep_utils_bonus.c
*/

void					del_last_zero(char **number, int size);
int						exp_after_rounding(char **number, int exp,
							int precision, int int_size);
void					adjust_precision(char *int_part,
							char *frac_part, int *precision);
void					adjust_number(char **number);

char					*check_exp_for_format(int exp, char *int_part,
							char *frac_part, int precision);
char					*get_number_shortest_rep(char *int_part,
							char *frac_part, int precision);
char					*get_dtoa_shortest_rep(unsigned long long mant,
							short exp, int precision);
char					*ft_dtoa_shortest_rep(double dbl,
							int precision);

#endif
