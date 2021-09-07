/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:55:23 by anadege           #+#    #+#             */
/*   Updated: 2021/09/07 14:59:07 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>

#define PROMPT_MSG "\033[1;38;5;51mPrompt > \033[0m"

/*
** Enum utile dans le cas ou la ligne de commande contiendrait
** un builtin.
** Ajout d'une valeur LAUNCH dans le cas ou la ligne de commande
** voudrait lancer un execuable (vraiment utile ?).
*/
typedef enum e_builtin
{
	NONE,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	LAUNCH
} t_builtin ;

/*
** Enum pour identifier le type de token stocke dans la
** structure t_cmd
*/
typedef enum e_tokentype
{
	IDENTIFIER,
	ASSIGNEMENT,
	OPERATOR,
	STRING
} t_tokentype ;

/*
** Structure de type liste chainee pour stocker la ligne
** de commande parsee
*/
typedef struct s_token
{
	char			*token;
	int				length;
	t_tokentype		type;
	struct s_token	*prev;
	struct s_token	*next;
} t_token ;

/*
** MINISHELL INFORMATION STRUCTURE
** Pour le moment, ne stock que les variables environnementales dans 
** un tableau char **env (autre possibilité : stocker dans liste
** chaînée).
*/
typedef struct s_infos
{
	char	*prompt;
	char	*curr_cmd;
	t_token	*cmd_tokens;
	int		fd_history;
	char	**env;
	int		last_exit_status; // Pour stocke le last exit status qui peut être appelé avec la variable $?
} t_infos ;

/*
** AFFICHAGE DU PROMPT / BULTIN PWD
** Quelques fonctions pour obtenir un affichage "propre" du
** prompteur sous le format :
** nom_du_prompteur > fichier_courant
** get_curr_dir permet d'obtenir le dossier courant, et simplifie
** HOME par ~ lorsque prompt est != 0. Il peut être utilisé pour obtenir
** le dossier courant lors de l'appel au bultin PWD.
*/
void	simplify_prompt_curr_dir(char **prompt);
char	*get_curr_dir(int prompt);
char	*get_prompt(void);

/*
** GESTION DE L'HISTORIQUE
** Fonction permettant de récupérer l'historique des appels précédents
** du programme minishell.
** Permet de stocker les lignes de commandes dans un fichier minishell_history.
** Le fichier est lu et chaque ligne est ajoutée à l'historique de readline
** pour pouvoir y accèder en appuyant sur la flèche du haut.
*/
int		get_previous_history(void);
void	add_line_to_history(int history_fd, char *str);

/*
** GESTION BUILTIN CD
** Attention, n'affiche pas message erreur si mauvais path (à ajouter).
*/
int		change_directory(char *new_dir_path);


/*
** GESTION BUILTINS ENV / EXPORT / UNSET
** Reminder : Appeler save_end au début du script du minishell pour stocker les
** variables d'environnements.
** La fonction add_elem_to_env doit être appelé lorsque le builtin
** EXPORT est appelé SOUS CONDITION que le format soit correct.
** La fonction show_env doit être appelée lorsque le builtin ENV est appelé.
*/
int		fill_env_with_deletion(char ***env, int elem_pos, int env_size);
int		delete_elem_from_env(char ***env, char *elem);
int		add_not_existing_elem_to_env(char ***env, char *new_elem, int env_size);
int		modify_existing_elem_to_env(char **env, char *new_elem, char *elem_name);
int		add_elem_to_env(char ***env, char *new_elem);
char	*get_elem_name(char *elem);
char	*get_env_elem(char **env, char *elem);
int		seek_elem_pos(char **env, char *elem_name);
void	show_env(char **env);
void	free_env(char **env, int last);
int		save_env(t_infos *infos, char **env);

/*
** GESTION EXIT
*/
int		check_if_exit_or_continue(t_infos *infos);
int		clean_exit(t_infos *infos);

/*
** INTIALISATION MINISHELL
*/
int	init_minishell(t_infos *infos, char **env);

/*
** INTERPRETATION LIGNE COMMANDE
*/
t_builtin	check_builtin(char *first_elem_cmd_line);

/*
** TOKENIZER
*/
t_token		*tokenize_cmd(char *cmd, int *syntax_error, char **error_pos);
void		free_token_list_from_extremity(t_token *tokens, int end);
t_token		*init_new_token(t_token **tokens, char *cmd, int *syntax_error, char **error_pos);
int			browse_string(char *begin_token, char stop_char, char **error_pos);
int			browse_token(char *begin_token, char **error_pos);
t_tokentype	identify_token_type(char *token, int length);
int			check_operators_and_undefined_char(t_token *curr, t_token *prev, int *syntax_error, char **error_pos);
void		add_back_token(t_token **tokens, t_token *new);

/*
** PARSING
*/
int	parsing_error(int syntax_error, char *error_pos);
int parse_cmd(t_infos *infos);

#endif
