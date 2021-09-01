/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:55:23 by anadege           #+#    #+#             */
/*   Updated: 2021/09/01 22:21:12 by anadege          ###   ########.fr       */
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

#define	PROMPT_MSG "\033[1;38;5;51mPrompt > \033[0m"

/*
** MINISHELL INFORMATION STRUCTURE
** Pour le moment, ne stock que les variables environnementales dans 
** un tableau char **env (autre possibilité : stocker dans liste
** chaînée).
*/
typedef struct s_infos
{
	char	**env;
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
int		delet_elem_from_env(char ***env, char *elem);
int		add_not_existing_elem_to_env(char ***env, char *new_elem, int env_size);
int		modify_existing_elem_to_env(char **env, char *new_elem, char *elem_name);
int		add_elem_to_env(char ***env, char *new_elem);
char	*get_elem_name(char *elem);
char	*get_env_elem(char **env, char *elem);
int		seek_elem_pos(char **env, char *elem_name);
void	show_env(char **env);
void	free_env(char **env, int last);
int		save_env(t_infos *infos, char **env);



#endif
