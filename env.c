/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:39:01 by anadege           #+#    #+#             */
/*   Updated: 2021/08/31 20:31:30 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fonction qui augmente la taille du tableau env pour y ajouter
** un nouvel element new_elem.
** Renvoie -1 en cas d'erreur, 0 sinon.
*/
int	add_not_existing_elem_to_env(char ***env, char *new_elem)
{
	char	**tmp_env;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
		i++;
	tmp_env = malloc(sizeof(*tmp_env) * (i + 2));
	if (!tmp_env)
		return (-1);
	j = 0;
	while (j < i + 2)
	{
		if (env[j])
			tmp_env[j] = ft_strdup(env[j]);
		else
			tmp_env[j] =  ft_strdup(new_elem);
		if (!tmp_env[j])
		{
			free_env(env, j);
			return (-1);
		}
		j++;
	}
	tmp_env[j] = NULL;
	free_env(env, 0);
	env = tmp_env;
	return (0);
}

/*
** Function qui modifie un element de env deja existant (de nom elem_name)
** et le remplace par new_elem.
** Retourne -1 en cas d'erreur, 0 sinon.
*/
int	add_existing_elem_to_env(char **env, char *new_elem, char *elem_name)
{
	int	i;
	int	elem_pos;

	i = 0;
	elem_pos = 0;
	while (env[i])
		i++;
	while (env[elem_pos])
	{
		if (ft_strncmp(env[elem_pos], elem_name, ft_strlen(elem_name)))
			break;
		elem_pos++;
	}
	if (elem_pos == i)
		return (-1);
	free(env[elem_pos]);
	env[elem_pos] = ft_strdup(new_elem);
	if (!env[elem_pos])
		return (-1);
	return (0);
}

/*
** Fonction a appeler lorsque le bultin export est en ligne de commande.
** Va ajouter la nouvelle variable new_elem (format "VAR=value") au tableau
** env.
** Renvoie -1 en cas d'erreur, 0 sinon.
** ATTENTION : Ne verifie pas la conformite de la string new_elem.
*/
int	add_elem_to_env(char **env, char *new_elem)
{
	char	*elem_name;
	int		i;
	int		res;

	i = 0;
	while (new_elem[i] != '=')
		i++;
	elem_name = malloc(sizeof(*elem_name) * (i + 1));
	if (!elem_name)
		return (-1);
	i = 0;
	while (new_elem[i] != '=')
	{
		elem_name[i] = new_elem[i];
		i++;
	}
	elem_name[i] = 0;
	if (!get_env_elem(env, elem_name))
		res = add_not_existing_elem_to_env(env, new_elem);
	else
		res = add_existing_elem_to_env(env, new_elem, elem_name);
	return (res);
}

/*
** Fonction retournant la valeur d'environnement correspondant a l'element donne
** (ex : Pour HOME, retourne "/home/user42").
** Fait le meme chose que la fonction getenv mais pour notre environnement ou des
** variables ont pu etre ajoutee. Il faut lui passer infos->env commme argument
** pour char **env.
** Retourne NULL si l'element n'est pas trouve.
*/
char	*get_env_elem(char **env, char *elem)
{
	int		i;
	char	*elem_value;
	int		elem_size;

	i = 0;
	elem_size = ft_strlen(elem);
	while (env[i])
	{
		if (!ft_strncmp(env[i], elem, elem_size))
		{
			elem_value = env[i];
			elem_value += elem_size + 1;
			return (elem_value);
		}
		i++;
	}
	return (NULL);
}

/*
** Fonction permettant de montrer les variables environnementales.
** A appeler lorsque le builtin "env" est entre en ligne de commande.
*/
void	show_env(t_infos *infos)
{
	int	i;

	i = 0;
	while (infos && infos->env && infos->env[i])
	{
		printf("%i %s\n", i, infos->env[i]);
		//write(1, infos->env[i], ft_strlen(infos->env[i]));
		//write (1, "\n", 1);
		i++;
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);

}

/*
** Fonction ayant pour visee de sauvegarder les variables d'environnement dans
** une struture contenant les informations pour le minishell.
** Autre option : Sauvegarder env dans une liste chainee contenant le nom de l'element
** (ex : PATH), le contenu correspondant et next vers le prochain element.
** Avantage : Plus propre et evite realloc pour ajouter/supprimer une variable. 
** Inconvenient : Plus complique a mettre en place et plus long/lent a explorer.
** Des allocations sont realisees pour pouvoir free sans soucis.
** Retourne -1 si erreur, 0 sinon.
*/
int	save_env(t_infos *infos, char **env)
{
	int		i;
	int		y;
	char	**tmp_env;

	i = 0;
	while (env[i])
		i++;
	tmp_env = malloc(sizeof(*tmp_env) * (i + 1));
	if (!tmp_env)
		return (-1);
	i = 0;
	while (env[i])
	{
		y = 0;
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
		{
			i -= 1;
			while (i >= 0)
				free(tmp_env[i--]);
			free(tmp_env);
			return (-1);
		}
		i++;
	}
	tmp_env[i] = NULL;
	infos->env = tmp_env;
	show_env(infos);
	add_elem_to_env(infos->env, "lol=12");
	show_env(infos);
	//add_elem_to_env(infos->env, "lol=1");
	//show_env(infos);
	free_env(infos->env);
	return (0);
}
